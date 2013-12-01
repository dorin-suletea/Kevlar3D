#pragma once


/*If MAC_OS include mac headers, else windows&linux headers*/
#ifdef __APPLE__  
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else 
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif


