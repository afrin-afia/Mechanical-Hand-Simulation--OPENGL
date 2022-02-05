#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes,flag=0, flagrl=0;        //flag for q/w press.
int flagmiddle=0;
int flagf1=0, flagf2=0, flagf3=0;       //flag for fingers
double angle;



float handAngle=0,handAnglerl=0;          //whole hand, vitore-baire (q,w)
float middleHandAngle=0;
float f1Angle=0,f2Angle=0,f3Angle=0;

void drawAxes()         //LAGE
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glTranslatef(-10,45,0);
		glBegin(GL_LINES);{

			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);         //axes: |
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void keyboardListener(unsigned char key, int x,int y){
	switch(key){



        case 'q':
                 if(handAngle<=88.0)handAngle+=2.0;
                 flag=1;
                 break;
        case 'w':

                 if(handAngle>=2.0)handAngle-=2.0;
                 flag=1;
                 break;

        case '2':
                if(handAnglerl<=44.0)handAnglerl+=2.0;
                flagrl=1;
                break;

        case '1':
                if(handAnglerl>=-42.0)handAnglerl-=2.0;
                flagrl=1;
                break;

        case '3':
                if(middleHandAngle>=-88.0) middleHandAngle-=2.0;
                flagmiddle=1;
                break;

        case '4':
                if(middleHandAngle<= -2.0) middleHandAngle+=2.0;
                flagmiddle=1;
                break;

        case '5':
                if(f1Angle>=-88.0) f1Angle-=2.0;
                flagf1=1;
                break;

        case '6':
                if(f1Angle<= -2.0) f1Angle+=2.0;
                flagf1=1;
                break;

        case '7':
                if(f2Angle>=-88.0) f2Angle-=2.0;
                flagf2=1;
                break;

        case '8':
                if(f2Angle<= -2.0) f2Angle+=2.0;
                flagf2=1;
                break;

        case '9':
                if(f3Angle>=-88.0) f3Angle-=2.0;
                flagf3=1;
                break;

        case '0':
                if(f3Angle<= -2.0) f3Angle+=2.0;
                flagf3=1;
                break;


		default:
			break;
	}
}


void specialKeyListener(int key, int x,int y){
	switch(key){
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


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
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

//****************************start******************************



void hand(){


        if(flag==1) {       //q,w
            glRotatef(handAngle,10.0,0.0,0.0);
            //flag=0;
        }
        if(flagrl ==1) {        //1,2
            glRotatef(handAnglerl,0.0,0.0,10.0);
            //flagrl=0;
        }

        glPushMatrix();
        {
            glScaled (0.25f ,1.30f ,0.25f);
            glTranslatef(0.0,-20,0);
            glRotatef(90.0,100.0,0.0,0.0);      //wireSphere zevabe ake, oivabe bosaite chaina. eijonno eke 90 degree rotate kore bosaisi
            glutWireSphere(20,10,20);   //param= radius, slices,stacks
        }
        glPopMatrix();
        //above: upper portion ok

        //middle portion
        if(flagmiddle==1){

                glTranslatef(0.0,-52,0);            //change the center of rotation, and rotate
                glRotatef(middleHandAngle,0.0,0.0,10.0);
                glTranslatef(0.0,52,0);
        }

        glPushMatrix();
        {
            glScaled (0.25f ,1.0f ,0.25f);
            glTranslatef(0.0,-69,0);
            glRotatef(90.0,100.0,0.0,0.0);
            glutWireSphere(18,10,20);   //param= radius, slices,stacks
        }
        glPopMatrix();

        //triangle
        glPushMatrix();
        {
                glBegin(GL_TRIANGLES);
                {
                        glVertex3f(0,-86,0);
                        glVertex3f(0,-102,-10);
                        glVertex3f(0,-102,10);

                }
                glEnd();
        }
        glPopMatrix();

        //finger1
        glPushMatrix();{        //needed because: shudhu finger1 er upor rotation apply krbo. So, consider f1 as a seperate draw
            if(flagf1==1){

                    glTranslatef(0.0,-100,0);            //change the center of rotation, and rotate
                    glRotatef(f1Angle,0.0,0.0,10.0);
                    glTranslatef(0.0,100,0);
            }
            //finger 2 draw
            glPushMatrix();
            {
                    glTranslatef(0.0,-107,-8.0);
                    glScaled (0.25f ,2.0f ,0.25f);
                    glRotatef(90.0,100.0,0.0,0.0);
                    glutWireSphere(3,8,8);
            }
            glPopMatrix();
        }
        glPopMatrix();


        //finger2
        glPushMatrix();{
            if(flagf2==1){

                        glTranslatef(0.0,-100,0);            //change the center of rotation, and rotate
                        glRotatef(f2Angle,0.0,0.0,10.0);
                        glTranslatef(0.0,100,0);
            }
            glPushMatrix();
            {
                    glTranslatef(0.0,-107,0);
                    glScaled (0.25f ,2.0f ,0.25f);
                    glRotatef(90.0,100.0,0.0,0.0);
                    glutWireSphere(3,8,8);
            }
            glPopMatrix();
        }
        glPopMatrix();

        //finger3
        glPushMatrix();{
                if(flagf3==1){

                            glTranslatef(0.0,-100,0);            //change the center of rotation, and rotate
                            glRotatef(f3Angle,0.0,0.0,10.0);
                            glTranslatef(0.0,100,0);
                }
            glPushMatrix();
            {
                    glTranslatef(0.0,-107,8.0);
                    glScaled (0.25f ,2.0f ,0.25f);
                    glRotatef(90.0,100.0,0.0,0.0);
                    glutWireSphere(3,8,8);
            }
            glPopMatrix();
        }
        glPopMatrix();

}


void display(){

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
	gluLookAt(100*cos(cameraAngle), cameraHeight,100*sin(cameraAngle),		0,0,0,		0,1,0);
	//gluLookAt(50,50,100,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	//drawgrid=1;
	//drawGrid();

    //glColor3f(1,0,0);
    //drawSquare(10);

    //drawSS();

    //drawCircle(30,80);          //wheel

    hand();
    //drawCone(20,50,24);

	//drawSphere(30,24,20);           //radius, slices, stack;

    //glutSolidTorus(20,50,5,3);

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;

	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=100.0;
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



int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My Hand");

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
