#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

typedef float Matrix4x4 [4][4];

// "Añadir más vértices"
typedef float Matrix4x6 [4][6];

Matrix4x4 transformationMatrix;
Matrix4x4 testMatrix = {
	{0, 0, 0.2, 0.2},
	{0, 0.2, 0.2, 0},
	{0, 0, 0, 0},
	{1, 1, 1, 1},
};

Matrix4x6 testMatrix2 = {
	{0, 0, 0.2, 0.2,-0.2, 0},
	{0, 0.2, 0.2, 0,0, 0},
	{0, 0, 0, 0,-0.35, -0.35},
	{1, 1, 1, 1,1, 1},
};
Matrix4x4 test1 = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{9, 10, 11, 12},
	{13, 14, 15, 16},
};

Matrix4x4 test2 = {
	{17, 18, 19, 20},
	{21, 22, 23, 24},
	{25, 26, 27, 28},
	{29, 30, 31, 32},
};

GLint X=300,Y=300,Z=300;

void printMatrix(Matrix4x4 toPrint){
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			std::cout << toPrint[j][i];
			if (i == 3)
			{
				std::cout << "\n";
			} else {
				std::cout << " ";
			}
			
		}
	}
}

void printMatrix2(Matrix4x6 toPrint){
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			std::cout << toPrint[j][i];
			if (i == 5)
			{
				std::cout << "\n";
			} else {
				std::cout << " ";
			}
			
		}
	}
}


void showAxis(){
	glColor3i(0,0,0);
	// the dots
	float dotX = 0;
	float dotY = 0;
	float dotZ = 0;
	float limit = 1;
	float step = 0.01;

		do {
			// Every 10 steps -> bigger point
			if ( !((int) (dotX * 100) % 9)) {
				glPointSize(5.0f);
				glBegin(GL_POINTS);
					glVertex2f(dotX,dotY);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex2f(dotX,dotY);
				glEnd();
			}
			dotX += step;

			if (dotX >= limit) {
				dotX = -limit;
				limit = 0;
			}
		} while (dotX <= limit && dotX != 0);
	dotX = 0;
	limit = 1;
	// improve later
		 do {
			// Every 10 steps -> bigger point
			if ( !((int) (dotY * 100) % 9)) {
				glPointSize(5.0f);
				glBegin(GL_POINTS);
					glVertex2f(dotX,dotY);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex2f(dotX,dotY);
				glEnd();
			}
			dotY += step;
			if (dotY >= limit) {
				dotY = -limit;
				limit = 0;
			}
		} while (dotY <= limit && dotY != 0);

	dotX = 0;
	limit = 1;
	// improve later
		 do {
			// Every 10 steps -> bigger point
			if ( !((int) (dotZ * 100) % 9)) {
				glPointSize(5.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			else {
				glPointSize(1.0f);
				glBegin(GL_POINTS);
					glVertex3f(dotX,dotY,dotZ);
				glEnd();
			}
			dotZ += step;
			if (dotZ >= limit) {
				dotZ = -limit;
				limit = 0;
			}
		} while (dotZ <= limit && dotZ != 0);
}

void toIdentityMatrix(Matrix4x4 toSet){
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			toSet[i][j] = (i == j);
		}
	}
}

void resetMatrix(Matrix4x4 toReset){
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			toReset[j][i] = 0;
		}
	}
}

void resetMatrix2(Matrix4x6 toReset){
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 6; i++)
		{
			toReset[j][i] = 0;
		}
	}
}

void matrixMult(Matrix4x4 a, Matrix4x6 b, Matrix4x6 result){
	for (int j = 0; j < 4; j++)
	{
		for (int h = 0; h < 6; h++)
		{
			for (int i = 0; i < 4; i++)
			{
				//std::cout << "Printing multiplication iteration: " << i << " " << j << "\n";
				//std::cout << a[j][i] << " " << b[i][h] << "\n";
				result[j][h] += a[j][i] * b[i][h];
				//std::cout << "result: " << result[j][h] << "\n";
				 
			}
		}
	}
}


void transform(Matrix4x4 transformMatrix, Matrix4x6 originalMatrix, Matrix4x6 result){
	matrixMult(transformMatrix, originalMatrix, result);
}

void reflectXY(Matrix4x6 originalMatrix, Matrix4x6 result){
	Matrix4x4 reflectMatrix;
	toIdentityMatrix(reflectMatrix);

	reflectMatrix[2][2] = -1;
	transform(reflectMatrix, originalMatrix, result);
}

