#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include <GL/glut.h>


float angle = 0.0f;
float angley = 0.0f;

float x1 = 200;

float lx=0.0f,lz=-1.0f, ly = 0.0f;

float x =-10.0f, z = 300.0f, y = 70.0f; 

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
  gluPerspective(45,ratio,0.1,5000);
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

void draw1(){
  
  glPushMatrix();
  glColor3f(1.0,0.0,0.0);
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
  glColor3f(1.0,0.0,0.0);
  glTranslatef(200.0f, 37.5f, 0.0f);
  glScalef(6.0, 75.0, 3.0);
  glutSolidCube(1.0);
  glPopMatrix();

}

void drawLadder(){
  for(int i = 0, j = 2; i <= 75; i += 5, j += 3){
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.8);
      glTranslatef( 0.0, j, -i);
      glScalef(30.0, 2.0, 8.0);
      glutSolidCube(1.0);
    glPopMatrix();
  }

  

  glPushMatrix();
    glColor3f(0.0, 0.0, 0.5);
    glTranslatef(15.0, 0.0, 0.0);
    glRotatef(-59.0,1.0, 0.0, 0.0);
    glScalef(2.0, 200.0, 10.0);

    glutSolidCube(1.0);
  glPopMatrix();
  

  glPushMatrix();
    glColor3f(0.0, 0.0, 0.5);
    glTranslatef(-16.0, 0.0, 0.0);
    glRotatef(-59.0, 1.0, 0.0, 0.0);
    glScalef(2.0, 185.0, 10.0);

    glutSolidCube(1.0);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-62.0, 54.0, -93.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    for(int i = -5, j = -1; i <= 70; i += 5, j += 3){
      glPushMatrix();
      glColor3f(0.5, 0.5, 0.8);
        glTranslatef( 0.0, j, -i);
        glScalef(30.0, 2.0, 8.0);
        glutSolidCube(1.0);
      glPopMatrix();
    }
    
  

  glPushMatrix();
    glColor3f(0.0, 0.0, 0.5);
    glTranslatef(15.0, 23.0, -35.0);
    glRotatef(-59.0,1.0, 0.0, 0.0);
    glScalef(2.0, 100.0, 10.0);

    glutSolidCube(1.0);
  glPopMatrix();
  

  glPushMatrix();
    glColor3f(0.0, 0.0, 0.5);
    glTranslatef(-16.0, 23.0, -35.0);
    glRotatef(-59.0, 1.0, 0.0, 0.0);
    glScalef(2.0, 101.0, 10.0);

    glutSolidCube(1.0);
  glPopMatrix();    
  glPopMatrix();


  //

  glPushMatrix();
    glTranslatef(-40.0,0.0,0.0);
    glPushMatrix();
      glColor3f(0.8, 0.8, 0.8);
        glTranslatef( 20.5, 50, -93);
        glScalef(70.0, 1.0, 30.0);
        glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
      glColor3f(0.0, 0.0, 0.5);
      glTranslatef(19.5, 51.5, -108.0);
      glScalef(73.0, 9.0, 2.0);

      glutSolidCube(1.0);

    glPopMatrix();

    glPushMatrix();
      glColor3f(0.0, 0.0, 0.5);
      glTranslatef(55.0, 51.5, -93.0);
      glScalef(2.0, 9.0, 32.0);
      glutSolidCube(1.0);

    glPopMatrix();

    glPushMatrix();
      glColor3f(0.0, 0.0, 0.5);
      glTranslatef(4.0, 51.5, -77.0);
      glScalef(42.0, 9.0, 2.0);

      glutSolidCube(1.0);

    glPopMatrix();
  glPopMatrix();



}

void drawWindows(){

  for(int i = -275; i < 300; i += 31){
  glPushMatrix();
    glTranslatef(i, 0.0, 0.0);
    
    glPushMatrix();
      glColor3f(1.0,1.0,1.0);
      glTranslatef(0.0, 123.0, 208.0);
      glScalef(30.0, 54.0, 1.0);
      glutSolidCube(1.0);
    glPopMatrix();
  
    glPushMatrix();
      glColor3f(0.2,1.0,1.0);

      glTranslatef(15.5, 123.0, 208.0);
      glScalef(1.0, 54.0, 1.0);

      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.2,1.0,1.0);

      glTranslatef(-15.5, 123.0, 208.0);
      glScalef(1.0, 54.0, 1.0);

      glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
      glColor3f(0.2,1.0,1.0);

      glTranslatef(0.0, 150.5, 208.0);
      glScalef(32.0, 1.0, 1.0);

      glutSolidCube(1.0);


    glPopMatrix();

    glPushMatrix();
      glColor3f(0.2,1.0,1.0);

      glTranslatef(0.0, 95.5, 208.0);
      glScalef(32.0, 1.0, 1.0);

      glutSolidCube(1.0);


  glPopMatrix();
  glPopMatrix();
}

}

