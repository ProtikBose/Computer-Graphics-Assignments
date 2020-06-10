#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#include <windows.h>
#include <glut.h>
#include<bits/stdc++.h>
#include "bitmap_image.hpp"
#define pi (2*acos(0.0))

using namespace std;


double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double cameraRotation;

int levelOfRec,numOfPixel,numOfObject;
int numberOfTilesInaSide=20;
int numOfLight;

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
            glVertex3f( 100,0,0);
            glVertex3f(-100,0,0);

            glVertex3f(0,-100,0);
            glVertex3f(0, 100,0);

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


class sphereClass
{


public:

    double centerPosX,centerPosY,centerPosZ;
    double radiusOfSphere;
    double colorOfRed,colorOfGreen,colorOfBlue;
    double ambientCoEff,diffuseCoEff,specularCoEff,reflectionCoEff;
    double specularExponent;

    sphereClass()
    {

    }




};

class triangleClass
{

public:

    double trianglePointAX,trianglePointAY,trianglePointAZ;
    double trianglePointBX,trianglePointBY,trianglePointBZ;
    double trianglePointCX,trianglePointCY,trianglePointCZ;


    triangleClass()
    {


    }


};

class pyramidClass
{


public:

    double lowestPosX,lowestPosY,lowestPosZ;
    double lengthOfBase,heightOfPyramid;
    double colorOfRed,colorOfGreen,colorOfBlue;
    double ambientCoEff,diffuseCoEff,specularCoEff,reflectionCoEff;
    double specularExponent;

    triangleClass triangleOne,triangleTwo,triangleThree,triangleFour;
    triangleClass allTriangle[4];


    pyramidClass()
    {

    }


    void setTriangleOne()
    {

        triangleOne.trianglePointAX=0+lowestPosX;
        triangleOne.trianglePointAY=0+lowestPosY;
        triangleOne.trianglePointAZ=0+lowestPosZ;

        triangleOne.trianglePointBX=0+lowestPosX;
        triangleOne.trianglePointBY=lengthOfBase+lowestPosY;
        triangleOne.trianglePointBZ=0+lowestPosZ;

        triangleOne.trianglePointCX=lengthOfBase/2+lowestPosX;
        triangleOne.trianglePointCY=lengthOfBase/2+lowestPosY;
        triangleOne.trianglePointCZ=heightOfPyramid+lowestPosZ;

        allTriangle[0]=triangleOne;

    }

    void setTriangleTwo()
    {

        triangleTwo.trianglePointAX=0+lowestPosX;
        triangleTwo.trianglePointAY=0+lowestPosY;
        triangleTwo.trianglePointAZ=0+lowestPosZ;

        triangleTwo.trianglePointBX=lengthOfBase+lowestPosX;
        triangleTwo.trianglePointBY=0+lowestPosY;
        triangleTwo.trianglePointBZ=0+lowestPosZ;

        triangleTwo.trianglePointCX=lengthOfBase/2+lowestPosX;
        triangleTwo.trianglePointCY=lengthOfBase/2+lowestPosY;
        triangleTwo.trianglePointCZ=heightOfPyramid+lowestPosZ;

        allTriangle[1]=triangleTwo;

    }

    void setTriangleThree()
    {

        triangleThree.trianglePointAX=lengthOfBase+lowestPosX;
        triangleThree.trianglePointAY=0+lowestPosY;
        triangleThree.trianglePointAZ=0+lowestPosZ;

        triangleThree.trianglePointBX=lengthOfBase+lowestPosX;
        triangleThree.trianglePointBY=lengthOfBase+lowestPosY;
        triangleThree.trianglePointBZ=0+lowestPosZ;

        triangleThree.trianglePointCX=lengthOfBase/2+lowestPosX;
        triangleThree.trianglePointCY=lengthOfBase/2+lowestPosY;
        triangleThree.trianglePointCZ=heightOfPyramid+lowestPosZ;

        allTriangle[2]=triangleThree;

    }

    void setTriangleFour()
    {

        triangleFour.trianglePointAX=0+lowestPosX;
        triangleFour.trianglePointAY=lengthOfBase+lowestPosY;
        triangleFour.trianglePointAZ=0+lowestPosZ;

        triangleFour.trianglePointBX=lengthOfBase+lowestPosX;
        triangleFour.trianglePointBY=lengthOfBase+lowestPosY;
        triangleFour.trianglePointBZ=0+lowestPosZ;

        triangleFour.trianglePointCX=lengthOfBase/2+lowestPosX;
        triangleFour.trianglePointCY=lengthOfBase/2+lowestPosY;
        triangleFour.trianglePointCZ=heightOfPyramid+lowestPosZ;

        allTriangle[3]=triangleFour;

    }

    //allTriangle[0]=new triangleClass();
    //allTriangle[0]=triangleOne;
    //allTriangle[1]=triangleTwo;
    //allTriangle[2]=triangleThree;
    //allTriangle[3]=triangleFour;



};

class RGBColorClass
{

public:
    double redColor,greenColor,blueColor;

    RGBColorClass()
    {


    }


};

class lightSourcesClass
{

public:
    double positionX,positionY,positionZ;

    lightSourcesClass()
    {

    }

};




vector<sphereClass>sphereVector;
vector<pyramidClass>pyramidVector;
vector<lightSourcesClass>lightVector;

double calculateDeterminant(double matrix[3][3])
{
    double value=matrix[0][0]*(matrix[1][1]*matrix[2][2] - matrix[1][2]*matrix[2][1]) - matrix[0][1]*(matrix[1][0]*matrix[2][2] - matrix[1][2]*matrix[2][0])
                 + matrix[0][2]*(matrix[1][0]*matrix[2][1] - matrix[2][0]*matrix[1][1]);
    return value;
}


double calculateTriangleArea(triangleClass triangleCheck)
{

    point firstVector,secondVector;
    firstVector.x=triangleCheck.trianglePointBX-triangleCheck.trianglePointAX;
    firstVector.y=triangleCheck.trianglePointBY-triangleCheck.trianglePointAY;
    firstVector.z=triangleCheck.trianglePointBZ-triangleCheck.trianglePointAZ;

    secondVector.x=triangleCheck.trianglePointCX-triangleCheck.trianglePointAX;
    secondVector.y=triangleCheck.trianglePointCY-triangleCheck.trianglePointAY;
    secondVector.z=triangleCheck.trianglePointCZ-triangleCheck.trianglePointAZ;

    point resultOfCrossProduct;
    resultOfCrossProduct.x=firstVector.y*secondVector.z-firstVector.z*secondVector.y;
    resultOfCrossProduct.y= -firstVector.x*secondVector.z+firstVector.z*secondVector.x;
    resultOfCrossProduct.z=firstVector.x*secondVector.y-firstVector.y*secondVector.x;

    double magnitudeOfProduct;
    magnitudeOfProduct=sqrt(resultOfCrossProduct.x*resultOfCrossProduct.x+resultOfCrossProduct.y*resultOfCrossProduct.y+resultOfCrossProduct.z*resultOfCrossProduct.z);
    magnitudeOfProduct=0.5*magnitudeOfProduct;

    return magnitudeOfProduct;

}

