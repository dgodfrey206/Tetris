#include <Windows.h>
#include <glut.h>
#include <stdio.h>    
#include <string.h>
#include <math.h>
#include <stdlib.h>     
#include <time.h> 


//METHOD DECLARATIONS

//the next two methods initialize the grid with the proper x and y values
void xCoInit();
void yCoInit();

//given a an x coordinate they return its index in the xCoordinates & yCoordinates arrays
int getXindex();
int getYindex();

void Display(void);
void print(int, int, char*);
void keyboard(int, int, int);
void charKeyboard(unsigned char, int, int);
void move(void);
void drawShapeOne(int, int, int);
void drawShapeTwo(int, int, int);
void drawShapeThree(int, int, int);
void drawShapeFour(int, int, int);
void drawShapeFive(int, int, int);
void drawShapeSix(int, int, int);
void drawShapeSeven(int, int, int);
void resetInitialPositions(void);
void collide(void);
int getHorizontal(int);
int getVertical(int);
int getMinX(void);
int getMinY(void);
int getMaxX(void);
int getMaxY(void);
void clearSquare(int, int);
void print(int, int, char*);
void refresh(void);
void redraw(void);
int getY(int); //gets the y value of a x value of one of the squares of the falling tetrimino
bool boardEmpty(void);
//GLOBAl ATTRIBUTES

//attributes for falling tetrimino

int x, y;
int x1i, x2i, x3i, x4i, x5i, x6i, x7i;
int y1i, y2i, y3i, y4i, y5i, y6i, y7i;

int xOne, xTwo, xThree, xFour; //x-coordinates for its four squares
int yOne, yTwo, yThree, yFour; //y-cooridnates for its four squares
float rotAngle; //current angle of ration of the falling tetrimino
int const side = 40;
int random;
int currentShape;
int xCenter;
int yCenter;
bool currentCollided;
bool lineFormed;
bool gap;
bool back;
int guardThisWithYourLife;
int saveThisAngleFromDoom;

//game field attributes
//The game field is a grid where each cell in this grid has an x & y coordinate, a shape number, a boolean attribute to 
//indicate whether or not its occupied, and a rotation angle

int const fieldWidth = 10;
int const fieldLength = 16;

bool gameStart;
bool gameOver;

int score = 0;

long double unitStep = 0.0000000000001; //the step that each tetrimino makes each post redisplay

int xCoordinates[fieldWidth][fieldLength];
int yCoordinates[fieldWidth][fieldLength];
int shape[fieldWidth][fieldLength];
bool isOccupied[fieldWidth][fieldLength];
int rotationAngle[fieldWidth][fieldLength];
bool scoreLine[16];


void main(int argc, char** argr)
{
	glutInit(&argc, argr);
	yCoInit();
	xCoInit();
	yOne = -1;
	yTwo = -1;
	yThree = -1;
	yFour = -1;
	random = rand() % 7 + 1;
	resetInitialPositions();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(side*fieldWidth, side*fieldLength);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Tetris");
	glutDisplayFunc(Display);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glPointSize(9.0);
	glLineWidth(9.0);
	gluOrtho2D(0.0, 400.0, 0.0, 640.0);
	glutKeyboardFunc(charKeyboard);
	glutSpecialFunc(keyboard);
	glutIdleFunc(move);
	glutMainLoop();

}

void move() {
	
	if (back == false) {
		collide();
		if ((currentShape == 1) && (isOccupied[getHorizontal(160)][getVertical(600)] == true)) {
			gameOver = true;
		}

		if ((currentShape != 1) && (isOccupied[getHorizontal(200)][getVertical(600)] == true)) {
			gameOver = true;
		}
	}

	if (currentCollided == false && (back == false)) {
		switch (currentShape) {
		case 1: y1i -= unitStep; break;
		case 2: y2i -= unitStep; break;
		case 3: y3i -= unitStep; break;
		case 4: y4i -= unitStep; break;
		case 5: y5i -= unitStep; break;
		case 6: y6i -= unitStep; break;
		case 7: y7i -= unitStep; break;
		}

	}

	

	for (int i = 0; i < 2000000; i++);

	glutPostRedisplay();
}