void myCube(){
  glPushMatrix();
    
    glBegin(GL_POLYGON);     
      glVertex3f(  0.5, -0.5, -0.5 );      
      glVertex3f(  0.5,  0.5, -0.5 );      
      glVertex3f( -0.5,  0.5, -0.5 );      
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
      glVertex3f(  0.5, -0.5, 0.5 );
      glVertex3f(  0.5,  0.5, 0.5 );
      glVertex3f( -0.5,  0.5, 0.5 );
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
      glVertex3f( 0.5, -0.5, -0.5 );
      glVertex3f( 0.5,  0.5, -0.5 );
      glVertex3f( 0.5,  0.5,  0.5 );
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glVertex3f(  0.5,  0.5,  0.5 );
      glVertex3f(  0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glVertex3f(  0.5, -0.5, -0.5 );
      glVertex3f(  0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
  glPopMatrix();
}

void firstFloor(){
  glPushMatrix();
  
    glColor4f(1, 0, 0 , 0.3);
    glBegin(GL_QUADS);
      glVertex3f( -370, 79, -150);
      glVertex3f( -370, 79, 150);
      glVertex3f( 292, 79, 150);
      glVertex3f( 292, 79, -150);
    glEnd();

  glColor3f(1,1,0);
  glBegin(GL_QUADS);
    glVertex3f( 292, 79, 150);
    glVertex3f( 370, 79, 150);
    glVertex3f( 370, 79, 40.236);
    glVertex3f( 292, 79, 40.236);
  glEnd();

  glColor3f(1,0,1);
  glBegin(GL_QUADS);
    glVertex3f( 370, 79, 40.236);
    glVertex3f( 332, 79, 40.236);
    glVertex3f( 332, 79, -150);
    glVertex3f( 370, 79, -150);

  glEnd();

  glColor3f(0,0,1);
  glBegin(GL_QUADS);
    glVertex3f( 332, 79, -150);
    glVertex3f( 332, 79, -128.721);
    glVertex3f( 292, 79, -128.721);
    glVertex3f( 292, 79, -150);
  glEnd();

  glColor3f(1,0.4,1);
  glBegin(GL_QUADS);
    glVertex3f( 332, 79, -88.721);
    glVertex3f( 292, 79, -88.721);
    glVertex3f( 292, 79, -53.48);
    glVertex3f( 332, 79, -53.48);
  glEnd();

  //
  glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
      glVertex3f( -370, 83.740, -150);
      glVertex3f( -370, 83.740, 150);
      glVertex3f( 292, 83.740, 150);
      glVertex3f( 292, 83.740, -150);
    glEnd();

  glColor3f(1,1,0);
  glBegin(GL_QUADS);
    glVertex3f( 292, 83.740, 150);
    glVertex3f( 370, 83.740, 150);
    glVertex3f( 370, 83.740, 40.236);
    glVertex3f( 292, 83.740, 40.236);
  glEnd();

  glColor3f(1,0,1);
  glBegin(GL_QUADS);
    glVertex3f( 370, 83.740, 40.236);
    glVertex3f( 332, 83.740, 40.236);
    glVertex3f( 332, 83.740, -150);
    glVertex3f( 370, 83.740, -150);

  glEnd();

  glColor3f(0,0,1);
  glBegin(GL_QUADS);
    glVertex3f( 332, 83.740, -150);
    glVertex3f( 332, 83.740, -128.721);
    glVertex3f( 292, 83.740, -128.721);
    glVertex3f( 292, 83.740, -150);
  glEnd();

  glColor3f(1,0.4,1);
  glBegin(GL_QUADS);
    glVertex3f( 332, 83.740, -88.721);
    glVertex3f( 292, 83.740, -88.721);
    glVertex3f( 292, 83.740, -53.48);
    glVertex3f( 332, 83.740, -53.48);
  glEnd();

  //

  glColor3f(0.4,0.4,1);
  glBegin(GL_QUADS);
    glVertex3f( -370, 79, 150);
    glVertex3f( 370, 79, 150);
    glVertex3f( 370, 83.740, 150);
    glVertex3f( -370, 83.740, 150);
    
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 79, -150);
    glVertex3f( 370, 79, -150);
    glVertex3f( 370, 83.740, -150);
    glVertex3f( -370, 83.740, -150);
    
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 79, 150);
    glVertex3f( 370, 79, 150);
    glVertex3f( 370, 83.740, 150);
    glVertex3f( -370, 83.740, 150);
    
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 79, 150);
    glVertex3f( -370, 79, -150);
    glVertex3f( -370, 83.740, -150);
    glVertex3f( -370, 83.740, 150);
    
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 79, 150);
    glVertex3f( 370, 79, -150);
    glVertex3f( 370, 83.740, -150);
    glVertex3f( 370, 83.740, 150);
    
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 79,40.236);
    glVertex3f(292, 79,40.236);
    glVertex3f(292, 83.740,40.236);
    glVertex3f(332, 83.740,40.236);

  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 79, -53.48);
    glVertex3f(292, 79, -53.48);
    glVertex3f(292, 83.740, -53.48);
    glVertex3f(332, 83.740, -53.48);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(292, 79, -53.48);
    glVertex3f(292, 79, 40.236);
    glVertex3f(292, 83.740, 40.236);
    glVertex3f(292, 83.740, -53.48);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 79, -53.48);
    glVertex3f(332, 79, 40.236);
    glVertex3f(332, 83.740, 40.236);
    glVertex3f(332, 83.740, -53.48);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(292, 79, -128.721);
    glVertex3f(292, 79, -88.721);
    glVertex3f(292, 83.740, -88.721);
    glVertex3f(292, 83.740, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 79, -128.721);
    glVertex3f(332, 79, -88.721);
    glVertex3f(332, 83.740, -88.721);
    glVertex3f(332, 83.740, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 79, -128.721);
    glVertex3f(292, 79, -128.721);
    glVertex3f(292, 83.740, -128.721);
    glVertex3f(332, 83.740, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 79, -88.721);
    glVertex3f(292, 79, -88.721);
    glVertex3f(292, 83.740, -88.721);
    glVertex3f(332, 83.740, -88.721);
  glEnd();

  glPopMatrix();
}

