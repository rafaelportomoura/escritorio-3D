#include <GL/glut.h>
#include <GL/glu.h>

#define DESK_COLOR 0.741f, 0.576f, 0.976f
#define FOOT_OF_DESK_COLOR  0.5f, 0.2f, 0.0f

class Desk {
  public:
  Desk() {
    this->width = 50;
    this->height = 2;
    this->deep = 30;
    this->foot_height = 15;
  };
  void draw() {
    glPushMatrix();
    GLfloat foot_position = ( width + height ) / 4;
    deskFoot( 5 + foot_position, 0, -foot_position );
    deskFoot( -5 - foot_position, 0, -foot_position );
    deskFoot( 5 + foot_position, 0, foot_position );
    deskFoot( -5 - foot_position, 0, foot_position );
    table();
    glPopMatrix();
  }
  private:
  GLfloat width, height, foot_height, deep;

  void deskFoot( GLfloat x, GLfloat y, GLfloat z ) {
    glPushMatrix();
    glColor3f( FOOT_OF_DESK_COLOR );
    glTranslatef( x, y, z );
    glRotatef( 15, 0, 1, 0 );
    glScalef( 1.0, foot_height, 1.0 );
    glutSolidCube( 1.0 );
    glPopMatrix();
  }

  void table() {
    glPushMatrix();
    glColor3f( DESK_COLOR );
    glTranslatef( 0, foot_height / 2 + height / 2, 0 );
    glScalef( width, height, deep );
    glutSolidCube( 1.0 );
    glPopMatrix();
  }

};

void drawDesk( GLfloat x, GLfloat y, GLfloat z ) {
  glPushMatrix();
  glTranslatef( x, y, z );
  Desk desk;
  desk.draw();
  glPopMatrix();
}