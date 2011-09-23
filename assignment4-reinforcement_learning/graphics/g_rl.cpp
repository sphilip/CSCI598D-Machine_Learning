#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
using namespace std;

int screenHeight, screenWidth;
int fieldHeight,fieldWidth;

void setup_scene()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  
  glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
  glLoadIdentity(); //Reset the drawing perspective

  /* 
  pretending that max height from origin = 100
  z-axis from viewer = 100
  
  	       /  |  1/2 the scene
      viewer  /_)_|  angle = tan^-1()
  */
  double fovy = atan((0.5*screenHeight)/100)*180/3.14;
  double aspect = 70/100;
  gluPerspective(fovy, aspect,-1,1);
}

void drawCart()
{
  glBegin(GL_POLYGON);
  glEnd();
}

void draw()
{
  fieldWidth = 100;
  fieldHeight = 10;
  //Clear information from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glBegin(GL_LINE_STRIP);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  glTranslated(0,-20,0);
  glVertex3i(-(fieldWidth/2),fieldHeight,0);
  glVertex3i(-(fieldWidth/2)+10,fieldHeight,0);
  glVertex3i(-(fieldWidth/2)+10,0,0);
  glVertex3i((fieldWidth/2)-10,0,0);
  glVertex3i((fieldWidth/2)-10,fieldHeight,0);
  glVertex3i((fieldWidth/2),fieldHeight,0);
 
  glPopMatrix();
  
  glEnd();
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
  glutInit(&argc,argv);

 /* double buffered, RGB color mode */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  screenHeight = 800;
  screenWidth = 800;
 
 /* size and placement hints to the window system */
  glutInitWindowSize(screenHeight, screenWidth);
  glutCreateWindow("Pole-Balancing Problem");  
  
  /* automatically scale normals to unit length after transformation */
  /* back-face culling on */
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);

  /* clear to BLACK */
  glClearColor(0.0,0.0,0.0, 1.0);

  /* Enable depth test  
  Makes 3D drawing work when something is in front of something else */
  glEnable(GL_DEPTH_TEST);

  setup_scene();
  glutDisplayFunc(draw);
  glutMainLoop();
  
  return 0;
}