void secondFloor(){ 
  glPushMatrix();
    glColor3f(0.1, 0.9, 0.3);
    glBegin(GL_QUADS);
      glVertex3f( -370, 143.5, -150);
      glVertex3f( -370, 143.5, 150);
      glVertex3f( 253.029, 143.5, 150);
      glVertex3f( 253.029, 143.5, -150);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_QUADS);
      glVertex3f(253.029, 143.5, 150);
      glVertex3f(253.029, 143.5, 44.236);
      glVertex3f(370, 143.5, 44.236);
      glVertex3f(370, 143.5, 150);

    glEnd();

    glColor3f(1, 0.2, 0.2);
    glBegin(GL_QUADS);
      glVertex3f(293.029,143.5,44.236);
      glVertex3f(370,143.5,44.236);
      glVertex3f(370,143.5, -49.48);
      glVertex3f(293.029,143.5, -49.48);
    glEnd();

    glColor3f(0.1,0.2, 0.3);
    glBegin(GL_QUADS);
      glVertex3f( 253.029, 143.5, -150);
      glVertex3f( 253.029, 143.5, -128.721);
      glVertex3f( 370, 143.5, -128.721);
      glVertex3f( 370, 143.5, -150);
    glEnd();

    glColor3f(1,0.2, 0.3);
    glBegin(GL_QUADS);
      glVertex3f( 332, 143.5, -128.721);
      glVertex3f( 370, 143.5, -128.721);
      glVertex3f( 370, 143.5, -49.48);
      glVertex3f( 332, 143.5, -49.48);
    glEnd();

    glColor3f(1,0.5, 0.5);
    glBegin(GL_QUADS);
      glVertex3f( 253.029, 143.5, -88.721);
      glVertex3f( 332, 143.5, -88.721);
      glVertex3f( 332.029, 143.5, -49.48);
      glVertex3f( 253.029, 143.5, -49.48);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
      glVertex3f( 253.029, 143.5, -128.721);
      glVertex3f( 253.029, 143.5, -88.721);
      glVertex3f( 292, 143.5, -88.721);
      glVertex3f( 292, 143.5, -128.721);
      
    glEnd();
    //
    glColor3f(0.1, 0.9, 0.3);
    glBegin(GL_QUADS);
      glVertex3f( -370, 144.5, -150);
      glVertex3f( -370, 144.5, 150);
      glVertex3f( 253.029, 144.5, 150);
      glVertex3f( 253.029, 144.5, -150);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_QUADS);
      glVertex3f(253.029, 144.5, 150);
      glVertex3f(253.029, 144.5, 44.236);
      glVertex3f(370, 144.5, 44.236);
      glVertex3f(370, 144.5, 150);

    glEnd();

    glColor3f(1, 0.2, 0.2);
    glBegin(GL_QUADS);
      glVertex3f(293.029,144.5,44.236);
      glVertex3f(370,144.5,44.236);
      glVertex3f(370,144.5, -49.48);
      glVertex3f(293.029,144.5, -49.48);
    glEnd();

    glColor3f(0.1,0.2, 0.3);
    glBegin(GL_QUADS);
      glVertex3f( 253.029, 144.5, -150);
      glVertex3f( 253.029, 144.5, -128.721);
      glVertex3f( 370, 144.5, -128.721);
      glVertex3f( 370, 144.5, -150);
    glEnd();

    glColor3f(1,0.2, 0.3);
    glBegin(GL_QUADS);
      glVertex3f( 332, 144.5, -128.721);
      glVertex3f( 370, 144.5, -128.721);
      glVertex3f( 370, 144.5, -49.48);
      glVertex3f( 332, 144.5, -49.48);
    glEnd();

    glColor3f(1,0.5, 0.5);
    glBegin(GL_QUADS);
      glVertex3f( 253.029, 144.5, -88.721);
      glVertex3f( 332, 144.5, -88.721);
      glVertex3f( 332.029, 144.5, -49.48);
      glVertex3f( 253.029, 144.5, -49.48);
    glEnd();

    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
      glVertex3f( 253.029, 144.5, -128.721);
      glVertex3f( 253.029, 144.5, -88.721);
      glVertex3f( 292, 144.5, -88.721);
      glVertex3f( 292, 144.5, -128.721);
      
    glEnd();
    //

    glColor3f(0.1,0.2, 1);
    glBegin(GL_QUADS);
      glVertex3f( -370, 143.5, 150);
      glVertex3f( 370, 143.5, 150);
      glVertex3f( 370, 144.5, 150);
      glVertex3f( -370, 144.5, 150);
    glEnd();

    glColor3f(0.1,0.2, 1);
    glBegin(GL_QUADS);
      glVertex3f( -370, 143.5, -150);
      glVertex3f( 370, 143.5, -150);
      glVertex3f( 370, 144.5, -150);
      glVertex3f( -370, 144.5, -150);
    glEnd();

    glColor3f(0.1,0.2, 1);
    glBegin(GL_QUADS);
      glVertex3f( -370, 143.5, -150);
      glVertex3f( -370, 143.5, 150);
      glVertex3f( -370, 144.5, 150);
      glVertex3f( -370, 144.5, -150);
    glEnd();

    glColor3f(0.1,0.2, 1);
    glBegin(GL_QUADS);
      glVertex3f( 370, 143.5, -150);
      glVertex3f( 370, 143.5, 150);
      glVertex3f( 370, 144.5, 150);
      glVertex3f( 370, 144.5, -150);
    glEnd();

    //

      glBegin(GL_QUADS);
    glVertex3f(292, 143.5, -128.721);
    glVertex3f(292, 143.5, -88.721);
    glVertex3f(292, 144.5, -88.721);
    glVertex3f(292, 144.5, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 143.5, -128.721);
    glVertex3f(332, 143.5, -88.721);
    glVertex3f(332, 144.5, -88.721);
    glVertex3f(332, 144.5, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 143.5, -128.721);
    glVertex3f(292, 143.5, -128.721);
    glVertex3f(292, 144.5, -128.721);
    glVertex3f(332, 144.5, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 143.5, -88.721);
    glVertex3f(292, 143.5, -88.721);
    glVertex3f(292, 144.5, -88.721);
    glVertex3f(332, 144.5, -88.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(293.029, 143.5, 44.236);
    glVertex3f(253.029, 143.5, 44.236);
    glVertex3f(253.029, 144.5, 44.236);
    glVertex3f(293.029, 144.5, 44.236);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(293.029, 143.5, -49.48);
    glVertex3f(253.029, 143.5, -49.48);
    glVertex3f(253.029, 144.5, -49.48);
    glVertex3f(293.029, 144.5, -49.48);
  glEnd();


  glBegin(GL_QUADS);
    glVertex3f(253.029, 143.5, 44.236);
    glVertex3f(253.029, 143.5, -49.48);
    glVertex3f(253.029, 144.5, -49.48);
    glVertex3f(253.029, 144.5, 44.236);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(293.029, 143.5, 44.236);
    glVertex3f(293.029, 143.5, -49.48);
    glVertex3f(293.029, 144.5, -49.48);
    glVertex3f(293.029, 144.5, 44.236);
  glEnd();

  
  glPopMatrix();
}

