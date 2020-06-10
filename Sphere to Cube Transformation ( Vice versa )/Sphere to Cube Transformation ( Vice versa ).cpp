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
double cameraRotation;



struct point
{
    double x,y,z;
};

point cameraPosition,upDirection,lookAt,rightDirection;


void drawAxes()
{
    if(drawaxes==1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glColor3f(1,0,0); //x axis red
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);

            glColor3f(0,1,0); //y axis green
            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);

            glColor3f(0,0,1); //z axis blue
            glVertex3f(0,0, 100);
            glVertex3f(0,0,-100);
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
            for(i=-8; i<=8; i++)
            {

                if(i==0)
                    continue;	//SKIP the MAIN axes

                //lines parallel to Y-axis
                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);

                //lines parallel to X-axis
                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }
        glEnd();
    }
}

class Box
{
    double totalLengthCube=160.0;
    double radiusOfSphere;
    int sliceNum;
    int stackNum;
    int segments;
    double lengthOfCubeAbovePlane;
    double cylinderheight;
    double squareLentgh;

public:
    Box()
    {
        radiusOfSphere=0.0;
        sliceNum=50;
        stackNum=30;
        segments=30;
        lengthOfCubeAbovePlane=50;
        cylinderheight=0.0;
        squareLentgh=0.0;
    }

    void draw2()
    {
       // drawAllUperSphere();
       /*countRadius();
         drawQuatSphere();*/
       /*  countRadius();
         countCylHeight();
         drawQuatCyl();*/
         drawQuatSquare();
    }

    void drawBox()
    {
        //drawing spheres
        glPushMatrix();
        {


            drawAllUperSphere();
            drawAllLowerSphere();
        }
        glPopMatrix();

        //drawing cylinders
        glPushMatrix();
        {
            //two upside and two downside cylinders,rotation around x axis,another two sides done
            drawTwoUpAndTwoDownCylinderAroundX();

            //two upside and two downside cylinders,rotation around y axis,two sides done
            drawTwoUpAndTwoDownCylinderAroundY();
            //all vertical cylinders
            drawAllVerticalCylinder();
        }
        glPopMatrix();

        //drawing all squares
        glPushMatrix();
        {
            //upper and lower squares/two
            drawAllSideUpperSquares();
            //side squares,four
            drawAllInnerSquaresSideWise();
        }
        glPopMatrix();
    }

    void drawAllSideUpperSquares()
    {
        //upper one
        glPushMatrix();
        {

            //glRotatef(0,0,0,1);
            //uplifting it on above the plane
            //upper one
            glTranslatef(0,0,totalLengthCube/2);
            //drawing a sqaure
            drawQuatSquare();
            //counting length
            countSqLength();
        }
        glPopMatrix();

        //lower one

        glPushMatrix();
        {

            glRotatef(180,0,1,0);
            //uplifting it on above the plane
            //lower one
            glTranslatef(0,0,totalLengthCube/2);
            //drawing a sqaure
            drawQuatSquare();
            //counting length
            countSqLength();
        }
        glPopMatrix();
    }

    void drawAllInnerSquaresSideWise()
    {
        glPushMatrix();
        {
            //rotating to a side because it was a upper square
            glRotatef(90,0,1,0);
            //glRotatef(0,0,0,1);
            glTranslatef(0,0,totalLengthCube/2);
            drawQuatSquare();
            countSqLength();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(90,0,0,1);
            glRotatef(90,0,1,0);
            //glRotatef(0,0,0,1);
            glTranslatef(0,0,totalLengthCube/2);
            drawQuatSquare();
            countSqLength();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(180,0,0,1);
            glRotatef(90,0,1,0);
            //glRotatef(0,0,0,1);
            glTranslatef(0,0,totalLengthCube/2);
            drawQuatSquare();
            countSqLength();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(270,0,0,1);
            glRotatef(90,0,1,0);
            //glRotatef(0,0,0,1);
            glTranslatef(0,0,totalLengthCube/2);
            drawQuatSquare();
            countSqLength();
        }
        glPopMatrix();
    }





