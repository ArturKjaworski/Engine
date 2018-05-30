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
		glVertex3f(-100, -1, -100);
		glVertex3f(100, -1, -100);
		glVertex3f(100, -1, 100);
		glVertex3f(-100, -1, 100);
		glEnd();
	glPopMatrix();
	
	glColor3f(0, 1, 1);
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex3f(-100, 10, -100);
		glVertex3f(100, 10, -100);
		glVertex3f(100, 10, 100);
		glVertex3f(-100, 10, 100);
	glEnd();
	glPopMatrix();
	////////
	//cubes
	glColor3f(1, 0, 0);

	glPushMatrix();
	glTranslatef(0, 0.0, -50);
	glutSolidCube(.5);
	glPopMatrix();

	glColor3f(0, 0, 1);
	glPushMatrix();
	glTranslatef(0, 0.0, 50);
	glutSolidCube(.5);
	glPopMatrix();

	glColor3f(0, 1, 1);
	glPushMatrix();
	glTranslatef(50, 0.0, 0);
	glutSolidCube(.5);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(-50, 0.0, 0);
	glutSolidCube(.5);
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
	if (player.cam.camType == Camera::TPP)
	{
		glColor3f(0, 0, 1);
		glPushMatrix();
			glTranslatef(-player.getPos('x'), -player.getPos('y'), -player.getPos('z'));
			glRotatef(90-player.getRot('x'), 0, 1, 0);
			glutSolidTeapot(.1);
		glPopMatrix();
	}
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

	int state = glutGetModifiers();
	switch (state)
	{
	case GLUT_ACTIVE_SHIFT:
		player.chState(Player::run);
		break;
	case GLUT_ACTIVE_CTRL:
		player.chState(Player::crouch);
		break;
	default:
		player.chState(Player::walk);
		break;
	}

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
				
		case 'w': case 'W':
			player.move(Player::front);
			
			break;

		case 's':case 'S':
			player.move(Player::back);
			break;

		case 'a':case 'A':
			player.move(Player::left);
		
			break;

		case 'd':case 'D':
			player.move(Player::right);
			break;

		case 'Q':
		case 'q':
		case 27:
			exit(0);
				
		case 'x':
			player.zoom('+');
			break;
		case 'z':
			player.zoom('-');
			break;
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
	{
		player.setForward();
		down = false;
	}
	if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		cout << "interact" << endl;
}

//look around
void mouseMove(int x, int y)
{
	if (down)
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
	glutSetCursor(GLUT_CURSOR_NONE);
	
	glutTimerFunc(1000 / 120, timer, 0);
	glutMainLoop();
    return 0;
}