void elevator(){
  glPushMatrix();
  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(292, 0, -128.721);
    glVertex3f(292, 0, -126.721);
    glVertex3f(292, 203, -126.721);
    glVertex3f(292, 203, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(292, 0, -90.721);
    glVertex3f(292, 0, -88.721);
    glVertex3f(292, 203, -88.721);
    glVertex3f(292, 203, -90.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 0, -128.721);
    glVertex3f(332, 0, -126.721);
    glVertex3f(332, 203, -126.721);
    glVertex3f(332, 203, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 0, -90.721);
    glVertex3f(332, 0, -88.721);
    glVertex3f(332, 203, -88.721);
    glVertex3f(332, 203, -90.721);
  glEnd();


  glBegin(GL_QUADS);
    glVertex3f(332, 0, -128.721);
    glVertex3f(330, 0, -128.721);
    glVertex3f(330, 203, -128.721);
    glVertex3f(332, 203, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(294, 0, -128.721);
    glVertex3f(292, 0, -128.721);
    glVertex3f(292, 203, -128.721);
    glVertex3f(294, 203, -128.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(332, 0, -88.721);
    glVertex3f(330, 0, -88.721);
    glVertex3f(330, 203, -88.721);
    glVertex3f(332, 203, -88.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(294, 0, -88.721);
    glVertex3f(292, 0, -88.721);
    glVertex3f(292, 203, -88.721);
    glVertex3f(294, 203, -88.721);
  glEnd();
  glPopMatrix();

}

void roof(){
  glPushMatrix();
    glColor3f(0.9,0.9,0.5);
    glBegin(GL_QUADS);
    glVertex3f( -370, 203, -150);
    glVertex3f( -370, 203, 150);
    glVertex3f( 370, 203, 150);
    glVertex3f( 370, 203, -150);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f( -370, 223, -150);
    glVertex3f( -370, 223, 150);
    glVertex3f( 370, 223, 150);
    glVertex3f( 370, 223, -150);
    glEnd();

    glColor3f(1,1,0);
    glBegin(GL_QUADS);
      glVertex3f( -370, 203, -150);
      glVertex3f( -370, 203,150);
      glVertex3f( -370, 223, 150);
      glVertex3f( -370, 223, -150);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f( 370, 203, -150);
      glVertex3f( 370, 203,150);
      glVertex3f( 370, 223, 150);
      glVertex3f( 370, 223, -150);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f( -370, 203, -150);
      glVertex3f( 370, 203, -150);
      glVertex3f( 370, 223, -150);
      glVertex3f( -370, 223, -150);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f( -370, 203, 150);
      glVertex3f( 370, 203, 150);
      glVertex3f( 370, 223, 150);
      glVertex3f( -370, 223, 150);
    glEnd();

  glPopMatrix();

}

void windows(){
  glPushMatrix();

    float f = -370;
    for(int i = 0; i < 60; i++){
      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, 150);
        glVertex3f(f+1, 83.740,150);
        glVertex3f(f+1,143.5,150);
        glVertex3f(f,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, 150);
        glVertex3f(f, 83.740,149);
        glVertex3f(f,143.5,149);
        glVertex3f(f,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, 150);
        glVertex3f(f + 1, 83.740,149);
        glVertex3f(f + 1,143.5,149);
        glVertex3f(f + 1,143.5,150);
      glEnd();

      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, 150);
        glVertex3f(f + 12.317, 83.740,150);
        glVertex3f(f + 12.317,143.5,150);
        glVertex3f(f + 1,143.5,150);
      glEnd();
      glDisable(GL_BLEND);

      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, 149);
        glVertex3f(f+1, 83.740,149);
        glVertex3f(f+1,143.5,149);
        glVertex3f(f,143.5,149);
      glEnd();

      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0,0,0,0.1);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, 149);
        glVertex3f(f + 12.317, 83.740,149);
        glVertex3f(f + 12.317,143.5,149);
        glVertex3f(f + 1,143.5,149);
      glEnd();
      glDisable(GL_BLEND);
      f+= 12.317;
    }

    glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, 150);
        glVertex3f(f+1, 83.740,150);
        glVertex3f(f+1,143.5,150);
        glVertex3f(f,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, 149);
        glVertex3f(f+1, 83.740,149);
        glVertex3f(f+1,143.5,149);
        glVertex3f(f,143.5,149);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, 150);
        glVertex3f(f + 1, 83.740,149);
        glVertex3f(f + 1,143.5,149);
        glVertex3f(f + 1,143.5,150);
      glEnd();

  glPopMatrix();






  






  float z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 83.740, z);
        glVertex3f(-370, 83.740,z - 1);
        glVertex3f(-370,143.5, z - 1);
        glVertex3f(-370,143.5,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 83.740, z - 1);
        glVertex3f(-370, 83.740, z - 12.3);
        glVertex3f(-370,143.5, z - 12.3);
        glVertex3f(-370,143.5, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 83.740, z);
        glVertex3f(-370, 83.740,z + 1);
        glVertex3f(-370,143.5, z + 1);
        glVertex3f(-370,143.5,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 83.740, z + 1);
        glVertex3f(-370, 83.740,z + 12.3);
        glVertex3f(-370,143.5, z + 12.3);
        glVertex3f(-370,143.5,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 83.740, z);
        glVertex3f(-370, 83.740,z - 1);
        glVertex3f(-370,143.5, z - 1);
        glVertex3f(-370,143.5,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 83.740, z - 1);
        glVertex3f(-370, 83.740,z - 12.42);
        glVertex3f(-370,143.5, z - 12.42);
        glVertex3f(-370,143.5,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);


  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 83.740, z);
        glVertex3f(-369, 83.740,z - 1);
        glVertex3f(-369,143.5, z - 1);
        glVertex3f(-369,143.5,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 83.740, z - 1);
        glVertex3f(-369, 83.740, z - 12.3);
        glVertex3f(-369,143.5, z - 12.3);
        glVertex3f(-369,143.5, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 83.740, z);
        glVertex3f(-369, 83.740,z + 1);
        glVertex3f(-369,143.5, z + 1);
        glVertex3f(-369,143.5,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 83.740, z + 1);
        glVertex3f(-369, 83.740,z + 12.3);
        glVertex3f(-369,143.5, z + 12.3);
        glVertex3f(-369,143.5,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 83.740, z);
        glVertex3f(-369, 83.740,z - 1);
        glVertex3f(-369,143.5, z - 1);
        glVertex3f(-369,143.5,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 83.740, z - 1);
        glVertex3f(-369, 83.740,z - 12.42);
        glVertex3f(-369,143.5, z - 12.42);
        glVertex3f(-369,143.5,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);
  //
  
  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 83.740, z);
        glVertex3f(370, 83.740,z - 1);
        glVertex3f(370,143.5, z - 1);
        glVertex3f(370,143.5,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 83.740, z - 1);
        glVertex3f(370, 83.740, z - 12.3);
        glVertex3f(370,143.5, z - 12.3);
        glVertex3f(370,143.5, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 83.740, z);
        glVertex3f(370, 83.740,z + 1);
        glVertex3f(370,143.5, z + 1);
        glVertex3f(370,143.5,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 83.740, z + 1);
        glVertex3f(370, 83.740,z + 12.3);
        glVertex3f(370,143.5, z + 12.3);
        glVertex3f(370,143.5,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 83.740, z);
        glVertex3f(370, 83.740,z - 1);
        glVertex3f(370,143.5, z - 1);
        glVertex3f(370,143.5,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 83.740, z - 1);
        glVertex3f(370, 83.740,z - 12.42);
        glVertex3f(370,143.5, z - 12.42);
        glVertex3f(370,143.5,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);

  ///
  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 83.740, z);
        glVertex3f(369, 83.740,z - 1);
        glVertex3f(369,143.5, z - 1);
        glVertex3f(369,143.5,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 83.740, z - 1);
        glVertex3f(369, 83.740, z - 12.3);
        glVertex3f(369,143.5, z - 12.3);
        glVertex3f(369,143.5, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 83.740, z);
        glVertex3f(369, 83.740,z + 1);
        glVertex3f(369,143.5, z + 1);
        glVertex3f(369,143.5,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 83.740, z + 1);
        glVertex3f(369, 83.740,z + 12.3);
        glVertex3f(369,143.5, z + 12.3);
        glVertex3f(369,143.5,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 83.740, z);
        glVertex3f(369, 83.740,z - 1);
        glVertex3f(369,143.5, z - 1);
        glVertex3f(369,143.5,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 83.740, z - 1);
        glVertex3f(369, 83.740,z - 12.42);
        glVertex3f(369,143.5, z - 12.42);
        glVertex3f(369,143.5,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);
  




  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 144.5, z);
        glVertex3f(-370, 144.5,z - 1);
        glVertex3f(-370,203, z - 1);
        glVertex3f(-370,203,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 144.5, z - 1);
        glVertex3f(-370, 144.5, z - 12.3);
        glVertex3f(-370,203, z - 12.3);
        glVertex3f(-370,203, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 144.5, z);
        glVertex3f(-370, 144.5,z + 1);
        glVertex3f(-370, 203, z + 1);
        glVertex3f(-370, 203,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 144.5, z + 1);
        glVertex3f(-370, 144.5,z + 12.3);
        glVertex3f(-370, 203, z + 12.3);
        glVertex3f(-370, 203,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 144.5, z);
        glVertex3f(-370, 144.5,z - 1);
        glVertex3f(-370, 203, z - 1);
        glVertex3f(-370, 203,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(-370, 144.5, z - 1);
        glVertex3f(-370, 144.5,z - 12.42);
        glVertex3f(-370,203, z - 12.42);
        glVertex3f(-370,203,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);


  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 144.5, z);
        glVertex3f(-369, 144.5,z - 1);
        glVertex3f(-369,203, z - 1);
        glVertex3f(-369,203,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 144.5, z - 1);
        glVertex3f(-369, 144.5, z - 12.3);
        glVertex3f(-369,203, z - 12.3);
        glVertex3f(-369,203, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 144.5, z);
        glVertex3f(-369, 144.5,z + 1);
        glVertex3f(-369,203, z + 1);
        glVertex3f(-369,203,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 144.5, z + 1);
        glVertex3f(-369, 144.5,z + 12.3);
        glVertex3f(-369,203, z + 12.3);
        glVertex3f(-369,203,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 144.5, z);
        glVertex3f(-369, 144.5,z - 1);
        glVertex3f(-369,203, z - 1);
        glVertex3f(-369,203,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(-369, 144.5, z - 1);
        glVertex3f(-369, 144.5,z - 12.42);
        glVertex3f(-369,203, z - 12.42);
        glVertex3f(-369,203,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);
  //
  
  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 144.5, z);
        glVertex3f(370, 144.5,z - 1);
        glVertex3f(370, 203, z - 1);
        glVertex3f(370, 203,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 144.5, z - 1);
        glVertex3f(370, 144.5, z - 12.3);
        glVertex3f(370, 203, z - 12.3);
        glVertex3f(370, 203, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 83.740, z);
        glVertex3f(370, 83.740,z + 1);
        glVertex3f(370,143.5, z + 1);
        glVertex3f(370,143.5,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 144.5, z + 1);
        glVertex3f(370, 144.5,z + 12.3);
        glVertex3f(370, 203, z + 12.3);
        glVertex3f(370, 203,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 144.5, z);
        glVertex3f(370, 144.5,z - 1);
        glVertex3f(370, 203, z - 1);
        glVertex3f(370, 203,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 144.5, z - 1);
        glVertex3f(370, 144.5,z - 12.42);
        glVertex3f(370, 203, z - 12.42);
        glVertex3f(370, 203,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);

  ///
  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 144.5, z);
        glVertex3f(369, 144.5,z - 1);
        glVertex3f(369,203, z - 1);
        glVertex3f(369,203,z);
      glEnd();

      z -= 12.3;
  }

  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 144.5, z - 1);
        glVertex3f(369, 144.5, z - 12.3);
        glVertex3f(369,203, z - 12.3);
        glVertex3f(369,203, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 144.5, z);
        glVertex3f(369, 144.5,z + 1);
        glVertex3f(369,203, z + 1);
        glVertex3f(369,203,z);
      glEnd();

      z += 12.3;
  }

  z = -150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 144.5, z + 1);
        glVertex3f(369, 144.5,z + 12.3);
        glVertex3f(369,203, z + 12.3);
        glVertex3f(369,203,z + 1);
      glEnd();

      z += 12.3;
  }
  glDisable(GL_BLEND);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 144.5, z);
        glVertex3f(369, 144.5,z - 1);
        glVertex3f(369, 203, z - 1);
        glVertex3f(369, 203,z);
      glEnd();

      z -= 12.42;
  }

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(369,144.5, z - 1);
        glVertex3f(369, 144.5,z - 12.42);
        glVertex3f(369,203, z - 12.42);
        glVertex3f(369,203,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);
  




  //

  glPushMatrix();

    f = -370;
    for(int i = 0; i < 60; i++){

      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, 150);
        glVertex3f(f+1, 144.5,150);
        glVertex3f(f+1,203,150);
        glVertex3f(f,203,150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, 150);
        glVertex3f(f, 144.5,149);
        glVertex3f(f,203,149);
        glVertex3f(f,203,150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 203, 150);
        glVertex3f(f + 1, 203,149);
        glVertex3f(f + 1,144.5,149);
        glVertex3f(f + 1,144.5,150);
      glEnd();


      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 144.5, 150);
        glVertex3f(f + 12.317, 144.5,150);
        glVertex3f(f + 12.317,203,150);
        glVertex3f(f + 1,203,150);
      glEnd();
      glDisable(GL_BLEND);

      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, 149);
        glVertex3f(f+1, 144.5,149);
        glVertex3f(f+1,203,149);
        glVertex3f(f,203,149);
      glEnd();

      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 144.5, 149);
        glVertex3f(f + 12.317, 144.5,149);
        glVertex3f(f + 12.317,203,149);
        glVertex3f(f + 1,203,149);
      glEnd();
      glDisable(GL_BLEND);

      f+= 12.317;
    }

    glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, 150);
        glVertex3f(f+1, 144.5,150);
        glVertex3f(f+1,203,150);
        glVertex3f(f,203,150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, 149);
        glVertex3f(f+1, 144.5,149);
        glVertex3f(f+1,203,149);
        glVertex3f(f,203,149);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 144.5, 150);
        glVertex3f(f + 1, 144.5,149);
        glVertex3f(f + 1,203,149);
        glVertex3f(f + 1,203,150);
      glEnd();

  glPopMatrix();

  //

  glPushMatrix();

    f = -370;
    for(int i = 0; i < 60; i++){
      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, -150);
        glVertex3f(f+1, 83.740,-150);
        glVertex3f(f+1,143.5,-150);
        glVertex3f(f,143.5,-150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, -150);
        glVertex3f(f, 83.740,-149);
        glVertex3f(f,143.5,-149);
        glVertex3f(f,143.5,-150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, -150);
        glVertex3f(f + 1, 83.740,-149);
        glVertex3f(f + 1,143.5,-149);
        glVertex3f(f + 1,143.5,-150);
      glEnd();

      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, -150);
        glVertex3f(f + 12.317, 83.740,-150);
        glVertex3f(f + 12.317,143.5,-150);
        glVertex3f(f + 1,143.5,-150);
      glEnd();
      glDisable(GL_BLEND);

      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, -149);
        glVertex3f(f+1, 83.740,-149);
        glVertex3f(f+1,143.5,-149);
        glVertex3f(f,143.5,-149);
      glEnd();

      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0,0,0,0.1);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, -149);
        glVertex3f(f + 12.317, 83.740,-149);
        glVertex3f(f + 12.317,143.5,-149);
        glVertex3f(f + 1,143.5,-149);
      glEnd();
      glDisable(GL_BLEND);
      f+= 12.317;
    }

    glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, -150);
        glVertex3f(f+1, 83.740,-150);
        glVertex3f(f+1,143.5,-150);
        glVertex3f(f,143.5,-150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 83.740, -149);
        glVertex3f(f+1, 83.740,-149);
        glVertex3f(f+1,143.5,-149);
        glVertex3f(f,143.5,-149);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 83.740, -150);
        glVertex3f(f + 1, 83.740,-149);
        glVertex3f(f + 1,143.5,-149);
        glVertex3f(f + 1,143.5,-150);
      glEnd();

  glPopMatrix();

  //

  glPushMatrix();

    f = -370;
    for(int i = 0; i < 60; i++){

      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, -150);
        glVertex3f(f+1, 144.5,-150);
        glVertex3f(f+1,203,-150);
        glVertex3f(f,203,-150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, -150);
        glVertex3f(f, 144.5,-149);
        glVertex3f(f,203,-149);
        glVertex3f(f,203,-150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 203, -150);
        glVertex3f(f + 1, 203,-149);
        glVertex3f(f + 1,144.5,-149);
        glVertex3f(f + 1,144.5,-150);
      glEnd();


      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 144.5, -150);
        glVertex3f(f + 12.317, 144.5,-150);
        glVertex3f(f + 12.317,203,-150);
        glVertex3f(f + 1,203,-150);
      glEnd();
      glDisable(GL_BLEND);

      glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, -149);
        glVertex3f(f+1, 144.5,-149);
        glVertex3f(f+1,203,-149);
        glVertex3f(f,203,-149);
      glEnd();

      glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
      glBegin(GL_QUADS);
        glVertex3f(f + 1, 144.5, -149);
        glVertex3f(f + 12.317, 144.5,-149);
        glVertex3f(f + 12.317,203,-149);
        glVertex3f(f + 1,203,-149);
      glEnd();
      glDisable(GL_BLEND);

      f+= 12.317;
    }

    glColor3f( 0.1, 0.4, 1);
      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, -150);
        glVertex3f(f+1, 144.5,-150);
        glVertex3f(f+1,203,-150);
        glVertex3f(f,203,-150);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f, 144.5, -149);
        glVertex3f(f+1, 144.5,-149);
        glVertex3f(f+1,203,-149);
        glVertex3f(f,203,-149);
      glEnd();

      glBegin(GL_QUADS);
        glVertex3f(f + 1, 144.5, -150);
        glVertex3f(f + 1, 144.5,-149);
        glVertex3f(f + 1,203,-149);
        glVertex3f(f + 1,203,-150);
      glEnd();

  glPopMatrix();
}

