#include "main.hpp"
#include "escritorio.hpp"
#include "notebook.hpp"
#include "desk.hpp"
#include "lampshade.hpp"
#include "chair.hpp"

// Objetos
//--------------------------------------------------------------------------------------

void display() {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f( 0.0f, 0.0f, 0.0f );


  glPushMatrix();
  drawOffice( floor_height, max_width );
  drawChair( CHAIR[0], CHAIR[1], CHAIR[2] );
  drawDesk( DESK[0], DESK[1], DESK[2] );
  drawNotebook( NOTEBOOK[0], NOTEBOOK[1], NOTEBOOK[2], texName, notebook_color );
  drawLampshade( LAMPSHADE[0], LAMPSHADE[1], LAMPSHADE[2], lampshade_color );
  glPopMatrix();

  glFlush();
  glutSwapBuffers();
}


// Teclado e Mouse
//-------------------------------------------------------------------------------------

void keyboard( unsigned char key, int x, int y ) {
  if ( key == 27 ) { // encerra o programa
    exit( 0 );
  }

  switch ( key ) {
    case 'c':
    case 'C':
      notebook_color = !notebook_color;
      break;
    case 'l':
    case 'L':
      lightSwitch( !light_state );
      break;
    case ' ':
      is_on_display_animation = !is_on_display_animation;
      break;
    case 'r':
    case 'R':
      fullscreen = !fullscreen;
      screenSize();
    default:
      break;
  }
  glutPostRedisplay();
}

void specialKeys( int key, int x, int y ) {
  switch ( key ) {
    case GLUT_KEY_LEFT: // rotaciona para esquerda
      obs_index++;
      if ( obs_index > qty_obs - 1 ) obs_index = 0;
      reshape( screenWidth, screenHeight );
      break;
    case GLUT_KEY_RIGHT: // rotaciona para direita
      obs_index--;
      if ( obs_index < 0 ) obs_index = qty_obs - 1;
      reshape( screenWidth, screenHeight );
      break;
    case GLUT_KEY_UP:
      observer_vertical_change -= 2;
      if ( observer_vertical_change < 1 ) observer_vertical_change = 1;
      reshape( screenWidth, screenHeight );
      break;
    case GLUT_KEY_DOWN:
      observer_vertical_change += 2;
      if ( observer_vertical_change > 39 ) observer_vertical_change = 39;
      reshape( screenWidth, screenHeight );
      break;
  }
  glutPostRedisplay();
}


void mouse( int button, int state, int x, int y ) {
  // muda cor da tela
  if ( state != GLUT_UP ) return;

  switch ( button ) {
    case GLUT_RIGHT_BUTTON:
      clickWitRightAction( x, y, &is_on_notebook_rotation_animation );
      break;

    case GLUT_LEFT_BUTTON:
      clickWithLeftAction( x, y );
      break;

    default:
      break;
  }
  glutPostRedisplay();
}


// Função Principal
//-------------------------------------------------------------------------------------

int main( int argc, char** argv ) {
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowPosition( 0, 0 );
  glutInitWindowSize( 1920, 1080 );
  glutCreateWindow( "Escritorio3D" );
  init();
  glutDisplayFunc( display );
  glutKeyboardFunc( keyboard );
  glutSpecialFunc( specialKeys );
  glutMouseFunc( mouse );
  glutReshapeFunc( reshape );
  glutTimerFunc( cube_delay, cubeAnimation, 0 );
  glutTimerFunc( display_delay, displayAnimation, 0 );
  glutTimerFunc( notebook_rotation_delay, notebookRotationAnimation, 0 );
  glutMainLoop();
  return 0;
}