int getMinX() {
	int min = xOne;
	if (xTwo < min)
		min = xTwo;
	if (xThree < min)
		min = xThree;
	if (xFour < min)
		min = xFour;
	return min;
}

int getMinY() {
	int min = yOne;
	if (yTwo < min)
		min = yTwo;
	if (yThree < min)
		min = yThree;
	if (yFour < min)
		min = yFour;
	return min;
}

int getMaxX() {
	int max = xOne;
	if (xTwo > max)
		max = xTwo;
	if (xThree > max)
		max = xThree;
	if (xFour > max)
		max = xFour;
	return max;
	printf("%i", max);
}

int getMaxY() {
	int max = yOne;
	if (yTwo > max)
		max = yTwo;
	if (yThree > max)
		max = yThree;
	if (yFour > max)
		max = yFour;
	return max;
}

void print(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void keyboard(int key, int xx, int yy) {


	/* */
	/*&& ((getMaxX() + 50 <= 400))*/
	/*&& (((rotAngle == 90.0f || rotAngle == 270.0f) && (currentShape != 1) && (xFour + 40 <= 400)) 
	|| ((rotAngle == 90.0f || rotAngle == 270.0f) && (currentShape == 1) && (xFour + 40 <= 400))
		|| (((rotAngle == 0.0f) || (rotAngle == 180.0f)) && (xFour + 40 <= 400)))*/

	/*((rotAngle == 90 || rotAngle == 270) && (currentShape !=1 || currentShape != 5) && (getMaxX() + 40 <= 400))*/


	if (key == GLUT_KEY_RIGHT && (((rotAngle == 90 || rotAngle == 270) && (currentShape == 1 || currentShape == 5) && (getMaxX() + 40 <= 400)) || (getMaxX() + 80 <= 400)))
	{

		//+40 because the x coordinate is the left most point fel square el akheer + 10 to make sure the move mesh hat3ady el frame beta3 el game
		//printf("max x is %i", maxX);
		switch (currentShape) {
		case 1: x1i += 40; break;
		case 2: x2i += 40; break;
		case 3: x3i += 40; break;
		case 4: x4i += 40; break;
		case 5: x5i += 40; break;
		case 6: x6i += 40; break;
		case 7: x7i += 40; break;
		}
	}
	//&& (getMinX() - 40 >= 0)

	//(((rotAngle == 90.0f || rotAngle == 270.0f) && (xOne >= 0))
	//	|| (((rotAngle == 0.0f) || (rotAngle == 180.0f)) && (xOne - 40 >= 0)))

	if (key == GLUT_KEY_LEFT && (getMinX() -40 >=0 )) {
		switch (currentShape) {
		case 1: x1i -= 40; break;
		case 2: x2i -= 40; break;
		case 3: x3i -= 40; break;
		case 4: x4i -= 40; break;
		case 5: x5i -= 40; break;
		case 6: x6i -= 40; break;
		case 7: x7i -= 40; break;
		}
	}

	if (key == GLUT_KEY_UP) {
		rotAngle += 90.0f;
		if (rotAngle == 360)
			rotAngle = 0;
	}

	if (key == GLUT_KEY_DOWN) {
		rotAngle -= 90.0f;
		if (rotAngle == -360)
			rotAngle = 0;
	}
	glutPostRedisplay();
}

void charKeyboard(unsigned char key, int xx, int yy) {
	if (key == 's' || key == 'S') {
		gameStart = true;
		currentShape = random;
		guardThisWithYourLife = random;
	}
	glutPostRedisplay();
}

void Display() {

	glClear(GL_COLOR_BUFFER_BIT);

	
	random = rand() % 7 + 1;

	glColor3d(1.0, 1.0, 1.0);
	char * stC[100];
	sprintf((char *)stC, "Score: %i", score);
	print(0, 620, (char *)stC);


	/*drawShapeFour(x4i, y4i, rotAngle);
	if (yOne == 0 || yTwo == 0 || yThree == 0 || yFour == 0)
		currentCollided = true;*/

	saveThisAngleFromDoom = rotAngle;
	redraw();


	if ((currentCollided == false) && (gameStart == true) && (gameOver == false)) {
		back = false;
		switch (guardThisWithYourLife){
		case 1: x = x1i; y = y1i; drawShapeOne(x, y, saveThisAngleFromDoom); break;
		case 2: x = x2i; y = y2i; drawShapeTwo(x, y, saveThisAngleFromDoom); break;
		case 3: x = x3i; y = y3i; drawShapeThree(x, y, saveThisAngleFromDoom); break;
		case 4: x = x4i; y = y4i; drawShapeFour(x, y, saveThisAngleFromDoom); break;
		case 5: x = x5i; y = y5i; drawShapeFive(x, y, saveThisAngleFromDoom); break;
		case 6: x = x6i; y = y6i; drawShapeSix(x, y, saveThisAngleFromDoom); break;
		case 7: x = x7i; y = y7i; drawShapeSeven(x, y, saveThisAngleFromDoom); break;
		default: break;
			
		}
	}

	if (currentCollided == true && (gameOver == false)){
		resetInitialPositions();
		currentShape = random;
		switch (random) {
		case 1: x = x1i; y = y1i; drawShapeOne(x, y, 0); break;
		case 2: x = x2i; y = y2i; drawShapeTwo(x, y, 0); break;
		case 3: x = x3i; y = y3i; drawShapeThree(x, y, 0); break;
		case 4: x = x4i; y = y4i; drawShapeFour(x, y, 0); break;
		case 5: x = x5i; y = y5i; drawShapeFive(x, y, 0); break;
		case 6: x = x6i; y = y6i; drawShapeSix(x, y, 0); break;
		case 7: x = x7i; y = y7i; drawShapeSeven(x, y, 0); break;
		default: break;
		
		}
		
		currentCollided = false;
		guardThisWithYourLife = currentShape;
	
		//saveThisAngleFromDoom = 0;

	}

	
	
	if (gameOver == true) {
		glColor3d(1.0, 1.0, 1.0);
		char * stC[100];
		sprintf((char *)stC, "GAME OVER");
		print(140, 320, (char *)stC);
		char * stD[100];
		sprintf((char *)stC, "Your Score is: % i", score);
		print(140, 300, (char *)stC);
	}
	

	
	glutSwapBuffers();
	glutPostRedisplay();
}


void xCoInit() {
	int initial = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 16; j++) {
			xCoordinates[i][j] = initial;
		}
		initial += 40;
	}
}

