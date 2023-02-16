#include <GL/glut.h>
#include <GL/glu.h>

#define NOTEBOOK_GRAY  0.2f, 0.2f, 0.2f 
#define NOTEBOOK_PINK 0.5f, 0.2f, 0.5f
#define ANIMATION_CUBE_COLOR 0.3f, 0.0f, 0.5f 


GLfloat cube_angle = 45;
bool is_on_display_animation = true;
bool is_on_notebook_rotation_animation = false;
bool to_close_notebook = true;
int notebook_rotation_delay = 100;
int cube_delay = 100; //milliseconds
int display_delay = 2000; //milliseconds
GLfloat R = 0.545f, G = 0.914f, B = 0.992f; // RGB para mudar cor do display
GLfloat notebook_rotation = 0;

const GLfloat notebook_width = 9;
const GLfloat notebook_height = 7.5;

class Notebook {
  public:
  Notebook( GLfloat texName, bool notebook_color ) {
    this->texName = texName;
    this->notebook_color = notebook_color;
  }

  void drawNotebook() {
    if ( notebook_color ) glColor3f( NOTEBOOK_GRAY ); // cinza 
    else glColor3f( NOTEBOOK_PINK ); // rosa
    glPushMatrix();
    drawKeyboard();
    glTranslatef( 0, 0, -notebook_height );
    glRotatef( notebook_rotation, 1, 0, 0 );
    drawCorpoNotebook();
    drawDisplayNotebook();
    drawCube();
    glPopMatrix();
  }

  private:
  GLfloat texName;
  bool notebook_color;
  GLfloat width, height;
  // { width, height, deep, translate_x, translate_y, translate_z }
  GLfloat keyboard[6] = { notebook_width, 0.5,notebook_height, 0, 0, 0 };
  GLfloat body[6] = { notebook_width, notebook_height, 1, 0,0,0 };
  GLfloat display[6] = { notebook_width - 0.2, notebook_height - 0.6, 0,  0,0,0 };
  GLfloat cube[6] = { 2.5,2.5,0,0,8,0.2 };

  void drawKeyboard() {
    GLfloat w = keyboard[0];
    GLfloat h = keyboard[1];
    GLfloat d = keyboard[2];
    GLfloat tx = keyboard[3];
    GLfloat ty = keyboard[4];
    GLfloat tz = keyboard[5];
    glTranslated( tx, ty, tz );
    glPushMatrix();
    glBegin( GL_QUADS );
    glNormal3f( 0.f, 0.f, -1.f );
    glVertex3f( w, h, -d );// frente
    glVertex3f( w, h, d );
    glVertex3f( w, -h, d );
    glVertex3f( w, -h, -d );

    glNormal3f( 0.f, 1.f, 0.f );
    glVertex3f( -w, -h, -d ); // lado esquerdo
    glVertex3f( w, -h, -d );
    glVertex3f( w, h, -d );
    glVertex3f( -w, h, -d );

    glNormal3f( 0.f, -1.f, 0.f );
    glVertex3f( -w, -h, d ); // lado direito
    glVertex3f( w, -h, d );
    glVertex3f( w, h, d );
    glVertex3f( -w, h, d );

    glNormal3f( -1.f, 0.f, 0.f );
    glVertex3f( -w, -h, -d ); // fundo
    glVertex3f( w, -h, -d );
    glVertex3f( w, -h, d );
    glVertex3f( -w, -h, d );

    glNormal3f( 0.f, 0.f, 1.f );
    glVertex3f( -w, h, -d ); // trazeira
    glVertex3f( -w, h, d );
    glVertex3f( -w, -h, d );
    glVertex3f( -w, -h, -d );
    glEnd();
    glPopMatrix();

    //Textura
    glEnable( GL_TEXTURE_2D );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );
#ifdef GL_VERSION_1_1
    glBindTexture( GL_TEXTURE_2D, texName );
#endif

