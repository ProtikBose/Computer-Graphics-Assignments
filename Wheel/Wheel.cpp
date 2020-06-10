#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

using namespace std;

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double wheelRotateSideWise;

struct point
{
    double x,y,z;
};


void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glColor3f(0.0f, 1.0f, 0.0f); //positive x axis green

            glVertex3f( 200,0,0);
            glColor3f(1.0f, 0.5f, 0.0f); //negative x axis orange
            glVertex3f(-200,0,0);

            glColor3f(1.0f, 0.5f, 0.0f);     //negative y axis orange
            glVertex3f(0,-200,0);
            glColor3f(1.0f, 0.0f, 0.0f);     // Red,positive y axis
            glVertex3f(0, 200,0);

            glColor3f(1.0f, 0.0f, 0.0f);     // Red,z axis
            glVertex3f(0,0, 200);
            glVertex3f(0,0,-200);
        }
        glEnd();
    }
}


void drawGrid()
{
    int i;
    if(drawgrid==1)
    {
        glColor3f(0.6, 0.6, 0.6);	//grey
        glBegin(GL_LINES);
        {
            for(i=-15; i<=15; i++)
            {

                //if(i==0)
                //continue;	//SKIP the MAIN axes

                //lines parallel to Y-axis
                glVertex3f(i*10, -150, 0);
                glVertex3f(i*10,  150, 0);

                //lines parallel to X-axis
                glVertex3f(-150, i*10, 0);
                glVertex3f( 150, i*10, 0);
            }
        }
        glEnd();
    }
}






class WheelModel
{

    double radius;
    double stickWidth;
    double wheelHeight;
    double stickHeight;
    point wheelCenterPoint;
    point directionVectorOfWheel;
    double rotation;
    double rotationAngle;
    double angleToRotate;

public:

    WheelModel()
    {
        radius=30.0;
        wheelHeight=15.0;
        stickHeight=radius;
        stickWidth=wheelHeight/4;
        wheelCenterPoint.x=0;
        wheelCenterPoint.y=0;
        wheelCenterPoint.z=radius;
        directionVectorOfWheel.x=1;
        directionVectorOfWheel.y=0;
        directionVectorOfWheel.z=0;
        rotation=3.0;
        rotationAngle=0.0;
        angleToRotate=0.0;
    }

    void init()
    {

    }

    void amountOfROtation()
    {

        rotationAngle=atan2(directionVectorOfWheel.y,directionVectorOfWheel.x);
        rotationAngle=rotationAngle*180/pi;
    }

    void rotateClockWise()
    {
        double angleRot=rotation*pi/180;
        double tempValx,tempValy;

        tempValx=directionVectorOfWheel.x*cos(angleRot)+directionVectorOfWheel.y*sin(angleRot);
        tempValy=directionVectorOfWheel.y*cos(angleRot)-directionVectorOfWheel.x*sin(angleRot);

        directionVectorOfWheel.x=tempValx;
        directionVectorOfWheel.y=tempValy;

        //amountOfROtation();
        //cout<<directionVectorOfWheel.x<<" " <<directionVectorOfWheel.y<<endl;
    }

    void rotateCounterClock()
    {

        double angleRot=rotation*pi/180;
        double tempValx,tempValy;

        tempValx=directionVectorOfWheel.x*cos(angleRot)-directionVectorOfWheel.y*sin(angleRot);
        tempValy=directionVectorOfWheel.y*cos(angleRot)+directionVectorOfWheel.x*sin(angleRot);

        directionVectorOfWheel.x=tempValx;
        directionVectorOfWheel.y=tempValy;

        //amountOfROtation();
        //cout<<directionVectorOfWheel.x<<" " <<directionVectorOfWheel.y<<endl;


    }

    void moveForward(){
        //point +vector makes a point
        wheelCenterPoint.x+=directionVectorOfWheel.x;
        wheelCenterPoint.y+=directionVectorOfWheel.y;
        wheelCenterPoint.z+=directionVectorOfWheel.z;

        //wheelStick rotation while forwarding
        double wheelRotateAngle=1.5*180/(pi*radius);
        angleToRotate=angleToRotate-wheelRotateAngle;
    }

    void moveBackward(){
        //point +vector makes a point
        wheelCenterPoint.x-=directionVectorOfWheel.x;
        wheelCenterPoint.y-=directionVectorOfWheel.y;
        wheelCenterPoint.z-=directionVectorOfWheel.z;

        //wheelStick rotation while forwarding
        double wheelRotateAngle=1.5*180/(pi*radius);
        angleToRotate=angleToRotate+wheelRotateAngle;
    }

