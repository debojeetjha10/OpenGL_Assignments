#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

int x1,yi,x2,y2;

void plot(int x, int y)
{
	glBegin(GL_LINES);
	x*=20;
	y*=20;
	int i, j;
	for(i=x-x%20; i<=x-x%20+20; i++)
	{
		for(j=y-y%20; j<=y-y%20+20; j++)
		{
			glColor3f(0.0f,1.0f,0.0f);
			glVertex2i(i,-j);
			glVertex2i(i,-j+1);	
		}
	}
	glEnd();
	glFlush();
}

void myInit(void)
{
	glClearColor(1.0,1.0,1.0,0.0);
	glColor3f(0.0f,0.0f,0.0f);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0,320.0,-240.0,240.0);
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);	
	int i, j;
	for(i=-320; i<=320; i+=20)
	{
		for(j=-240; j<=240; j=j+20)
		{
			glVertex2i(-320,j);
			glVertex2i(320,j);
			glVertex2i(i,-320);
			glVertex2i(i,320);
		}
	}
	int dx, dy, p;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-yi;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < yi) incy = -1;
	x = x1; y = yi;
	if (dx > dy) 
	{
		plot(x*20, y*20);
		p = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++)
		{
			if (p >= 0)
			{
				y += incy;
				p += inc1;
			}
			else
				p += inc2;
			x += incx;
			plot(x, y);
		}

	}
	else
	{
		plot(x*20, y*20);
		p = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++)
		 {
			if (p >= 0)
			{
				x += incx;
				p += inc1;
			}
			else
				p += inc2;
			y += incy;
			plot(x, y);
		 }
	}

 
glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	printf("Enter the value of x1 : ");
    scanf("%d",&x1);
    printf("Enter the value of y1 : ");
    scanf("%d",&yi);
    printf("Enter the value of x2 : ");
    scanf("%d",&x2);
    printf("Enter the value of y2 : ");
    scanf("%d",&y2);
	glutCreateWindow("Bresenham's Algorithm in Grid");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
