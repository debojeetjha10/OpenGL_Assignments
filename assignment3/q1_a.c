#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<stdio.h>

int X,Y,r,m=400;
const int width = 1000;
const int height = 750;
void plot(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x+X,y+Y);
    glEnd();
}

void myInit(void)
{
    glEnable(GL_POINT_SMOOTH);
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width, width, -height, height);

}



void Circle()
{

    int x,y;
    float d;
    x=0;
    y=r;
    d=3-2*r;
    plot (x,y);
    while(x<=y){

        if(d<0){
            x++;
            d+=2*x+1;
        }

        else{

            y--;
            x++;
            d+=2*(x-y)+1;
        }
        plot(x,y);
        plot(x,-y);
        plot(-x,y);
        plot(-x,-y);
        plot(y,x);
        plot(-y,x);plot(y,-x);plot(-y,-x);

    }
}


void display(void){
 glClear (GL_COLOR_BUFFER_BIT);
 glColor3f (0.0, 0.0, 0.0);
 //Axes();
 Circle();
 glFlush();
}

int main(int argc, char **argv) {
    printf("enter the X and Y coordinates and radius:\n");
    scanf("%d %d %d",&X,&Y,&r);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);

        glutInitWindowPosition(50, 50);

    glutInitWindowSize(width, height);

     glutCreateWindow("circle");
     glutDisplayFunc(display);
     myInit ();
     glutMainLoop();
     return EXIT_SUCCESS;
}