bool intersectingPointInsideTriangle(point point,triangleClass triangleCheck)
{

    double wholePartTriangle;
    double firstTraingleArea,secondTraingleArea,thirdTraingleArea,fourthTraingleArea;

    wholePartTriangle=calculateTriangleArea(triangleCheck);

    triangleClass triangleOne;
    triangleOne.trianglePointAX=triangleCheck.trianglePointAX;
    triangleOne.trianglePointAY=triangleCheck.trianglePointAY;
    triangleOne.trianglePointAZ=triangleCheck.trianglePointAZ;
    triangleOne.trianglePointBX=triangleCheck.trianglePointBX;
    triangleOne.trianglePointBY=triangleCheck.trianglePointBY;
    triangleOne.trianglePointBZ=triangleCheck.trianglePointBZ;
    triangleOne.trianglePointCX=point.x;
    triangleOne.trianglePointCY=point.y;
    triangleOne.trianglePointCZ=point.z;

    firstTraingleArea=calculateTriangleArea(triangleOne);

    triangleClass triangleTwo;
    triangleTwo.trianglePointAX=triangleCheck.trianglePointCX;
    triangleTwo.trianglePointAY=triangleCheck.trianglePointCY;
    triangleTwo.trianglePointAZ=triangleCheck.trianglePointCZ;
    triangleTwo.trianglePointBX=triangleCheck.trianglePointBX;
    triangleTwo.trianglePointBY=triangleCheck.trianglePointBY;
    triangleTwo.trianglePointBZ=triangleCheck.trianglePointBZ;
    triangleTwo.trianglePointCX=point.x;
    triangleTwo.trianglePointCY=point.y;
    triangleTwo.trianglePointCZ=point.z;

    secondTraingleArea=calculateTriangleArea(triangleTwo);

    triangleClass triangleThree;
    triangleThree.trianglePointAX=triangleCheck.trianglePointCX;
    triangleThree.trianglePointAY=triangleCheck.trianglePointCY;
    triangleThree.trianglePointAZ=triangleCheck.trianglePointCZ;
    triangleThree.trianglePointBX=triangleCheck.trianglePointAX;
    triangleThree.trianglePointBY=triangleCheck.trianglePointAY;
    triangleThree.trianglePointBZ=triangleCheck.trianglePointAZ;
    triangleThree.trianglePointCX=point.x;
    triangleThree.trianglePointCY=point.y;
    triangleThree.trianglePointCZ=point.z;

    thirdTraingleArea=calculateTriangleArea(triangleThree);

    double maxDiff=0.1;

    if(abs(firstTraingleArea+secondTraingleArea+thirdTraingleArea-wholePartTriangle)<maxDiff)
    {
        //cout<<"true"<<endl;
        return true;
    }
    else
        return false;


}

point calculateNormalOfTriangle(triangleClass triangleCheck)
{

    point firstVector,secondVector;
    firstVector.x=triangleCheck.trianglePointBX-triangleCheck.trianglePointAX;
    firstVector.y=triangleCheck.trianglePointBY-triangleCheck.trianglePointAY;
    firstVector.z=triangleCheck.trianglePointBZ-triangleCheck.trianglePointAZ;

    secondVector.x=triangleCheck.trianglePointCX-triangleCheck.trianglePointAX;
    secondVector.y=triangleCheck.trianglePointCY-triangleCheck.trianglePointAY;
    secondVector.z=triangleCheck.trianglePointCZ-triangleCheck.trianglePointAZ;

    point resultOfCrossProduct;
    resultOfCrossProduct.x=firstVector.y*secondVector.z-firstVector.z*secondVector.y;
    resultOfCrossProduct.y= -firstVector.x*secondVector.z+firstVector.z*secondVector.x;
    resultOfCrossProduct.z=firstVector.x*secondVector.y-firstVector.y*secondVector.x;

    return resultOfCrossProduct;

}

