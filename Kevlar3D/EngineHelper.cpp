#include "EngineHelper.h"


EngineHelper::EngineHelper(void)
{
}


EngineHelper::~EngineHelper(void)
{
}

/*static*/
Material* 
EngineHelper::MakeDefaultMaterial(){
	Material *defaultMaterial = new Material("Default material");
	Shader vertShader =   Shader("vertex_position_shader.txt",ShaderTypes::VERTEX_SHADER);
	Shader fragShader =   Shader("fragment_shader.txt",ShaderTypes::FRAGMENT_SHADER);
	
	defaultMaterial->AddShader(vertShader);
	defaultMaterial->AddShader(fragShader);
	defaultMaterial->Compile();
	return defaultMaterial;
}

/*static*/
Material* 
EngineHelper::MakeDebugMaterial(){
	Material *debug = new Material("Default material");
	Shader debugVertShader =   Shader("vertex_shader.txt",ShaderTypes::VERTEX_SHADER);
	Shader debugFragShader =   Shader("fragment_shader.txt",ShaderTypes::FRAGMENT_SHADER);
	
	debug->AddShader(debugVertShader);
	debug->AddShader(debugFragShader);
	debug->Compile();
	return debug;
}

/*static*/
std::vector<Vector3>
EngineHelper::LoadDravenVerts(){
	vector<glm::vec3> out_vertices = vector<glm::vec3>(); 
	vector<glm::vec2> out_uvs = vector<glm::vec2>(); 
	vector<glm::vec3> out_normals = vector<glm::vec3>(); 

	vector<Vector3> ret = vector<Vector3>(); 

	ResourceLoader loader =  ResourceLoader();
	vector<Vector3> manequinVerts = vector<Vector3>(); 
	loader.LoadMeshOBJ("D:/Tools/Development/Dropbox/Workspaces/WorkspaceCpp/Kevlar3D/K3Res/cube.obj",out_vertices,out_uvs,out_normals);

	int meshSize = out_vertices.size();
	for (int i=0;i<meshSize;i++){
		ret.push_back(Vector3(out_vertices.at(i)));
	}
		
	return ret;
}

/*static*/
std::vector<Vector3> LoadCubeVerts(){
	vector<Vector3> cube1Points = vector<Vector3>();
	cube1Points.push_back(Vector3(-0.5f  , 0.5f , 0.5f));
	cube1Points.push_back(Vector3(0.5f  , -0.5f  , 0.5f));
	cube1Points.push_back(Vector3( -0.5f  , -0.5f  , 0.5f));

	cube1Points.push_back(Vector3(0.5f  , 0.5f , 0.5f));
	cube1Points.push_back(Vector3( -0.5f  , +0.5f  , 0.5f));
	cube1Points.push_back(Vector3(0.5f   , -0.5f , -0.5f));


	cube1Points.push_back(Vector3(-0.5f  , 0.5f  , 0.5f));
	cube1Points.push_back(Vector3(-0.5f  , 0.5f  , -0.5f));
	cube1Points.push_back(Vector3( 0.5f  , 0.5f  , 0.5f));

	cube1Points.push_back(Vector3(-0.5f  , 0.5f , 0.5f));
	cube1Points.push_back(Vector3(0.5f  , 0.5f , 0.5f));
	cube1Points.push_back(Vector3(0.5f   , -0.5f , +0.5f));
	return cube1Points;
}
