#include <iostream>
#include <GL/freeglut.h>


//tweening
float xpos = 0;
float deltax = 1;

//mouse
float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
//keyboard
float xsca = 1.0f;
float ysca = 1.0f;
float zsca = 1.0f;
float xtra = 0.0f;
float ytra = 0.0f;
float ztra = 0.0f;

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glScalef(xsca, ysca, zsca);
	glTranslatef(xtra, ytra, ztra);

	glBegin(GL_QUADS);
	glVertex2f(-10.0, -10.0);
	glVertex2f(-10.0, 10.0);
	glVertex2f(10.0, 10.0);
	glVertex2f(10.0, -10.0);
	glEnd();

	glPushMatrix();
	glPopMatrix();
	glutSwapBuffers();

}

void myinit(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	GLfloat ambientlight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat diffuselight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularlight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { -80.0, 0.0, 50.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuselight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, specularlight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-1000, 1000, -1000, 1000, -1000, 1000);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-100, 100, -100 * (GLfloat)h / (GLfloat)w,
			100 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
	else
		glOrtho(-100 * (GLfloat)w / (GLfloat)h,
			100 * (GLfloat)w / (GLfloat)h, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	if (!mouseDown)
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
}

void mouseMotion(int x, int y)
{
	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

void myKeyboard(unsigned char key, int x, int y) {

	switch (key) {
	case 'w'://ZoomIn
	case 'W':
		//glScalef(1.05, 1.05, 1.05);
		xsca += 0.1;
		ysca += 0.1;
		zsca += 0.1;
		break;
	case 's'://ZoomOut
	case 'S':
		xsca += -0.1;
		ysca += -0.1;
		zsca += -0.1;
		break;
	case 'a':
	case 'A': //CameraLeft
		xtra += 4.0;
		break;
	case 'd':
	case 'D': //CameraRight
		xtra -= 4.0;
		break;
	}
	Display();
}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);

	yrot += 1;

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 80);
	glutCreateWindow("Bimo Adam - 672018274 | Yosefhin R.Y - 672018412");

	myinit();

	glutDisplayFunc(Display);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);


	glutMainLoop();
	return 1;
}