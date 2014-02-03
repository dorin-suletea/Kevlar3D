#include "MD2Animation.h"
#include <memory>
#include "GLIncludes.h"
#include "Log.h"


MD2Animation::MD2Animation()
{
	m_buffer	=NULL;
	m_texData	=NULL;
	m_triData	=NULL;
	m_vertData	=NULL;
	m_frameData	=NULL;
	m_glVertexData=NULL;
	m_glIndicesData=NULL;
	currentFrameIndex=0;
	animationName="Default Animation Name";
}

MD2Animation::MD2Animation(std::string vanimName) {
	m_buffer	=NULL;
	m_texData	=NULL;
	m_triData	=NULL;
	m_vertData	=NULL;
	m_frameData	=NULL;
	m_glVertexData=NULL;
	m_glIndicesData=NULL;
	currentFrameIndex=0;
	animationName = vanimName;
}

MD2Animation::~MD2Animation()
{
	md2Free((void**)&m_buffer);
	md2Free((void**)&m_texData);
	md2Free((void**)&m_triData);
	md2Free((void**)&m_vertData);
	md2Free((void**)&m_glVertexData);
	md2Free((void**)&m_glIndicesData);
	for (int index=0;index<m_header.numFrames;index++)
		md2Free((void**)&m_frameData[index].pvertices);
	md2Free((void**)&m_frameData);
}

/*
	Name : Load
*/
int MD2Animation::Load(const char* fileName)
{
	int result=0;

	result=md2ReadFile(fileName);
	if (result!=0)
		return result;
						
	result=md2ReadHeader(m_buffer,&m_header);
	if (result!=0)
		return result;


	md2InitData();
	md2LoadData();
	md2ProcessData();
	md2WriteLog(fileName);
	SetFrame(0); // Initially set it to Point to First Frame
	if ("Default Animation Name"== animationName){
		animationName = fileName;
	}
	return 0;
}

/*
	Name : md2Malloc
*/
void* MD2Animation::md2Malloc(size_t size)
{
	void* p=malloc(size);
	if (p==NULL)
		return p;
	memset(p,0,size);

	return p;
}

/*
	Name : md2Free
*/
void MD2Animation::md2Free(void** p)
{
	if (*p!=NULL)
	{
		free(*p);
		*p=NULL;
	}
}

/*
	Name : md2ReadFile
*/
int MD2Animation::md2ReadFile(const char* fileName)
{
	FILE	*fp;


	fp=fopen(fileName,"rb");
	if (!fp){
		return 1;
	}

	md2Free((void**)&m_buffer);

	long fileSize= md2FileSize(fp);
	if (fileSize<=0)
		return 1;


	m_buffer=(byte*)md2Malloc(fileSize);
	if (!m_buffer)
		return 1;

	if (fread(m_buffer,1,fileSize,fp)!=(size_t)fileSize)
		return 1;

	fclose(fp);
	return 0;
}

/*
	Name : md2FileSize
*/
long MD2Animation::md2FileSize(FILE *fp)
{
	long oldpos=ftell(fp);
	fseek(fp,0,SEEK_END);
	long curpos=ftell(fp);
	fseek(fp,oldpos,SEEK_SET);
	return curpos;
}




/*
	Name : md2ReadHeader
*/
int MD2Animation::md2ReadHeader(byte *buffer,pmd2Header phead)
{
	memcpy(phead,buffer,sizeof(*phead));

	if (phead->magic != MD2_MAGIC_NO)
		return 1;

	return 0;
}

/*
	Name : md2InitData
*/
void MD2Animation::md2InitData()
{
	int index=0;

	for (index=0;index<MAX_NO_SKIN;index++)
		memset(this->m_skinName[index],0,MAX_SKIN_NAME);

	md2Free((void**)&m_texData);
	md2Free((void**)&m_triData);
	md2Free((void**)&m_vertData);
	md2Free((void**)&m_frameData);
	if (m_frameData!=NULL)
	{
		for (int index=0;index<m_header.numFrames;index++)
			md2Free((void**)&m_frameData[index].pvertices);
		md2Free((void**)&m_frameData);
	}
}

/*
	Name : md2LoadData
*/
void MD2Animation::md2LoadData()
{

	md2LoadSkinNames();
	md2LoadTextureCoord();

	md2LoadTriangles();

	md2LoadFrames();
	md2LoadGLCommands();
}