int checkForRayMovementFreely(lightSourcesClass tempLight,point tempPoint)
{
    point directionOfChecking;
    point originPoint,rayDirection;

    tempPoint.x=tempPoint.x+0.01;
    tempPoint.y=tempPoint.y+0.01;
    tempPoint.z=tempPoint.z+0.01;

    directionOfChecking.x=tempLight.positionX-tempPoint.x;
    directionOfChecking.y=tempLight.positionY-tempPoint.y;
    directionOfChecking.z=tempLight.positionZ-tempPoint.z;

    double magnitudeOfChecking;

    magnitudeOfChecking=sqrt(directionOfChecking.x*directionOfChecking.x+directionOfChecking.y*directionOfChecking.y+directionOfChecking.z*directionOfChecking.z);
    directionOfChecking.x=directionOfChecking.x/magnitudeOfChecking;
    directionOfChecking.y=directionOfChecking.y/magnitudeOfChecking;
    directionOfChecking.z=directionOfChecking.z/magnitudeOfChecking;

    originPoint=tempPoint;
    rayDirection=directionOfChecking;
    double answer=magnitudeOfChecking;

    for(int i=0; i<sphereVector.size(); i++)
    {

        sphereClass sphereCla;
        sphereCla=sphereVector[i];

        point rDot;
        rDot.x=originPoint.x-sphereCla.centerPosX;
        rDot.y=originPoint.y-sphereCla.centerPosY;
        rDot.z=originPoint.z-sphereCla.centerPosZ;

        double dotProductOfB=rDot.x*rayDirection.x+rDot.y*rayDirection.y+rDot.z*rayDirection.z;
        double dotProductOfC=rDot.x*rDot.x+rDot.y*rDot.y+rDot.z*rDot.z;

        double quadraticValueA=1;
        double quadraticValueB=2*dotProductOfB;
        double quadraticValueC=dotProductOfC-sphereCla.radiusOfSphere*sphereCla.radiusOfSphere;

        double determinant=quadraticValueB*quadraticValueB-4*quadraticValueA*quadraticValueC;

        if(determinant>=0)
        {

            double tPositive,tNegative;
            tPositive= (-quadraticValueB+sqrt(determinant))/(2*quadraticValueA);
            tNegative= (-quadraticValueB-sqrt(determinant))/(2*quadraticValueA);

            if(tPositive>0 && tPositive<answer )
            {
                return 1;
            }

            if(tNegative>0 && tNegative<answer)
            {
                return 1;
            }


        }



    }


    for(int i=0; i<pyramidVector.size(); i++)
    {
        pyramidClass pyramidCla=pyramidVector[i];
        for(int j=0; j<4; j++)
        {

            triangleClass triangle=pyramidCla.allTriangle[j];
            point firstPoint,secondPoint,thirdPoint;

            firstPoint.x=triangle.trianglePointAX;
            firstPoint.y=triangle.trianglePointAY;
            firstPoint.z=triangle.trianglePointAZ;

            secondPoint.x=triangle.trianglePointBX;
            secondPoint.y=triangle.trianglePointBY;
            secondPoint.z=triangle.trianglePointBZ;

            thirdPoint.x=triangle.trianglePointCX;
            thirdPoint.y=triangle.trianglePointCY;
            thirdPoint.z=triangle.trianglePointCZ;

            point originVector;
            originVector.x=firstPoint.x-originPoint.x;
            originVector.y=firstPoint.y-originPoint.y;
            originVector.z=firstPoint.z-originPoint.z;

            /* double determinantOfAll=(firstPoint.x-secondPoint.x)*(rayDirection.z*(firstPoint.y-thirdPoint.y)-rayDirection.y*(firstPoint.z-thirdPoint.z))-
                                     (firstPoint.x-thirdPoint.x)*(rayDirection.z*(firstPoint.y-secondPoint.y)-rayDirection.y*(firstPoint.z-secondPoint.z))+
                                     (rayDirection.x)*((firstPoint.y-secondPoint.y)*(firstPoint.z-thirdPoint.z)-(firstPoint.y-thirdPoint.y)*(firstPoint.z-secondPoint.z));
             //cout<<determinantOfAll<<endl;
             if(determinantOfAll==0) continue;
             //cout<<"entering"<<endl;
             double betaValue= (firstPoint.x-originVector.x)*(rayDirection.z*(firstPoint.y-thirdPoint.y)-rayDirection.y*(firstPoint.z-thirdPoint.z))-
                               (firstPoint.x-thirdPoint.x)*(rayDirection.z*(firstPoint.y-originVector.y)-rayDirection.y*(firstPoint.z-originVector.z))+
                               (rayDirection.x)*((firstPoint.y-originVector.y)*(firstPoint.z-thirdPoint.z)-(firstPoint.y-thirdPoint.y)*(firstPoint.z-originVector.z));

             double gammaValue=(firstPoint.x-secondPoint.x)*(rayDirection.z*(firstPoint.y-originVector.y)-rayDirection.y*(firstPoint.z-originVector.z))-
                               (firstPoint.x-originVector.x)*(rayDirection.z*(firstPoint.y-secondPoint.y)-rayDirection.y*(firstPoint.z-secondPoint.z))+
                               (rayDirection.x)*((firstPoint.y-secondPoint.y)*(firstPoint.z-originVector.z)-(firstPoint.y-originVector.y)*(firstPoint.z-secondPoint.z));

             double tvalue=(firstPoint.x-secondPoint.x)*((firstPoint.z-originVector.z)*(firstPoint.y-thirdPoint.y)-(firstPoint.y-originVector.y)*(firstPoint.z-thirdPoint.z))-
                           (firstPoint.x-thirdPoint.x)*((firstPoint.z-originVector.z)*(firstPoint.y-secondPoint.y)-(firstPoint.y-originVector.y)*(firstPoint.z-secondPoint.z))+
                           (firstPoint.x-originVector.x)*((firstPoint.y-secondPoint.y)*(firstPoint.z-thirdPoint.z)-(firstPoint.y-thirdPoint.y)*(firstPoint.z-secondPoint.z));

             betaValue=betaValue/determinantOfAll;
             gammaValue=gammaValue/determinantOfAll;
             tvalue=tvalue/determinantOfAll; */

            double upperMatrix[3][3]= {{originVector.x,firstPoint.x-secondPoint.x,firstPoint.x-thirdPoint.x},
                {originVector.y,firstPoint.y-secondPoint.y,firstPoint.y-thirdPoint.y},
                {originVector.z,firstPoint.z-secondPoint.z,firstPoint.z-thirdPoint.z}
            };

            double lowerMatrix[3][3]= {{rayDirection.x,firstPoint.x-secondPoint.x,firstPoint.x-thirdPoint.x},
                {rayDirection.y,firstPoint.y-secondPoint.y,firstPoint.y-thirdPoint.y},
                {rayDirection.z,firstPoint.z-secondPoint.z,firstPoint.z-thirdPoint.z}
            };

            double betaMatrix[3][3]= {{originVector.x,firstPoint.x-thirdPoint.x,rayDirection.x},
                {originVector.y,firstPoint.y-thirdPoint.y,rayDirection.y},
                {originVector.z,firstPoint.z-thirdPoint.z,rayDirection.z}
            };

            double gammaMatrix[3][3]= {{firstPoint.x-secondPoint.x,originVector.x,rayDirection.x},
                {firstPoint.y-secondPoint.y,originVector.y,rayDirection.y},
                {firstPoint.z-secondPoint.z,originVector.z,rayDirection.z}
            };


            double val=calculateDeterminant(lowerMatrix);
            if(val==0) continue;

            double tvalue=calculateDeterminant(upperMatrix)/val;

            double betaValue=calculateDeterminant(betaMatrix)/val;
            double gammaValue=calculateDeterminant(gammaMatrix)/val;
            //cout<<tvalue<<endl;
            //if(betaValue<=0 || gammaValue<=0 || betaValue+gammaValue>1 || tvalue<=0) continue;
            //cout<<"entering"<<endl;
            if(tvalue<0) continue;
            //cout<<tvalue<<endl;
            point tempPoints;
            tempPoints.x=originPoint.x+tvalue*rayDirection.x;
            tempPoints.y=originPoint.y+tvalue*rayDirection.y;
            tempPoints.z=originPoint.z+tvalue*rayDirection.z;
            //cout<<"working"<<endl;
            if(intersectingPointInsideTriangle(tempPoints,triangle))
            {
                //cout<<"1"<<endl;
                if(tvalue<answer)
                {
                    //cout<<"2"<<endl;
                    return 1;
                }
            }


        }
    }

    return 0;





}