    glBegin( GL_QUADS );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -w, h, d ); // topo
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -w, h, -d );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( w, h, -d );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( w, h, d );
    glEnd();

    glDisable( GL_TEXTURE_2D );
  }

  void drawCorpoNotebook() {
    GLfloat w = body[0];
    GLfloat h = 2 * body[1];
    GLfloat d = body[2];

    glPushMatrix();
    glBegin( GL_QUADS );
    glNormal3f( 0.f, 0.f, -1.f );
    glVertex3f( w, h, d );// frente
    glVertex3f( w, h, d );
    glVertex3f( w, 0, -d );
    glVertex3f( w, 0, d );

    glNormal3f( 0.f, 1.f, 0.f );
    glVertex3f( -w, 0, -d ); // lado esquerdo
    glVertex3f( -w, 0, d );
    glVertex3f( -w, h, d );
    glVertex3f( -w, h, -d );

    glNormal3f( 0.f, -1.f, 0.f );
    glVertex3f( w, 0, -d ); // lado direito
    glVertex3f( w, 0, d );
    glVertex3f( w, h, d );
    glVertex3f( w, h, -d );

    glNormal3f( -1.f, 0.f, 0.f );
    glVertex3f( -w, 0, -d ); // fundo
    glVertex3f( -w, 0, d );
    glVertex3f( w, 0, d );
    glVertex3f( w, 0, -d );

    glNormal3f( 0.f, 0.f, 1.f );
    glVertex3f( -w, h, -d ); // trazeira
    glVertex3f( w, h, -d );
    glVertex3f( w, 0, -d );
    glVertex3f( -w, 0, -d );

    glNormal3f( 0.f, 1.f, 0.f );
    glVertex3f( -w, h, -d ); // em cima
    glVertex3f( w, h, -d );
    glVertex3f( w, h, d );
    glVertex3f( -w, h, d );
    glEnd();
    glPopMatrix();
  }

  void drawDisplayNotebook() {
    GLfloat w = display[0];
    GLfloat h = 2 * display[1];
    GLfloat d = display[2];

    glBegin( GL_QUADS );
    glNormal3f( 0.f, 0.f, 1.f );
    glColor3f( R, G, B );
    glVertex3f( w, 0, d );
    glVertex3f( w, h, d );
    glVertex3f( -w, h, d );
    glVertex3f( -w, 0, d );
    glEnd();
  }

  void drawCube() {
    GLfloat w = cube[0];
    GLfloat h = cube[1];
    GLfloat d = cube[2];
    GLfloat tx = cube[3];
    GLfloat ty = cube[4];
    GLfloat tz = cube[5];
    glPushMatrix();
    glTranslatef( tx, ty, tz );
    glRotatef( cube_angle, 0, 0, 1 );
    glClearColor( 0.f, 0.f, 0.f, 0.f );
    glColor3f( ANIMATION_CUBE_COLOR );
    glNormal3f( 0.f, 0.f, 1.f );
    glBegin( GL_QUADS );
    glVertex3f( -w, h, d );
    glVertex3f( w, h, d );
    glVertex3f( w, -h, d );
    glVertex3f( -w, -h, d );
    glEnd();
    glPopMatrix();
  }
};

void drawNotebook( GLfloat x, GLfloat y, GLfloat z, GLuint texName, bool notebook_color ) {
  glPushMatrix();
  glTranslatef( x, y, z );
  Notebook notebook( texName, notebook_color );
  notebook.drawNotebook();
  glPopMatrix();
}


void cubeAnimation( int v ) {
  glutTimerFunc( cube_delay, cubeAnimation, 0 );
  if ( !is_on_display_animation ) return;

  cube_angle = cube_angle >= 360 ? 0 : cube_angle + 1;
  glutPostRedisplay();
}

void notebookRotationAnimation( int v ) {
  glutTimerFunc( notebook_rotation_delay, notebookRotationAnimation, 0 );

  if ( !is_on_notebook_rotation_animation ) return;

  if ( to_close_notebook ) {
    if ( notebook_rotation >= 90 ) {
      notebook_rotation = 90;
      is_on_notebook_rotation_animation = false;
      to_close_notebook = false;
      glutPostRedisplay();
      return;
    }

    notebook_rotation += 3;
    glutPostRedisplay();
    return;
  }


  if ( notebook_rotation <= 0 ) {
    notebook_rotation = 0;
    is_on_notebook_rotation_animation = false;
    to_close_notebook = true;
    glutPostRedisplay();
    return;
  }

  notebook_rotation -= 3;
  glutPostRedisplay();
}

void displayAnimation( int v ) {
  glutTimerFunc( display_delay, displayAnimation, 0 );
  if ( !is_on_display_animation ) return;

  t++;
  switch ( t ) {
    case 1:
      R = 1.000f;
      G = 0.722f;
      B = 0.424f;
      break;

    case 2:
      R = 1.000f;
      G = 0.475f;
      B = 0.776f;
      break;

    case 3:
      R = 0.314f;
      G = 0.980f;
      B = 0.482f;
      break;

    case 4:
      R = 0.545f;
      G = 0.914f;
      B = 0.992f;
      break;

    default:
      t = 0;
      break;
  }
  glutPostRedisplay();
}
