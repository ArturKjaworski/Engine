#include "stdafx.h"
#include "Player.h"
#include "PickUp_Obj.h"


int _width(920);
int _height(640);
	
Player* player = new Player(10.0f);
vector<PickUp_Obj*> PU_objects;
PxRigidStatic* ground;
PxRigidStatic* sky;

bool down = false;

#pragma region Physx
static PxDefaultErrorCallback gDefaultErrorCallback;
static PxDefaultAllocator gDefaultAllocatorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene = NULL;

PxRigidDynamic* createDActor(const PxGeometry& geometry, PxVec3& pos)
{
	PxQuat kwat(0, PxVec3(0, 0, 1));
	PxTransform t(pos, kwat);

	PxMaterial* m = gPhysics->createMaterial(0.5,0.5,0.5);
	PxRigidDynamic* actor = PxCreateDynamic(*gPhysics, t, geometry, *m, 10.0f);
	gScene->addActor(*actor);
	return actor;
}

PxRigidStatic* createSActor(const PxGeometry& geometry, PxVec3& pos)
{
	PxQuat kwat(0, PxVec3(0,0,1));
	PxTransform t(pos, kwat);

	PxMaterial* m = gPhysics->createMaterial(.5f, .5f, .5f);
	PxRigidStatic* actor = PxCreateStatic(*gPhysics, t, geometry, *m);

	gScene->addActor(*actor);
	return actor;
}
#pragma endregion

void init()
{
	//Physx
	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	
	gDispatcher = PxDefaultCpuDispatcherCreate(1);
	sceneDesc.cpuDispatcher = gDispatcher;

	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	PxBoxGeometry plane(200, 0.02, 200);
	ground = createSActor(plane, PxVec3(-100, -1, -100));
	sky = createSActor(plane, PxVec3(-100, 20, -100));
	
	PxBoxGeometry box(1, 1, 1);
	player->setBox(createDActor(box, PxVec3(0,0,0)));
}

void addObj(Vec3& pos, const string& name)
{
	PickUp_Obj* ob = new PickUp_Obj(pos, name);

	PxSphereGeometry sphere(1);
	ob->setBox(createDActor(sphere, PxVec3(pos.x, pos.y, pos.z)));
	PU_objects.push_back(ob);
}

void intro()
{
	system("cls");
	cout << "1: create PickUp Obj\n";
	cout << "2: create Interct Obj\n";

	cout << "w,s,a,d: movement\n";
	cout << "z,x: zoom in/out\n";
	cout << "\nMouse:\nhold RMB to looking around\nwithout anu btn: move in that direction\n";
	cout << "LMB to interact (not working for now)\n";

	cout << "q: exit\n";
}

#pragma region matrix transformation
// By Muhammad Mobeen Movania
void getColumnMajor(PxMat33 m, PxVec3 t, float* mat)
{
	mat[0] = m.column0[0];
	mat[1] = m.column0[1];
	mat[2] = m.column0[2];
	mat[3] = 0;

	mat[4] = m.column1[0];
	mat[5] = m.column1[1];
	mat[6] = m.column1[2];
	mat[7] = 0;

	mat[8] = m.column2[0];
	mat[9] = m.column2[1];
	mat[10] = m.column2[2];
	mat[11] = 0;

	mat[12] = t[0];
	mat[13] = t[1];
	mat[14] = t[2];
	mat[15] = 1;
}

void SetupGLMatrix(const PxTransform &pose) {
	float glmat[16];	//4x4 ogl matrix
	PxMat33 m = PxMat33(pose.q);  //Quat of obj
	getColumnMajor(m, pose.p, glmat); //set val in mat for obj
	glMultMatrixf(glmat);
}

#pragma endregion

#pragma region render obejcts
void renderObj()
{
	PxTransform pose;
	//ground
	glPushMatrix();
		pose = ground->getGlobalPose();
		SetupGLMatrix(pose);

		glColor4f(0, 1, 0, 1);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 200);
			glVertex3f(200, 0, 200);
			glVertex3f(200, 0, 0);
		glEnd();
	glPopMatrix();
	
	//sky
	glPushMatrix();
		pose = sky->getGlobalPose();
		SetupGLMatrix(pose);

		glColor4f(0, 1, 1, 1);
		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 200);
			glVertex3f(200, 0, 200);
			glVertex3f(200, 0, 0);
		glEnd();
	glPopMatrix();

//PU objects
	for (int ii = 0; ii < PU_objects.size(); ++ii)
	{
		glPushMatrix();
			pose = PU_objects[PU_objects.size() - 1]->getBox()->getGlobalPose();
			SetupGLMatrix(pose);

			glColor4f(1, 0, 0, 1);
				glutSolidSphere(1, 32, 32);			//mesh
		glPopMatrix();
	}

	//character
	if (player->cam.camType == Camera::TPP)
	{
		glPushMatrix();
			pose = player->getBox()->getGlobalPose();
			SetupGLMatrix(pose);

			glColor4f(0, 0, 1, player->getAlpha());
			glutSolidTeapot(1);					//mesh
		glPopMatrix();
	}
}
#pragma endregion

void render()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gScene->simulate(SIM_TIME);
	gScene->fetchResults(true);

	gluLookAt(-player->cam.getPos().x, -player->cam.getPos().y, -player->cam.getPos().z,
		-player->getPos().x, -player->getPos().y, -player->getPos().z,
		0, 1, 0);

	renderObj();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, float(w / h), 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	_width = w;
	_height = h;
}

void keyboard(unsigned char key, int x, int y)
{
	int state = glutGetModifiers();
	switch (state)
	{
	case GLUT_ACTIVE_SHIFT:
		player->setState(Player::run);
		break;
	case GLUT_ACTIVE_CTRL:
		player->setState(Player::crouch);
		break;
	default:
		player->setState(Player::walk);
		break;
	}

	switch (key)
	{
	case '1':
		system("cls");
		//addObj(player->getforward()*= 10, "skrzynka");
		cout << "dodano: "<<PU_objects[PU_objects.size()-1]->getName();
		break;

	case 'w': case 'W':
		player->move(Player::front);
		break;

	case 's':case 'S':
		player->move(Player::back);
		break;

	case 'a':case 'A':
		player->move(Player::left);
		break;

	case 'd':case 'D':
		player->move(Player::right);
		break;

	case 32:
		//jump
		break;

	case 'Q':
	case 'q':
	case 27:
		exit(0);

	case 'x':
		player->zoom('+');
		break;
	case 'z':
		player->zoom('-');
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
		player->setForward();
		down = false;
	}
	if (but == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		cout << "interact" << endl;
}

//look around
void mouseMove(int x, int y)
{
	if (down)
		player->mouse(x - width / 2, y - height / 2);
}

//move in that direction
void passiveMouseMove(int x, int y)
{
	player->look(x - width / 2, y - height / 2);
}

void timer(int val)
{
	render();
	glutTimerFunc(val, timer, 0);
}

void ex()
{
	delete player;
	PU_objects.clear();
	
	//physx
	gScene->release();
	gDispatcher->release();
	gPhysics->release();
	gFoundation->release();
}

int main(int argc, char *argv[])
{
	intro();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(_width, _height);
	glutInitWindowPosition(1920 - _width, 1080 - _height);
	glutCreateWindow("FPP");

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(passiveMouseMove);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutWarpPointer(_width / 2, _height / 2);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutTimerFunc(1000 / FPS, timer, 0);

	atexit(ex);
	init();
	glutMainLoop();
	
	return 0;
}

