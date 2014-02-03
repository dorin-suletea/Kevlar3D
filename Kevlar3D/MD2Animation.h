#pragma once


#define MD2_MAGIC_NO	('I'+('D'<<8)+('P'<<16)+('2'<<24))
#define MAX_NO_SKIN		5
#define MAX_SKIN_NAME	64
#define FRAME_HEADER_SIZE	(sizeof(float)*6+16)


#include <stdio.h>
#include <string.h>
#include <vector>
#include "Vector.h"


typedef unsigned char	byte;
typedef short*	pshort;
typedef struct _md2Header
{
	int		magic;
	int		version;
	int		skinWidth;
	int		skinHeight;
	int		frameSize;

	int		numSkins;
	int		numVertices;
	int		numTexCoords;
	int		numTriangles;
	int		numGlCommands;
	int		numFrames;

	int		offsetSkins;
	int		offsetTexCoord;
	int		offsetTriangles;
	int		offsetFrames;
	int		offsetGlCommands;
	int		offsetEnd;
}md2Header,*pmd2Header;
typedef struct _md2TriangleVertex
{
	byte	vertex[3];
	byte	lightNormalIndex;
}md2TriangleVertex,*pmd2TriangleVertex;
typedef struct _md2Frame
{
	float				scale[3];
	float				translate[3];
	char				name[16];
	pmd2TriangleVertex	pvertices;
}md2Frame,*pmd2Frame;
typedef struct _md2Triangle
{
	short	vertexIndices[3];
	short	textureIndices[3];
}md2Triangle,*pmd2Triangle;
typedef struct _md2TextureCoord
{
	short	s,t;
}md2TextureCoord,*pmd2TextureCoord;
typedef struct _md2GLCommand
{
	float	s,t;
	int		vertexIndex;
}md2GLCommand,*pmd2GLCommand;
typedef struct _md2GLVertex
{
	float	x,y,z;
}md2GLVertex,*pmd2GLVertex;



class MD2Animation
{
	public:
		MD2Animation();
		MD2Animation(std::string vanimName);
		~MD2Animation();

		int						Load(const char* fileName);
		int						GetNumFrames();
		std::vector<Vector3>	GetVertices();
		void					SetFrame(int frame);
		void					NextFrame();
		string					GetAnimationName();

	private:

		void*					md2Malloc(size_t size);
		void					md2Free(void** p);
		int						md2ReadFile(const char* fileName);
		int						md2ReadHeader(byte *buffer,pmd2Header phead);
		long					md2FileSize(FILE *fp);
		void					md2DumpHeader(const pmd2Header phead);
		void					md2InitData();
		void					md2LoadData();
		void					md2LoadSkinNames();
		void					md2LoadTextureCoord();
		void					md2LoadFrames();
		void					md2LoadTriangles();
		void					md2LoadGLCommands();
		void					md2LoadTextures(const char* md2FileName);
		void					md2ProcessData();
		void					md2WriteLog(const char* fileName);

	private:
		byte*					m_buffer;
		md2Header				m_header;
		char					m_skinName[MAX_NO_SKIN][MAX_SKIN_NAME];
		pmd2TextureCoord		m_texData;
		pmd2Triangle			m_triData;
		pmd2TriangleVertex		m_vertData;
		pmd2Frame				m_frameData;

		pmd2GLVertex			m_glVertexData;
		pshort					m_glIndicesData;

		unsigned int			m_listID;
		float					framesPerSec;
		int						currentFrameIndex;  
		string					animationName;
};