void yCoInit() {
	int initial = 0;
	for (int i = 0; i < 10; i++) {
		initial = 0;
		for (int j = 0; j < 16; j++) {
			yCoordinates[i][j] = initial;
			initial += 40;
		}

	}
}

void drawShapeOne(int x, int y, int angle) {

	currentShape = 1;


	xOne = x;
	xTwo = x + side;
	xThree = x + 2 * side;
	xFour = x + 3 * side;

	yOne = y;
	yTwo = y;
	yThree = y;
	yFour = y;

	xCenter = xThree;
	yCenter = y + (side / 2);

	rotAngle = angle;

	glPushMatrix();

	glTranslatef(xCenter, yCenter, 0.0f);
	glRotatef(rotAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xCenter, -yCenter, 0.0f);


	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2i(x, y);
	glVertex2i(x, y + side);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2i(x + 2 * side, y);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 3 * side, y + side);
	glVertex2i(x + 3 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2i(x + 3 * side, y);
	glVertex2i(x + 3 * side, y + side);
	glVertex2i(x + 4 * side, y + side);
	glVertex2i(x + 4 * side, y);
	glEnd();


	glPopMatrix();
}

void drawShapeTwo(int x, int y, int angle) {

	currentShape = 2;

	xOne = x;
	xTwo = x;
	xThree = x + side;
	xFour = x + 2 * side;

	yOne = y;
	yTwo = y + side;
	yThree = y;
	yFour = y;

	xCenter = xThree + (side / 2);
	yCenter = y + side;

	rotAngle = angle;

	glPushMatrix();

	glTranslatef(xCenter, yCenter, 0.0f);
	glRotatef(rotAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xCenter, -yCenter, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(x, y);
	glVertex2i(x, y + side);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(x, y + side);
	glVertex2i(x, y + 2 * side);
	glVertex2i(x + side, y + 2 * side);
	glVertex2i(x + side, y + side);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2i(x + 2 * side, y);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 3 * side, y + side);
	glVertex2i(x + 3 * side, y);
	glEnd();

	glPopMatrix();

}