RGBColorClass calculateColorFromPoint(point originPoint,int levelOfReflection,point rayDirection,int num)
{

    double magnitudeOfRay;

    magnitudeOfRay=sqrt(rayDirection.x*rayDirection.x+rayDirection.y*rayDirection.y+rayDirection.z*rayDirection.z);
    rayDirection.x=rayDirection.x/magnitudeOfRay;
    rayDirection.y=rayDirection.y/magnitudeOfRay;
    rayDirection.z=rayDirection.z/magnitudeOfRay;

    RGBColorClass resultColor;
    resultColor.redColor=0.0;
    resultColor.greenColor=0.0;
    resultColor.blueColor=0.0;

    //cout<<levelOfReflection<<endl;

    point rayIntersectionPoint;
    point planeNormalPoint;
    double ambientCoefficient,diffuseCoefficient;
    double specularCoefficient,reflectionCoefficient;
    double specularExponent;

    if(levelOfReflection==0)
    {

        RGBColorClass RGBCol;

        RGBCol.redColor=0.0;
        RGBCol.greenColor=0.0;
        RGBCol.blueColor=0.0;

        return RGBCol;
    }

    double answer;
    answer=1000.0;

    for(int i=0; i<sphereVector.size(); i++)
    {

        sphereClass sphereCla;
        sphereCla=sphereVector[i];

        point rDot;
        rDot.x=originPoint.x-sphereCla.centerPosX;
        rDot.y=originPoint.y-sphereCla.centerPosY;
        rDot.z=originPoint.z-sphereCla.centerPosZ;

        double dotProductOfB=rDot.x*rayDirection.x+rDot.y*rayDirection.y+rDot.z*rayDirection.z;
        double dotProductOfC=rDot.x*rDot.x+rDot.y*rDot.y+rDot.z*rDot.z;

        double quadraticValueA=1;
        double quadraticValueB=2*dotProductOfB;
        double quadraticValueC=dotProductOfC-sphereCla.radiusOfSphere*sphereCla.radiusOfSphere;

        double determinant=quadraticValueB*quadraticValueB-4*quadraticValueA*quadraticValueC;

        if(determinant>=0)
        {

            double tPositive,tNegative;
            tPositive= (-quadraticValueB+sqrt(determinant))/(2*quadraticValueA);
            tNegative= (-quadraticValueB-sqrt(determinant))/(2*quadraticValueA);

            if(tPositive>0 && tPositive<answer )
            {
                answer=tPositive;
            }

            if(tNegative>0 && tNegative<answer)
            {
                answer=tNegative;
            }

            if(answer==tPositive || answer==tNegative)
            {

                rayIntersectionPoint.x=originPoint.x+answer*rayDirection.x;
                rayIntersectionPoint.y=originPoint.y+answer*rayDirection.y;
                rayIntersectionPoint.z=originPoint.z+answer*rayDirection.z;

                planeNormalPoint.x=rayIntersectionPoint.x-sphereCla.centerPosX;
                planeNormalPoint.y=rayIntersectionPoint.y-sphereCla.centerPosY;
                planeNormalPoint.z=rayIntersectionPoint.z-sphereCla.centerPosZ;

                ambientCoefficient=sphereCla.ambientCoEff;
                diffuseCoefficient=sphereCla.diffuseCoEff;
                specularCoefficient=sphereCla.specularCoEff;
                reflectionCoefficient=sphereCla.reflectionCoEff;
                specularExponent=sphereCla.specularExponent;

                resultColor.redColor=sphereCla.colorOfRed;
                resultColor.greenColor=sphereCla.colorOfGreen;
                resultColor.blueColor=sphereCla.colorOfBlue;

            }
        }



    }

    for(int i=0; i<pyramidVector.size(); i++)
    {
        pyramidClass pyramidCla=pyramidVector[i];
        for(int j=0; j<4; j++)
        {

            triangleClass triangle=pyramidCla.allTriangle[j];
            point firstPoint,secondPoint,thirdPoint;

            firstPoint.x=triangle.trianglePointAX;
            firstPoint.y=triangle.trianglePointAY;
            firstPoint.z=triangle.trianglePointAZ;

            secondPoint.x=triangle.trianglePointBX;
            secondPoint.y=triangle.trianglePointBY;
            secondPoint.z=triangle.trianglePointBZ;

            thirdPoint.x=triangle.trianglePointCX;
            thirdPoint.y=triangle.trianglePointCY;
            thirdPoint.z=triangle.trianglePointCZ;

            point originVector;
            originVector.x=firstPoint.x-originPoint.x;
            originVector.y=firstPoint.y-originPoint.y;
            originVector.z=firstPoint.z-originPoint.z;

            /* double determinantOfAll=(firstPoint.x-secondPoint.x)*(rayDirection.z*(firstPoint.y-thirdPoint.y)-rayDirection.y*(firstPoint.z-thirdPoint.z))-
                                     (firstPoint.x-thirdPoint.x)*(rayDirection.z*(firstPoint.y-secondPoint.y)-rayDirection.y*(firstPoint.z-secondPoint.z))+
                                     (rayDirection.x)*((firstPoint.y-secondPoint.y)*(firstPoint.z-thirdPoint.z)-(firstPoint.y-thirdPoint.y)*(firstPoint.z-secondPoint.z));
             //cout<<determinantOfAll<<endl;
             if(determinantOfAll==0) continue;
             //cout<<"entering"<<endl;
             double betaValue= (firstPoint.x-originVector.x)*(rayDirection.z*(firstPoint.y-thirdPoint.y)-rayDirection.y*(firstPoint.z-thirdPoint.z))-
                               (firstPoint.x-thirdPoint.x)*(rayDirection.z*(firstPoint.y-originVector.y)-rayDirection.y*(firstPoint.z-originVector.z))+
                               (rayDirection.x)*((firstPoint.y-originVector.y)*(firstPoint.z-thirdPoint.z)-(firstPoint.y-thirdPoint.y)*(firstPoint.z-originVector.z));

             double gammaValue=(firstPoint.x-secondPoint.x)*(rayDirection.z*(firstPoint.y-originVector.y)-rayDirection.y*(firstPoint.z-originVector.z))-
                               (firstPoint.x-originVector.x)*(rayDirection.z*(firstPoint.y-secondPoint.y)-rayDirection.y*(firstPoint.z-secondPoint.z))+
                               (rayDirection.x)*((firstPoint.y-secondPoint.y)*(firstPoint.z-originVector.z)-(firstPoint.y-originVector.y)*(firstPoint.z-secondPoint.z));

             double tvalue=(firstPoint.x-secondPoint.x)*((firstPoint.z-originVector.z)*(firstPoint.y-thirdPoint.y)-(firstPoint.y-originVector.y)*(firstPoint.z-thirdPoint.z))-
                           (firstPoint.x-thirdPoint.x)*((firstPoint.z-originVector.z)*(firstPoint.y-secondPoint.y)-(firstPoint.y-originVector.y)*(firstPoint.z-secondPoint.z))+
                           (firstPoint.x-originVector.x)*((firstPoint.y-secondPoint.y)*(firstPoint.z-thirdPoint.z)-(firstPoint.y-thirdPoint.y)*(firstPoint.z-secondPoint.z));

             betaValue=betaValue/determinantOfAll;
             gammaValue=gammaValue/determinantOfAll;
             tvalue=tvalue/determinantOfAll; */

            double upperMatrix[3][3]= {{originVector.x,firstPoint.x-secondPoint.x,firstPoint.x-thirdPoint.x},
                {originVector.y,firstPoint.y-secondPoint.y,firstPoint.y-thirdPoint.y},
                {originVector.z,firstPoint.z-secondPoint.z,firstPoint.z-thirdPoint.z}
            };

            double lowerMatrix[3][3]= {{rayDirection.x,firstPoint.x-secondPoint.x,firstPoint.x-thirdPoint.x},
                {rayDirection.y,firstPoint.y-secondPoint.y,firstPoint.y-thirdPoint.y},
                {rayDirection.z,firstPoint.z-secondPoint.z,firstPoint.z-thirdPoint.z}
            };

            double betaMatrix[3][3]= {{originVector.x,firstPoint.x-thirdPoint.x,rayDirection.x},
                {originVector.y,firstPoint.y-thirdPoint.y,rayDirection.y},
                {originVector.z,firstPoint.z-thirdPoint.z,rayDirection.z}
            };

            double gammaMatrix[3][3]= {{firstPoint.x-secondPoint.x,originVector.x,rayDirection.x},
                {firstPoint.y-secondPoint.y,originVector.y,rayDirection.y},
                {firstPoint.z-secondPoint.z,originVector.z,rayDirection.z}
            };


            double val=calculateDeterminant(lowerMatrix);
            if(val==0) continue;

            double tvalue=calculateDeterminant(upperMatrix)/val;

            double betaValue=calculateDeterminant(betaMatrix)/val;
            double gammaValue=calculateDeterminant(gammaMatrix)/val;
            //cout<<tvalue<<endl;
            //if(betaValue<=0 || gammaValue<=0 || betaValue+gammaValue>1 || tvalue<=0) continue;
            //cout<<"entering"<<endl;
            if(tvalue<=0) continue;
            //cout<<tvalue<<endl;
            point tempPoint;
            tempPoint.x=originPoint.x+tvalue*rayDirection.x;
            tempPoint.y=originPoint.y+tvalue*rayDirection.y;
            tempPoint.z=originPoint.z+tvalue*rayDirection.z;
            //cout<<"working"<<endl;
            if(intersectingPointInsideTriangle(tempPoint,triangle))
            {
                //cout<<"1"<<endl;
                if(tvalue<answer)
                {
                    //cout<<"2"<<endl;
                    answer=tvalue;
                    rayIntersectionPoint=tempPoint;

                    ambientCoefficient=pyramidCla.ambientCoEff;
                    diffuseCoefficient=pyramidCla.diffuseCoEff;
                    specularCoefficient=pyramidCla.specularCoEff;
                    reflectionCoefficient=pyramidCla.reflectionCoEff;
                    specularExponent=pyramidCla.specularExponent;

                    resultColor.redColor=pyramidCla.colorOfRed;
                    resultColor.greenColor=pyramidCla.colorOfGreen;
                    resultColor.blueColor=pyramidCla.colorOfBlue;

                    planeNormalPoint=calculateNormalOfTriangle(triangle);
                }
            }


        }
    }

    //floor coloring
    point firstPoint,secondPoint,thirdPoint;
    firstPoint.x=0.0;
    firstPoint.y=0.0;
    firstPoint.z=0.0;

    secondPoint.x=1.0;
    secondPoint.y=0.0;
    secondPoint.z=0.0;

    thirdPoint.x=0.0;
    thirdPoint.y=1.0;
    thirdPoint.z=0.0;

    point originVector;
    originVector.x=firstPoint.x-originPoint.x;
    originVector.y=firstPoint.y-originPoint.y;
    originVector.z=firstPoint.z-originPoint.z;

    double upperMatrix[3][3]= {{originVector.x,firstPoint.x-secondPoint.x,firstPoint.x-thirdPoint.x},
        {originVector.y,firstPoint.y-secondPoint.y,firstPoint.y-thirdPoint.y},
        {originVector.z,firstPoint.z-secondPoint.z,firstPoint.z-thirdPoint.z}
    };

    double lowerMatrix[3][3]= {{rayDirection.x,firstPoint.x-secondPoint.x,firstPoint.x-thirdPoint.x},
        {rayDirection.y,firstPoint.y-secondPoint.y,firstPoint.y-thirdPoint.y},
        {rayDirection.z,firstPoint.z-secondPoint.z,firstPoint.z-thirdPoint.z}
    };

    double deteminanatValue=calculateDeterminant(lowerMatrix);



    double tvalue=calculateDeterminant(upperMatrix)/deteminanatValue;

    if(deteminanatValue && tvalue>=0 && tvalue<answer)
    {

        answer=tvalue;
        rayIntersectionPoint.x=originPoint.x+tvalue*rayDirection.x;
        rayIntersectionPoint.y=originPoint.y+tvalue*rayDirection.y;
        rayIntersectionPoint.z=originPoint.z+tvalue*rayDirection.z;

        ambientCoefficient=0.4;
        diffuseCoefficient=0.2;
        specularCoefficient=0.0;
        specularExponent=0.0;
        reflectionCoefficient=0.3;


        planeNormalPoint.x=0.0;
        planeNormalPoint.y=0.0;
        planeNormalPoint.z=1.0;

        int positionX,positionY;

        positionX=((int)ceil(abs(rayIntersectionPoint.x)/15.0))/2;
        positionY=((int)ceil(abs(rayIntersectionPoint.y)/15.0))/2;

        if((positionX%2==1 && positionY%2==1) || (positionX%2==0 && positionY%2==0))
        {
            resultColor.redColor=1.0;
            resultColor.greenColor=1.0;
            resultColor.blueColor=1.0;
        }
        else
        {
            resultColor.redColor=0.0;
            resultColor.greenColor=0.0;
            resultColor.blueColor=0.0;
        }

    }
    //checking far point
    if(answer==1000)
    {
        RGBColorClass RGBCol;

        RGBCol.redColor=0.0;
        RGBCol.greenColor=0.0;
        RGBCol.blueColor=0.0;

        return RGBCol;
    }


    //check light

    double valueLamportMethod=0.0;
    double valuePhongMethod=0.0;

    double magnitudeOfNormal;
    magnitudeOfNormal=sqrt(planeNormalPoint.x*planeNormalPoint.x+planeNormalPoint.y*planeNormalPoint.y+planeNormalPoint.z*planeNormalPoint.z);
    planeNormalPoint.x=planeNormalPoint.x/magnitudeOfNormal;
    planeNormalPoint.y=planeNormalPoint.y/magnitudeOfNormal;
    planeNormalPoint.z=planeNormalPoint.z/magnitudeOfNormal;


    for(int i=0; i<lightVector.size(); i++)
    {

        lightSourcesClass lightCla;
        point rayFromReflection;
        lightCla=lightVector[i];

        int checkValueForBlock;
        checkValueForBlock=checkForRayMovementFreely(lightCla,rayIntersectionPoint);
        if(checkValueForBlock==1) continue;

        //calculate reflected ray
        double dotProductInReflection;
        point lightFocusingOnPlane,lightReflectedFromPlane;
        point rayTolight;

        lightFocusingOnPlane.x=rayIntersectionPoint.x-lightCla.positionX;
        lightFocusingOnPlane.y=rayIntersectionPoint.y-lightCla.positionY;
        lightFocusingOnPlane.z=rayIntersectionPoint.z-lightCla.positionZ;

        dotProductInReflection=lightFocusingOnPlane.x*planeNormalPoint.x+lightFocusingOnPlane.y*planeNormalPoint.y+lightFocusingOnPlane.z*planeNormalPoint.z;

        lightReflectedFromPlane.x=lightFocusingOnPlane.x-2*dotProductInReflection*planeNormalPoint.x;
        lightReflectedFromPlane.y=lightFocusingOnPlane.y-2*dotProductInReflection*planeNormalPoint.y;
        lightReflectedFromPlane.z=lightFocusingOnPlane.z-2*dotProductInReflection*planeNormalPoint.z;

        double magnitudeOfReflection;

        magnitudeOfReflection=sqrt(lightReflectedFromPlane.x*lightReflectedFromPlane.x+lightReflectedFromPlane.y*lightReflectedFromPlane.y+lightReflectedFromPlane.z*lightReflectedFromPlane.z);
        lightReflectedFromPlane.x=lightReflectedFromPlane.x/magnitudeOfReflection;
        lightReflectedFromPlane.y=lightReflectedFromPlane.y/magnitudeOfReflection;
        lightReflectedFromPlane.z=lightReflectedFromPlane.z/magnitudeOfReflection;

        rayTolight.x=lightCla.positionX-rayIntersectionPoint.x;
        rayTolight.y=lightCla.positionY-rayIntersectionPoint.y;
        rayTolight.z=lightCla.positionZ-rayIntersectionPoint.z;

        double magnitudeToLight;

        magnitudeToLight=sqrt(rayTolight.x*rayTolight.x+rayTolight.y*rayTolight.y+rayTolight.z*rayTolight.z);
        rayTolight.x=rayTolight.x/magnitudeToLight;
        rayTolight.y=rayTolight.y/magnitudeToLight;
        rayTolight.z=rayTolight.z/magnitudeToLight;

        valueLamportMethod+=max(rayTolight.x*planeNormalPoint.x+rayTolight.y*planeNormalPoint.y+rayTolight.z*planeNormalPoint.z,0.0);
        valuePhongMethod+=max(pow((lightReflectedFromPlane.x*rayTolight.x+lightReflectedFromPlane.y*rayTolight.y+lightReflectedFromPlane.z*rayTolight.z),specularExponent),0.0);
        //valuePhongMethod+=pow((lightReflectedFromPlane.x*rayTolight.x+lightReflectedFromPlane.y*rayTolight.y+lightReflectedFromPlane.z*rayTolight.z),specularExponent);

    }


    //calculate color
    rayIntersectionPoint.x=rayIntersectionPoint.x+0.01;
    rayIntersectionPoint.y=rayIntersectionPoint.y+0.01;
    rayIntersectionPoint.z=rayIntersectionPoint.z+0.01;

    point recursionReflect,lightFocusingOnPlane;
    double dotProductInReflection;

    lightFocusingOnPlane.x=rayIntersectionPoint.x-originPoint.x;
    lightFocusingOnPlane.y=rayIntersectionPoint.y-originPoint.y;
    lightFocusingOnPlane.z=rayIntersectionPoint.z-originPoint.z;

    dotProductInReflection=lightFocusingOnPlane.x*planeNormalPoint.x+lightFocusingOnPlane.y*planeNormalPoint.y+lightFocusingOnPlane.z*planeNormalPoint.z;

    recursionReflect.x=lightFocusingOnPlane.x-2*dotProductInReflection*planeNormalPoint.x;
    recursionReflect.y=lightFocusingOnPlane.y-2*dotProductInReflection*planeNormalPoint.y;
    recursionReflect.z=lightFocusingOnPlane.z-2*dotProductInReflection*planeNormalPoint.z;

    RGBColorClass colorOfReflecion=calculateColorFromPoint(rayIntersectionPoint,levelOfReflection-1,recursionReflect,3);
    if(colorOfReflecion.redColor>1.0 || colorOfReflecion.greenColor>1.0 || colorOfReflecion.blueColor>1.0){
        colorOfReflecion.redColor=resultColor.redColor;
        colorOfReflecion.greenColor=resultColor.greenColor;
        colorOfReflecion.blueColor=resultColor.blueColor;
    }


    resultColor.redColor=ambientCoefficient*resultColor.redColor+valueLamportMethod*diffuseCoefficient*resultColor.redColor+
                         valuePhongMethod*specularCoefficient*resultColor.redColor+
                         reflectionCoefficient*colorOfReflecion.redColor;

    resultColor.greenColor=ambientCoefficient*resultColor.greenColor+valueLamportMethod*diffuseCoefficient*resultColor.greenColor+
                           valuePhongMethod*specularCoefficient*resultColor.greenColor+
                           reflectionCoefficient*colorOfReflecion.greenColor;

    resultColor.blueColor=ambientCoefficient*resultColor.blueColor+valueLamportMethod*diffuseCoefficient*resultColor.blueColor+
                          valuePhongMethod*specularCoefficient*resultColor.blueColor
                          +reflectionCoefficient*colorOfReflecion.greenColor;

    return resultColor;



}

