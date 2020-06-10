#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include<stdio.h>

#define PI (2*acos(0.0))
using namespace std;

double valueEyeX,valueEyeY,valueEyeZ;
double valueLookX,valueLookY,valueLookZ;
double valueUpX,valueUpY,valueUpZ;
double valueFovY,valueAspectRatio,valueNear,valueFar;
double identityMatrix[4][4]= {};
double resultProductMatrix[4][4]= {};
double viewTranslationMatrix[4][4]= {};
double viewRotationMatrix[4][4]= {};
double finalViewMatrix[4][4]= {};
double finalProjectionMatrix[4][4]= {};
double resultView[4][4]={};
double resultProjection[4][4]={};
//stack<double *[4]>mainStack;




class holdMatrix
{

public:

    double tempMatrix[4][4];

    holdMatrix(double val[4][4])
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                tempMatrix[i][j]=val[i][j];
            }
        }
    }

};

void createAndSendIdentityMatrix()
{

    //identityMatrix=new double*[4];
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
            {
                identityMatrix[i][j]=1.0;
            }
            else
            {
                identityMatrix[i][j]=0.0;
            }
        }
    }


}

void printAndCheckMatrix(double vari[4][4])
{
    cout<<"printing"<<endl;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            cout<<vari[i][j]<<" ";
        }
        cout<<endl;
    }

}

stack<holdMatrix>mainStack;
stack<holdMatrix>tempStack;


void mainProductionMatrix(double matrixTwo[4][4])
{

    //matrix multiplication
    //pop from the stack and multiply
    holdMatrix hd=mainStack.top();
    double matrixOne[4][4];
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            matrixOne[i][j]=hd.tempMatrix[i][j];
        }
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            resultProductMatrix[i][j]=0.0;
        }
    }

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                resultProductMatrix[i][j] += matrixOne[i][k]*matrixTwo[k][j];
            }
        }
    }


}

void mainNormalizeMatrix()
{

    //normalizing the matrix
    //may cause inf or nan value
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            resultProductMatrix[j][i]=resultProductMatrix[j][i]/resultProductMatrix[3][i];
        }
    }

}

void commandTriangle()
{


    //taking input for triangle points
    double triangleMatrix[4][4];
    double pointFromFile[3];
    for(int i=0; i<3; i++)
    {
        //three points from one line
        cin>>pointFromFile[0]>>pointFromFile[1]>>pointFromFile[2];
        //assigning the points to the matrix
        for(int j=0; j<3; j++)
        {
            triangleMatrix[j][i]=pointFromFile[j];
        }
    }
    for(int i=0; i<3; i++)
    {
        triangleMatrix[3][i]=1.0;
    }
    triangleMatrix[0][3]=1.0;
    triangleMatrix[1][3]=1.0;
    triangleMatrix[2][3]=1.0;
    triangleMatrix[3][3]=1.0;

    mainProductionMatrix(triangleMatrix);
    //mainNormalizeMatrix();
    //printAndCheckMatrix(resultProductMatrix);

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            //cout<<setprecision(7)<<resultProductMatrix[i][j]<<"    ";
            cout<<fixed<<setprecision(7)<<resultProductMatrix[j][i]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;

}

void commandTranslation()
{

    double translationMatrix[4][4];
    double translateX,translateY,translateZ;

    cin>>translateX>>translateY>>translateZ;

    //creating the identity matrix
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
            {
                translationMatrix[i][j]=1.0;
            }
            else
            {
                translationMatrix[i][j]=0.0;
            }

        }
    }

    translationMatrix[0][3]=translateX;
    translationMatrix[1][3]=translateY;
    translationMatrix[2][3]=translateZ;

    mainProductionMatrix(translationMatrix);
    // mainNormalizeMatrix();
    mainStack.pop();
    //pushing the multiplication result
    holdMatrix hd(resultProductMatrix);
    mainStack.push(hd);
    //printAndCheckMatrix(resultProductMatrix);
    //cout<<endl;

}

