#include <GL/glut.h>
#include <GL/glu.h>

#define LAMPSHADE_TRUNK_COLOR 0.9, 0.9, 0.9
#define LAMPSHADE_LIGHT_COLOR  0.0, 1.0, 0.9
#define LAMPSHADE_FOOT_COLOR 1.0, 1.0, 1.0

#define SECUNDARY_LAMPSHADE_LIGHT_COLOR  0.314f, 0.980f, 0.482f
class Lampshade {
  public:
  Lampshade( bool lampshade_color ) {
    this->trunk_height = 8.0f;
    this->light_height = 3.0f;
    this->light_width = 6.0f;
    this->foot_width = 6.0f;
    this->foot_height = 1.0f;
    this->lampshade_color = lampshade_color;
  }

  void draw() {
    // Desenha o abajur
    glPushMatrix();
    foot();
    trunk();
    light();
    glPopMatrix();
  }

  private:
  GLfloat trunk_height;
  GLfloat light_width, light_height;
  GLfloat foot_width, foot_height;
  bool lampshade_color;

  void trunk() {
    // Desenha a perna abajur
    glPushMatrix();

    glColor3f( LAMPSHADE_TRUNK_COLOR );
    glTranslatef( 0, 0, 0 );
    glScalef( 1.0, trunk_height, 1.0 );
    glutSolidCube( 1.0 );
    glPopMatrix();
  }

  void light() {
    // Desenha a luz do abajur
    glPushMatrix();
    if ( lampshade_color ) glColor3f( LAMPSHADE_LIGHT_COLOR ); // cinza 
    else glColor3f( SECUNDARY_LAMPSHADE_LIGHT_COLOR ); // rosa
    glTranslatef( 0, trunk_height / 2 + light_height / 2, 0 );
    glScalef( light_width, light_height, light_width );
    glutSolidCube( 1.0 );
    glPopMatrix();
  }

  void foot() {
    // Desenha o pe do abajur
    glPushMatrix();
    glColor3f( LAMPSHADE_FOOT_COLOR );
    glTranslatef( 0, -trunk_height / 2 + -foot_height / 2, 0 );
    glScalef( foot_width, foot_height, foot_width );
    glutSolidCube( 1.0 );
    glPopMatrix();
  }
};

void drawLampshade( GLfloat x, GLfloat y, GLfloat z, bool lampshade_color ) {
  glPushMatrix();
  glTranslatef( x, y, z );
  Lampshade lampshade( lampshade_color );
  lampshade.draw();
  glPopMatrix();
}