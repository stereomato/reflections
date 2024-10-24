// #include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>

typedef float Matrix4x4 [4][4];

Matrix4x4 matrizTransformacion;

float matrizPuntosI[5][3]={{50,140,-50},{45,15,-75},{95,15,-75},{25,15,-25},{75,15,-25}};
float matrizPuntosF[5][3];

float traslacionX,traslacionY,traslacionZ;

GLint X=300,Y=300,Z=300;


void matrixSetIdentity(Matrix4x4 m)
{    //Inicializa la matriz identidad
	int i,j;
	for (i=0; i<4; i++)
		for (j=0; j<4; j++)
			m[i][j] = (i == j);
}

void matrixPreMultiply(Matrix4x4 a , Matrix4x4 b)
{
	int i,j;
	Matrix4x4 tmp;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			tmp[i][j]= a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j];
		for (i = 0; i < 4; i++)
			for (j = 0; j < 4; j++)
				matrizTransformacion[i][j] = tmp[i][j];
}
void Traslacion(int tx, int ty, int tz)
{
	Matrix4x4 m;
	matrixSetIdentity(m);
	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;
	matrixPreMultiply(m, matrizTransformacion);
}

void EscalacionO(float Ex, float Ey, float Ez)
{
	Matrix4x4 m;
	matrixSetIdentity(m);
	m[0][0] = Ex;
	m[1][1] = Ey;
	m[2][2] = Ez;
	matrixPreMultiply(m, matrizTransformacion);
}

void ReflXY()
{
	Matrix4x4 m;
	matrixSetIdentity(m);
	m[2][2] =-1 ;
	matrixPreMultiply(m, matrizTransformacion);
}
void TransformarPuntos(void)
{
	int i,k;
	float tmp ;
	for(k=0 ; k<5 ; k++)
		for (i=0 ; i<3 ; i++)
			matrizPuntosF[k][i] = matrizTransformacion[i][0]*matrizPuntosI[k][0] +
						   matrizTransformacion[i][1]*matrizPuntosI[k][1] +
						   matrizTransformacion[i][2]*matrizPuntosI[k][2] +
						   matrizTransformacion[i][3];
}

void ejes3D(void)
{
    glBegin(GL_LINES);

    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,Z);

    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,Y,0);

    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(X,0,0);

    glEnd();
    glFlush();
}

void dibujo(void)
{
  /* glBegin(GL_QUADS);

    glColor3f(1,0,0);
    glVertex3f(10,10,0);
    glColor3f(0,0,0);
    glVertex3f(10,20,0);
     glColor3f(0,1,0);
    glVertex3f(20,20,0);
    glColor3f(0,0,1);
    glVertex3f(20,10,0);

    glEnd();

    glFlush();*/
//////////////////////////////////
    //glBegin(GL_LINE_LOOP);

    glBegin(GL_POLYGON);
    glColor3f(0,1,0);

    glVertex3f(0,0,20);
    glColor3f(1,0,0);
    glVertex3f(0,10,20);
    glColor3f(0,0,0);
    glVertex3f(10,10,20);
    glColor3f(0,0,1);
    glVertex3f(10,0,20);

    glEnd();


    glFlush();
}
void Dibujar(float a[5][3])
{         //muestra la figura
	int i;
	glColor3f (0.7, 0.4, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(a[0][0],a[0][1],a[0][2]);
	glVertex3f(a[1][0],a[1][1],a[1][2]);
	glVertex3f(a[2][0],a[2][1],a[2][2]);
	glEnd();

	glColor3f (0.8, 0.6, 0.5);
	glBegin(GL_POLYGON);
	glVertex3s(a[0][0],a[0][1],a[0][2]);
	glVertex3s(a[1][0],a[1][1],a[1][2]);
	glVertex3s(a[3][0],a[3][1],a[3][2]);
	glEnd();

	glColor3f (0.2, 0.4, 0.7);
	glBegin(GL_POLYGON);
	glVertex3f(a[0][0],a[0][1],a[0][2]);
	glVertex3f(a[2][0],a[2][1],a[2][2]);
	glVertex3f(a[4][0],a[4][1],a[4][2]);
	glEnd();

	glColor3f (0.5, 0.4, 0.3);
	glBegin(GL_POLYGON);
	glVertex3s(a[0][0],a[0][1],a[0][2]);
	glVertex3s(a[4][0],a[4][1],a[4][2]);
	glVertex3s(a[3][0],a[3][1],a[3][2]);
	glEnd();
	glColor3f (0.5, 0.6, 0.2);
	glBegin(GL_POLYGON);
	glVertex3s(a[1][0],a[1][1],a[1][2]);
	glVertex3s(a[2][0],a[2][1],a[2][2]);
	glVertex3s(a[4][0],a[4][1],a[4][2]);
	glVertex3s(a[3][0],a[3][1],a[3][2]);
	glEnd();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0,0,0,0); //COLOR DE FONDO
  ejes3D();
  //dibujo();
    Dibujar(matrizPuntosI); //Dibuja el cubo
	matrixSetIdentity(matrizTransformacion); //inicializa con unos la mtriz
	Traslacion(0 ,0 ,100);
	EscalacionO(2,2,2);
	/*ReflXY();
	Traslacion(0,0,50);
	Traslacion(0,0,100);
	Traslacion(0,0,50);
	Traslacion(0,0,50);*/

	TransformarPuntos();
	Dibujar(matrizPuntosF);

  glutSwapBuffers();
}

void inicio(void)
{
   /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  glOrtho(-X, X, -Y, Y, -Z, Z);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(5.0, 5.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 0.0, 1.0);      /* up is in positive Y direction */
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("escena 3D");
  glutDisplayFunc(display);
  inicio();
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
