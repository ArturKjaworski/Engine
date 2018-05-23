#include "stdafx.h"
#include "Player.h"
#include "PickUp_Obj.h"

#define width 920
#define height 640
//Interactable_Obj* ob;		
//PickUp_Obj* obj;
Player player;
bool down = false;	

void intro()
{
	system("cls");
	cout << "1: create PickUp Obj\n";
	cout << "2: create Interct Obj\n";
	cout << "q: exit\n";
}

#pragma region render obejcts
void renderObj()
{
	//plain
	glColor3f(0, 1, 0);
	glPushMatrix();
		glBegin(GL_QUADS);
		glVertex3f(-10, -1, -10);
		glVertex3f(10, -1, -10);
		glVertex3f(10, -1, 10);
		glVertex3f(-10, -1, 10);
		glEnd();
	glPopMatrix();
	
	glColor3f(0, 1, 1);
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex3f(-10, 10, -10);
		glVertex3f(10, 10, -10);
		glVertex3f(10, 10, 10);
		glVertex3f(-10, 10, 10);
	glEnd();
	glPopMatrix();
	////////
	//cubes
	glColor3f(1, 0, 0);

	glPushMatrix();
	glTranslatef(0, 0.0, -5);
	glutSolidCube(.05);
	glPopMatrix();

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0.0, 5);
	glutSolidCube(.05);
	glPopMatrix();

	glColor3f(0, 1, 1);
	glPushMatrix();
	glTranslatef(5, 0.0, 0);
	glutSolidCube(.05);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(-5, 0.0, 0);
	glutSolidCube(.05);
	glPopMatrix();
	////////
}
#pragma endregion

void render()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	gluLookAt(-player.cam.getPos('x'), -player.cam.getPos('y'), -player.cam.getPos('z'),
		-player.getPos('x'), -player.getPos('y'), -player.getPos('z'),
		0, 1, 0);

	renderObj();
	////character
	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(-player.getPos('x'), -player.getPos('y'), -player.getPos('z'));
	glutSolidTeapot(.1);
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int x, int y)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, width / height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1':
			system("cls");
		//	obj = new PickUp_Obj("qwe");
			
			break;

		case '2':
			system("cls");
			cout << "\nInteract Obj added!\n";
			break;
				
		case 'w':
			player.move(0, 0, 0.1);
			cout << player.getPos('z')<<endl;
			break;

		case 's':
			player.move(0, 0, -0.1);
			break;

		case 'a':
			player.move(.1, 0, 0);
		
			break;

		case 'd':
			player.move(-.1, 0, 0);
			break;
		case 'z':
			player.move(0, .1, 0);
			break;

		case 'x':
			player.move(0, -.1, 0);
			break;

		case 'Q':
		case 'q':
		case 27:
			exit(0);
				
		default:
			intro();
			break;
	}
}

void mouse(int but, int state, int x, int y)
{
	if (but == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		down = true;

	if (but == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		down = false;

	if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		cout << "fail" << endl;
}

//look around
void mouseMove(int x, int y)
{
	//if (down)
	player.mouse(x - width / 2, y - height / 2);
	
}

//move in that direction
void passiveMouseMove(int x, int y)
{
	player.look(x - width / 2, y - height / 2);
}

void timer(int val)
{
	render();
	
	glutTimerFunc(val,timer,val);
}

int main(int argc, char *argv[])
{
	intro();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(1920-width, 1080-height);
	glutCreateWindow("FPP");
	
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(passiveMouseMove);

	glutWarpPointer(width / 2, height / 2);
	//glutSetCursor(GLUT_CURSOR_NONE);
	
	glutTimerFunc(1000 / 120, timer, 0);
	glutMainLoop();
    return 0;
}