void commandScale()
{

    double scaleMatrix[4][4];
    double scaleValueX,scaleValueY,scaleValueZ;

    cin>>scaleValueX>>scaleValueY>>scaleValueZ;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
            {
                scaleMatrix[i][j]=1.0;
            }
            else
            {
                scaleMatrix[i][j]=0.0;
            }

        }
    }

    scaleMatrix[0][0]=scaleValueX;
    scaleMatrix[1][1]=scaleValueY;
    scaleMatrix[2][2]=scaleValueZ;

    //multiplication with last item in stack
    mainProductionMatrix(scaleMatrix);
    // mainNormalizeMatrix();
    mainStack.pop();
    //pushing the multiplication result
    holdMatrix hd(resultProductMatrix);
    mainStack.push(hd);

    //printAndCheckMatrix(resultProductMatrix);
    //cout<<endl;


}

void commandRotation()
{
    double rotationMatrix[4][4];
    double angleOfRotation,axisX,axisY,axisZ;
    cin>>angleOfRotation>>axisX>>axisY>>axisZ;

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
            {
                rotationMatrix[i][j]=1.0;
            }
            else
            {
                rotationMatrix[i][j]=0.0;
            }

        }
    }

    //normalize vector a
    double aValueX,aValueY,aValueZ;
    double squareVal;

    squareVal=sqrt(axisX*axisX+axisY*axisY+axisZ*axisZ);
    aValueX=axisX/squareVal;
    aValueY=axisY/squareVal;
    aValueZ=axisZ/squareVal;

    //generating other vectors
    double vectorOneX,vectorOneY,vectorOneZ;
    double vectorTwoX,vectorTwoY,vectorTwoZ;
    double vectorThreeX,vectorThreeY,vectorThreeZ;
    double angleCos=cos(PI*angleOfRotation/180);
    double angleSin=sin(PI*angleOfRotation/180);

    //c1
    vectorOneX=angleCos+(1-angleCos)*aValueX*aValueX;
    vectorOneY=(1-angleCos)*aValueX*aValueY+angleSin*aValueZ;
    vectorOneZ=(1-angleCos)*aValueX*aValueZ-(angleSin)*aValueY;

    //c2
    vectorTwoX=(1-angleCos)*aValueX*aValueY-(angleSin)*aValueZ;
    vectorTwoY=(angleCos)+(1-angleCos)*aValueY*aValueY;
    vectorTwoZ=(1-angleCos)*aValueY*aValueZ+(angleSin)*aValueX;

    //c3
    vectorThreeX=(1-angleCos)*aValueX*aValueZ+(angleSin)*aValueY;
    vectorThreeY=(1-angleCos)*aValueY*aValueZ-(angleSin)*aValueX;
    vectorThreeX=(1-angleCos)*aValueZ*aValueZ+(angleCos);

    rotationMatrix[0][0]=vectorOneX;
    rotationMatrix[1][0]=vectorOneY;
    rotationMatrix[2][0]=vectorOneZ;

    rotationMatrix[0][1]=vectorTwoX;
    rotationMatrix[1][1]=vectorTwoY;
    rotationMatrix[2][1]=vectorTwoZ;

    rotationMatrix[0][2]=vectorThreeX;
    rotationMatrix[1][2]=vectorThreeY;
    rotationMatrix[2][2]=vectorThreeZ;

    mainProductionMatrix(rotationMatrix);
    //mainNormalizeMatrix();
    mainStack.pop();
    holdMatrix hd(resultProductMatrix);
    mainStack.push(hd);

    //printAndCheckMatrix(resultProductMatrix);
    //cout<<endl;

}

void viewTranslateOperation(double valueEyeX,double valueEyeY,double valueEyeZ)
{

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
            {
                viewTranslationMatrix[i][j]=1.0;
            }
            else
            {
                viewTranslationMatrix[i][j]=0.0;
            }
        }
    }

    viewTranslationMatrix[0][3]= -valueEyeX;
    viewTranslationMatrix[1][3]= -valueEyeY;
    viewTranslationMatrix[2][3]= -valueEyeZ;


}

