#include <GL/glut.h>
#include <GL/glu.h>

// Definções da textura 
//--------------------------------------------------------------------------------------


#define	checkImageWidth 16
#define	checkImageHeight 16
static GLubyte checkImage[checkImageHeight][checkImageWidth][8];

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

void makeCheckImage( void ) {
  int i, j, c;

  for ( i = 0; i < checkImageHeight; i++ ) {
    for ( j = 0; j < checkImageWidth; j++ ) {
      c = ( ( ( ( i & 0x8 ) == 0 ) ^ ( ( ( j & 0x8 ) ) == 0 ) ) ) * 20;
      checkImage[i][j][0] = ( GLubyte )c;
      checkImage[i][j][1] = ( GLubyte )c;
      checkImage[i][j][2] = ( GLubyte )c;
      checkImage[i][j][3] = ( GLubyte )255;
    }
  }
}