void support(){
  glPushMatrix();
  glColor3f( 1, 0, 0);
  
  glBegin(GL_QUADS);
    glVertex3f( 370, 0 , -100);
    glVertex3f( 370, 250, -100);
    glVertex3f( 410, 250, -100);
    glVertex3f( 410, 0 , -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 0 , -75);
    glVertex3f( 370, 250, -75);
    glVertex3f( 410, 250, -75);
    glVertex3f( 410, 0 , -75);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 0 , -100);
    glVertex3f( 370, 0, -75);
    glVertex3f( 370, 79, -75);
    glVertex3f( 370, 79 , -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 83.740 , -100);
    glVertex3f( 370, 83.740, -75);
    glVertex3f( 370, 143.5, -75);
    glVertex3f( 370, 143.5 , -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 144.5 , -100);
    glVertex3f( 370, 144.5, -75);
    glVertex3f( 370, 203, -75);
    glVertex3f( 370, 203 , -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 410, 0, -100);
    glVertex3f( 410, 0, -75);
    glVertex3f( 410, 250, -75);
    glVertex3f( 410,  250, -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 223, -100);
    glVertex3f( -370, 223, -75);
    glVertex3f( 370, 223, -75);
    glVertex3f( 370,  223, -100);
  glEnd();

  
  glBegin(GL_QUADS);
    glVertex3f( -410, 250, -100);
    glVertex3f( -410, 250, -75);
    glVertex3f( 410, 250, -75);
    glVertex3f( 410,  250, -100);
  glEnd();
  
  glBegin(GL_QUADS);
    glVertex3f( -370, 223, -100);
    glVertex3f( -370, 250, -100);
    glVertex3f( 370, 250, -100);
    glVertex3f( 370,  223, -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 223, -75);
    glVertex3f( -370, 250, -75);
    glVertex3f( 370, 250, -75);
    glVertex3f( 370,  223, -75);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 0 , -100);
    glVertex3f( -370, 250, -100);
    glVertex3f( -410, 250, -100);
    glVertex3f( -410, 0 , -100);
  glEnd();

  

  glBegin(GL_QUADS);
    glVertex3f( -370, 0 , -75);
    glVertex3f( -370, 250, -75);
    glVertex3f( -410, 250, -75);
    glVertex3f( -410, 0 , -75);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 0 , -100);
    glVertex3f( -370, 0, -75);
    glVertex3f( -370, 79, -75);
    glVertex3f( -370, 79 , -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 83.740 , -100);
    glVertex3f( -370, 83.740, -75);
    glVertex3f( -370, 143.5, -75);
    glVertex3f( -370, 143.5 , -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 144.5 , -100);
    glVertex3f( -370, 144.5, -75);
    glVertex3f( -370, 203, -75);
    glVertex3f( -370, 203 , -100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -410, 0, -100);
    glVertex3f( -410, 0, -75);
    glVertex3f( -410, 250, -75);
    glVertex3f( -410,  250, -100);
  glEnd();

  //

  glBegin(GL_QUADS);
    glVertex3f( 370, 0 , 100);
    glVertex3f( 370, 250, 100);
    glVertex3f( 410, 250, 100);
    glVertex3f( 410, 0 , 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 0 , 75);
    glVertex3f( 370, 250, 75);
    glVertex3f( 410, 250, 75);
    glVertex3f( 410, 0 , 75);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 0 , 100);
    glVertex3f( 370, 0, 75);
    glVertex3f( 370, 79, 75);
    glVertex3f( 370, 79 , 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 83.740 , 100);
    glVertex3f( 370, 83.740, 75);
    glVertex3f( 370, 143.5, 75);
    glVertex3f( 370, 143.5 , 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 370, 144.5 , 100);
    glVertex3f( 370, 144.5, 75);
    glVertex3f( 370, 203, 75);
    glVertex3f( 370, 203 , 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( 410, 0, 100);
    glVertex3f( 410, 0, 75);
    glVertex3f( 410, 250, 75);
    glVertex3f( 410,  250, 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 223, 100);
    glVertex3f( -370, 223, 75);
    glVertex3f( 370, 223, 75);
    glVertex3f( 370,  223, 100);
  glEnd();

  
  glBegin(GL_QUADS);
    glVertex3f( -410, 250, 100);
    glVertex3f( -410, 250, 75);
    glVertex3f( 410, 250, 75);
    glVertex3f( 410,  250, 100);
  glEnd();
  
  glBegin(GL_QUADS);
    glVertex3f( -370, 223, 100);
    glVertex3f( -370, 250, 100);
    glVertex3f( 370, 250, 100);
    glVertex3f( 370,  223, 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 223, 75);
    glVertex3f( -370, 250, 75);
    glVertex3f( 370, 250, 75);
    glVertex3f( 370,  223, 75);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 0 , 100);
    glVertex3f( -370, 250, 100);
    glVertex3f( -410, 250, 100);
    glVertex3f( -410, 0 , 100);
  glEnd();

  

  glBegin(GL_QUADS);
    glVertex3f( -370, 0 , 75);
    glVertex3f( -370, 250, 75);
    glVertex3f( -410, 250, 75);
    glVertex3f( -410, 0 , 75);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 0 , 100);
    glVertex3f( -370, 0, 75);
    glVertex3f( -370, 79, 75);
    glVertex3f( -370, 79 , 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 83.740 , 100);
    glVertex3f( -370, 83.740, 75);
    glVertex3f( -370, 143.5, 75);
    glVertex3f( -370, 143.5 , 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -370, 144.5 , 100);
    glVertex3f( -370, 144.5, 75);
    glVertex3f( -370, 203, 75);
    glVertex3f( -370, 203 , 100);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f( -410, 0, 100);
    glVertex3f( -410, 0, 75);
    glVertex3f( -410, 250, 75);
    glVertex3f( -410,  250, 100);
  glEnd();

  glPopMatrix();
}