void viewRotationOperation()
{

    double viewLaxisX,viewLaxisY,viewLaxisZ;
    double modulusOfL;
    double viewRaxisX,viewRaxisY,viewRaxisZ;
    double modulusOfR;
    double viewUaxisX,viewUaxisY,viewUaxisZ;
    double modulusOfU;

    //l axis
    viewLaxisX=valueLookX-valueEyeX;
    viewLaxisY=valueLookY-valueEyeY;
    viewLaxisZ=valueLookZ-valueEyeZ;
    modulusOfL=sqrt(viewLaxisX*viewLaxisX+viewLaxisY*viewLaxisY+viewLaxisZ*viewLaxisZ);
    viewLaxisX=viewLaxisX/modulusOfL;
    viewLaxisY=viewLaxisY/modulusOfL;
    viewLaxisZ=viewLaxisZ/modulusOfL;

    //r axis
    viewRaxisX=viewLaxisY*valueUpZ-viewLaxisZ*valueUpY;
    viewRaxisY=viewLaxisZ*valueUpX-viewLaxisX*valueUpZ;
    viewRaxisZ=viewLaxisX*valueUpY-viewLaxisY*valueUpX;
    modulusOfR=sqrt(viewRaxisX*viewRaxisX+viewRaxisY*viewRaxisY+viewRaxisZ*viewRaxisZ);
    viewRaxisX=viewRaxisX/modulusOfR;
    viewRaxisY=viewRaxisY/modulusOfR;
    viewRaxisZ=viewRaxisZ/modulusOfR;

    //u axis
    viewUaxisX=viewRaxisY*viewLaxisZ-viewRaxisZ*viewLaxisY;
    viewUaxisY=viewRaxisZ*viewLaxisX-viewRaxisX*viewLaxisZ;
    viewUaxisZ=viewRaxisX*viewLaxisY-viewRaxisY*viewLaxisX;
    modulusOfU=sqrt(viewUaxisX*viewUaxisX+viewUaxisY*viewUaxisY+viewUaxisZ*viewUaxisZ);
    viewUaxisX=viewUaxisX/modulusOfU;
    viewUaxisY=viewUaxisY/modulusOfU;
    viewUaxisZ=viewUaxisZ/modulusOfU;

    //making the identity matrix
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
            {
                viewRotationMatrix[i][j]=1.0;
            }
            else
            {
                viewRotationMatrix[i][j]=0.0;
            }
        }
    }

    //making the matrix
    viewRotationMatrix[0][0]=viewRaxisX;
    viewRotationMatrix[0][1]=viewRaxisY;
    viewRotationMatrix[0][2]=viewRaxisZ;
    viewRotationMatrix[1][0]=viewUaxisX;
    viewRotationMatrix[1][1]=viewUaxisY;
    viewRotationMatrix[1][2]=viewUaxisZ;
    viewRotationMatrix[2][0]=-viewLaxisX;
    viewRotationMatrix[2][1]=-viewLaxisY;
    viewRotationMatrix[2][2]=-viewLaxisZ;
}

void generatingViewMatrixFinal()
{

    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                finalViewMatrix[i][j] += viewRotationMatrix[i][k]*viewTranslationMatrix[k][j];
            }
        }
    }


}

void generatingProjectionMatrixFinal()
{

    //initializing value for stage3
    double fovXvalue,tValue,rValue;
    fovXvalue=valueFovY*valueAspectRatio;
    tValue=valueNear*tan(valueFovY/2*PI/180.0);
    rValue=valueNear*tan(fovXvalue/2*PI/180.0);

    //initializing the matrix
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {

            finalProjectionMatrix[i][j]=0.0;

        }
    }

    //making the final projection matrix
    finalProjectionMatrix[0][0]=valueNear/rValue;
    finalProjectionMatrix[1][1]=valueNear/tValue;
    finalProjectionMatrix[2][2]= -(valueFar+valueNear)/(valueFar-valueNear);
    finalProjectionMatrix[2][3]= - (2*valueFar*valueNear)/(valueFar-valueNear);
    finalProjectionMatrix[3][2]= -1;

}

void multiplicationWithViewMatrix(double matrixTwo[4][4]){

    //double matrixResult[4][4];

    //initializing the result matrix
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            resultView[i][j]=0.0;
        }
    }

    //multiplication matrix with the view matrix and triangle matrix
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                resultView[i][j] += finalViewMatrix[i][k]*matrixTwo[k][j];
            }
        }
    }

    //printing for stage2
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            //cout<<setprecision(7)<<resultProductMatrix[i][j]<<"    ";
            cout<<fixed<<setprecision(7)<<resultView[j][i]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;


}

