#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

int X1, Y1, X2, Y2;

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
			glVertex2i(i,-240);
			glVertex2i(i,240);
		}
	}
	int dx=X2-X1;
	int dy=Y2-Y1;
	int steps;
	if(abs(dx)>abs(dy)) steps=abs(dx);
	else steps=abs(dy);
	float Xinc=dx/(float)steps;
	float Yinc=dy/(float)steps;
	i=0;
	float x=(float)X1, y=(float)Y1;
	plot(X1*20,Y1*20);
	for(i; i<steps; i++)
	{
		x+=Xinc;
		y+=Yinc;
		plot((x),(y));
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	printf("Enter the value of x1 : ");
    scanf("%d",&X1);
    printf("Enter the value of y1 : ");
    scanf("%d",&Y1);
    Y1*=(-1);
    printf("Enter the value of x2 : ");
    scanf("%d",&X2);
    printf("Enter the value of y2 : ");
    scanf("%d",&Y2);
    Y2*=(-1);
	glutCreateWindow("Digital Differential Analyzer in Grid");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
