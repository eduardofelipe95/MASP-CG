#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

float angle = 0.0f;
float angley = 0.0f;

float lx=0.0f,lz=-1.0f, ly = 0.0f;

float x =0.0f, z = 100.0f, y = 1.0f; 

float deltaAngle = 0.0f;
float deltaAngle2 = 0.0f;
float deltaMove = 0;
float rightLeftMove = 0;
int xOrigin = -1;
int yOrigin = -1;

int h,w;

int mainWindow, subWindow1;
int border = 6;

void setProjection(int w1, int h1)
{
  float ratio;
  
  ratio = 1.0f * w1 / h1;
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

      glViewport(0, 0, w1, h1);

  // Set the clipping volume
  gluPerspective(45,ratio,0.1,1000);
  glMatrixMode(GL_MODELVIEW);
}

void changeSize(int w1,int h1) {

  if(h1 == 0)
    h1 = 1;

  // we're keeping these values cause we'll need them latter
  w = w1;
  h = h1;

  // set subwindow 1 as the active window
  glutSetWindow(subWindow1);
  // resize and reposition the sub window
  glutPositionWindow(border,border);
  glutReshapeWindow(w-2*border, h - border*3/2);
  setProjection(w-2*border, h - border*3/2);

}

void drawSnowMan() {

  glColor3f(1.0f, 1.0f, 1.0f);

  // Draw Body
  glTranslatef(0.0f ,0.75f, 0.0f);
  glutSolidSphere(0.75f,20,20);

  // Draw Head
  glTranslatef(0.0f, 1.0f, 0.0f);
  glutSolidSphere(0.25f,20,20);

  // Draw Eyes
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.05f, 0.10f, 0.18f);
  glutSolidSphere(0.05f,10,10);
  glTranslatef(-0.1f, 0.0f, 0.0f);
  glutSolidSphere(0.05f,10,10);
  glPopMatrix();

  // Draw Nose
  glColor3f(1.0f, 0.5f, 0.5f);
  glRotatef(0.0f,1.0f, 0.0f, 0.0f);
  glutSolidCone(0.08f,0.5f,10,2);

  glColor3f(1.0f, 1.0f, 1.0f);

}

void computePos(float deltaMove) {

  x += deltaMove * lx * 0.1f;
  z += deltaMove * lz * 0.1f;
  y += deltaMove * ly * 0.1f;
}

// Common Render Items for all subwindows
void renderScene2() { //desenha os objetos

  // Draw ground
  
  glColor3f(0.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glVertex3f(-1000.0f, 0.0f, -1000.0f);
  glVertex3f(-1000.0f, 0.0f,  1000.0f);
  glVertex3f( 1000.0f, 0.0f,  1000.0f);
  glVertex3f( 1000.0f, 0.0f, -1000.0f);
  glEnd();

  

  //z = azul
  //y = vermelho
  //x = verde

  
  glPushMatrix();
  glColor3f(1.0,0.0,0.0);
  glTranslatef(0.0f, 500.0f, 0.0f);
  glScalef(1.0, 2000.0, 1.0);
  glutSolidCube(0.5);
  glPopMatrix();
  
  glPushMatrix();
  glColor3f(0.0,1.0,0.0);
  glTranslatef(0.0f, 0.0f, 0.0f);
  glScalef(4000.0, 1.0, 1.0);
  glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.0,0.0,1.0);
  glTranslatef(0.0f, 0.0f, 0.0f);
  glScalef(1.0, 1.0, 4000.0);
  glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-100.0f, 0.0f, 0.0f);
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  glTranslatef(0.0f, 37.5f, 0.0f);
  glScalef(6.0, 75.0, 3.0);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0,0.0,0.0);
  glTranslatef(100.0f, 72.0f, 0.0f);
  glScalef(200.0, 6.0, 3.0);
  glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1.0,0.0,1.0);
  glTranslatef(200.0f, 37.5f, 0.0f);
  glScalef(6.0, 75.0, 3.0);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();



  


}

// Display func for main window
void renderScene() {
  glutSetWindow(mainWindow);
  glClear(GL_COLOR_BUFFER_BIT);
  glutSwapBuffers();
}

// Display func for sub window 1
void renderScenesw1() {

  glutSetWindow(subWindow1);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(x, y, z, //posição da câmera
    x + lx,y + ly,z + lz, //para onde o observador está olhando
    0.0f,1.0f,0.0f); //estabelece o vetor up, indica o "lado de cima de uma cena 3D"

  renderScene2(); //Desenha os bonecos e o plano

  glutSwapBuffers();
}

// Global render func
void renderSceneAll() {

  // check for keyboard movement
  if (deltaMove) {
    computePos(deltaMove);
    glutSetWindow(mainWindow);
    glutPostRedisplay();
  }

  renderScene();
  renderScenesw1();
}

// -----------------------------------
//          KEYBOARD
// -----------------------------------

void processNormalKeys(unsigned char key, int xx, int yy) {

  switch (key){
    case 'w':
        break;
    case 's':
        break;
    case 'a':
        break;
    case 'd':
        break;
  }
}

void pressKey(int key, int xx, int yy) {

  switch (key) {
  case GLUT_KEY_UP : deltaMove = 4.5f; break;
  case GLUT_KEY_DOWN : deltaMove = -4.5f; break;
  }
  glutSetWindow(mainWindow);
  glutPostRedisplay();

}

void releaseKey(int key, int x, int y) {

  switch (key) {
  case GLUT_KEY_UP :
  case GLUT_KEY_DOWN : deltaMove = 0;break;
  }
}

// -----------------------------------
//          MOUSE
// -----------------------------------

void mouseMove(int x, int y) {

  // this will only be true when the left button is down
  if (xOrigin >= 0) {

  // update deltaAngle
  deltaAngle = (x - xOrigin) * 0.001f;
  deltaAngle2 = (y - yOrigin) * 0.001f;

  // update camera's direction
  lx = -sin(angle + deltaAngle);
  lz = -cos(angle + deltaAngle);
  ly = sin(angley + deltaAngle2);

  glutSetWindow(mainWindow);
  glutPostRedisplay();
  }
}

void mouseButton(int button, int state, int x, int y) {

  // only start motion if the left button is pressed
  if (button == GLUT_LEFT_BUTTON) {

    
    if (state == GLUT_UP) {
      angle += deltaAngle;
      angley += deltaAngle2;
      deltaAngle = 0.0f;
      deltaAngle2 = 0.0f;

      xOrigin = -1;
      yOrigin = -1;
    }
    else  {// state = GLUT_DOWN
      xOrigin = x;
      yOrigin = y;

    }
  }
}

// -----------------------------------
//          MAIN and INIT
// -----------------------------------

void init() {

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // register callbacks
  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(pressKey);
  glutSpecialUpFunc(releaseKey);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
}

int main(int argc, char **argv) {

  // init GLUT and create main window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(1080,720);
  mainWindow = glutCreateWindow("MASP");

  // callbacks for main window
  glutDisplayFunc(renderSceneAll);
  glutReshapeFunc(changeSize);

  // Removing the idle function to save CPU and GPU
  //glutIdleFunc(renderSceneAll);
  init();

  // sub windows
  subWindow1 = glutCreateSubWindow(mainWindow, border,border,w-2*border, h/2 - border*3/2);
  glutDisplayFunc(renderScenesw1);
  init();

  // enter GLUT event processing cycle
  glutMainLoop();
 
  return 1;
}