void drawShapeThree(int x, int y, int angle) {
	currentShape = 3;

	xOne = x;
	xTwo = x + side;
	xThree = x + 2 * side;
	xFour = x + 2 * side;

	yOne = y;
	yTwo = y;
	yThree = y;
	yFour = y + side;

	xCenter = xTwo + (side / 2);
	yCenter = y + side;

	rotAngle = angle;

	glPushMatrix();

	glTranslatef(xCenter, yCenter, 0.0f);
	glRotatef(rotAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xCenter, -yCenter, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2i(x, y);
	glVertex2i(x, y + side);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2i(x + 2 * side, y);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 3 * side, y + side);
	glVertex2i(x + 3 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y + 2 * side);
	glVertex2i(x + 3 * side, y + 2 * side);
	glVertex2i(x + 3 * side, y + side);
	glEnd();

	glPopMatrix();


}

void drawShapeFour(int x, int y, int angle) {
	currentShape = 4;

	xOne = x;
	xTwo = x + side;
	xThree = x;
	xFour = x + side;

	yOne = y;
	yTwo = y;
	yThree = y + side;
	yFour = y + side;

	xCenter = xTwo;
	yCenter = y + side;

	rotAngle = angle;

	glPushMatrix();

	glTranslatef(xCenter, yCenter, 0.0f);
	glRotatef(rotAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xCenter, -yCenter, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2i(x, y);
	glVertex2i(x, y + side);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2i(x, y + side);
	glVertex2i(x, y + 2 * side);
	glVertex2i(x + side, y + 2 * side);
	glVertex2i(x + side, y + side);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y + 2 * side);
	glVertex2i(x + 2 * side, y + 2 * side);
	glVertex2i(x + 2 * side, y + side);
	glEnd();

	glPopMatrix();

}

void drawShapeFive(int x, int y, int angle) {
	currentShape = 5;

	xOne = x;
	xTwo = x + side;
	xThree = x + side;
	xFour = x + 2 * side;

	yOne = y;
	yTwo = y;
	yThree = y + side;
	yFour = y + side;

	xCenter = xTwo;
	yCenter = y + side;

	rotAngle = angle;

	glPushMatrix();

	glTranslatef(xCenter, yCenter, 0.0f);
	glRotatef(rotAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xCenter, -yCenter, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.5f, 1.0f, 0.0f);
	glVertex2i(x, y);
	glVertex2i(x, y + side);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 1.0f, 0.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 1.0f, 0.0f);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y + 2 * side);
	glVertex2i(x + 2 * side, y + 2 * side);
	glVertex2i(x + 2 * side, y + side);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 1.0f, 0.0f);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y + 2 * side);
	glVertex2i(x + 3 * side, y + 2 * side);
	glVertex2i(x + 3 * side, y + side);
	glEnd();

	glPopMatrix();

}