void makeImageFromWindow()
{

    //cout<<"working.."<<endl;
    double widthOfFrame=2*tan(45*pi/180);
    double heightOfFrame=widthOfFrame;

    point centerPointOfFrame;
    centerPointOfFrame.x=cameraPosition.x+lookAt.x;
    centerPointOfFrame.y=cameraPosition.y+lookAt.y;
    centerPointOfFrame.z=cameraPosition.z+lookAt.z;

    point topAndLeftofFrame;
    topAndLeftofFrame.x=centerPointOfFrame.x+heightOfFrame/2*upDirection.x-widthOfFrame/2*rightDirection.x;
    topAndLeftofFrame.y=centerPointOfFrame.y+heightOfFrame/2*upDirection.y-widthOfFrame/2*rightDirection.y;
    topAndLeftofFrame.z=centerPointOfFrame.z+heightOfFrame/2*upDirection.z-widthOfFrame/2*rightDirection.z;
    //cout<<"working.."<<endl;
    //cout<<numOfPixel<<endl;
    point** allFramePoints;
    //cout<<"working.."<<endl;
    allFramePoints=new point* [numOfPixel];
    for(int i=0; i<numOfPixel; i++)
    {
        allFramePoints[i]=new point[numOfPixel];
    }


    for(int i=0; i<numOfPixel; i++)
    {
        //allFramePoints[i]=new point[numOfPixel];
        for(int j=0; j<numOfPixel; j++)
        {
            allFramePoints[i][j].x=topAndLeftofFrame.x+rightDirection.x*widthOfFrame/numOfPixel*j-upDirection.x*heightOfFrame/numOfPixel*i;
            allFramePoints[i][j].y=topAndLeftofFrame.y+rightDirection.y*widthOfFrame/numOfPixel*j-upDirection.y*heightOfFrame/numOfPixel*i;
            allFramePoints[i][j].z=topAndLeftofFrame.z+rightDirection.z*widthOfFrame/numOfPixel*j-upDirection.z*heightOfFrame/numOfPixel*i;
        }
    }
    //cout<<"working.."<<endl;
    RGBColorClass** storeColor;
    storeColor=new RGBColorClass* [numOfPixel];
    for(int i=0; i<numOfPixel; i++)
    {
        storeColor[i]=new RGBColorClass[numOfPixel];
        for(int j=0; j<numOfPixel; j++)
        {

            point rayDirection;
            rayDirection.x=allFramePoints[i][j].x-cameraPosition.x;
            rayDirection.y=allFramePoints[i][j].y-cameraPosition.y;
            rayDirection.z=allFramePoints[i][j].z-cameraPosition.z;

            storeColor[i][j]=calculateColorFromPoint(allFramePoints[i][j],levelOfRec,rayDirection,1);
        }
    }

    //cout<<"working.."<<endl;
    bitmap_image image(numOfPixel,numOfPixel);
    //bitmap_image image(500,500);
    for (int x = 0; x < numOfPixel; x++)
    {
        for (int y = 0; y < numOfPixel; y++)
        {
            image.set_pixel(x, y, storeColor[y][x].redColor*255,storeColor[y][x].greenColor*255,storeColor[y][x].blueColor*255);
        }
    }
    image.save_image("out.bmp");
    cout << "Printing Picture..." << endl;

}


