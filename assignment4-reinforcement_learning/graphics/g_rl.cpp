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

                    / | <0, 20, 0>
                   /  |
  	          /   |  1/2 the scene
      camera     /____|  angle = tan^-1(height/camera)
      <0,0,-100>
  */
  //   double fovy = atan(100/100)*180/M_PI;
  //   double aspect = 100/30;


  //   gluPerspective(fovy, aspect,1,1);

  //   glViewport(0,0,100,40);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-50, 50, -50, 50);
  glPushMatrix();
}


void drawWheel(double cx, double cy, double r)
{
  int num_segments = 10;
  double theta = 2 * M_PI / double(num_segments);
  double tangetial_factor = tanf(theta);//calculate the tangential factor

  double radial_factor = cosf(theta);//calculate the radial factor

  double x = r;//we start at angle = 0

  double y = 0;

  glBegin(GL_LINE_LOOP);
  for(int ii = 0; ii <= num_segments; ii++)
  {
    glVertex2f(x + cx, y + cy);//output vertex

    //calculate the tangential vector
    //remember, the radial vector is (x, y)
    //to get the tangential vector we flip those coordinates and negate one of them

    double tx = -y;
    double ty = x;

    //add the tangential vector

    x += tx * tangetial_factor;
    y += ty * tangetial_factor;

    //correct using the radial factor

    x *= radial_factor;
    y *= radial_factor;
  }
  glEnd();
}

void drawCart()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // draw body
  glBegin(GL_LINE_LOOP);
  glVertex3d(-8.0,10.0,0.0);
  glVertex3d(-8.0,2.0,0.0);
  glVertex3d(8.0,2.0,0.0);
  glVertex3d(8.0,10.0,0.0);
  glEnd();

  // draw wheels
  double x,y,radius;
  radius = 2.0;

  // left wheel
  x = -5.0;
  y = 2.0;
  drawWheel(x,y,radius);

  // right wheel
  x = 5.0;
  drawWheel(x,y,radius);

  glPopMatrix();
  glutSwapBuffers();
}

void drawField()
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
  glEnd();

  /*
  // test projection matrix
  GLdouble env[16];
  glGetDoublev(GL_PROJECTION_MATRIX, env);
  cout << env[0] << "\t" << env[1] << "\t" << env[2] << "\t" << env[3] << endl;
  cout << env[4] << "\t" << env[5] << "\t" << env[6] << "\t" << env[7] << endl;
  cout << env[8] << "\t" << env[9] << "\t" << env[10] << "\t" << env[11] << endl;
  cout << env[12] << "\t" << env[13] << "\t" << env[14] << "\t" << env[15] << endl;
  */

  /*
  // draw x,y axis to test scaling
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
*/
  glPopMatrix();
  glEnd();

  glutSwapBuffers();
}

void drawPole()
{
  glMatrixMode(GL_MODELVIEW);

  // draw pole
  glBegin(GL_LINE_LOOP);
  glVertex2d(-0.75,8.0);
  glVertex2d(0.75,8.0);
  glVertex2d(0.75,40.0);
  glVertex2d(-0.75,40.0);
  glEnd();

  // draw hinge
  drawWheel(0.0,9.0,0.25);
}
void draw()
{
  drawField();
  drawCart();
  drawPole();

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
  glDisable(GL_DEPTH_TEST);

  setup_scene();
  glutDisplayFunc(draw);
  glutMainLoop();

  return 0;
}