void object1(){
  glPushMatrix();
  glColor3f(1,1,0);
    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 0, -2.5);
      glVertex3f(1.5 , 0, -2.5);
      glVertex3f(1.5 , 0, 2.5);
      glVertex3f(-1.5 , 0, 2.5);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 0, -2.5);
      glVertex3f(-1.5 , 3, -2.5);
      glVertex3f(-1.5 , 3, 2.5);
      glVertex3f(-1.5 , 0, 2.5);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 3, -2.5);
      glVertex3f(-1.5 , 3.5, -2.5);
      glVertex3f(-1.5 , 3.5, -0.25);
      glVertex3f(-1.5 , 3, -0.25);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(1.5 , 3, -2.5);
      glVertex3f(1.5 , 3.5, -2.5);
      glVertex3f(1.5 , 3.5, -0.25);
      glVertex3f(1.5 , 3, -0.25);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_QUADS);
      glVertex3f(1.5 , 3, 2.5);
      glVertex3f(1.5 , 3.5, 2.5);
      glVertex3f(1.5 , 3.5, 0.25);
      glVertex3f(1.5 , 3, 0.25);
    glEnd();

    glColor3f(1,0,1);
    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 3.5, -2.5);
      glVertex3f(-1.5 , 3.5, -0.25);
      glVertex3f(1.5 , 3.5, -0.25);
      glVertex3f(1.5 , 3.5, -2.5);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 3.5, 0.25);
      glVertex3f(-1.5 , 3.5, 2.5);
      glVertex3f(1.5 , 3.5, 2.5);
      glVertex3f(1.5 , 3.5, 0.25);
    glEnd();

    glColor3f(0,0,1);

    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 3, 2.5);
      glVertex3f(-1.5 , 3.5, 2.5);
      glVertex3f(-1.5 , 3.5, 0.25);
      glVertex3f(-1.5 , 3, 0.25);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(1.5 , 0, -2.5);
      glVertex3f(1.5 , 3, -2.5);
      glVertex3f(1.5 , 3, 2.5);
      glVertex3f(1.5 , 0, 2.5);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 0, -2.5);
      glVertex3f(-1.5 , 3.5, -2.5);
      glVertex3f(1.5 , 3.5, -2.5);
      glVertex3f(1.5 , 0, -2.5);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 0, 2.5);
      glVertex3f(-1.5 , 3.5, 2.5);
      glVertex3f(1.5 , 3.5, 2.5);
      glVertex3f(1.5 , 0, 2.5);
    glEnd();

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,0.3);
    glBegin(GL_QUADS);
      glVertex3f(-4.5 , 3, -0.25);
      glVertex3f(-4.5 , 21, -0.25);
      glVertex3f(4.5 , 21, -0.25);
      glVertex3f(4.5 , 3, -0.25);
    glEnd();

    
    glBegin(GL_QUADS);
      glVertex3f(-4.5 , 3, 0.25);
      glVertex3f(-4.5 , 21, 0.25);
      glVertex3f(4.5 , 21, 0.25);
      glVertex3f(4.5 , 3, 0.25);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(-4.5 , 3, -0.25);
      glVertex3f(-4.5 , 21, -0.25);
      glVertex3f(-4.5 , 21, 0.25);
      glVertex3f(-4.5 , 3, 0.25);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(4.5 , 3, -0.25);
      glVertex3f(4.5 , 21, -0.25);
      glVertex3f(4.5 , 21, 0.25);
      glVertex3f(4.5 , 3, 0.25);
    glEnd();


    glBegin(GL_QUADS);
      glVertex3f(4.5 , 21, -0.25);
      glVertex3f(-4.5 , 21, -0.25);
      glVertex3f(-4.5 , 21, 0.25);
      glVertex3f(4.5 , 21, 0.25);
    glEnd();

    glBegin(GL_QUADS);
      glVertex3f(4.5 , 3, -0.25);
      glVertex3f(-4.5 , 3, -0.25);
      glVertex3f(-4.5 , 3, 0.25);
      glVertex3f(4.5 , 3, 0.25);
    glEnd();

    glDisable(GL_BLEND);

  glPopMatrix();
}

