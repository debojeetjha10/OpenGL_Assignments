#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<stdio.h>
#define WIDTH 400
#define HEIGHT 400
int c=0,x2,y2,r;
void MidPointCircle(int x, int y,int r);
void initial()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1*WIDTH, WIDTH, -1*HEIGHT, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT);
}
void MyMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		y = HEIGHT - y;
		x = x - WIDTH;
		c++;
		glColor3f(0, 0, 1);
		glPointSize(2.0);
		//glPointSize(3);
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();
		glFlush();
		if(c==1)
		{
			x2=x,y2=y;
		}
		else if(c==2)
		{
			c=0;
			int r=sqrt((x2-x)*(x2-x)+(y2-y)*(y2-y));
			MidPointCircle(x2,y2,r);
		}
	}
}
void CirclePoints(int cx,int cy,int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(cx+x, cy+y); glVertex2i(cx+y, cy+x);
	glVertex2i(cx-x, cy+y); glVertex2i(cx+y, cy-x);
	glVertex2i(cx+x, cy-y); glVertex2i(cx-y, cy+x);
	glVertex2i(cx-x, cy-y); glVertex2i(cx-y, cy-x);
	glEnd();
	glFlush();
}
void MidPointCircle(int x1,int y1,int r)
{
	float d;
	int x0 = abs(x1);
	int y0 = abs(y1);
	if (x0 > y0)
	{
		int xx = x0;
		x0 = y0;
		y0 = xx;
	}
	int x, y;
	x = 0, y =r;
	//d = 1.25 - r;
	d = 1 - r;// Simplify calculations, round
	CirclePoints(x1,y1,x, y);
	while (x <= y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		CirclePoints(x1,y1,x, y);
	}
}
void display(void)
{
	//MidPointCircle(50,10);
	glClear(GL_COLOR_BUFFER_BIT);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(2*WIDTH, 2*HEIGHT);
	glutCreateWindow("MidPointCircle");
	initial();
	glutMouseFunc(&MyMouse);
	glutDisplayFunc(&display);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
	return 0;
}