void drawShapeSix(int x, int y, int angle) {
	currentShape = 6;

	xOne = x;
	xTwo = x + side;
	xThree = x + 2 * side;
	xFour = x + side;

	yOne = y;
	yTwo = y;
	yThree = y;
	yFour = y + side;

	xCenter = xTwo + (side / 2);
	yCenter = y + side;

	rotAngle = angle;

	glPushMatrix();

	glTranslatef(xCenter, yCenter, 0.0f);
	glRotatef(rotAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xCenter, -yCenter, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 1.0f);
	glVertex2i(x, y);
	glVertex2i(x, y + side);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 1.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 1.0f);
	glVertex2i(x + 2 * side, y);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 3 * side, y + side);
	glVertex2i(x + 3 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.0f, 1.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + 2 * side);
	glVertex2i(x + 2 * side, y + 2 * side);
	glVertex2i(x + 2 * side, y);
	glEnd();

	glPopMatrix();


}

void drawShapeSeven(int x, int y, int angle) {
	currentShape = 1;

	xOne = x;
	xTwo = x + side;
	xThree = x;
	xFour = x - side;

	yOne = y;
	yTwo = y;
	yThree = y + side;
	yFour = y + side;

	xCenter = xOne + (side / 2);
	yCenter = y + side;

	rotAngle = angle;

	glPushMatrix();

	glTranslatef(xCenter, yCenter, 0.0f);
	glRotatef(rotAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xCenter, -yCenter, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(x, y);
	glVertex2i(x, y + side);
	glVertex2i(x + side, y + side);
	glVertex2i(x + side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x + 2 * side, y + side);
	glVertex2i(x + 2 * side, y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(x, y + side);
	glVertex2i(x, y + 2 * side);
	glVertex2i(x + side, y + 2 * side);
	glVertex2i(x + side, y + side);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(x - side, y + side);
	glVertex2i(x - side, y + 2 * side);
	glVertex2i(x, y + 2 * side);
	glVertex2i(x, y + side);
	glEnd();

	glPopMatrix();




}

void clearSquare(int x, int y) {
	int i = getHorizontal(x);
	int j = getVertical(y);
	isOccupied[i][j] = false;

	glPushMatrix();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2i(x, y);
	glVertex2i(x + side, y);
	glVertex2i(x + side, y + side);
	glVertex2i(x, y + side);
	glEnd();

	glPopMatrix();
	glFlush();
}

void resetInitialPositions() {
	x1i = 120;
	y1i = 640;

	x2i = x1i;
	y2i = y1i;

	x3i = x1i;
	y3i = y1i;

	x4i = 160;
	y4i = y1i;

	x5i = 160;
	y5i = y1i;

	x6i = 160;
	y6i = y1i;

	x7i = 200;
	y7i = y1i;
}

int getHorizontal(int value){
	int j = 0;
	for (int i = 0; i < fieldWidth; i++) {
		if (((i == fieldWidth - 1) && (value >= xCoordinates[i][j])) || (value >= xCoordinates[i][j]) && (value < xCoordinates[i + 1][j]))
		return i;
	}
	return -1;
}

int getVertical(int value){

	int i = 0;
	for (int j = 0; j < fieldLength; j++){

		if (((j == fieldLength - 1) && (value >= yCoordinates[i][j])) || (value >= yCoordinates[i][j]) && (value < yCoordinates[i][j + 1]))
			return j;
	}
	return -1;
}

int getY(int x) {
	if (x == xOne)
		return yOne;
	else {
		if (x == xTwo)
			return yTwo;
		else {
			if (x == xThree)
				return yThree;
			else
				return yFour;
		}
	}
}

void collide() {

	int xTemp = xOne;
	int yTemp = yOne - 40;
	int i = getHorizontal(xTemp);
	int j = getVertical(yTemp);

		if (isOccupied[i][j] || yOne == 0) {
			isOccupied[getHorizontal(xOne)][getVertical(yOne)] = true;
			currentCollided = true;
			shape[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = currentShape;
			rotationAngle[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = saveThisAngleFromDoom;
			isOccupied[getHorizontal(xTwo)][getVertical(yTwo)] = true;
			isOccupied[getHorizontal(xThree)][getVertical(yThree)] = true;
			isOccupied[getHorizontal(xFour)][getVertical(yFour)] = true;
		}

		else {

			int xTemp = xTwo;
			int yTemp = yTwo - 40;
			int i = getHorizontal(xTemp);
			int j = getVertical(yTemp);
			if ((isOccupied[i][j] || yTwo == 0)) {
				currentCollided = true;
				shape[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = currentShape;
				rotationAngle[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = saveThisAngleFromDoom;
				isOccupied[getHorizontal(xOne)][getVertical(yOne)] = true;
				isOccupied[getHorizontal(xTwo)][getVertical(yTwo)] = true;
				isOccupied[getHorizontal(xThree)][getVertical(yThree)] = true;
				isOccupied[getHorizontal(xFour)][getVertical(yFour)] = true;
			}
			else {

				int xTemp = xThree;
				int yTemp = yThree - 40;
				int i = getHorizontal(xTemp);
				int j = getVertical(yTemp);
				if ((isOccupied[i][j] || yThree == 0)) {
					currentCollided = true;
					shape[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = currentShape;
					rotationAngle[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = saveThisAngleFromDoom;
					isOccupied[getHorizontal(xThree)][getVertical(yThree)] = true;
					isOccupied[getHorizontal(xOne)][getVertical(yOne)] = true;
					isOccupied[getHorizontal(xTwo)][getVertical(yTwo)] = true;
					isOccupied[getHorizontal(xFour)][getVertical(yFour)] = true;
				}

				else {
					int xTemp = xFour;
					int yTemp = yFour - 40;
					int i = getHorizontal(xTemp);
					int j = getVertical(yTemp);
					if ((isOccupied[i][j] || yFour == 0)) {
						currentCollided = true;
						shape[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = currentShape;
						rotationAngle[getHorizontal(getMinX())][getVertical(getY(getMinX()))] = saveThisAngleFromDoom;
						isOccupied[getHorizontal(xOne)][getVertical(yOne)] = true;
						isOccupied[getHorizontal(xTwo)][getVertical(yTwo)] = true;
						isOccupied[getHorizontal(xThree)][getVertical(yThree)] = true;
						isOccupied[getHorizontal(xFour)][getVertical(yFour)] = true;
					}
				}
			}
		}
	}

void redraw() {
	back = true;
	glPushMatrix();
	for (int j = 0; j < fieldLength; j++) {
		for (int i = 0; i < fieldWidth; i++) {
			if (isOccupied[i][j] == false)
				gap = true;
			if (shape[i][j] != 0 && isOccupied[i][j]) {
				switch (shape[i][j]){
				case 1: drawShapeOne(xCoordinates[i][0], yCoordinates[0][j], rotationAngle[i][j]); break;
				case 2: drawShapeTwo(xCoordinates[i][0], yCoordinates[0][j], rotationAngle[i][j]); break;
				case 3: drawShapeThree(xCoordinates[i][0], yCoordinates[0][j], rotationAngle[i][j]); break;
				case 4: drawShapeFour(xCoordinates[i][0], yCoordinates[0][j], rotationAngle[i][j]); break;
				case 5: drawShapeFive(xCoordinates[i][0], yCoordinates[0][j], rotationAngle[i][j]); break;
				case 6: drawShapeSix(xCoordinates[i][0], yCoordinates[0][j], rotationAngle[i][j]); break;
				case 7: drawShapeSeven(xCoordinates[i][0], yCoordinates[0][j], rotationAngle[i][j]); break;

				}
			}
		}
		if (gap == true)
			gap = false;
		else {
			if (scoreLine[j] == false) {
			score = score + 10;
			scoreLine[j] = true;
		}
		}
	}
	glPopMatrix();
}


