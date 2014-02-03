//#include "MD2Model.h"
//
//
//// ----------------------------------------------
//// LoadModel() - load model from file.
//// ----------------------------------------------
//
//bool MD2Model::LoadModel( const char *filename )
//{
//    std::ifstream   file;           // file stream
//    md2_t           header;         // md2 header
//    char            *buffer;        // buffer storing frame data
//    frame_t         *frame;         // temporary variable
//    vec3_t          *ptrverts;      // pointer on m_vertices
//    int             *ptrnormals;    // pointer on m_lightnormals
//
//
//    // try to open filename
//    file.open( filename, std::ios::in | std::ios::binary );
//
//    if( file.fail() )
//        return false;
//
//    // read header file
//    file.read( (char *)&header, sizeof( md2_t ) );
//
//
//    /////////////////////////////////////////////
//    //      verify that this is a MD2 file
//
//    // check for the ident and the version number
//
//    if( (header.ident != MD2_IDENT) && (header.version != MD2_VERSION) )
//    {
//        // this is not a MD2 model
//        file.close();
//        return false;
//    }
//
//    /////////////////////////////////////////////