/*
	Name : md2LoadFrames
*/
void MD2Animation::md2LoadFrames()
{
	int index=0;
	byte	*buf_t		= m_buffer+ m_header.offsetFrames;
	long	frameHeaderSize	= m_header.numFrames * sizeof(md2Frame);
	long	frameVertSize	= m_header.numVertices * sizeof(md2TriangleVertex); 

	m_frameData =(pmd2Frame)md2Malloc(frameHeaderSize);
	if (!m_frameData)
		return;

	for (index=0;index< m_header.numFrames;index++)
	{
		m_frameData[index].pvertices = (pmd2TriangleVertex)md2Malloc(frameVertSize);
		if (!m_frameData[index].pvertices)
			return;
	}

	for (index=0;index< m_header.numFrames;index++)
	{
		memcpy(&m_frameData[index],buf_t, FRAME_HEADER_SIZE);
		buf_t+= FRAME_HEADER_SIZE;
		memcpy(m_frameData[index].pvertices, buf_t, frameVertSize);
		buf_t+=frameVertSize;
	}
	Log::GetInstance()->LogInfo("MD2 Frames loaded"+to_string(m_header.numFrames));
}

/*
	Name : md2LoadTriangles
*/
void MD2Animation::md2LoadTriangles()
{

	byte	*buf_t		= m_buffer+ m_header.offsetTriangles;
	long	totalsize	= m_header.numTriangles * sizeof(md2Triangle);
					Log::GetInstance()->LogErr("-------------------loading data"+to_string(m_header.numTriangles));
	m_triData = (pmd2Triangle)md2Malloc(totalsize);
	if (!m_triData)
		return;

	memcpy(m_triData, buf_t, totalsize);
}

/*
	Name : md2LoadTextureCoord
*/
void MD2Animation::md2LoadTextureCoord()
{
	int		index=0;
	byte	*buf_t=m_buffer+m_header.offsetTexCoord;
	long	totalsize = m_header.numTexCoords*sizeof(md2TextureCoord);

	m_texData=(pmd2TextureCoord)md2Malloc(totalsize);
	if (!m_texData)
		return;

	memcpy(m_texData,buf_t,totalsize);
}

/*
	Name : md2LoadSkinNames
*/
void MD2Animation::md2LoadSkinNames()
{
	int		index=0;
	byte*	buf_t=m_buffer+m_header.offsetSkins;

	for (index=0;index<m_header.numSkins;index++,buf_t+=MAX_SKIN_NAME)
		strcpy(m_skinName[index],(const char*)buf_t);
}

/*
	Name : md2LoadGLCommands
*/
void MD2Animation::md2LoadGLCommands()
{
	return;
}

/*
	Name : md2ProcessData
*/
void MD2Animation::md2ProcessData()
{
	md2Free((void**)&m_glVertexData);
	m_glVertexData = (pmd2GLVertex) md2Malloc(m_header.numVertices*sizeof(md2GLVertex));
	if (!m_glVertexData)
	{
		printf("Error at md2ProcessData\n");
		return;
	}
}



/*
	Name : md2WriteLog
*/
void MD2Animation::md2WriteLog(const char* fileName)
{
	char	data[512]={0};
	char	logfname[255]={0};
	FILE	*fp;
	int		index=0;
	pmd2Header	phead= &m_header;

	strcpy(logfname,fileName);
	strcpy(logfname+strlen(fileName)-3,"log");

	fp=fopen(logfname,"w");
	if (!fp)
		return;

	sprintf(data,"File Name       : %s\n", fileName);fwrite(data,strlen(data),1,fp);
	sprintf(data,"magic           : %c%c%c%c\n", (phead->magic&0xFF),((phead->magic>>8)&0xFF),((phead->magic>>16)&0xFF),((phead->magic>>24)&0xFF));fwrite(data,strlen(data),1,fp);
	sprintf(data,"version         : %d\n", phead->version);fwrite(data,strlen(data),1,fp);
	sprintf(data,"skinWidth       : %d\n", phead->skinWidth);fwrite(data,strlen(data),1,fp);
	sprintf(data,"skinHeight      : %d\n", phead->skinHeight);fwrite(data,strlen(data),1,fp);
	sprintf(data,"frameSize       : %d\n", phead->frameSize);fwrite(data,strlen(data),1,fp);
	sprintf(data,"numSkins        : %d\n", phead->numSkins);fwrite(data,strlen(data),1,fp);
	sprintf(data,"numVertices     : %d\n", phead->numVertices);fwrite(data,strlen(data),1,fp);
	sprintf(data,"numTexCoords    : %d\n", phead->numTexCoords);fwrite(data,strlen(data),1,fp);
	sprintf(data,"numTriangles    : %d\n", phead->numTriangles);fwrite(data,strlen(data),1,fp);
	sprintf(data,"numGlCommands   : %d\n", phead->numGlCommands);fwrite(data,strlen(data),1,fp);
	sprintf(data,"numFrames       : %d\n", phead->numFrames);fwrite(data,strlen(data),1,fp);
	sprintf(data,"---------------------\n");fwrite(data,strlen(data),1,fp);
	sprintf(data,"offsetSkins     : %d\n", phead->offsetSkins);fwrite(data,strlen(data),1,fp);
	sprintf(data,"offsetTexCoord  : %d\n", phead->offsetTexCoord);fwrite(data,strlen(data),1,fp);
	sprintf(data,"offsetTriangles : %d\n", phead->offsetTriangles);fwrite(data,strlen(data),1,fp);
	sprintf(data,"offsetFrames    : %d\n", phead->offsetFrames);fwrite(data,strlen(data),1,fp);
	sprintf(data,"offsetGlCommands: %d\n", phead->offsetGlCommands);fwrite(data,strlen(data),1,fp);
	sprintf(data,"offsetEnd       : %d\n", phead->offsetEnd);fwrite(data,strlen(data),1,fp);

	sprintf(data,"Total Frames  : %.3d\n----------------------\n", m_header.numFrames);fwrite(data,strlen(data),1,fp);
	for (index=0;index< m_header.numFrames;index++)
	{
		sprintf(data, "[%3d] %s\n", (index+1), m_frameData[index].name);
		fwrite(data,strlen(data),1,fp);
	}

	fclose(fp);
}