void reflectXZ(Matrix4x6 originalMatrix, Matrix4x6 result){
	Matrix4x4 reflectMatrix;
	toIdentityMatrix(reflectMatrix);

	reflectMatrix[1][1] = -1;
	transform(reflectMatrix, originalMatrix, result);
}

void reflectYZ(Matrix4x6 originalMatrix, Matrix4x6 result){
	Matrix4x4 reflectMatrix;
	toIdentityMatrix(reflectMatrix);

	reflectMatrix[0][0] = -1;
	transform(reflectMatrix, originalMatrix, result);
}

void reflect(Matrix4x6 originalMatrix, Matrix4x6 result){
	Matrix4x4 reflectMatrix;
	toIdentityMatrix(reflectMatrix);

	reflectMatrix[0][0] = -1;
	reflectMatrix[1][1] = -1;
	reflectMatrix[2][2] = -1;
	transform(reflectMatrix, originalMatrix, result);
}

void translate(float factorX, float factorY, float factorZ, Matrix4x6 originalMatrix, Matrix4x6 result){
	Matrix4x4 translateMatrix;
	toIdentityMatrix(translateMatrix);

	translateMatrix[0][3] = factorX;
	translateMatrix[1][3] = factorY;
	translateMatrix[2][3] = factorZ;
	transform(translateMatrix, originalMatrix, result);
	//printMatrix(translateMatrix);
}

void scale(float refpointX, float refpointY, float refpointZ, float factorX, float factorY, float factorZ,Matrix4x6 originalMatrix, Matrix4x6 result){
	Matrix4x4 scaleMatrix;
	toIdentityMatrix(scaleMatrix);

	scaleMatrix[0][0] = factorX;
	scaleMatrix[1][1] = factorY;
	scaleMatrix[2][2] = factorZ;
	
	if (refpointX != 0 || refpointY != 0 || refpointZ != 0)
	{
		Matrix4x6 helper = {
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0},
			{0,0,0,0,0,0}
		};
		translate(-refpointX, -refpointY, -refpointZ, originalMatrix, helper);
		transform(scaleMatrix, helper, result);
		resetMatrix2(helper);
		translate(refpointX, refpointY, refpointZ, result, helper);
	} else {
			transform(scaleMatrix, originalMatrix, result);
	}

	//std::cout << "PRINTINGSCALEMATRIx\n";
	//printMatrix(scaleMatrix);
}

void draw(Matrix4x6 toDraw, int numVertex){
	glPointSize(5);
	glBegin(GL_POINTS);
		std::cout << "PRINTING DRAW POINTS\n";
		for (int j = 0; j < 6; j++)
		{
			if (j < 4) {
				std::cout << toDraw[j][0] << " " << toDraw[j][1] << " " << toDraw[j][2] << " " << toDraw[j][3] << " " << toDraw[j][4] << " " << toDraw[j][5] << "\n";
			}
			
			glVertex3f(toDraw[0][j], toDraw[1][j], toDraw[2][j]);
		}
	glEnd();
	

	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1,1); //COLOR DE FONDO

	/*
	Matrix4x4 resultMatrix = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};
	*/

	Matrix4x6 resultMatrix;
	resetMatrix2(resultMatrix);

	glColor3f(0,0,1);
	//scale(0,0,0,1.25, 1.25, 1.25, testMatrix2, resultMatrix);

	//reflectYZ(testMatrix2,resultMatrix);

	translate(0.5,-0.75,0.5,testMatrix2, resultMatrix);
	draw(resultMatrix,6);

	

	
	//resetMatrix(resultMatrix);

	
	
	/*glPushMatrix();
		glColor3f(0,0,1);
		draw(testMatrix);
	glPopMatrix();*/

	std::cout << "PRINTING TESTMATRIX\n";
	printMatrix2(testMatrix2);
	
	/*
	Matrix4x4 testMatrix = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
	};
	matrixMult(test1, test2, testMatrix);
	std::cout << "PRINTING TESTMATRIX\n";
	printMatrix(testMatrix);
	//scale(5,6,7);
	//translate(8,9,10);
	*/
	glutSwapBuffers();
}

void init(){
		/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view of the cube. */
	glMatrixMode(GL_PROJECTION);
	//glOrtho(-X, X, -Y, Y, -Z, Z);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.1, 0.1, 0.1, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("escena 3D");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;						 /* ANSI C requires main to return int. */
}