#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

const int XX = 1000;
const int YY = 900;

int m = 14;

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void drawPixel(float x, float y)
{
    glBegin(GL_POINTS);

	x = ( x + 0.5) * m;
	y = ( y + 0.5) * m;

	glBegin(GL_POLYGON);
	glVertex2d(x,y);
	glVertex2d(x+m,y);
	glVertex2d(x+m,y+m);
	glVertex2d(x,y+m);

	glEnd();
	glFlush();
}


//Rectangle

void drawRectangle(int x,int y)
{
    glColor3f(0.3,0.1,0.1);

    for(int i = 4; i <= 20 ;i++) {
        drawPixel(i + x,4 + y);
        drawPixel(i + x,40 + y);
    }
    for(int i = 4 ;i <= 40 ;i++) {
        drawPixel(4 + x,i + y);
        drawPixel(20+ x,i + y);
    }
}

void drawGrid()
{
    glColor3f(0.0f,0.0f,0.0f);
     glBegin(GL_LINES);

    // Horizontal lines.
    for (int i= -XX ; i<= XX; i += m) {
      glVertex2f(i,YY);
      glVertex2f(i,-YY);
    }

    // Vertical lines.
    for (int i=-YY ; i<= YY; i += m) {
      glVertex2f(XX,i);
      glVertex2f(-XX,i);
    }

  glEnd();
}

void drawAxes() {

  glColor4f(0.0f, 0.0f, 0.0f,0.0f);

  glBegin(GL_LINES);
  glVertex2f(0,YY);
  glVertex2f(0,-YY);
  glVertex2f(XX,0);
  glVertex2f(-XX,0);
  glEnd();

  glFlush();

}




void myinit() {

  glEnable(GL_POINT_SMOOTH);
  glClearColor(1.0, 1.0,1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glPointSize(10.0);
  glLoadIdentity();
  gluOrtho2D(-XX,XX,-YY,YY);

}



void display() {

  glClear(GL_COLOR_BUFFER_BIT);
  drawGrid();
  drawAxes();

  int t = 3;
    while(t--){

        drawRectangle(0,0);
        delay(1);
        glClear(GL_COLOR_BUFFER_BIT);
        drawGrid();
        drawAxes();
        drawRectangle(10,20);
        delay(1);
        glClear(GL_COLOR_BUFFER_BIT);
        drawGrid();
        drawAxes();
    }
  drawRectangle(10,20);
}


int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(XX,YY);
  glutInitWindowPosition(200,70);
  glutCreateWindow("Rectangle");
  glutDisplayFunc(display);
  myinit();
  glutMainLoop();
  return 0;
}