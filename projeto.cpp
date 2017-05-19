#include <stdio.h>
#include <stdlib.h>
#include <math.h>



#include <GL/glut.h>
#include <SFML/Graphics.hpp>
#include <fstream>



int flag = 0;
float angle = 0.0f;
float angley = 0.0f;
int go1 = 0;
int gol2 = 0;

float x1 = 1;
float y2 = 1;

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

GLuint texture_id[20];

void loadTextureFromFile(char const *filename,int index) {
  int width, height, c;
  c = 3;
  std::ifstream file(filename);
  if(! file.good())
    throw "file not found";
  file.close();

sf::Image image;
image.loadFromFile(filename);

    printf("%d %d\n", width, height);

  glGenTextures(1, &texture_id[index]);
  glBindTexture(GL_TEXTURE_2D, texture_id[index]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
  glBindTexture(GL_TEXTURE_2D, 0);
}

void initTextures(){
  loadTextureFromFile("Piso.jpg", 0);
  loadTextureFromFile("concreto.jpg", 1);
  loadTextureFromFile("1.jpg", 2);
  loadTextureFromFile("madeiraEscura.jpg", 3);
  loadTextureFromFile("madeira.jpg", 4);
  loadTextureFromFile("tv.png", 5);
  loadTextureFromFile("ac.png", 6);
  
  
}

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

void computePos(float deltaMove) {

  x += deltaMove * lx * 0.1f;
  z += deltaMove * lz * 0.1f;
  y += deltaMove * ly * 0.1f;
}

void myCube(){
  glPushMatrix();
    
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1);    
      glVertex3f(  0.5, -0.5, -0.5 );      
      glVertex3f(  0.5,  0.5, -0.5 );      
      glVertex3f( -0.5,  0.5, -0.5 );      
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
      glVertex3f(  0.5, -0.5, 0.5 );
      glVertex3f(  0.5,  0.5, 0.5 );
      glVertex3f( -0.5,  0.5, 0.5 );
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glVertex3f( 0.5,  0.5, -0.5 );
      glVertex3f( 0.5,  0.5,  0.5 );
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glVertex3f(  0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glVertex3f(  0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
  glPopMatrix();
}

void firstFloor(){
  glPushMatrix();
  
    glColor4f(1, 1, 1 , 0);
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_QUADS);
    
    
      glNormal3f(0,-1,0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f( -370, 79, -150);

      glTexCoord2f(0.0f, 1.0f);
      glVertex3f( -370, 79, 150);

      glTexCoord2f(0.894594595, 1.0f);
      glVertex3f( 292, 79, 150);

      glTexCoord2f(0.894594595, 0.0f);
      glVertex3f( 292, 79, -150);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

  glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

    glTexCoord2f(0.894594595, 0.633333333);
    glVertex3f( 292, 79, 40.236);

     glTexCoord2f(0.894594595, 1.0f);
    glVertex3f( 292, 79, 150);

     glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 370, 79, 150);

     glTexCoord2f(1.0f, 0.633333333);
    glVertex3f( 370, 79, 40.236);

     
  glEnd();

  

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

    glTexCoord2f(1,0.633333333);
    glVertex3f( 370, 79, 40.236);

    glTexCoord2f(0.948648649,0.633333333);
    glVertex3f( 332, 79, 40.236);

    glTexCoord2f(0.948648649,0);
    glVertex3f( 332, 79, -150);


    glTexCoord2f(1,0);
    glVertex3f( 370, 79, -150);

  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
      glNormal3f(0,-1,0);
    glTexCoord2f(0.948648649,0);
    glVertex3f( 332, 79, -150);

    glTexCoord2f(0.948648649,0.07093);
    glVertex3f( 332, 79, -128.721);

    glTexCoord2f(0.894594595,0.07093);
    glVertex3f( 292, 79, -128.721);

    glTexCoord2f(0.894594595,0);
    glVertex3f( 292, 79, -150);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

    glTexCoord2f(0.948648649,0.204263333);
    glVertex3f( 332, 79, -88.721);
    glTexCoord2f(0.894594595,0.204263333);
    glVertex3f( 292, 79, -88.721);
    glTexCoord2f(0.894594595,0.321733333);
    glVertex3f( 292, 79, -53.48);
    glTexCoord2f(0.948648649,0.321733333);
    glVertex3f( 332, 79, -53.48);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  
  //
  
    glColor4f(1, 1, 1 , 0);
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_QUADS);
    
    
      glNormal3f(0,-1,0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f( -370, 83.740, -150);

      glTexCoord2f(0.0f, 1.0f);
      glVertex3f( -370, 83.740, 150);

      glTexCoord2f(0.894594595, 1.0f);
      glVertex3f( 292, 83.740, 150);

      glTexCoord2f(0.894594595, 0.0f);
      glVertex3f( 292, 83.740, -150);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);

  glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

    glTexCoord2f(0.894594595, 0.633333333);
    glVertex3f( 292, 83.740, 40.236);

     glTexCoord2f(0.894594595, 1.0f);
    glVertex3f( 292, 83.740, 150);

     glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 370, 83.740, 150);

     glTexCoord2f(1.0f, 0.633333333);
    glVertex3f( 370, 83.740, 40.236);

     
  glEnd();

  

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

    glTexCoord2f(1,0.633333333);
    glVertex3f( 370, 83.740, 40.236);

    glTexCoord2f(0.948648649,0.633333333);
    glVertex3f( 332, 83.740, 40.236);

    glTexCoord2f(0.948648649,0);
    glVertex3f( 332, 83.740, -150);


    glTexCoord2f(1,0);
    glVertex3f( 370, 83.740, -150);

  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
      glNormal3f(0,-1,0);
    glTexCoord2f(0.948648649,0);
    glVertex3f( 332, 83.740, -150);

    glTexCoord2f(0.948648649,0.07093);
    glVertex3f( 332, 83.740, -128.721);

    glTexCoord2f(0.894594595,0.07093);
    glVertex3f( 292, 83.740, -128.721);

    glTexCoord2f(0.894594595,0);
    glVertex3f( 292, 83.740, -150);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

    glTexCoord2f(0.948648649,0.204263333);
    glVertex3f( 332, 83.740, -88.721);
    glTexCoord2f(0.894594595,0.204263333);
    glVertex3f( 292, 83.740, -88.721);
    glTexCoord2f(0.894594595,0.321733333);
    glVertex3f( 292, 83.740, -53.48);
    glTexCoord2f(0.948648649,0.321733333);
    glVertex3f( 332, 83.740, -53.48);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);

  
  

  //
  glColor3f(1,1.,1);
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  
  glBegin(GL_QUADS);
    glNormal3f(0,0,1);

    glTexCoord2f(0,0);
    glVertex3f( -370, 79, 150);

    glTexCoord2f(0,1);
    glVertex3f( 370, 79, 150);

    glTexCoord2f(1,1);
    glVertex3f( 370, 83.740, 150);

    glTexCoord2f(1,0);
    glVertex3f( -370, 83.740, 150);
    
  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
    glNormal3f(0,0,-1);

    glTexCoord2f(0,0);
    glVertex3f( -370, 79, -150);

    glTexCoord2f(0,1);
    glVertex3f( 370, 79, -150);

    glTexCoord2f(1,1);
    glVertex3f( 370, 83.740, -150);

    glTexCoord2f(1,0);
    glVertex3f( -370, 83.740, -150);
    
  glEnd();

  
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);

    glTexCoord2f(0,0);
    glVertex3f( -370, 79, 150);
    glTexCoord2f(0,1);
    glVertex3f( -370, 79, -150);
    glTexCoord2f(1,1);
    glVertex3f( -370, 83.740, -150);
    glTexCoord2f(1,0);
    glVertex3f( -370, 83.740, 150);
    
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
    glTexCoord2f(0,0);
    glVertex3f( 370, 79, 150);
    glTexCoord2f(0,1);
    glVertex3f( 370, 79, -150);
    glTexCoord2f(1,1);
    glVertex3f( 370, 83.740, -150);
    glTexCoord2f(1,0);
    glVertex3f( 370, 83.740, 150);
    
  glEnd();
  glBindTexture(GL_TEXTURE_2D,0);

  //

  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glBegin(GL_QUADS);
  glNormal3f(0,0,-1);
    glTexCoord2f(0,0);
    glVertex3f(332, 79,40.236);
    glTexCoord2f(0,1);
    glVertex3f(292, 79,40.236);
    glTexCoord2f(1,1);
    glVertex3f(292, 83.740,40.236);
    glTexCoord2f(1,0);
    glVertex3f(332, 83.740,40.236);

  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
    glVertex3f(332, 79, -53.48);
    glTexCoord2f(0,1);
    glVertex3f(292, 79, -53.48);
    glTexCoord2f(1,1);
    glVertex3f(292, 83.740, -53.48);
    glTexCoord2f(1,0);
    glVertex3f(332, 83.740, -53.48);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
    glVertex3f(292, 79, -53.48);
    glTexCoord2f(0,1);
    glVertex3f(292, 79, 40.236);
    glTexCoord2f(1,1);
    glVertex3f(292, 83.740, 40.236);
    glTexCoord2f(1,0);
    glVertex3f(292, 83.740, -53.48);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
  glTexCoord2f(0,0);
    glVertex3f(332, 79, -53.48);
    glTexCoord2f(0,1);
    glVertex3f(332, 79, 40.236);
    glTexCoord2f(1,1);
    glVertex3f(332, 83.740, 40.236);
    glTexCoord2f(1,0);
    glVertex3f(332, 83.740, -53.48);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);


  /*
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
  */

  glPopMatrix();
}