    void drawTwoUpAndTwoDownCylinderAroundX()
    {

        glPushMatrix();
        {

            glPushMatrix();
            {
                glRotatef(90,1,0,0);
                glRotatef(0,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();

            glPushMatrix();
            {
                glRotatef(90,1,0,0);
                glRotatef(90,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();

            glPushMatrix();
            {
                glRotatef(90,1,0,0);
                glRotatef(180,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();

            glPushMatrix();
            {
                glRotatef(90,1,0,0);
                glRotatef(270,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();
        }
        glPopMatrix();

    }

    void drawTwoUpAndTwoDownCylinderAroundY()
    {

        glPushMatrix();
        {

            glPushMatrix();
            {
                glRotatef(90,0,1,0);
                glRotatef(0,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();

            glPushMatrix();
            {
                glRotatef(90,0,1,0);
                glRotatef(90,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();

            glPushMatrix();
            {
                glRotatef(90,0,1,0);
                glRotatef(180,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();

            glPushMatrix();
            {
                glRotatef(90,0,1,0);
                glRotatef(270,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
                drawQuatCyl();
                countRadius();
                countCylHeight();
            }
            glPopMatrix();
        }
        glPopMatrix();

    }

    void drawAllVerticalCylinder()
    {
        glPushMatrix();
        {
            glRotatef(0,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
            drawQuatCyl();
            countRadius();
            countCylHeight();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(90,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
            drawQuatCyl();
            countRadius();
            countCylHeight();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(180,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
            drawQuatCyl();
            countRadius();
            countCylHeight();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(270,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,-cylinderheight/2);
            drawQuatCyl();
            countRadius();
            countCylHeight();
        }
        glPopMatrix();

    }

    void drawQuatCyl()
    {
        struct point lowerCylPoints[100],upperCylPoints[100];

        //generate points
        for(int i=0; i<=segments; i++)
        {
            lowerCylPoints[i].x=radiusOfSphere*cos(((double)i/(double)segments)*pi/2);
            lowerCylPoints[i].y=radiusOfSphere*sin(((double)i/(double)segments)*pi/2);
            lowerCylPoints[i].z=0;

            upperCylPoints[i].x=lowerCylPoints[i].x;
            upperCylPoints[i].y=lowerCylPoints[i].y;
            upperCylPoints[i].z=cylinderheight;
        }

        //draw quadrilateral
        for(int i=0; i<segments; i++)
        {
            //create shading effect

            glColor3f(0,1,0);

            glBegin(GL_QUADS);
            {
                glVertex3f(lowerCylPoints[i].x,lowerCylPoints[i].y,lowerCylPoints[i].z);
                glVertex3f(lowerCylPoints[i+1].x,lowerCylPoints[i+1].y,lowerCylPoints[i+1].z);
                glVertex3f(upperCylPoints[i+1].x,upperCylPoints[i+1].y,upperCylPoints[i+1].z);
                glVertex3f(upperCylPoints[i].x,upperCylPoints[i].y,upperCylPoints[i].z);
            }
            glEnd();
        }

    }

    void drawQuatSquare()
    {

        glColor3f(1.0,1.0,1.0);

        glBegin(GL_QUADS);
        {
            glVertex3f(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane, 0);
            glVertex3f(lengthOfCubeAbovePlane, -lengthOfCubeAbovePlane, 0);
            glVertex3f(-lengthOfCubeAbovePlane,-lengthOfCubeAbovePlane,0);
            glVertex3f(-lengthOfCubeAbovePlane, lengthOfCubeAbovePlane, 0);
        }
        glEnd();

    }

    void countRadius()
    {
        radiusOfSphere=totalLengthCube/2-lengthOfCubeAbovePlane;
    }

    void countCylHeight()
    {
        cylinderheight=lengthOfCubeAbovePlane*2;
    }

    void countSqLength()
    {
        squareLentgh=lengthOfCubeAbovePlane;
    }





    void drawAllUperSphere()
    {

        //first sphere at corner
        glPushMatrix();
        {
            glRotatef(0,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);

            drawQuatSphere();
            countRadius();
        }
        glPopMatrix();

        //second sphere at corner
        glPushMatrix();
        {
            glRotatef(90,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);
            //countRadius();
            drawQuatSphere();
            countRadius();
        }
        glPopMatrix();

        //third sphere at corner
        glPushMatrix();
        {
            glRotatef(180,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);
            //countRadius();
            drawQuatSphere();
            countRadius();
        }
        glPopMatrix();

        //fourth sphere at corner
        glPushMatrix();
        {
            glRotatef(270,0,0,1);
            glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);
            //countRadius();
            drawQuatSphere();
            countRadius();
        }
        glPopMatrix();




    }


    void drawAllLowerSphere()
    {
        glPushMatrix();
        {
            glRotatef(180,0,1,0);

            //first sphere at corner
            glPushMatrix();
            {
                glRotatef(0,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);

                drawQuatSphere();
                countRadius();
            }
            glPopMatrix();

            //second sphere at corner
            glPushMatrix();
            {
                glRotatef(90,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);
                //countRadius();
                drawQuatSphere();
                countRadius();
            }
            glPopMatrix();

            //third sphere at corner
            glPushMatrix();
            {
                glRotatef(180,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);
                //countRadius();
                drawQuatSphere();
                countRadius();
            }
            glPopMatrix();

            //fourth sphere at corner
            glPushMatrix();
            {
                glRotatef(270,0,0,1);
                glTranslatef(lengthOfCubeAbovePlane,lengthOfCubeAbovePlane,lengthOfCubeAbovePlane);
                //countRadius();
                drawQuatSphere();
                countRadius();
            }
            glPopMatrix();
        }
        glPopMatrix();




    }

    void drawQuatSphere()
    {

        struct point points[100][100];

        double height,rad;
        //generate points
        for(int i=0; i<=stackNum; i++)
        {
            //for the upper part x and y axis
            height=radiusOfSphere*sin(((double)i/(double)stackNum)*(pi/2)); //dividing the upper hemisphere into stacks
            rad=radiusOfSphere*cos(((double)i/(double)stackNum)*(pi/2));

            //generating points
            //pi/2 is used for the 1/4th of upper part, that means it is the eightth part of whole sphere
            for(int j=0; j<=sliceNum; j++)
            {
                points[i][j].x=rad*cos(((double)j/(double)sliceNum)*(pi/2));
                points[i][j].y=rad*sin(((double)j/(double)sliceNum)*(pi/2));
                points[i][j].z=height;
            }
        }
        //draw quads using generated points
        for(int i=0; i<stackNum; i++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            glColor3f(1,0,0);

            for(int j=0; j<sliceNum; j++)
            {
                glBegin(GL_QUADS);
                {
                    //upper hemisphere
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

                }
                glEnd();
            }
        }



    }


    void drawHalfSphere()
    {
        struct point points[100][100];

        double height,rad;
        //generate points
        for(int i=0; i<=stackNum; i++)
        {
            height=radiusOfSphere*sin(((double)i/(double)stackNum)*(pi/2)); //dividing the upper hemisphere into stacks
            rad=radiusOfSphere*cos(((double)i/(double)stackNum)*(pi/2));

            for(int j=0; j<=sliceNum; j++)
            {
                points[i][j].x=rad*cos(((double)j/(double)sliceNum)*(2*pi));
                points[i][j].y=rad*sin(((double)j/(double)sliceNum)*(2*pi));
                points[i][j].z=height;
            }
        }
        //draw quads using generated points
        for(int i=0; i<stackNum; i++)
        {
            //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
            glColor3f(1,0,0);

            for(int j=0; j<sliceNum; j++)
            {
                glBegin(GL_QUADS);
                {
                    //upper hemisphere
                    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
                    glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
                    glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
                    glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

                }
                glEnd();
            }
        }

    }

    void cubeToSphere()
    {
        if(lengthOfCubeAbovePlane>0)
            lengthOfCubeAbovePlane--;
    }

    void sphereToCube()
    {
        if(lengthOfCubeAbovePlane<totalLengthCube/2)
            lengthOfCubeAbovePlane++;
    }


};

Box box;

void keyboardListener(unsigned char key, int x,int y)
{
    double ang=cameraRotation*pi/180;
    switch(key)
    {

    case '1':
        //drawgrid=1-drawgrid;

        //lookAt vector rotation (towards rightDirection) axis updirection
        lookAt.x=lookAt.x*cos(ang)-rightDirection.x*sin(ang);
        lookAt.y=lookAt.y*cos(ang)-rightDirection.y*sin(ang);
        lookAt.z=lookAt.z*cos(ang)-rightDirection.z*sin(ang);

        //new rightdirection will be cross product of new lookat and updirection

        rightDirection.x=lookAt.y*upDirection.z-lookAt.z*upDirection.y;
        rightDirection.y=-(lookAt.x*upDirection.z-lookAt.z*upDirection.x);
        rightDirection.z=lookAt.x*upDirection.y-lookAt.y*upDirection.x;
        break;

    case '2':
         //double ang=cameraRotation*pi/180;
         //lookAt vector rotation (against rightDirection) axis updirection
        lookAt.x=lookAt.x*cos(ang)+rightDirection.x*sin(ang);
        lookAt.y=lookAt.y*cos(ang)+rightDirection.y*sin(ang);
        lookAt.z=lookAt.z*cos(ang)+rightDirection.z*sin(ang);

        //new rightdirection will be cross product of new lookat and updirection

        rightDirection.x=lookAt.y*upDirection.z-lookAt.z*upDirection.y;
        rightDirection.y= -(lookAt.x*upDirection.z-lookAt.z*upDirection.x);
        rightDirection.z=lookAt.x*upDirection.y-lookAt.y*upDirection.x;
        break;

    case '3':
         //double ang=cameraRotation*pi/180;
         //updirection vector rotation (against lookat) axis rightdirection
        upDirection.x=upDirection.x*cos(ang)-lookAt.x*sin(ang);
        upDirection.y=upDirection.y*cos(ang)-lookAt.y*sin(ang);
        upDirection.z=upDirection.z*cos(ang)-lookAt.z*sin(ang);

        //new lookat will be cross product of new updirection and right

        lookAt.x=upDirection.y*rightDirection.z-upDirection.z*rightDirection.y;
        lookAt.y=-(upDirection.x*rightDirection.z-upDirection.z*rightDirection.x);
        lookAt.z=upDirection.x*rightDirection.y-upDirection.y*rightDirection.x;
        break;

    case '4':
         //double ang=cameraRotation*pi/180;
         //lookAt vector rotation (against rightDirection) axis updirection
        upDirection.x=upDirection.x*cos(ang)+lookAt.x*sin(ang);
        upDirection.y=upDirection.y*cos(ang)+lookAt.y*sin(ang);
        upDirection.z=upDirection.z*cos(ang)+lookAt.z*sin(ang);

        //ner rightdirection will be cross product of new left and updirection

        lookAt.x=upDirection.y*rightDirection.z-upDirection.z*rightDirection.y;
        lookAt.y=-(upDirection.x*rightDirection.z-upDirection.z*rightDirection.x);
        lookAt.z=upDirection.x*rightDirection.y-upDirection.y*rightDirection.x;
        break;

    case '5':
         //double ang=cameraRotation*pi/180;
         //updirection vector rotation (against lookat) axis rightdirection
        upDirection.x=upDirection.x*cos(ang)+rightDirection.x*sin(ang);
        upDirection.y=upDirection.y*cos(ang)+rightDirection.y*sin(ang);
        upDirection.z=upDirection.z*cos(ang)+rightDirection.z*sin(ang);

        //new rightdirection will be cross product of new lookat and updirection

        rightDirection.x=lookAt.y*upDirection.z-lookAt.z*upDirection.y;
        rightDirection.y= -(lookAt.x*upDirection.z-lookAt.z*upDirection.x);
        rightDirection.z=lookAt.x*upDirection.y-lookAt.y*upDirection.x;
        break;

    case '6':
         //double ang=cameraRotation*pi/180;
         //updirection vector rotation (against lookat) axis rightdirection
        upDirection.x=upDirection.x*cos(ang)-rightDirection.x*sin(ang);
        upDirection.y=upDirection.y*cos(ang)-rightDirection.y*sin(ang);
        upDirection.z=upDirection.z*cos(ang)-rightDirection.z*sin(ang);

        //new rightdirection will be cross product of new lookat and updirection

        rightDirection.x=lookAt.y*upDirection.z-lookAt.z*upDirection.y;
        rightDirection.y= -(lookAt.x*upDirection.z-lookAt.z*upDirection.x);
        rightDirection.z=lookAt.x*upDirection.y-lookAt.y*upDirection.x;
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
        //cameraHeight -= 3.0;
        //backward movement
        cameraPosition.x=cameraPosition.x-2.0*lookAt.x;
        cameraPosition.y=cameraPosition.y-2.0*lookAt.y;
        cameraPosition.z=cameraPosition.z-2.0*lookAt.z;
        break;
    case GLUT_KEY_UP:		// up arrow key
        //cameraHeight += 3.0;
        //forward movement
        cameraPosition.x=cameraPosition.x+2.0*lookAt.x;
        cameraPosition.y=cameraPosition.y+2.0*lookAt.y;
        cameraPosition.z=cameraPosition.z+2.0*lookAt.z;
        break;

    case GLUT_KEY_RIGHT:
        //cameraAngle += 0.03;
        //right movement
        cameraPosition.x=cameraPosition.x+2.0*rightDirection.x;
        cameraPosition.y=cameraPosition.y+2.0*rightDirection.y;
        cameraPosition.z=cameraPosition.z+2.0*rightDirection.z;
        break;
    case GLUT_KEY_LEFT:
        //cameraAngle -= 0.03;
        //left movement
        cameraPosition.x=cameraPosition.x-2.0*rightDirection.x;
        cameraPosition.y=cameraPosition.y-2.0*rightDirection.y;
        cameraPosition.z=cameraPosition.z-2.0*rightDirection.z;
        break;

    case GLUT_KEY_PAGE_UP:
        //up movement
        cameraPosition.x=cameraPosition.x+2.0*upDirection.x;
        cameraPosition.y=cameraPosition.y+2.0*upDirection.y;
        cameraPosition.z=cameraPosition.z+2.0*upDirection.z;
        break;
    case GLUT_KEY_PAGE_DOWN:
        //down movement
        cameraPosition.x=cameraPosition.x-2.0*upDirection.x;
        cameraPosition.y=cameraPosition.y-2.0*upDirection.y;
        cameraPosition.z=cameraPosition.z-2.0*upDirection.z;
        break;

    case GLUT_KEY_INSERT:
        break;

    case GLUT_KEY_HOME:
        box.cubeToSphere();
        break;


    case GLUT_KEY_END:
        box.sphereToCube();
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

    // gluLookAt(200,200,50,	0,0,0,	0,0,1);
    //gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    //gluLookAt(0,0,200,	0,0,0,	0,1,0);
    gluLookAt(cameraPosition.x,cameraPosition.y,cameraPosition.z,
              cameraPosition.x+lookAt.x,cameraPosition.y+lookAt.y,cameraPosition.z+lookAt.z,
            upDirection.x,upDirection.y,upDirection.z);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawAxes();
    drawGrid();
    //box.draw2();
    box.drawBox();
    //glColor3f(1,0,0);
    //drawSquare(10);



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

void cameraInit(){

    cameraPosition.x=200.0;
    cameraPosition.y=300.0;
    cameraPosition.z=0.0;

    upDirection.x=0.0;
    upDirection.y=0.0;
    upDirection.z=1.0;

    lookAt.x=-1/sqrt(2);
    lookAt.y=-1/sqrt(2);
    lookAt.z=0;

    rightDirection.x=-1/sqrt(2);
    rightDirection.y=1/sqrt(2);
    rightDirection.z=0;

    cameraRotation=5.0;

}

void init()
{
    //codes for initialization
    drawgrid=0;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;
    angle=0;

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
    cameraInit();

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing

    glutDisplayFunc(display);	//display callback function
    glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();		//The main loop of OpenGL

    return 0;
}
