#include<GL/glut.h>
#include<stdio.h>
#include<math.h>


float X1=0.0,X2=5.0,Y1=0.0,Y2=5.0;
int width=1000, height=750;
int m = 20,counter=1;
int scale = 20/2;

void myInit(void){

    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,1.0f,0.8f);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width,width,-height,height);

}

float estimate(float x){

    return floor(x + 0.5);

}

void drawPixel(float x, float y){



    int XT = estimate(x)*m;
    int YT = estimate(y)*m;
    glBegin(GL_POLYGON);
    // printf("%d %d\n\n",XT, YT);
    glVertex2d(XT,YT);
    glVertex2d(XT, YT + m);
    glVertex2d(XT+m, YT + m);
    glVertex2d(XT+m,YT);
    glEnd();

}

void plotPoints(float x, float y){

    //printf("%f %f \n\n", x,y);
    drawPixel(X1+x,Y1+y);
    drawPixel(X1-x,Y1+y);
    drawPixel(X1+x,Y1-y);
    drawPixel(X1-x,Y1-y);
    drawPixel(X1+y,Y1+x);
    drawPixel(X1-y,Y1+x);
    drawPixel(X1+y,Y1-x);
    drawPixel(X1-y,Y1-x);
    
}


void midpoint_circle(){

    glColor3f(0.0f,1.0f,1.0f);
    
    float radius = (X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1);
    radius = sqrt(radius);
    //printf("%f\n\n", radius);
    float y = radius, x = 0.0;
    double d = 5.0/4.0 - radius;
    plotPoints(x , y);

    while(y>x){
        if(d<0) d+=2.0*x + 3.0;
        else{
            d += 2.0*(x-y) + 5.0;
            y--;
        }
        x++;
        plotPoints(x,y);
    }

}

void mouse(int button,int state, int x,int y){
    int yy;
    yy = glutGet(GLUT_WINDOW_HEIGHT);
    y = yy - y;
    glColor3f(1.0, 0.0, 0.0);
    
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)&&(counter%2==1))
    {
        X1 = (x - width/2)/scale;
        Y1 = (y - height/2)/scale;
        // X1= x;
        // Y1 = y;
        counter++;
    }
    else if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)&&(counter%2==0))
    {
        X2 = (x - width/2)/scale;
        Y2 = (y - height/2)/scale;
        // X2 = x;
        // Y2=y;
        midpoint_circle();
        glEnd();
        counter++;
    }
    glFlush();
}

void drawGrid(void){

    glColor3f(0.0f,0.0f,0.1f);
    glBegin(GL_LINES);
    for(int t = m;t<=width;t+=m){
        glVertex2f(t,height);
        glVertex2f(t,-height);
        glVertex2f(-t,height);
        glVertex2f(-t,-height);
    }

    for(int t=m;t<=height;t+=m){
        glVertex2f(-width,t);
        glVertex2f(width,t);
        glVertex2f(-width,-t);
        glVertex2f(width,-t);
    }

    glColor3f(1.0f,0.0f,0.0f);
    glVertex2f(0,-height);
    glVertex2f(0,height);
    glVertex2f(width,0);
    glVertex2f(-width,0);

    glEnd();

}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    //midpoint_circle();
    glFlush();

}


int main(int argc, char** argv){

    // printf("Enter the co-ordinates of the center : ");
    // scanf("%f %f", &X1, &Y1);

    // printf("Enter any point on the circumference : ");
    // scanf("%f %f", &X2, &Y2);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Midpoint Circle Drawing");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    myInit();
    glutMainLoop();
    
    return 0;

}