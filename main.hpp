#include <GL/glut.h>
#include <GL/glu.h>
#include <iostream>
#include "check_image.hpp"

using namespace std;

int obs_index = 0; // index do observador
const int qty_obs = 8; // qtd de observadores
int observer_vertical_change = 0;
const int max_width = 110;

const float MAX = ( float )max_width / ( float )2;
const float _ = 0.70 * MAX;

GLdouble obs[qty_obs][3] = {
  {MAX, MAX, 0.f },
  {_, MAX, _ },
  {0.f, MAX, MAX },
  {-_, MAX, _ },
  {-MAX, MAX, 0.f },
  {-_, MAX, -_ },
  {0.f, MAX, -MAX },
  {_, MAX, -_ }
};


int screenWidth = 1920, screenHeight = 1080; // largura e altura da janela
GLfloat floor_height = 0.0f; // altura inicial da animação 
bool notebook_color = 1; //cor do notebook
bool lampshade_color = 1; // cor da lampada
bool light_state = 1;
int t = 0; // incrementa para mudar cor da tela
bool fullscreen = true;
GLfloat NOTEBOOK[3] = { 0,17.5,-40 };
GLfloat CHAIR[3] = { 0,7,-10 };
GLfloat DESK[3] = { 0,7.5,-40 };
GLfloat LAMPSHADE[3] = { 20,22,-40 };
bool is_init = true;
void screenSize() {
  if ( fullscreen ) {
    glutFullScreen();
  }
  else {
    glutReshapeWindow( 1920, 1080 );
  }
  if ( is_init ) {
    is_init = false;
    return;
  }
  glutPostRedisplay();
}

void init() {
  glClearColor( 1.0, 1.0, 1.0, 1.0 );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  float globalAmb[ ] = { 0.4f, 0.4f, 0.4f, 1.0f };
  glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmb );

  float light0[4][4] = {
    { 0.3f, 0.3f, 0.3f, 1.0f }, // Ambiente
    { 0.3f, 0.3f, 0.3f, 1.0f }, // Difusa
    { 0.1f, 0.1f, 0.1f, 0.0f }, // Especular 
    { 0.0, 200.0f, 0.0, 0.0f } };// Posição

  glLightfv( GL_LIGHT0, GL_AMBIENT, &light0[0][0] );
  glLightfv( GL_LIGHT0, GL_DIFFUSE, &light0[1][0] );
  glLightfv( GL_LIGHT0, GL_SPECULAR, &light0[2][0] );
  glLightfv( GL_LIGHT0, GL_POSITION, &light0[3][0] );

  glEnable( GL_COLOR_MATERIAL );
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );

  glEnable( GL_DEPTH_TEST );
  glEnable( GL_DEPTH );
  glShadeModel( GL_FLAT );
  glEnable( GL_BLEND );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

  makeCheckImage();
  glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

#ifdef GL_VERSION_1_1
  glGenTextures( 1, &texName );
  glBindTexture( GL_TEXTURE_2D, texName );
#endif

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
#ifdef GL_VERSION_1_1
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight,
    0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage );
#else
  glTexImage2D( GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight,
    0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage );
#endif

  screenSize();
}

void reshape( int w, int h ) {
  if ( h == 0 ) // evita divisão por 0
    h = 1;

  float aspect = ( float )w / ( float )h;
  screenWidth = w;
  screenHeight = h;

  glViewport( 0, 0, w, h );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 90, aspect, 0.1, 200 );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();


  GLdouble x = obs[obs_index][0];
  GLdouble y = obs[obs_index][1] - observer_vertical_change;
  GLdouble z = obs[obs_index][2];
  // cout << obs_index << " " << x << " " << y << " " << z << endl;
  gluLookAt( x, y, z, 0, 0, 0, 0, 1, 0 );
}

void lightSwitch( bool ligth ) {
  light_state = ligth;
  if ( light_state ) {
    glEnable( GL_LIGHT0 );
    glutPostRedisplay();
  }
  else {
    glDisable( GL_LIGHT0 );
    glutPostRedisplay();
  }
}


bool checkIfObjectIsSelected( GLfloat mouseX, GLfloat posX, GLfloat mouseY, GLfloat posY, GLfloat winZ ) {
  GLfloat distance = winZ * 100;
  // cout << "mouseX: " << posX - distance << " <= " << mouseX << " <= " << posX + distance << " = " << ( posX - distance <= mouseX && mouseX <= posY + distance ) << endl;
  // cout << "mouseY: " << posY - distance << " <= " << mouseY << " <= " << posY + distance << " = " << ( posY - distance <= mouseY && mouseY <= posY + distance ) << endl;
  // cout << "screenWidth: " << screenWidth << "\t" << "screenHeight: " << screenHeight << endl;

  if ( not( posX - distance <= mouseX && mouseX <= posX + distance ) ) {
    return false;
  }

  if ( not( posY - distance <= mouseY && mouseY <= posY + distance ) ) {
    return false;
  }

  return true;
}

bool selectObject( float mouseX, float mouseY, float points[ ] ) {
  float objX = points[0];
  float objY = points[1];
  float objZ = points[2];
        // Obtem a posicao do objeto na viewport
  GLdouble modelview[16];
  GLdouble projection[16];
  GLint viewport[4];
  glGetDoublev( GL_PROJECTION_MATRIX, projection );
  glGetIntegerv( GL_VIEWPORT, viewport );
  glGetDoublev( GL_MODELVIEW_MATRIX, modelview );

  GLdouble winX, winY, winZ;
  gluProject( objX, objY, objZ, modelview, projection, viewport, &winX, &winY, &winZ );

  GLdouble posX = ( ( winX - viewport[0] ) / viewport[2] ) * screenWidth;
  GLdouble posY = ( ( viewport[3] - winY - 1 ) / viewport[3] ) * screenHeight;

  if ( checkIfObjectIsSelected( mouseX, posX, mouseY, posY, winZ ) ) {
    return true;
  }

  return false;
}

void clickWithLeftAction( float x, float y ) {
  if ( selectObject( x, y, NOTEBOOK ) ) {
    notebook_color = !notebook_color;
  }
  else if ( selectObject( x, y, LAMPSHADE ) ) {
    lightSwitch( !light_state );
  }
}


void clickWitRightAction( float x, float y, bool* is_on_notebook_rotation_animation ) {
  if ( selectObject( x, y, NOTEBOOK ) ) {
    *is_on_notebook_rotation_animation = !*is_on_notebook_rotation_animation;
  }
  else if ( selectObject( x, y, LAMPSHADE ) ) {
    lampshade_color = !lampshade_color;
  }
}