#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;


void draw()
{
  glBegin(GL_TRIANGLE_STRIP);
  glVertex3i(0,0,0);
  glVertex3i(10,0,0);
  glVertex3i(5,5,0);
  glEnd();
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
  GLint wid;
  glutInit(&argc,argv);

  /* size and placement hints to the window system */
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(10,10);

  /* double buffered, RGB color mode */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  wid =  glutCreateWindow("Pole-Balancing Problem");  
  /* back-face culling on */
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  /* automatically scale normals to unit length after transformation */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glPointSize(4);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  /* clear to BLACK */
  glClearColor(0.0,0.0,0.0, 1.0);

  /* Enable depth test  */
  glEnable(GL_DEPTH_TEST);

  glutSetWindow(wid);
  
  draw();
  glutMainLoop();
  
  return 0;
}