/* Bezier's Curve Flag */
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1416

typedef struct wcPt3D {
	GLfloat x, y, z;
};

int nCr(int n, int r)
{
	if (r == 0)
		return 1;
	else if (r == n)
		return 1;
	else
		return nCr(n - 1, r - 1) + nCr(n - 1, r);
}

void computeBezPt(GLfloat u, wcPt3D* bezPt, GLint nCtrlPts, wcPt3D* ctrlPts)
{
	GLint k, n = nCtrlPts - 1;
	GLfloat bezBlendFcn;
	bezPt->x = bezPt->y = bezPt->z = 0.0;

	for (k = 0; k < nCtrlPts; k++) {
		bezBlendFcn = nCr( n, k ) * pow(u, k) * pow(1 - u, n - k);
		bezPt->x += ctrlPts[k].x * bezBlendFcn;
		bezPt->y += ctrlPts[k].y * bezBlendFcn;
		bezPt->z += ctrlPts[k].z * bezBlendFcn;
	}
}

void bezier(wcPt3D* ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint k;
	glBegin(GL_LINE_STRIP);

	for (k = 0; k <= nBezCurvePts; k++) {
		u = GLfloat(k) / GLfloat(nBezCurvePts);
		computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts);
		glVertex2f(bezCurvePt.x, bezCurvePt.y);
	}
	glEnd();
}

void displayFcn()
{
	GLint nCtrlPts = 4, nBezCurvePts = 20;

	static float theta = 0;

	wcPt3D ctrlPts[4] = {
		{ 20, 100, 0 },
		{ 30, 110, 0 },
		{ 50, 90, 0 },
		{ 60, 100, 0 }
	};

	ctrlPts[1].x += 10 * sin(theta * PI / 180.0);
	ctrlPts[1].y += 5 * sin(theta * PI / 180.0);
	ctrlPts[2].x -= 10 * sin((theta + 30) * PI / 180.0);
	ctrlPts[2].y -= 10 * sin((theta + 30) * PI / 180.0);
	ctrlPts[3].x -= 4 * sin((theta)*PI / 180.0);
	ctrlPts[3].y += sin((theta - 30) * PI / 180.0);
	theta += 0.9;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(5);

	glPushMatrix();
	glLineWidth(5);

	glColor3f(255 / 255, 153 / 255.0, 51 / 255.0);
	for (int i = 0; i < 8; i++) {
		glTranslatef(0, -0.8, 0);
		bezier(ctrlPts, nCtrlPts, nBezCurvePts);
	}

	glColor3f(1, 1, 1);
	for (int i = 0; i < 8; i++) {
		glTranslatef(0, -0.8, 0);
		bezier(ctrlPts, nCtrlPts, nBezCurvePts);
	}

	glColor3f(19 / 255.0, 136 / 255.0, 8 / 255.0);
	for (int i = 0; i < 8; i++) {
		glTranslatef(0, -0.8, 0);
		bezier(ctrlPts, nCtrlPts, nBezCurvePts);
	}

	glPopMatrix();

	glColor3f(0.7, 0.5, 0.3);

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(20, 100);
	glVertex2f(20, 40);
	glEnd();

	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

void winReshapeFun(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 130, 0, 130);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Bezier Curve");
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFun);
	glutMainLoop();
	return 0;
}