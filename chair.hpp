#include <GL/glut.h>
#include <GL/glu.h>

#define CHAIR_COLOR 0.384f, 0.447f, 0.643f
#define FOOT_OF_CHAIR_COLOR 0.5f, 0.2f, 0.0f

const GLfloat CHAIR_WIDTH_CONSTANT = 3.0;

class Chair {
  public:
  Chair() {
    this->width = 6;
    this->height = 17;
    this->foot_height = 14;
  }

  void draw() {
    glPushMatrix();
    foot( width, 0, width );
    foot( width, 0, -width );
    foot( -width, 0, -width );
    foot( -width, 0, width );
    chair();
    back();
    glPopMatrix();
  }

  private:
  GLfloat width, height, foot_height;

  void chair() {
    glPushMatrix();
    glColor3f( CHAIR_COLOR );
    glTranslatef( 0, foot_height / 2, 0 );
    glScalef( CHAIR_WIDTH_CONSTANT, 0.5, CHAIR_WIDTH_CONSTANT );
    glutSolidCube( width );
    glPopMatrix();
  }

  void back() {
    glPushMatrix();
    glColor3f( CHAIR_COLOR );
    glTranslatef( 0, foot_height / 2 + height / 2, +width * CHAIR_WIDTH_CONSTANT / 2 );
    glScalef( CHAIR_WIDTH_CONSTANT, height / width, 0.3 );
    glutSolidCube( width );
    glPopMatrix();
  }

  void foot( GLfloat x, GLfloat y, GLfloat z ) {
    glPushMatrix();
    glColor3f( FOOT_OF_CHAIR_COLOR );
    glTranslatef( x, y, z );
    glRotatef( 30, 0, 1, 0 );
    glScalef( 1.0, foot_height, 1.0 );
    glutSolidCube( 1.0 );
    glPopMatrix();
  }
};

void drawChair( GLfloat x, GLfloat y, GLfloat z ) {
  glPushMatrix();
  glTranslatef( x, y, z );
  Chair chair;
  chair.draw();
  glPopMatrix();
}