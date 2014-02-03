//#pragma once
//#include "Vector.h"
//#include "Animation.h"
//#include <vector>
//using namespace std;
//// ============================================
//// CMD2Model - MD2 model class object.
//// ============================================
//
//
//class MD2Model
//{
//public:
//
//    MD2Model( void );
//    ~MD2Model( void );
//
//    // functions
//    bool    LoadModel( const char *filename );
//    bool    LoadSkin( const char *filename );
//
//    void    DrawModel( float time );
//    void    DrawFrame( int frame );
//
//    void    SetAnim( int type );
//
//private:
//    void    Animate( float time );
//    void    ProcessLighting( void );
//    void    Interpolate( Vector3 *vertlist );
//    void    RenderFrame( void );
//
//
//public:
//    static Animation   animlist[21];       // animation list
//
//
//private:
//    int             num_frames;         // number of frames
//    int             num_xyz;            // number of vertices
//    int             num_glcmds;         // number of opengl commands
//
//	vector<Vector3>  m_vertices;        // vertex array
//    int             *m_glcmds;          // opengl command array
//};