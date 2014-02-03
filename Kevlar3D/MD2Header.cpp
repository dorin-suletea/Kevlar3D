
// magic number "IDP2" or 844121161
#define MD2_IDENT                (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define MD2_VERSION 

struct Md2Header
{
  int ident;          // Magic number, "IDP2"
  int version;        // Md2 format version, should be 8

  int skinwidth;      // Texture width
  int skinheight;     // Texture height

  int framesize;      // Size of a frame, in bytes

  int num_skins;      // Number of skins
  int num_vertices;   // Number of vertices per frame
  int num_st;         // Number of texture coords
  int num_tris;       // Number of triangles
  int num_glcmds;     // Number of OpenGL commands
  int num_frames;     // Number of frames

  int offset_skins;   // offset to skin data
  int offset_st;      // offset to texture coords
  int offset_tris;    // offset to triangle data
  int offset_frames;  // offset to frame data
  int offset_glcmds;  // offset to OpenGL commands
  int offset_end;     // offset to the end of the file
};