void multiplicationWithProjectionMatrix(double matrixTwo[4][4]){

    //double matrixResult[4][4];
    //initializing the result matrix
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            resultProjection[i][j]=0.0;
        }
    }

    //multiplication of projection matrix and final view matrix of triangle
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                resultProjection[i][j] += finalProjectionMatrix[i][k]*matrixTwo[k][j];
            }
        }
    }

    //printing the final projection result matrix
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            //cout<<setprecision(7)<<resultProductMatrix[i][j]<<"    ";
            cout<<fixed<<setprecision(7)<<resultProjection[j][i]/resultProjection[3][i]<<"  ";
        }
        cout<<endl;
    }
    cout<<endl;


}

void commandPush()
{

    double tempMatrixPush[4][4];
    //pushMatrix function
    //storing the final one and putting them into second
    holdMatrix hd=mainStack.top();
    tempStack.push(hd);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tempMatrixPush[i][j]=hd.tempMatrix[i][j];
        }
    }
    holdMatrix hdTemp(tempMatrixPush);

    mainStack.push(hdTemp);


}

void commandPop()
{

    mainStack.pop();
}



int main()
{

    //char *fileName="scene.txt";
    string commandFromFile;
    //if input file exists
    if(freopen("scene.txt","r",stdin))
    {
        //print("No file exists !!");
        cout<<"File exists !!"<<endl;
        //exit(0);
    }
    //if input file doesn't exists
    else
    {
        //print("File Exists !!!");

        cout<<"No file exists !!"<<endl;
        exit(0);
    }

    //deriving value from files (first four lines)
    for(int i=0; i<4; i++)
    {
        if(i==0)
        {
            //eye values
            cin>>valueEyeX>>valueEyeY>>valueEyeZ;
        }
        else if(i==1)
        {
            //look values
            cin>>valueLookX>>valueLookY>>valueLookZ;
        }
        else if(i==2)
        {
            //up values
            cin>>valueUpX>>valueUpY>>valueUpZ;
        }
        else if(i==3)
        {
            //perspective values
            cin>>valueFovY>>valueAspectRatio>>valueNear>>valueFar;
        }
    }

    //creating identity matrix
    createAndSendIdentityMatrix();
    //printMatrix(identityMatrix);

    //storing identity matrix
    holdMatrix hd(identityMatrix);
    mainStack.push(hd);

    //viewing matrix creating
    //translation matrix for view
    viewTranslateOperation(valueEyeX,valueEyeY,valueEyeZ);
    //rotating the matrix into the origin
    viewRotationOperation();
    //finally making the matrix
    generatingViewMatrixFinal();

    //creating projection matrix
    generatingProjectionMatrixFinal();
    //starting reading from line 5
    while(true)
    {

        cin>>commandFromFile;
        //triangle command
        if(commandFromFile=="triangle")
        {
            //cout<<"triangle"<<endl;
            //triangle command
            freopen("stage1.txt","a",stdout);
            commandTriangle();
            fclose(stdout);

            //triangle for viewing
            freopen("stage2.txt","a",stdout);
            multiplicationWithViewMatrix(resultProductMatrix);
            fclose(stdout);

            //triangle for projection
            freopen("stage3.txt","a",stdout);
            multiplicationWithProjectionMatrix(resultView);
            fclose(stdout);
        }
        //translate command
        else if(commandFromFile=="translate")
        {
            //cout<<"translate"<<endl;
            commandTranslation();
        }
        //scale command
        else if(commandFromFile=="scale")
        {
            //cout<<"scale"<<endl;
            commandScale();
        }
        //rotate command
        else if(commandFromFile=="rotate")
        {
            //cout<<"rotate"<<endl;
            commandRotation();
        }
        else if(commandFromFile=="push")
        {
            //cout<<"push"<<endl;
            commandPush();
        }
        else if(commandFromFile=="pop")
        {
            //cout<<"pop"<<endl;
            commandPop();
        }
        else if(commandFromFile=="end")
        {
            break;
        }
    }





    return 0;
}