void secondFloor(){ 
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

      glTexCoord2f(0,0);
      glVertex3f( -370, 143.5, -150);

      glTexCoord2f(0,1);
      glVertex3f( -370, 143.5, 150);

      glTexCoord2f(0.841931081,1);
      glVertex3f( 253.029, 143.5, 150);

      glTexCoord2f(0.841931081,0);
      glVertex3f( 253.029, 143.5, -150);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.841931081,1);
      glVertex3f(253.029, 143.5, 150);
      glTexCoord2f(0.841931081,0.647453333);
      glVertex3f(253.029, 143.5, 44.236);
      glTexCoord2f(1,0.647453333);
      glVertex3f(370, 143.5, 44.236);
      glTexCoord2f(1,1);
      glVertex3f(370, 143.5, 150);

    glEnd();

    glBegin(GL_QUADS);
      glNormal3f(0,-1,0);

      glTexCoord2f(0.895985135,0.647453333);
      glVertex3f(293.029,143.5,44.236);
      glTexCoord2f(1,0.647453333);
      glVertex3f(370,143.5,44.236);
      glTexCoord2f(1,0.335066667);
      glVertex3f(370,143.5, -49.48);
      glTexCoord2f(0.895985135,0.335066667);
      glVertex3f(293.029,143.5, -49.48);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.841931081,0);
      glVertex3f( 253.029, 143.5, -150);

      glTexCoord2f(0.841931081,0.07093);
      glVertex3f( 253.029, 143.5, -128.721);

      glTexCoord2f(1,0.07093);
      glVertex3f( 370, 143.5, -128.721);

      glTexCoord2f(1,0);
      glVertex3f( 370, 143.5, -150);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.948648649,0.07093);
      glVertex3f( 332, 143.5, -128.721);
      glTexCoord2f(1,0.07093);
      glVertex3f( 370, 143.5, -128.721);
      glTexCoord2f(1,0.335066667);
      glVertex3f( 370, 143.5, -49.48);
      glTexCoord2f(0.948648649,0.335066667);
      glVertex3f( 332, 143.5, -49.48);
    glEnd();

   
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

      glTexCoord2f(0.841931081,0.204263333);
      glVertex3f( 253.029, 143.5, -88.721);
      glTexCoord2f(0.948648649,0.204263333);
      glVertex3f( 332, 143.5, -88.721);
      glTexCoord2f(0.948648649,0.335066667);
      glVertex3f( 332.029, 143.5, -49.48);
      glTexCoord2f(0.841931081,0.335066667);
      glVertex3f( 253.029, 143.5, -49.48);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.841931081,0.07093);
      glVertex3f( 253.029, 143.5, -128.721);
      glTexCoord2f(0.841931081,0.204263333);
      glVertex3f( 253.029, 143.5, -88.721);
      glTexCoord2f(0.894594595,0.204263333);
      glVertex3f( 292, 143.5, -88.721);
      glTexCoord2f(0.894594595,0.07093);
      glVertex3f( 292, 143.5, -128.721);
      
    glEnd();
    //
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

      glTexCoord2f(0,0);
      glVertex3f( -370, 144.5, -150);

      glTexCoord2f(0,1);
      glVertex3f( -370, 144.5, 150);

      glTexCoord2f(0.841931081,1);
      glVertex3f( 253.029, 144.5, 150);

      glTexCoord2f(0.841931081,0);
      glVertex3f( 253.029, 144.5, -150);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.841931081,1);
      glVertex3f(253.029, 144.5, 150);
      glTexCoord2f(0.841931081,0.647453333);
      glVertex3f(253.029, 144.5, 44.236);
      glTexCoord2f(1,0.647453333);
      glVertex3f(370, 144.5, 44.236);
      glTexCoord2f(1,1);
      glVertex3f(370, 144.5, 150);

    glEnd();

    glBegin(GL_QUADS);
      glNormal3f(0,-1,0);

      glTexCoord2f(0.895985135,0.647453333);
      glVertex3f(293.029,144.5,44.236);
      glTexCoord2f(1,0.647453333);
      glVertex3f(370,144.5,44.236);
      glTexCoord2f(1,0.335066667);
      glVertex3f(370,144.5, -49.48);
      glTexCoord2f(0.895985135,0.335066667);
      glVertex3f(293.029,144.5, -49.48);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.841931081,0);
      glVertex3f( 253.029, 144.5, -150);

      glTexCoord2f(0.841931081,0.07093);
      glVertex3f( 253.029, 144.5, -128.721);

      glTexCoord2f(1,0.07093);
      glVertex3f( 370, 144.5, -128.721);

      glTexCoord2f(1,0);
      glVertex3f( 370, 144.5, -150);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.948648649,0.07093);
      glVertex3f( 332, 144.5, -128.721);
      glTexCoord2f(1,0.07093);
      glVertex3f( 370, 144.5, -128.721);
      glTexCoord2f(1,0.335066667);
      glVertex3f( 370, 144.5, -49.48);
      glTexCoord2f(0.948648649,0.335066667);
      glVertex3f( 332, 144.5, -49.48);
    glEnd();

   
    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);

      glTexCoord2f(0.841931081,0.204263333);
      glVertex3f( 253.029, 144.5, -88.721);
      glTexCoord2f(0.948648649,0.204263333);
      glVertex3f( 332, 144.5, -88.721);
      glTexCoord2f(0.948648649,0.335066667);
      glVertex3f( 332.029, 144.5, -49.48);
      glTexCoord2f(0.841931081,0.335066667);
      glVertex3f( 253.029, 144.5, -49.48);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0,-1,0);
      glTexCoord2f(0.841931081,0.07093);
      glVertex3f( 253.029, 144.5, -128.721);
      glTexCoord2f(0.841931081,0.204263333);
      glVertex3f( 253.029, 144.5, -88.721);
      glTexCoord2f(0.894594595,0.204263333);
      glVertex3f( 292, 144.5, -88.721);
      glTexCoord2f(0.894594595,0.07093);
      glVertex3f( 292, 144.5, -128.721);
      
    glEnd();
    
    //
    

    
    glBegin(GL_QUADS);
    glNormal3f(0,0,1);
      glTexCoord2f(0,0);
      glVertex3f( -370, 143.5, 150);
      glTexCoord2f(0,1);
      glVertex3f( 370, 143.5, 150);
      glTexCoord2f(1,0);
      glVertex3f( 370, 144.5, 150);
      glTexCoord2f(1,1);
      glVertex3f( -370, 144.5, 150);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0,0);
      glVertex3f( -370, 143.5, -150);
      glTexCoord2f(0,1);
      glVertex3f( 370, 143.5, -150);
      glTexCoord2f(1,0);
      glVertex3f( 370, 144.5, -150);
      glTexCoord2f(1,1);
      glVertex3f( -370, 144.5, -150);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(-1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( -370, 143.5, -150);
      glTexCoord2f(0,1);
      glVertex3f( -370, 143.5, 150);
      glTexCoord2f(1,0);
      glVertex3f( -370, 144.5, 150);
      glTexCoord2f(1,1);
      glVertex3f( -370, 144.5, -150);
    glEnd();

    
    glBegin(GL_QUADS);
    glNormal3f(1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( 370, 143.5, -150);
      glTexCoord2f(0,1);
      glVertex3f( 370, 143.5, 150);
      glTexCoord2f(1,0);
      glVertex3f( 370, 144.5, 150);
      glTexCoord2f(1,1);
      glVertex3f( 370, 144.5, -150);
    glEnd();

    //
     /* 
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
  */

  //
  glBegin(GL_QUADS);
  glNormal3f(0,0,-1);
    glTexCoord2f(0,0);
    glVertex3f(293.029, 143.5, 44.236);
    glTexCoord2f(0,1);
    glVertex3f(253.029, 143.5, 44.236);
    glTexCoord2f(1,0);
    glVertex3f(253.029, 144.5, 44.236);
    glTexCoord2f(1,1);
    glVertex3f(293.029, 144.5, 44.236);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
    glVertex3f(293.029, 143.5, -49.48);
    glTexCoord2f(0,1);
    glVertex3f(253.029, 143.5, -49.48);
    glTexCoord2f(1,1);
    glVertex3f(253.029, 144.5, -49.48);
    glTexCoord2f(1,0);
    glVertex3f(293.029, 144.5, -49.48);
  glEnd();


  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
    glTexCoord2f(0,0);
    glVertex3f(253.029, 143.5, 44.236);
    glTexCoord2f(0,1);
    glVertex3f(253.029, 143.5, -49.48);
    glTexCoord2f(1,0);
    glVertex3f(253.029, 144.5, -49.48);
    glTexCoord2f(1,1);
    glVertex3f(253.029, 144.5, 44.236);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(-1,0,0);
  glTexCoord2f(0,0);
    glVertex3f(293.029, 143.5, 44.236);
    glTexCoord2f(0,1);
    glVertex3f(293.029, 143.5, -49.48);
    glTexCoord2f(1,0);
    glVertex3f(293.029, 144.5, -49.48);
    glTexCoord2f(1,1);
    glVertex3f(293.029, 144.5, 44.236);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
  //
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
  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(292, 0, -90.721);
    glVertex3f(292, 0, -88.721);
    glVertex3f(292, 203, -88.721);
    glVertex3f(292, 203, -90.721);
  glEnd();

  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.3);
  glBegin(GL_QUADS);
    glVertex3f( 292, 40,-90.721);
    glVertex3f( 292, 79,-90.721);
    glVertex3f( 292, 79,-126.721);
    glVertex3f( 292, 40,-126.721);
  glEnd();
  glDisable(GL_BLEND);

  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(332, 0, -128.721);
    glVertex3f(332, 0, -126.721);
    glVertex3f(332, 203, -126.721);
    glVertex3f(332, 203, -128.721);
  glEnd();

  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(332, 0, -90.721);
    glVertex3f(332, 0, -88.721);
    glVertex3f(332, 203, -88.721);
    glVertex3f(332, 203, -90.721);
  glEnd();

  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.3);
  glBegin(GL_QUADS);
    glVertex3f( 332, 0,-90.721);
    glVertex3f( 332, 79,-90.721);
    glVertex3f( 332, 79,-126.721);
    glVertex3f( 332, 0,-126.721);
  glEnd();

  glDisable(GL_BLEND);

  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(332, 0, -128.721);
    glVertex3f(330, 0, -128.721);
    glVertex3f(330, 203, -128.721);
    glVertex3f(332, 203, -128.721);
  glEnd();

  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(294, 0, -128.721);
    glVertex3f(292, 0, -128.721);
    glVertex3f(292, 203, -128.721);
    glVertex3f(294, 203, -128.721);
  glEnd();

  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.3);

  glBegin(GL_QUADS);
    glVertex3f(294, 0, -128.721);
    glVertex3f(330, 0, -128.721);
    glVertex3f(330, 203, -128.721);
    glVertex3f(294, 203, -128.721);
  glEnd();

  glDisable(GL_BLEND);

  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(332, 0, -88.721);
    glVertex3f(330, 0, -88.721);
    glVertex3f(330, 203, -88.721);
    glVertex3f(332, 203, -88.721);
  glEnd();

  glColor3f(0,0,0);
  glBegin(GL_QUADS);
    glVertex3f(294, 0, -88.721);
    glVertex3f(292, 0, -88.721);
    glVertex3f(292, 203, -88.721);
    glVertex3f(294, 203, -88.721);
  glEnd();

  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.3);
  glBegin(GL_QUADS);
    glVertex3f(294, 0, -88.721);
    glVertex3f(330, 0, -88.721);
    glVertex3f(330, 203, -88.721);
    glVertex3f(294, 203, -88.721);
  glEnd();

  glDisable(GL_BLEND);

  //porta do elevador

  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0,0,0,0.2);
  glBegin(GL_QUADS);
    glVertex3f(292, 0, -90.721);
    glVertex3f(292, 0, -108.621 + x1);
    glVertex3f(292, 40, -108.621 + x1);
    glVertex3f(292, 40, -90.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(293, 0, -90.721);
    glVertex3f(293, 0, -108.621 + x1);
    glVertex3f(293, 40, -108.621 + x1);
    glVertex3f(293, 40, -90.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(292, 0, -108.621 + x1);
    glVertex3f(292, 40, -108.621 + x1);
    glVertex3f(293, 40, -108.621 + x1);
    glVertex3f(293, 0, -108.621 + x1);
  glEnd();






  glBegin(GL_QUADS);
    glVertex3f(292, 0, -126.721);
    glVertex3f(292, 0, -108.721 - x1);
    glVertex3f(292, 40, -108.721 - x1);
    glVertex3f(292, 40, -126.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(293, 0, -126.721);
    glVertex3f(293, 0, -108.721 - x1);
    glVertex3f(293, 40, -108.721 - x1);
    glVertex3f(293, 40, -126.721);
  glEnd();

  glBegin(GL_QUADS);
    glVertex3f(292, 0, -108.721 - x1);
    glVertex3f(292, 40, -108.721 - x1);
    glVertex3f(293, 40, -108.721 - x1);
    glVertex3f(293, 0, -108.721 - x1);
  glEnd();

  glDisable(GL_BLEND);

  //porta do elevador

  glColor3f(0, 1,0);
  glBegin(GL_QUADS);
  glVertex3f(294, y2, -128.521);
  glVertex3f(332, y2, -128.521);
  glVertex3f(332, y2, -89.521);
  glVertex3f(294, y2, -89.521);

  glEnd();

  


  glPopMatrix();

}

void roof(){
  glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f( -370, 203, -150);
    glTexCoord2f(0,1);
    glVertex3f( -370, 203, 150);
    glTexCoord2f(1,0);
    glVertex3f( 370, 203, 150);
    glTexCoord2f(1,1);
    glVertex3f( 370, 203, -150);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex3f( -370, 223, -150);
    glTexCoord2f(0,1);
    glVertex3f( -370, 223, 150);
    glTexCoord2f(1,0);
    glVertex3f( 370, 223, 150);
    glTexCoord2f(1,1);
    glVertex3f( 370, 223, -150);
    glEnd();

    
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
      glVertex3f( -370, 203, -150);
      glTexCoord2f(0,1);
      glVertex3f( -370, 203,150);
      glTexCoord2f(1,0);
      glVertex3f( -370, 223, 150);
      glTexCoord2f(1,1);
      glVertex3f( -370, 223, -150);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
      glVertex3f( 370, 203, -150);
      glTexCoord2f(0,1);
      glVertex3f( 370, 203,150);
      glTexCoord2f(1,0);
      glVertex3f( 370, 223, 150);
      glTexCoord2f(1,1);
      glVertex3f( 370, 223, -150);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
      glVertex3f( -370, 203, -150);
      glTexCoord2f(0,1);
      glVertex3f( 370, 203, -150);
      glTexCoord2f(1,0);
      glVertex3f( 370, 223, -150);
      glTexCoord2f(1,1);
      glVertex3f( -370, 223, -150);
    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
      glVertex3f( -370, 203, 150);
      glTexCoord2f(0,1);
      glVertex3f( 370, 203, 150);
      glTexCoord2f(1,0);
      glVertex3f( 370, 223, 150);
      glTexCoord2f(1,1);
      glVertex3f( -370, 223, 150);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();

}

void windows(){
  glPushMatrix();

    float f = -370;
    glColor3f(1,1,1);
    for(int i = 0; i < 60; i++){
      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 83.740, 150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,150);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 83.740, 150);
        glTexCoord2f(0,1);
        glVertex3f(f, 83.740,149);
        glTexCoord2f(1,0);
        glVertex3f(f,143.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f + 1, 83.740, 150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 83.740,149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,143.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 83.740, 149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,149);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, 0);

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

      

      
      f+= 12.317;
    }
    //
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
   
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 83.740, 150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,150);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 83.740, 149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,149);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f + 1, 83.740, 150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 83.740,149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,143.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,143.5,150);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,0);
  glPopMatrix();
  //







  






  float z = 137.7;
  glColor3f( 1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(-370, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(-370, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-370,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-370,143.5,z);
      glEnd();

      z -= 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  
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

  
  z = -137.7;
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-370, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(-370, 83.740,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(-370,143.5, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(-370,143.5,z);
      glEnd();

      z += 12.3;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(-370, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(-370, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-370,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-370,143.5,z);
      glEnd();

      z -= 12.42;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);

  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-369, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(-369, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-369,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-369,143.5,z);
      glEnd();

      z -= 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
        glVertex3f(-369, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(-369, 83.740,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(-369,143.5, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(-369,143.5,z);
      glEnd();

      z += 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-369, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(-369, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-369,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-369,143.5,z);
      glEnd();

      z -= 12.42;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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

  
  
  z = 137.7;
  glColor3f( 1, 1, 1);
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(370, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(370, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(370,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(370,143.5,z);
      glEnd();

      z -= 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  
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

  
  z = -137.7;
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(370, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(370, 83.740,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(370,143.5, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(370,143.5,z);
      glEnd();

      z += 12.3;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(370, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(370, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(370,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(370,143.5,z);
      glEnd();

      z -= 12.42;
  }

  glBindTexture(GL_TEXTURE_2D, 0);

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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);

  z = 137.7;
  glColor3f( 0.1, 0.4, 1);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(369, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(369, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(369,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(369,143.5,z);
      glEnd();

      z -= 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);

  glColor3f( 0.1, 0.4, 1);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
        glVertex3f(369, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(369, 83.740,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(369,143.5, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(369,143.5,z);
      glEnd();

      z += 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);

  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(369, 83.740, z);
        glTexCoord2f(0,1);
        glVertex3f(369, 83.740,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(369,143.5, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(369,143.5,z);
      glEnd();

      z -= 12.42;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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
  
  
  //
  
  




  z = 137.7;
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(-370, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(-370, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-370,203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-370,203,z);
      glEnd();

      z -= 12.3;
  }

  glBindTexture(GL_TEXTURE_2D, 0);


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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(-370, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(-370, 144.5,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(-370, 203, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(-370, 203,z);
      glEnd();

      z += 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-370, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(-370, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-370, 203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-370, 203,z);
      glEnd();

      z -= 12.42;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  z = 137.7;
  
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-369, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(-369, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-369,203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-369,203,z);
      glEnd();

      z -= 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-369, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(-369, 144.5,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(-369,203, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(-369,203,z);
      glEnd();

      z += 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(-369, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(-369, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(-369,203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(-369,203,z);
      glEnd();

      z -= 12.42;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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

  //////
  z = 137.7;
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(370, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(370, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(370,203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(370,203,z);
      glEnd();

      z -= 12.3;
  }

  glBindTexture(GL_TEXTURE_2D, 0);


  z = 150;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 144.5, z - 1);
        glVertex3f(370, 144.5, z - 12.3);
        glVertex3f(370,203, z - 12.3);
        glVertex3f(370,203, z - 1);
      glEnd();

      z -= 12.3;
  }
  glDisable(GL_BLEND);

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(370, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(370, 144.5,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(370, 203, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(370, 203,z);
      glEnd();

      z += 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glColor3f( 0.1, 0.4, 1);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(370, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(370, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(370, 203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(370, 203,z);
      glEnd();

      z -= 12.42;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(370, 144.5, z - 1);
        glVertex3f(370, 144.5,z - 12.42);
        glVertex3f(370,203, z - 12.42);
        glVertex3f(370,203,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  z = 137.7;
  
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(369, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(369, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(369,203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(369,203,z);
      glEnd();

      z -= 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);
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
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  
  z = -137.7;
  for(int i = 0; i < 4; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(369, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(369, 144.5,z + 1);
        glTexCoord2f(1,0);
        glVertex3f(369,203, z + 1);
        glTexCoord2f(1,1);
        glVertex3f(369,203,z);
      glEnd();

      z += 12.3;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

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

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  z = 75;
  for(int i = 0; i < 13; i++){
    glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(369, 144.5, z);
        glTexCoord2f(0,1);
        glVertex3f(369, 144.5,z - 1);
        glTexCoord2f(1,0);
        glVertex3f(369,203, z - 1);
        glTexCoord2f(1,1);
        glVertex3f(369,203,z);
      glEnd();

      z -= 12.42;
  }
  glBindTexture(GL_TEXTURE_2D, 0);

  z = 75;
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(1,1,1,0.7);
  for(int i = 0; i < 12; i++){
    glBegin(GL_QUADS);
        glVertex3f(369, 144.5, z - 1);
        glVertex3f(369, 144.5,z - 12.42);
        glVertex3f(369,203, z - 12.42);
        glVertex3f(369,203,z - 1);
      glEnd();

      z -= 12.42;
  }
  glDisable(GL_BLEND);
  //////
  //
  
  




  //

  glPushMatrix();

    f = -370;

    for(int i = 0; i < 60; i++){
      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      
      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 144.5, 150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,150);
        glTexCoord2f(1,1);
        glVertex3f(f,203,150);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 144.5, 150);
        glTexCoord2f(0,1);
        glVertex3f(f, 144.5,149);
        glTexCoord2f(1,0);
        glVertex3f(f,203,149);
        glTexCoord2f(1,1);
        glVertex3f(f,203,150);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f + 1, 203, 150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 203,149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,144.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,144.5,150);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

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

      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 144.5, 149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,149);
        glTexCoord2f(1,1);
        glVertex3f(f,203,149);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

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
    
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
    
      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 144.5, 150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,150);
        glTexCoord2f(1,1);
        glVertex3f(f,203,150);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 144.5, 149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,149);
        glTexCoord2f(1,1);
        glVertex3f(f,203,149);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f + 1, 144.5, 150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 144.5,149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,203,149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,203,150);
      glEnd();

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);

  f = -370;

    for(int i = 0; i < 60; i++){
      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      
      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 144.5, -150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,-150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,-150);
        glTexCoord2f(1,1);
        glVertex3f(f,203,-150);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 144.5, -150);
        glTexCoord2f(0,1);
        glVertex3f(f, 144.5,-149);
        glTexCoord2f(1,0);
        glVertex3f(f,203,-149);
        glTexCoord2f(1,1);
        glVertex3f(f,203,-150);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f + 1, 203, -150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 203,-149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,144.5,-149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,144.5,-150);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

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

      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 144.5, -149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,-149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,-149);
        glTexCoord2f(1,1);
        glVertex3f(f,203,-149);
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);

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
    
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
    
      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 144.5, -150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,-150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,-150);
        glTexCoord2f(1,1);
        glVertex3f(f,203,-150);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 144.5, -149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 144.5,-149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,203,-149);
        glTexCoord2f(1,1);
        glVertex3f(f,203,-149);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f + 1, 144.5, -150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 144.5,-149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,203,-149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,203,-150);
      glEnd();

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
  
  //
    f = -370;
    glColor3f(1,1,1);
    for(int i = 0; i < 60; i++){
      glBindTexture(GL_TEXTURE_2D, texture_id[3]);
      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 83.740, -150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,-150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,-150);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,-150);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 83.740, -150);
        glTexCoord2f(0,1);
        glVertex3f(f, 83.740,-149);
        glTexCoord2f(1,0);
        glVertex3f(f,143.5,-149);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,-150);
      glEnd();

      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f + 1, 83.740, -150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 83.740,-149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,143.5,-149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,143.5,-150);
      glEnd();

      glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(f, 83.740, -149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,-149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,-149);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,-149);
      glEnd();

      glBindTexture(GL_TEXTURE_2D, 0);

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

      

      
      f+= 12.317;
    }
    //
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
   
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 83.740, 150);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,150);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,150);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,150);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f, 83.740, 149);
        glTexCoord2f(0,1);
        glVertex3f(f+1, 83.740,149);
        glTexCoord2f(1,0);
        glVertex3f(f+1,143.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f,143.5,149);
      glEnd();

      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(f + 1, 83.740, 150);
        glTexCoord2f(0,1);
        glVertex3f(f + 1, 83.740,149);
        glTexCoord2f(1,0);
        glVertex3f(f + 1,143.5,149);
        glTexCoord2f(1,1);
        glVertex3f(f + 1,143.5,150);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,0);
  glPopMatrix();
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

void object1(int i){
  glPushMatrix();
  glColor3f(1,1,1);
    glBegin(GL_QUADS);
      glVertex3f(-1.5 , 0, -2.5);
      glVertex3f(1.5 , 0, -2.5);
      glVertex3f(1.5 , 0, 2.5);
      glVertex3f(-1.5 , 0, 2.5);
    glEnd();
    //
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex3f(-1.5 , 0, -2.5);
      glTexCoord2f(0.928571429,0);
      glVertex3f(-1.5 , 3, -2.5);
      glTexCoord2f(0.928571429,1);
      glVertex3f(-1.5 , 3, 2.5);
      glTexCoord2f(0,1);
      glVertex3f(-1.5 , 0, 2.5);
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex3f(1.5 , 0, -2.5);
      glTexCoord2f(0.928571429,0);
      glVertex3f(1.5 , 3, -2.5);
      glTexCoord2f(0.928571429,1);
      glVertex3f(1.5 , 3, 2.5);
      glTexCoord2f(0,1);
      glVertex3f(1.5 , 0, 2.5);
    glEnd();

    
    glColor3f(1,1,1);
    glBegin(GL_QUADS);
      glTexCoord2f(0.928571429,0);
      glVertex3f(-1.5 , 3, -2.5);
      glTexCoord2f(1,0);
      glVertex3f(-1.5 , 3.5, -2.5);
      glTexCoord2f(1, 0.45);
      glVertex3f(-1.5 , 3.5, -0.25);
      glTexCoord2f(0.928571429, 0.45);
      glVertex3f(-1.5 , 3, -0.25);
    glEnd();
    glBegin(GL_QUADS);
      glTexCoord2f(0.928571429,0);
      glVertex3f(1.5 , 3, -2.5);
      glTexCoord2f(1,0);
      glVertex3f(1.5 , 3.5, -2.5);
      glTexCoord2f(1, 0.45);
      glVertex3f(1.5 , 3.5, -0.25);
      glTexCoord2f(0.928571429, 0.45);
      glVertex3f(1.5 , 3, -0.25);
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(0.928571429,1);
      glVertex3f(1.5 , 3, 2.5);
      glTexCoord2f(1,1);
      glVertex3f(1.5 , 3.5, 2.5);
      glTexCoord2f(1,0.55);
      glVertex3f(1.5 , 3.5, 0.25);
      glTexCoord2f(0.928571429,0.55);
      glVertex3f(1.5 , 3, 0.25);
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(0.928571429,1);
      glVertex3f(-1.5 , 3, 2.5);
      glTexCoord2f(1,1);
      glVertex3f(-1.5 , 3.5, 2.5);
      glTexCoord2f(1,0.55);
      glVertex3f(-1.5 , 3.5, 0.25);
      glTexCoord2f(0.928571429,0.55);
      glVertex3f(-1.5 , 3, 0.25);
    glEnd();

    
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
      glVertex3f(-1.5 , 3.5, -2.5);
      glTexCoord2f(0,1);
      glVertex3f(-1.5 , 3.5, -0.25);
      glTexCoord2f(1,0);
      glVertex3f(1.5 , 3.5, -0.25);
      glTexCoord2f(1,1);
      glVertex3f(1.5 , 3.5, -2.5);
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex3f(-1.5 , 3.5, 0.25);
      glTexCoord2f(0,1);
      glVertex3f(-1.5 , 3.5, 2.5);
      glTexCoord2f(1,0);
      glVertex3f(1.5 , 3.5, 2.5);
      glTexCoord2f(1,1);
      glVertex3f(1.5 , 3.5, 0.25);
    glEnd();

   

    

    

    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex3f(-1.5 , 0, -2.5);
      glTexCoord2f(0,1);
      glVertex3f(-1.5 , 3.5, -2.5);
      glTexCoord2f(1,0);
      glVertex3f(1.5 , 3.5, -2.5);
      glTexCoord2f(1,1);
      glVertex3f(1.5 , 0, -2.5);
    glEnd();

    glBegin(GL_QUADS);
      glTexCoord2f(0,0);
      glVertex3f(-1.5 , 0, 2.5);
      glTexCoord2f(0,1);
      glVertex3f(-1.5 , 3.5, 2.5);
      glTexCoord2f(1,0);
      glVertex3f(1.5 , 3.5, 2.5);
      glTexCoord2f(1,1);
      glVertex3f(1.5 , 0, 2.5);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
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

    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    glBegin(GL_QUADS);
      glTexCoord2f(0,1);
      glVertex3f(-3.5 , 6, 0.28);
      glTexCoord2f(0,0);
      glVertex3f(-3.5 , 18, 0.28);
      glTexCoord2f(1,0);
      glVertex3f(3.5 , 18, 0.28);
      glTexCoord2f(1,1);
      glVertex3f(3.5 , 6, 0.28);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

  glPopMatrix();
}

void pictures(){

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 83.740,-90);
    glRotatef(90, 0, 1,0);
    
    object1(i);
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 83.740, 0);
    glRotatef(90, 0, 1,0);
    
    object1(i);
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 83.740,90);
    glRotatef(90, 0, 1,0);
    
    object1(i);
    glPopMatrix();
  }


  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 144.5,-90);
    glRotatef(90, 0, 1,0);
    
    object1(i);
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 144.5, 0);
    glRotatef(90, 0, 1,0);
    
    object1(i);
    glPopMatrix();
  }

  for(int i = -300; i < 200; i+= 50){
    glPushMatrix();
    glTranslatef(i, 144.5,90);
    glRotatef(90, 0, 1,0);
    
    object1(i);
    glPopMatrix();
  }
}

void ladder(){
  glPushMatrix();
    
      glBindTexture(GL_TEXTURE_2D, texture_id[1]);
      glColor3f(1,1,1);
      glBegin(GL_QUADS);
      glTexCoord2f(0,0);
        glVertex3f(292, 79, -53.48);
        glTexCoord2f(0,1);
        glVertex3f(332, 79, -53.48);
        glTexCoord2f(1,0);
        glVertex3f(332, 79, -48.986);
        glTexCoord2f(1,1);
        glVertex3f(292, 79, -48.986);
      glEnd();
      glBindTexture(GL_TEXTURE_2D,0);

      

      int i; 
      for(i = 0; i < 29; i++){
        glPushMatrix();
          
          glTranslatef(292 + 20, 82.95 - i*1.580, -53.48 + i*2.247);
          glScalef(40, 1.580, 4.494);
          ///
          glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
          ///

        glPopMatrix();
    }

        glPushMatrix();
          
          glTranslatef(292 + 20, 82.95 - 28*1.580 , -53.48 + 29*2.247 + 20);
          glScalef(40, 1.580, 40);
                glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
        glPopMatrix();



   glPushMatrix();
   glRotatef(-90, 0, 1, 0);
   glTranslatef(28*1.1235,0,-292 + 2.247);
    for(i = 0; i < 24; i++){
        glPushMatrix();
          
          glTranslatef(0, 82.95 -( 29 + i)*1.580, 0 + i*2.247);
          glScalef(40, 1.580, 4.494);
          ///
                glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
          ///
        glPopMatrix();
    }
    glPopMatrix();




    glPushMatrix();
    glRotatef(180, 0,1,0);
    glTranslatef(-273,0,-41.9);
    for(i = 0; i < 20; i++){
        glPushMatrix();
          
          glTranslatef(0, 143.5 - i*1.580, 0 + i*2.247);
          glScalef(40, 1.580, 4.494);
          ///
                    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
          ///
        glPopMatrix();
    }
    glPopMatrix();

    
    glPushMatrix();
    glRotatef(180, 0,1,0);
    glTranslatef(-273,0,-41.9);
   
          glTranslatef(-20, 143.5 - 20*1.580, 20 + 20*2.247);
          glScalef(80, 1.580, 40);
                glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
    glPopMatrix();

    

    
    glPushMatrix();
    glTranslatef(312, 0, 7*(2.47));

    for(i = 20; i < 38; i++){
        glPushMatrix();
          glTranslatef(0, 143.5 - 0.73 - i*1.580, 0 + (-28 + i)*2.247);
          glScalef(40, 1.580, 4.494);
          ///
                glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
          ///
        glPopMatrix();
    }
      
    glPopMatrix();

    



  glPopMatrix();

}

void object2(){
glPushMatrix();
  glTranslatef(-340, 83.740, 110);
  glRotatef(90,0,1,0);
  glPushMatrix();
    glColor3f(1,1,1);

    glTranslatef(0,5,0);
    glScalef(20,10,20);
          glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  glPopMatrix();

  glColor3f(1,1,0);
  glPushMatrix();
    glTranslatef(0,12,0);
    glutSolidTeapot(2.0f);
  glPopMatrix();

  glPushMatrix();
  glEnable(GL_BLEND);
      glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
      glColor4f(1,1,1,0.5);
      glTranslatef(0,20,0);
      glScalef(20,20,20);
      myCube();
      glDisable(GL_BLEND);
    glPopMatrix();
glPopMatrix();

}

void object3(){
  glPushMatrix();
    glRotatef(90, 0,1,0);
    glTranslatef(-88,99,369);
    
    glScalef(16, 9, 1);
      glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D, texture_id[5]);
    glPushMatrix();
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1);    
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5, -0.5 );  
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );  
       glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);
      glColor3f(0,0,0);
      glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
      glVertex3f(  0.5, -0.5, 0.5 );
      glVertex3f(  0.5,  0.5, 0.5 );
      glVertex3f( -0.5,  0.5, 0.5 );
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glVertex3f( 0.5,  0.5, -0.5 );
      glVertex3f( 0.5,  0.5,  0.5 );
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glVertex3f(  0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glVertex3f(  0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
      glPopMatrix();
  glPopMatrix();
}

void object4(){
  glPushMatrix();
    glRotatef(90, 0,1,0);
    glTranslatef(-88,129,369);
    
    glScalef(20, 8, 1);
    glColor3f(1,1,1);
    
    glBindTexture(GL_TEXTURE_2D, texture_id[6]);
    glPushMatrix();
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1);    
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5, -0.5 );  
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );  
       glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
      glEnd();
      glBindTexture(GL_TEXTURE_2D, 0);
      glColor3f(1,1,1);
      glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
      glVertex3f(  0.5, -0.5, 0.5 );
      glVertex3f(  0.5,  0.5, 0.5 );
      glVertex3f( -0.5,  0.5, 0.5 );
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glVertex3f( 0.5,  0.5, -0.5 );
      glVertex3f( 0.5,  0.5,  0.5 );
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glVertex3f(  0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5, -0.5 );
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glVertex3f(  0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5,  0.5 );
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
      glPopMatrix();
  glPopMatrix();
}

