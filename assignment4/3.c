#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define XX 1000
#define YY 1000

int m = 16;

int Round(float x)
{
    return (int)(x + 0.5);
}

void delay()
{
    int milli_seconds = 300;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

void drawPixel(float x, float y,float theta)
{
    glBegin(GL_POINTS);

	x = Round( x ) * m;
	y = Round( y ) * m;

	x = x * cos(theta) - y * sin(theta);
	y = x * sin(theta) + y * cos(theta);

	glBegin(GL_POLYGON);
	glVertex2d(x,y);
	glVertex2d(x+m,y);
	glVertex2d(x+m,y+m);
	glVertex2d(x,y+m);

	glEnd();
	glFlush();
}

void drawLine(int X1,int Y1,int X2,int Y2,float theta) {


     glColor4f(0.0f, 0.0f, 0.0f,0.0f);  //color of the line

    int dX = X2 - X1;
    int dY = Y2 - Y1;

    int x = X1;
    int y = Y1;

    // When slope < 1

    if(abs(dX) > abs(dY))
    {
        int pk = (2 * abs(dY)) - abs(dX);
        int i;
        for(i = 0; i < abs(dX) ; i++)
        {
            drawPixel(x,y,theta);

            if(pk < 0)
                pk = pk + (2 * abs(dY));
            else
            {
                if(dY >= 0)
                y = y + 1;
                else
                y = y - 1;
                pk = pk + (2 * abs(dY)) - (2 * abs(dX));
            }
            if(dX >= 0)
            x = x + 1;
            else
            x = x - 1;
        }
    }

    // for slope >= 1

    else
    {
        int pk = (2 * abs(dX)) - abs(dY);
        int i;
        for(i = 0; i < abs(dY) ; i++)
        {
             drawPixel(x,y,theta);

            if(pk < 0)
                pk = pk + (2 * abs(dX));
            else
            {
               if(dX >= 0)
               x = x + 1;
               else
               x = x - 1;
                pk = pk + (2 * abs(dX)) - (2 *abs(dY));
            }
            if(dY >= 0)
            y = y + 1;
            else
            y  = y -1;
        }

    }

    glFlush();
}


void drawCircle(int X , int Y , float r, float theta) {


 glColor3f(0.0, 0.0, 0.0);
 glPointSize(2.0);

 float x = 0.0;
 float y = r;
 float p = (5/4) - r;

 glBegin(GL_POINTS);

 while (x  <= y)
 {
   drawPixel(X+x,Y+y,theta);
   drawPixel(X-x,Y+y,theta);
   drawPixel(X+x,Y-y,theta);
   drawPixel(X-x,Y-y,theta);
   drawPixel(X+y,Y+x,theta);
   drawPixel(X-y,Y+x,theta);
   drawPixel(X+y,Y-x,theta);
   drawPixel(X-y,Y-x,theta);

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

void  drawEllipse(int X ,int Y ,int rx,int ry, float theta)
{

    glColor3f(0.0f,0.0f,0.0f);

    float x = 0;
    float y = ry;
    float p1 = ry * ry - (rx * rx)* ry + (rx * rx) * (0.25) ;
    float dx = 2 * (ry * ry) * x;
    float dy = 2 * (rx * rx) * y;

    while(dx < dy)
    {
         drawPixel(X+x,Y+y,theta);
         drawPixel(X-x,Y+y,theta);
         drawPixel(X+x,Y-y,theta);
         drawPixel(X-x,Y-y,theta);
        if(p1 < 0)
        {
            x = x + 1;
            dx = 2 * (ry * ry) * x;
            p1 = p1 + dx + (ry * ry);
        }
        else
        {
            x = x + 1;
            y = y - 1;
            dx =  2 * (ry * ry) * x;
            dy =  2 * (rx * rx) * y;
             p1 = p1 + dx - dy +(ry * ry);
        }
    }
    float p2 = (ry * ry )* ( x +  0.5) * ( x +  0.5) +  ( rx * rx) * ( y - 1) * ( y - 1) - (rx * rx )* (ry * ry);


    while(y > 0)
    {
        drawPixel(X+x,Y+y,theta);
         drawPixel(X-x,Y+y,theta);
         drawPixel(X+x,Y-y,theta);
         drawPixel(X-x,Y-y,theta);
        if(p2 > 0)
        {
            x = x;
            y = y - 1;
            dy = 2 * (rx * rx) * y;
            p2 = p2 - dy + (rx * rx);
        }
        else
        {
            x = x + 1;
            y = y - 1;
            dy = dy - 2 * (rx * rx) ;
            dx = dx + 2 * (ry * ry) ;
            p2 = p2 + dx -
            dy + (rx * rx);
        }
    }


}



//Grid

void drawGrid()
{
    glColor3f(0.0f,0.0f,0.0f);
     glBegin(GL_LINES);

    // Horizontal lines.
    int i;
    for (i= -XX ; i<= XX; i += m) {
      glVertex2f(i,YY);
      glVertex2f(i,-YY);
    }

    // Vertical lines.
    for (i=-YY ; i<= YY; i += m) {
      glVertex2f(XX,i);
      glVertex2f(-XX,i);
    }

  glEnd();
}
  // Main axes

void drawAxes() {

  glColor4f(1.0f, 0.0f, 0.0f,0.0f); //color of the axis

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
  glClearColor(0.0, 0.0,0.8, 0.0);
  glMatrixMode(GL_PROJECTION);
  glPointSize(10.0);
  glLoadIdentity();
  gluOrtho2D(-XX,XX,-YY,YY);

}

void clear()
{
 glClear(GL_COLOR_BUFFER_BIT);
  drawGrid();
  drawAxes();
}

// Display function

void display() {

  clear();

  float theta = (25 * 3.14)/180;

  drawLine(-22,20,-1,50,0);
  drawLine(22,20,-1,50,0);
  drawEllipse(0,21,20,5,0);
  drawCircle(0,10,10,0);

   delay();
   clear();

  drawLine(-22,20,-1,50,theta);
  drawLine(22,20,-1,50,theta);
  drawEllipse(0,21,20,5,theta);
  drawCircle(0,10,10,theta);

}

//main function

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(XX,YY);
  glutInitWindowPosition(200,75);
  glutCreateWindow("Rotation");

  glutDisplayFunc(display);
  myinit();
  glutMainLoop();

  return 0;
}