    void drawWheel()
    {
        glPushMatrix();
        {


            //calculating the amount of the rotation

            //uplifiting it above the plane
            glTranslatef(wheelCenterPoint.x,wheelCenterPoint.y,wheelCenterPoint.z);

            //rotation from user input
            glRotatef(rotationAngle,0,0,1);
            amountOfROtation();
            //making it stand
            glRotatef(90,1,0,0);
            //rotation, for wheel sticks,for forwarding and backwarding
            glRotatef(angleToRotate,0,0,1);
            //two sticks are drawn
            wheelStickDraw();
            //sphere srawing
            drawSphere(100);

        }
        glPopMatrix();

    }

    void wheelStickDraw()
    {
        glColor3f(1,0,0);
        //first stick
        glBegin(GL_QUADS);
        {
            glVertex3f(0,-stickHeight,stickWidth);
            glVertex3f(0,stickHeight,stickWidth);
            glVertex3f(0,stickHeight,-stickWidth);
            glVertex3f(0,-stickHeight,-stickWidth);
        }
        glEnd();
        //glTranslatef(0,0,stickWidth);

        //second stick
        glBegin(GL_QUADS);
        {

            glVertex3f(-stickHeight,0,stickWidth);
            glVertex3f(stickHeight,0,stickWidth);
            glVertex3f(stickHeight,0,-stickWidth);
            glVertex3f(-stickHeight,0,-stickWidth);
        }
        glEnd();

    }

    void drawSphere(int segments)
    {

        glColor3f(0.6,0.6,0.6);
        struct point firstCircle[200];
        struct point secondCircle[200];

        //generating points
        for(int i=0; i<=segments; i++)
        {

            //first circle
            firstCircle[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            firstCircle[i].y=radius*sin(((double)i/(double)segments)*2*pi);
            firstCircle[i].z=wheelHeight/2;
            //second circle
            secondCircle[i].x=radius*cos(((double)i/(double)segments)*2*pi);
            secondCircle[i].y=radius*sin(((double)i/(double)segments)*2*pi);
            secondCircle[i].z=-wheelHeight/2;

        }

        //connecting points
        //using quad
        for(int i=0; i<segments; i++)
        {
            glBegin(GL_QUADS);
            {
                glVertex3f(firstCircle[i].x,firstCircle[i].y,firstCircle[i].z);
                glVertex3f(firstCircle[i+1].x,firstCircle[i+1].y,firstCircle[i+1].z);
                glVertex3f(secondCircle[i+1].x,secondCircle[i+1].y,secondCircle[i+1].z);
                glVertex3f(secondCircle[i].x,secondCircle[i].y,secondCircle[i].z);
            }
            glEnd();
        }


    }

};

WheelModel wheel;

void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case '1':
        drawgrid=1-drawgrid;
        break;
    case 'a':
        //wheelRotateSideWise+=3.0;
        wheel.rotateCounterClock();
        break;
    case 'd':
        //wheelRotateSideWise-=3.0;
        wheel.rotateClockWise();
        break;
    case 'w':
        wheel.moveForward();
        break;
    case 's':
        wheel.moveBackward();
        break;

    default:
        break;
    }
}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:		//down arrow key
        cameraHeight -= 3.0;
        break;
    case GLUT_KEY_UP:		// up arrow key
        cameraHeight += 3.0;
        break;

    case GLUT_KEY_RIGHT:
        cameraAngle += 0.03;
        break;
    case GLUT_KEY_LEFT:
        cameraAngle -= 0.03;
        break;

    case GLUT_KEY_PAGE_UP:
        break;
    case GLUT_KEY_PAGE_DOWN:
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_END:
        break;

    default:
        break;
    }
}


void mouseListener(int button, int state, int x, int y) 	//x, y is the x-y of the screen (2D)
{
    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) 		// 2 times?? in ONE click? -- solution is checking DOWN or UP
        {
            drawaxes=1-drawaxes;
        }
        break;

    case GLUT_RIGHT_BUTTON:
        //........
        break;

    case GLUT_MIDDLE_BUTTON:
        //........
        break;

    default:
        break;
    }
}



void display()
{

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);	//color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?

    //gluLookAt(100,100,100,	0,0,0,	0,0,1);
    gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(0,0,200,	0,0,0,	0,1,0);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes();
    drawGrid();
    wheel.drawWheel();
    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

    //drawSphere(30,24,20);




    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{
    angle+=0.05;
    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init()
{
    //codes for initialization
    drawgrid=1;
    drawaxes=1;
    cameraHeight=120.0;
    cameraAngle=1.0;
    angle=0;
    //wheel=new WheelModel();
    //clear the screen
    glClearColor(0,0,0,0);

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80,	1,	1,	1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