void pictures(){

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 83.740,-90);
    glRotatef(90, 0, 1,0);
    
    object1();
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 83.740, 0);
    glRotatef(90, 0, 1,0);
    
    object1();
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 83.740,90);
    glRotatef(90, 0, 1,0);
    
    object1();
    glPopMatrix();
  }


  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 144.5,-90);
    glRotatef(90, 0, 1,0);
    
    object1();
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 144.5, 0);
    glRotatef(90, 0, 1,0);
    
    object1();
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 144.5,90);
    glRotatef(90, 0, 1,0);
    
    object1();
    glPopMatrix();
  }
}

void Timer(int value)
{
    
     x1-=1;
    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
}

// Common Render Items for all subwindows
void renderScene2() { //desenha os objetos

  // Draw ground
  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
    glVertex3f(-1000.0f, 0.0f, -1000.0f);
    glVertex3f(-1000.0f, 0.0f,  1000.0f);
    glVertex3f( 1000.0f, 0.0f,  1000.0f);
    glVertex3f( 1000.0f, 0.0f, -1000.0f);
  glEnd();
  glPopMatrix();
  
  //z = azul
  //y = vermelho
  //x = verde

  //eixos
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
  //eixos

  
  firstFloor();
  secondFloor();
  elevator();
  roof();
  windows();
  support();

  pictures();
  glColor3f(0,0,1);
  glBegin(GL_QUADS);
    glVertex3f(-x1,0,0);
    glVertex3f(x1,0,0);
    glVertex3f(x1,50,0);
    glVertex3f(-x1,50,0);

  glEnd();

  
  

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
  case GLUT_KEY_UP : deltaMove = 20.5f; break;
  case GLUT_KEY_DOWN : deltaMove = -20.5f; break;
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
  glEnable(GL_MULTISAMPLE);
  glEnable ( GL_TEXTURE_2D );
  glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
  
  // register callbacks
  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(pressKey);
  glutSpecialUpFunc(releaseKey);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
  glutTimerFunc(33, Timer, 1);

}

int main(int argc, char **argv) {

  // init GLUT and create main window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
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