void keyboardListener(unsigned char key, int x,int y)
{
    double ang=cameraRotation*pi/180;
    switch(key)
    {

    case '0':
        cout<<"Hoise"<<endl;
        makeImageFromWindow();
        break;

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

void drawBlackAndWhiteFloorOneSide()
{

    struct point floorPoints[100][100];
    //int numberOfTilesInaSide=20;

    for(int i=0; i<=numberOfTilesInaSide; i++)
    {
        for(int j=0; j<=numberOfTilesInaSide; j++)
        {
            floorPoints[i][j].x=i*30;
            floorPoints[i][j].y=j*30;
            floorPoints[i][j].z=0;
        }
    }

    for(int i=0; i<numberOfTilesInaSide; i++)
    {
        for(int j=0; j<numberOfTilesInaSide; j++)
        {

            if ((i+j)%2 == 1)
            {
                glColor3f(0, 0, 0);
            }
            else
            {
                glColor3f(1, 1, 1);
            }

            glBegin(GL_QUADS);
            {
                //upper hemisphere
                glVertex3f(floorPoints[i][j].x,floorPoints[i][j].y,floorPoints[i][j].z);
                glVertex3f(floorPoints[i][j+1].x,floorPoints[i][j+1].y,floorPoints[i][j+1].z);
                glVertex3f(floorPoints[i+1][j+1].x,floorPoints[i+1][j+1].y,floorPoints[i+1][j+1].z);
                glVertex3f(floorPoints[i+1][j].x,floorPoints[i+1][j].y,floorPoints[i+1][j].z);

            }
            glEnd();
        }
    }




}


void getValueFromFile()
{

    freopen("description.txt","r",stdin);
    cin>>levelOfRec;
    cin>>numOfPixel;
    //cin.ignore();
    cin>>numOfObject;
    //cin.ignore();
    string command;
    // sphereVector=new vector<sphereClass>();
    for(int i=0; i<numOfObject; i++)
    {
        cin>>command;
        if(command=="sphere" || command=="1")
        {
            sphereClass sphereCla;

            cin>>sphereCla.centerPosX>>sphereCla.centerPosY>>sphereCla.centerPosZ;
            cin>>sphereCla.radiusOfSphere;
            cin>>sphereCla.colorOfRed>>sphereCla.colorOfGreen>>sphereCla.colorOfBlue;
            cin>>sphereCla.ambientCoEff>>sphereCla.diffuseCoEff>>sphereCla.specularCoEff>>sphereCla.reflectionCoEff;
            cin>>sphereCla.specularExponent;

            sphereVector.push_back(sphereCla);

        }

        else if(command=="pyramid" || command=="2")
        {
            pyramidClass pyramidCla;

            cin>>pyramidCla.lowestPosX>>pyramidCla.lowestPosY>>pyramidCla.lowestPosZ;
            cin>>pyramidCla.lengthOfBase>>pyramidCla.heightOfPyramid;
            cin>>pyramidCla.colorOfRed>>pyramidCla.colorOfGreen>>pyramidCla.colorOfBlue;
            cin>>pyramidCla.ambientCoEff>>pyramidCla.diffuseCoEff>>pyramidCla.specularCoEff>>pyramidCla.reflectionCoEff;
            cin>>pyramidCla.specularExponent;

            pyramidCla.setTriangleOne();
            pyramidCla.setTriangleTwo();
            pyramidCla.setTriangleThree();
            pyramidCla.setTriangleFour();

            pyramidVector.push_back(pyramidCla);

        }
        // cin.ignore();
    }

    cin>>numOfLight;

    for(int i=0; i<numOfLight; i++)
    {

        double valueOfX,valueOfY,valueOfZ;
        cin>>valueOfX>>valueOfY>>valueOfZ;

        lightSourcesClass lightClassObject;
        lightClassObject.positionX=valueOfX;
        lightClassObject.positionY=valueOfY;
        lightClassObject.positionZ=valueOfZ;

        lightVector.push_back(lightClassObject);
        //cout<<lightClassObject.positionX;
    }



}

void drawSphereFromClass(sphereClass sphereCla)
{



    struct point spherePoints[100][100];
    double height,rad;

    int stackNum=30;
    int sliceNum=50;

    double radiusOfSphere=sphereCla.radiusOfSphere;

    for(int i=0; i<=stackNum; i++)
    {
        //for the upper part x and y axis
        height=radiusOfSphere*sin(((double)i/(double)stackNum)*(pi*2)); //dividing the upper hemisphere into stacks
        rad=radiusOfSphere*cos(((double)i/(double)stackNum)*(pi*2));

        //generating points
        //pi/2 is used for the 1/4th of upper part, that means it is the eightth part of whole sphere
        for(int j=0; j<=sliceNum; j++)
        {
            spherePoints[i][j].x=rad*cos(((double)j/(double)sliceNum)*(pi*2));
            spherePoints[i][j].y=rad*sin(((double)j/(double)sliceNum)*(pi*2));
            spherePoints[i][j].z=height;
        }
    }
    //draw quads using generated points
    for(int i=0; i<stackNum; i++)
    {
        //glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
        glColor3f(sphereCla.colorOfRed,sphereCla.colorOfGreen,sphereCla.colorOfBlue);

        for(int j=0; j<sliceNum; j++)
        {
            glBegin(GL_QUADS);
            {
                //upper hemisphere
                glVertex3f(spherePoints[i][j].x,spherePoints[i][j].y,spherePoints[i][j].z);
                glVertex3f(spherePoints[i][j+1].x,spherePoints[i][j+1].y,spherePoints[i][j+1].z);
                glVertex3f(spherePoints[i+1][j+1].x,spherePoints[i+1][j+1].y,spherePoints[i+1][j+1].z);
                glVertex3f(spherePoints[i+1][j].x,spherePoints[i+1][j].y,spherePoints[i+1][j].z);

            }
            glEnd();
        }
    }


}

void drawPyramidFromClass(pyramidClass pyramidCla)
{

    glColor3f(pyramidCla.colorOfRed,pyramidCla.colorOfGreen,pyramidCla.colorOfBlue);

    glBegin(GL_QUADS);
    {
        glVertex3f(0,0,0);
        glVertex3f(0,pyramidCla.lengthOfBase,0);
        glVertex3f(pyramidCla.lengthOfBase,pyramidCla.lengthOfBase,0);
        glVertex3f(pyramidCla.lengthOfBase,0,0);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0,0,0);
        glVertex3f(0,pyramidCla.lengthOfBase,0);
        glVertex3f(pyramidCla.lengthOfBase/2,pyramidCla.lengthOfBase/2,pyramidCla.heightOfPyramid);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0,0,0);
        glVertex3f(pyramidCla.lengthOfBase,0,0);
        glVertex3f(pyramidCla.lengthOfBase/2,pyramidCla.lengthOfBase/2,pyramidCla.heightOfPyramid);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(pyramidCla.lengthOfBase,0,0);
        glVertex3f(pyramidCla.lengthOfBase,pyramidCla.lengthOfBase,0);
        glVertex3f(pyramidCla.lengthOfBase/2,pyramidCla.lengthOfBase/2,pyramidCla.heightOfPyramid);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glVertex3f(0,pyramidCla.lengthOfBase,0);
        glVertex3f(pyramidCla.lengthOfBase,pyramidCla.lengthOfBase,0);
        glVertex3f(pyramidCla.lengthOfBase/2,pyramidCla.lengthOfBase/2,pyramidCla.heightOfPyramid);
    }
    glEnd();


}



