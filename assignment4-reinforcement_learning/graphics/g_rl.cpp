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
  
  glPushMatrix();
  /* 
  max height from origin = 20
  camera at = <0,0,-100>
  
                 /| <0, 20, 0>
                / |
  	       /  |  1/2 the scene
      camera  /___|  angle = tan^-1(height/camera)
      <0,0,-100>
  */
  double fovy = atan(20/100)*180/M_PI;
  double aspect = 100/30;

  
//   gluPerspective(fovy, aspect,1,1);

//   glViewport(0,0,100,40);
  gluOrtho2D(-50, 50, -20, 20);
  glPushMatrix();
}

void drawCart()
{
  glBegin(GL_POLYGON);
  glEnd();
}

void draw()
{
  glMatrixMode(GL_MODELVIEW);
  
  //Clear information from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  fieldWidth = 100;
  fieldHeight = 10;
    
  /*
  -------              __10__                 ------- 
        |              |  |  |                |
        |              |__|__|                |
        |______________O__|__O________________|
  -50   -40               0                  40    50
  */
  /*
  glBegin(GL_LINE_STRIP);
  glPushMatrix();
  glLoadIdentity();
  glVertex3d(-50,10,0);
  glVertex3d(-40,10,0);
  glVertex3d(-40,0,0);
  
  glVertex3d(40,0,0);
  glVertex3d(40,10,0);
  glVertex3d(50,10,0);
  glPopMatrix();
  glEnd();*/
  
  GLdouble env[16];
  glGetDoublev(GL_PROJECTION_MATRIX, env);
  cout << env[0] << "\t" << env[1] << "\t" << env[2] << "\t" << env[3] << endl;
  cout << env[4] << "\t" << env[5] << "\t" << env[6] << "\t" << env[7] << endl;
  cout << env[8] << "\t" << env[9] << "\t" << env[10] << "\t" << env[11] << endl;
  cout << env[12] << "\t" << env[13] << "\t" << env[14] << "\t" << env[15] << endl;

  glBegin(GL_LINES);
  // X-AXIS
  glPushMatrix();
  glLoadIdentity();
  glColor3f(1.0f,0,0);
  glVertex3d(0,0,0);
  glVertex3d(1,0,0);
  
  // Y-AXIS
  glColor3f(0,1.0f,0);
  glVertex3d(0,0,0);
  glVertex3d(0,1,0);
  
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
  glutInitWindowSize(screenWidth,screenHeight);
  glutCreateWindow("Pole-Balancing Problem");  
  
  /* automatically scale normals to unit length after transformation */
  /* back-face culling on */
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);

  /* clear to BLACK */
  glClearColor(0.0,0.0,0.0, 1.0);

  /* Enable depth test  
  Makes 3D drawing work when something is in front of something else */
//   glEnable(GL_DEPTH_TEST);

  setup_scene();
  glutDisplayFunc(draw);
  glutMainLoop();
  
  return 0;
}
