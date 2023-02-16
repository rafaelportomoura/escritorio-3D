#include <GL/glut.h>
#include <GL/glu.h>

#define WALL_COLOR 0.3f, 0.0f, 0.5f 
#define FLOOR_COLOR 0.157f, 0.165f, 0.212f 

class Office {
  public:
  Office( GLfloat floor_tam, GLfloat size ) {
    this->size = size;
    this->floor_tam = floor_tam;
  };
  void draw() {
    this->wall();
    this->floor();
  }
  private:
  GLfloat size, floor_tam;

  void wall() {
    glPushMatrix();
    glColor3f( WALL_COLOR );
    glutSolidCube( size );
    glPopMatrix();
  }

  void floor() {
    GLfloat mid_size = size / 2;
    glBegin( GL_QUADS );
    glColor3f( FLOOR_COLOR );
    glNormal3f( 0.f, -1.f, 0.f );
    glVertex3f( -mid_size, floor_tam, -mid_size );
    glVertex3f( -mid_size, floor_tam, mid_size );
    glVertex3f( mid_size, floor_tam, mid_size );
    glVertex3f( mid_size, floor_tam, -mid_size );
    glEnd();
  }

};

void drawOffice( GLfloat floor, GLfloat size ) {
  glPushMatrix();
  Office office( floor, size );
  office.draw();
  glPopMatrix();
}