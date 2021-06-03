#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include<time.h>

#define XX 1000
#define YY 1000

int m = 8;

int X = 30;
int Y = 50;

int Round(float x)
{
    return (int)(x + 0.5);
}

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void drawPixel(float x, float y)
{
    glBegin(GL_POINTS);

	x = Round(X + x) * m;
	y = Round(Y + y) * m;

	glBegin(GL_POLYGON);
	glVertex2d(x,y);
	glVertex2d(x+m,y);
	glVertex2d(x+m,y+m);
	glVertex2d(x,y+m);

	glEnd();
	glFlush();
}

//Grid

void drawGrid()
{
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);

    int i = -XX;
    // Horizontal lines.
    for (i ; i<= XX; i += m) {
      glVertex2f(i,YY);
      glVertex2f(i,-YY);
    }

    i = -YY;
    // Vertical lines.
    for (i ; i<= YY; i += m) {
      glVertex2f(XX,i);
      glVertex2f(-XX,i);
    }

  glEnd();
}
  // Main axes

void drawAxes() {

  glColor3f(1.0f, 0.0f, 0.0f); //color of the axis

  glBegin(GL_LINES);
  glVertex2f(0,YY);
  glVertex2f(0,-YY);
  glVertex2f(XX,0);
  glVertex2f(-XX,0);
  glEnd();

  glFlush();

}

// Midpoint Circle drawing Algorithm

void drawCircle(float r) {

 glColor3f(0.0, 0.0, 0.9);
 glPointSize(2.0);

 float x = 0.0;
 float y = r;
 float p = (5/4) - r;

 glBegin(GL_POINTS);

 while (x  <= y)
 {
   drawPixel(x, y);
   drawPixel(-x, y);
   drawPixel(x, -y);
   drawPixel(-x, -y);
   drawPixel(y, x);
   drawPixel(-y, x);
   drawPixel(y, -x);
   drawPixel(-y, -x);

  if (p < 0) {

   p += 2 * (x + 1) + 1;

  }
  else {

   y--;
   p += 2 * (x + 1) + 1 - 2 * (y - 1);

  }
   x++;

 }
 glEnd();

}


void myinit() {

  glEnable(GL_POINT_SMOOTH);
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glPointSize(10.0);
  glLoadIdentity();
  gluOrtho2D(-XX,XX,-YY,YY);

}

// clear function

void clear()
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawGrid();
  drawAxes();

}

//display function

void display() {

   clear();

  int times = 5;

  float r = 19;

  int i;

  for(i = 1; i<= times ;i++)
  {
      drawCircle(r);
      delay(1);
      clear();
      if(i == times) break;
      drawCircle(4*r);
      delay(1);
      clear();
  }

  drawCircle(4*r);


}

//main function

int main(int argc, char **argv) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(XX,YY);
  glutInitWindowPosition(300,50);
  glutCreateWindow("Circle Scaling");
  glutDisplayFunc(display);
  myinit();
  glutMainLoop();

  return 0;
}
