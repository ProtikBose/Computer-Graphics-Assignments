#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <windows.h>
#include <glut.h>
#define changeAngle 2
#define pi (2*acos(0.0))
#define degToRad (pi/180)
#define angleChange 2.0

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double forwardAngle;
double rotateAngle;
double wheelRad;

typedef struct point
{
    double x,y,z;
}point;

point wheelCenter;
point upVector;
point directionVector;
point headPos;

point rotateAround(point axis, point vect, double angle);

void drawGrid()
{
    int i;
    if(drawgrid==1)
    {
        glColor3f(0.6, 0.6, 0.6);   //grey
        glBegin(GL_LINES);{
            for(i=-8;i<=8;i++){

                //lines parallel to Y-axis
                glVertex3f(i*10, -30,-90);
                glVertex3f(i*10, -30, 90);

                //lines parallel to X-axis
                glVertex3f(-90, -30, i*10);
                glVertex3f( 90, -30, i*10);
            }
        }glEnd();
    }
}


void drawWheel(double radius, double width, double segments){

    glTranslatef(wheelCenter.x, wheelCenter.y, wheelCenter.z);
    glRotatef(rotateAngle, 0,1,0);
    glRotatef(forwardAngle, 0,0,-1);

    int i;
    struct point points[100];
    //glColor3f(0.8,0.8,0.8);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw wheel
    for(i=0;i<segments;i++)
    {
        if(i<(segments/2))
            glColor3f(1.0,0.0,0.0);
        else
            glColor3f(0.600, 0.196, 0.800);
        glBegin(GL_QUADS);
        {
            glVertex3f(points[i].x,points[i].y,width/2);
            glVertex3f(points[i+1].x,points[i+1].y,width/2);
            glVertex3f(points[i+1].x,points[i+1].y,-width/2);
            glVertex3f(points[i].x,points[i].y,-width/2);
        }
        glEnd();
    }

    //draw wheel sticks
    glColor3f(0.678, 1.000, 0.184);
    glBegin(GL_QUADS);{
        glVertex3f(0, radius, -width/4);
        glVertex3f(0, radius, width/4);
        glVertex3f(0, -radius, width/4);
        glVertex3f(0, -radius, -width/4);

    }glEnd();

    glBegin(GL_QUADS);{
        glVertex3f(-radius, 0, -width/4);
        glVertex3f(-radius, 0, width/4);
        glVertex3f(radius, 0, width/4);
        glVertex3f(radius, 0,-width/4);

    }glEnd();

}

void drawPointer(){
    glColor3f(1,0,0);
    glTranslatef(headPos.x, headPos.y, headPos.z);
    glRotatef(rotateAngle, upVector.x,upVector.y,upVector.z);

    glBegin(GL_TRIANGLES);{
        glVertex3f(0,0,0);
        glVertex3f(-10,0,10);
        glVertex3f(10,0,10);
    }glEnd();

    /*glColor3f(1,1,0);
    glBegin(GL_LINE);{
        glVertex3f(0,0,0);
        glVertex3f(0,10,0);
    }glEnd();*/
}


void keyboardListener(unsigned char key, int x,int y){
    switch(key){

        case 'w':
            forwardAngle += angleChange;
            wheelCenter.x += degToRad*angleChange*wheelRad*directionVector.x;
            wheelCenter.y += degToRad*angleChange*wheelRad*directionVector.y;
            wheelCenter.z += degToRad*angleChange*wheelRad*directionVector.z;
            break;
        case 's':
            forwardAngle -= angleChange;
            wheelCenter.x -= degToRad*angleChange*wheelRad*directionVector.x;
            wheelCenter.y -= degToRad*angleChange*wheelRad*directionVector.y;
            wheelCenter.z -= degToRad*angleChange*wheelRad*directionVector.z;
            break;
        case 'a':
            rotateAngle += angleChange;
            directionVector = rotateAround(upVector, directionVector, angleChange);
            break;
        case 'd':
            rotateAngle -= angleChange;
            directionVector = rotateAround(upVector, directionVector, -angleChange);
            break;

        default:
            break;
    }
}


void specialKeyListener(int key, int x,int y){
    switch(key){
        case GLUT_KEY_DOWN:     //down arrow key
            cameraHeight -= 3.0;

            break;
        case GLUT_KEY_UP:       // up arrow key
            cameraHeight += 3.0;

            break;

        case GLUT_KEY_RIGHT:
            rotateAngle += angleChange;
            directionVector = rotateAround(upVector, directionVector, angleChange);

            break;
        case GLUT_KEY_LEFT:
            rotateAngle -= angleChange;
            directionVector = rotateAround(upVector, directionVector, -angleChange);

            break;

        case GLUT_KEY_PAGE_UP:

            break;
        case GLUT_KEY_PAGE_DOWN:

            break;

        default:
            break;
    }
}


void mouseListener(int button, int state, int x, int y){    //x, y is the x-y of the screen (2D)
    switch(button){
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN){     // 2 times?? in ONE click? -- solution is checking DOWN or UP
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



void display(){

    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,0,0,0);  //color black
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

    gluLookAt(200*cos(cameraAngle),cameraHeight,200*sin(cameraAngle),   0,0,0,      0,1,0);

    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);


    /****************************
    / Add your objects from here
    ****************************/
    //add objects

    drawGrid();

    //drawWheel(wheelRad, 20, 24);
    drawPointer();
    /*glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);{
        glVertex3f(0,0,0);
        glVertex3f(-20,20,0);
        glVertex3f(20,20,0);
    }glEnd();*/



    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate(){

    headPos.x += directionVector.x*0.03;
    headPos.y += directionVector.y*0.03;
    headPos.z += directionVector.z*0.03;
    //codes for any changes in Models, Camera
    glutPostRedisplay();
}

void init(){
    //codes for initialization
    drawgrid=1;
    drawaxes=1;
    cameraHeight=150.0;
    cameraAngle=1.0;

    wheelRad = 30;
    wheelCenter =  {0,0,0};
    upVector = {0,1,0};
    directionVector = {0,0,-1};
    rotateAngle = 0;
    headPos = {0,0,0};
    forwardAngle = 0;


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
    gluPerspective(80,  1,  1,  1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}

int main(int argc, char **argv){
    glutInit(&argc,argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(450, 250);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);   //Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program"); //title of the window

    init();

    glEnable(GL_DEPTH_TEST);    //enable Depth Testing

    glutDisplayFunc(display);   //display callback function
    glutIdleFunc(animate);      //what you want to do in the idle time (when no drawing is occuring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();     //The main loop of OpenGL

    return 0;
}



point rotateAround(point axis, point vect, double angle){

    point ret;

    point perp = {(axis.y*vect.z - axis.z*vect.y), -(axis.x*vect.z - axis.z*vect.x), (axis.x*vect.y - axis.y*vect.x)};
    ret = {perp.x*sin(degToRad*angle)+ vect.x*cos(degToRad*angle), perp.y*sin(degToRad*angle)+ vect.y*cos(degToRad*angle), perp.z*sin(degToRad*angle)+ vect.z*cos(degToRad*angle)};

    return ret;
}