void drawFigure()
{


    for(int i=0; i<sphereVector.size(); i++)
    {
        //cout<<"entry"<<endl;
        glPushMatrix();
        {
            glTranslatef(sphereVector[i].centerPosX,sphereVector[i].centerPosY,sphereVector[i].centerPosZ);
            drawSphereFromClass(sphereVector[i]);
        }
        glPopMatrix();
    }

    for(int i=0; i<pyramidVector.size(); i++)
    {

        glPushMatrix();
        {
            glTranslatef(pyramidVector[i].lowestPosX,pyramidVector[i].lowestPosY,pyramidVector[i].lowestPosZ);
            drawPyramidFromClass(pyramidVector[i]);
        }
        glPopMatrix();

    }

    /*glPushMatrix();
    {

        drawBlackAndWhiteFloorOneSide();
        glPushMatrix();
        {
            glTranslatef(-numberOfTilesInaSide*30,0,0);
            drawBlackAndWhiteFloorOneSide();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0,-numberOfTilesInaSide*30,0);
            drawBlackAndWhiteFloorOneSide();
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(0,-numberOfTilesInaSide*30,0);
            glTranslatef(-numberOfTilesInaSide*30,0,0);
            drawBlackAndWhiteFloorOneSide();
        }
        glPopMatrix();
    }
    glPopMatrix();
    */
    int valColor=1;
    for(int i=-30; i<=30; i++)
    {
        glPushMatrix();
        {
            glTranslatef(-900,30*i,0);
            for(int j=0; j<60; j++)
            {
                if(j%2==0)
                    glColor3f(1,1,1);
                else
                    glColor3f(0,0,0);
                glColor3f((double)valColor,(double)valColor,(double)valColor);
                glBegin(GL_QUADS);
                {
                    glVertex3f(15,15,0);
                    glVertex3f(15,-15,0);
                    glVertex3f(-15,-15,0);
                    glVertex3f(-15,15,0);
                }
                glEnd();
                glTranslatef(30, 0, 0);
                valColor=valColor^1;
            }


        }
        glPopMatrix();
        valColor=valColor^1;
    }

    //cout<<lightVector.size();
    for(int i=0; i<lightVector.size(); i++)
    {
        //cout<<"working"<<endl;
        //cout<<lightVector[i].positionX<<endl;
        sphereClass tempClass;
        tempClass.ambientCoEff=0.0;
        tempClass.specularCoEff=0.0;
        tempClass.specularExponent=0.0;
        tempClass.diffuseCoEff=0.0;
        tempClass.reflectionCoEff=0.0;
        tempClass.colorOfRed=1.0;
        tempClass.colorOfBlue=1.0;
        tempClass.colorOfGreen=1.0;
        tempClass.centerPosX=lightVector[i].positionX;
        tempClass.centerPosY=lightVector[i].positionY;
        tempClass.centerPosZ=lightVector[i].positionZ;
        tempClass.radiusOfSphere=1.0;
        //cout<<tempClass.centerPosX;
        glPushMatrix();
        {
            glTranslatef(tempClass.centerPosX,tempClass.centerPosY,tempClass.centerPosZ);
            drawSphereFromClass(tempClass);
        }
        glPopMatrix();
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

    //drawAxes();
    //drawGrid();
    drawFigure();




    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}


void animate()
{
    angle+=0.05;
    //codes for any changes in Models, Camera
    glutPostRedisplay();
}


void cameraInit()
{

    cameraPosition.x=100.0;
    cameraPosition.y=100.0;
    cameraPosition.z=50.0;

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
    gluPerspective(90,	1,	1,	1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
    getValueFromFile();
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