void object5(){
  glColor3f(0.8, 0.9, 0.9);
  glRotatef(-90, 0,1,0);
  glTranslatef(120,83,-345);
  glPushMatrix();
  glPushMatrix();
    glPushMatrix();
    glTranslatef(-10,8.75,0);
      glScalef(1,17.5,1);
      
      glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,8.75,0);
      glScalef(1,17.5,1);
      
      glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  glPopMatrix();
    glPopMatrix();

    
    glPushMatrix();
      glScalef(35,5,1);
      glTranslatef(0,3,1);
      glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  glPopMatrix();
    glPopMatrix();

    
    glPushMatrix();
      glTranslatef(0,8,5.5);
      glScalef(35,1,10);
      
      glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  glPopMatrix();
    glPopMatrix();


   

    glPushMatrix();
      glTranslatef(10,4,9.5);
      glScalef(1,8,1);
      
     glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  glPopMatrix();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-10,4,9.5);
      glScalef(1,8,1);
      
      glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_POLYGON);
      glNormal3f(0,0,-1); 
      glTexCoord2f(0,0);   
      glVertex3f(  0.5, -0.5, -0.5 ); 
      glTexCoord2f(0,1);     
      glVertex3f(  0.5,  0.5, -0.5 );   
      glTexCoord2f(1,0);   
      glVertex3f( -0.5,  0.5, -0.5 );    
      glTexCoord2f(1,1);  
      glVertex3f( -0.5, -0.5, -0.5 );      
       
    glEnd();
    
    glBegin(GL_POLYGON);
    glNormal3f(0,0,1);
    glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, 0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, 0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, 0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, 0.5 );
    glEnd();
     
    // Lado roxo - DIREITA
    glBegin(GL_POLYGON);
    glNormal3f(1,0,0);
    glTexCoord2f(0,0);
      glVertex3f( 0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f( 0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( 0.5,  0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( 0.5, -0.5,  0.5 );
    glEnd();
     
    // Lado verde - ESQUERDA
    glBegin(GL_POLYGON);
      glNormal3f(-1,0,0);
      glTexCoord2f(0,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f( -0.5,  0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
     
    // Lado azul - TOPO
    glBegin(GL_POLYGON);
      glNormal3f(0,1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5,  0.5,  0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5,  0.5, -0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5,  0.5, -0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5,  0.5,  0.5 );
    glEnd();
     
    // Lado vermelho - BASE
    glBegin(GL_POLYGON);
      glNormal3f(0,-1,0);
      glTexCoord2f(0,0);
      glVertex3f(  0.5, -0.5, -0.5 );
      glTexCoord2f(0,1);
      glVertex3f(  0.5, -0.5,  0.5 );
      glTexCoord2f(1,0);
      glVertex3f( -0.5, -0.5,  0.5 );
      glTexCoord2f(1,1);
      glVertex3f( -0.5, -0.5, -0.5 );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
  glPopMatrix();
    glPopMatrix();

    glPopMatrix();




  glPopMatrix();

}

void Timer(int value)
{
    if(x1 != 14 && flag == 1)
     x1++;

    if(x1 != 1 && flag == 2)
      x1--;
    if(y2 != 84 && flag == 3)
      y2++;
    if(y2 != 143 && flag == 5)
      y2++;

    if(y2 != 1 && flag == 4)
      y2--;

    glutPostRedisplay();
    glutTimerFunc(433,Timer, 1);
}
void renderScene2() { //desenha os objetos

  
  glPushMatrix();
  glColor3f(1.0f, 1.0f, 1.0f);
  glBindTexture(GL_TEXTURE_2D, texture_id[0]);
  glBegin(GL_QUADS);
    glNormal3f(0,1,0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1000.0f, 0.0f, -1000.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1000.0f, 0.0f,  1000.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1000.0f, 0.0f,  1000.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1000.0f, 0.0f, -1000.0f);
  glEnd();
glBindTexture(GL_TEXTURE_2D, 0);

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
  //object1(1);
  pictures();
  secondFloor();
  elevator();
  roof();
  windows();
  support();

  

  ladder();

  object2();
  object3();
  object4();
  object5();

  
  
  
  

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
        flag = 1;
        break;
    case 's':
    flag = 2;
        break;
    case 'a':

    if(flag == 3){
      flag == 5;
    }else{
    flag = 3;}
        break;
    case 'd':
    flag = 4;
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
  glEnable(GL_TEXTURE_2D);
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
  glutTimerFunc(133, Timer, 1);
  initTextures();
  //BEGIN - ILUMINATION

    GLfloat luzAmbiente[4]={0.3,0.3,0.3,1.0}; 
  //GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};    // "cor" 
  //GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
  GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

  //ATIVAR
  //Posições das luzes nos interiores, falta dar as coordenadas x, y e z
  GLfloat posicaoLuz1[4] = {150, 120, 0, 1.0}; 
  GLfloat posicaoLuz2[4] = {-150, 120, 0, 1.0};
  GLfloat posicaoLuz3[4] = {150, 170, 0, 1.0};
  GLfloat posicaoLuz4[4] = {-150, 170, 0, 1.0};
  GLfloat direction[3] = {0.0, 1.0, 0.0};
  

  // Capacidade de brilho do material
  GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
  GLint especMaterial = 60;

  // Especifica que a cor de fundo da janela será preta
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  
  // Habilita o modelo de colorização de Gouraud
  glShadeModel(GL_SMOOTH);

  // Define a refletância do material 
  glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
  // Define a concentração do brilho
  glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

  // Ativa o uso da luz ambiente 
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

  // Define os parâmetros da luz de número 0
  glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
  //glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
  
  
  //Luzes interiores
  glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
  
  glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz2);
  glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction);
  
  glLightfv(GL_LIGHT3, GL_POSITION, posicaoLuz3);
  glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
  glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction);

  glLightfv(GL_LIGHT4, GL_POSITION, posicaoLuz4);
  glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
  glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, direction);

  

  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);
  //Habilita o uso de iluminação
  glEnable(GL_LIGHTING);  
  // Habilita a luz de número 0
  glEnable(GL_LIGHT0);

 
  //Luzes dos pisos 
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  glEnable(GL_LIGHT4);
  

  // Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);

  //END - ILUMINATION


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