/*
	Name : GetNumFrames
*/
int	MD2Animation::GetNumFrames() 
{ 
	return this->m_header.numFrames; 
}

void MD2Animation::SetFrame(int frame)
{
	if (frame<0 || frame>= m_header.numFrames)
		return;

	int index=0;
	if (m_glVertexData!=NULL)
	{
		memset(m_glVertexData,0,sizeof(md2GLVertex)*m_header.numVertices);

		for (index=0;index<m_header.numVertices;index++)
		{
			// Every vertex of frame is multiplied by it's respective scale and then the translation is added.
			m_glVertexData[index].x = (m_frameData[frame].pvertices[index].vertex[0] * m_frameData[frame].scale[0])+m_frameData[frame].translate[0];
			m_glVertexData[index].y = (m_frameData[frame].pvertices[index].vertex[1] * m_frameData[frame].scale[1])+m_frameData[frame].translate[1];
			m_glVertexData[index].z = (m_frameData[frame].pvertices[index].vertex[2] * m_frameData[frame].scale[2])+m_frameData[frame].translate[2];
		}
	}
}


void MD2Animation::NextFrame(){
	currentFrameIndex++;
	if (currentFrameIndex >= m_header.numFrames){
		currentFrameIndex=0;
	}
	SetFrame(currentFrameIndex);
}

string	MD2Animation::GetAnimationName(){
	return animationName;
}
vector<Vector3> MD2Animation::GetVertices()
{
	GLfloat	v1[3],v2[3],v3[3];

	int index=0;
	std::vector<Vector3> ret = vector<Vector3>();
		for (index=0;index< m_header.numTriangles;index++)
		{
			// Calculate the two vertex out of 3 by [v1 - v2] & [v2 - v3] (Read Bernard Koleman Elementary Linear Algebra P-193)
			v1[0] = m_glVertexData[m_triData[index].vertexIndices[2]].x - m_glVertexData[m_triData[index].vertexIndices[1]].x;
			v1[1] = m_glVertexData[m_triData[index].vertexIndices[2]].y - m_glVertexData[m_triData[index].vertexIndices[1]].y;
			v1[2] = m_glVertexData[m_triData[index].vertexIndices[2]].z - m_glVertexData[m_triData[index].vertexIndices[1]].z;

			v2[0] = m_glVertexData[m_triData[index].vertexIndices[1]].x - m_glVertexData[m_triData[index].vertexIndices[0]].x;
			v2[1] = m_glVertexData[m_triData[index].vertexIndices[1]].y - m_glVertexData[m_triData[index].vertexIndices[0]].y;
			v2[2] = m_glVertexData[m_triData[index].vertexIndices[1]].z - m_glVertexData[m_triData[index].vertexIndices[0]].z;

			// Take the Cross Product of v1 x v2
			v3[0] = v1[1]*v2[2] - v1[2]*v2[1];
			v3[1] = v1[2]*v2[0] - v1[0]*v2[2];
			v3[2] = v1[0]*v2[1] - v1[1]*v2[0];
		
			ret.push_back(Vector3(
									 m_glVertexData[m_triData[index].vertexIndices[2]].x,
									 m_glVertexData[m_triData[index].vertexIndices[2]].z,
									 m_glVertexData[m_triData[index].vertexIndices[2]].y
								)
						 );
			
			ret.push_back(Vector3(
									 m_glVertexData[m_triData[index].vertexIndices[1]].x,
									 m_glVertexData[m_triData[index].vertexIndices[1]].z,
									 m_glVertexData[m_triData[index].vertexIndices[1]].y
								)
						 );
			
			ret.push_back(Vector3(
									 m_glVertexData[m_triData[index].vertexIndices[0]].x,
									 m_glVertexData[m_triData[index].vertexIndices[0]].z,
									 m_glVertexData[m_triData[index].vertexIndices[0]].y
								)
						 );
		}

	return ret;
}