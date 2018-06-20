#include "stdafx.h"
#include "player/Player.h"
#include "PickUp_Obj.h"
#include "graphics classes/Targa.hpp"
#include "graphics classes/ThreeMaxLoader.h"

int _width(920);
int _height(640);

#define obj_amount 1

#pragma region tex & models

GLuint tex[obj_amount+2];
obj_type obj[obj_amount];

GLint PU_Obj;
#pragma endregion

#pragma region global vars for world & player
GLUquadricObj *sphere1;
Player* player;
vector<PickUp_Obj*> PU_objects;
PxRigidStatic* ground, *sky;
#pragma endregion

#pragma region light vars
GLfloat lightAmb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat lightDif[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat lightSpec[] = { 1.0, 1.0, 1.0, 1 };
GLfloat lightColor0[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float l_pos1[] = {0,300,0,1};
#pragma endregion

bool down = false;      //bool for (not)pressed RMB button check

#pragma region Physx
static PxDefaultErrorCallback gDefaultErrorCallback;
static PxDefaultAllocator gDefaultAllocatorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene = NULL;

PxRigidDynamic* createDActor(PxVec3& pos, const float& angle,const PxVec3& axis, const PxGeometry& geometry)
{
	PxQuat kwat(angle*PI/180, axis);
	PxTransform t(pos, kwat);

	PxMaterial* m = gPhysics->createMaterial(0.5,0.5,0.5);
	PxRigidDynamic* actor = PxCreateDynamic(*gPhysics, t, geometry, *m, 10.0f);
	gScene->addActor(*actor);
	return actor;
}

PxRigidStatic* createSActor(PxVec3& pos, const float& angle, const PxVec3& axis, const PxGeometry& geometry)
{
	PxQuat kwat(angle*PI / 180, axis);
	PxTransform t(pos, kwat);

	PxMaterial* m = gPhysics->createMaterial(.5f, .5f, .5f);
	PxRigidStatic* actor = PxCreateStatic(*gPhysics, t, geometry, *m);

	gScene->addActor(*actor);
	return actor;
}
#pragma endregion

bool loadTex(const int& id, char* path)
{
	glBindTexture(GL_TEXTURE_2D, tex[id]);
	if (!LoadTGATexture(path))
	{
		puts("blad podczas wczytywania tekstury");
		return false;
	}
	return true;
}

void compileModel(const obj_type& object, const int& texId)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId+1);
	
	glBegin(GL_TRIANGLES);
	for (int l_index = 0; l_index<object.polygons_qty; l_index++)
	{
		glTexCoord2f(object.mapcoord[object.polygon[l_index].a].u,
			object.mapcoord[object.polygon[l_index].a].v);
		glVertex3f(object.vertex[object.polygon[l_index].a].x, object.vertex[object.polygon[l_index].a].y, object.vertex[object.polygon[l_index].a].z);

		glTexCoord2f(object.mapcoord[object.polygon[l_index].b].u,
			object.mapcoord[object.polygon[l_index].b].v);
		glVertex3f(object.vertex[object.polygon[l_index].b].x, object.vertex[object.polygon[l_index].b].y, object.vertex[object.polygon[l_index].b].z);

		glTexCoord2f(object.mapcoord[object.polygon[l_index].c].u,
			object.mapcoord[object.polygon[l_index].c].v);
		glVertex3f(object.vertex[object.polygon[l_index].c].x, object.vertex[object.polygon[l_index].c].y, object.vertex[object.polygon[l_index].c].z);
	}
	glEnd();
}

void init()
{
#pragma region enable
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#pragma endregion

#pragma region Physx init
	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	
	gDispatcher = PxDefaultCpuDispatcherCreate(1);
	sceneDesc.cpuDispatcher = gDispatcher;

	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);
#pragma endregion

#pragma region textures
	glGenTextures(obj_amount +2 , tex);

	loadTex(0, "res/tex/grass.tga");
	loadTex(1, "res/tex/sky.tga");
	loadTex(2, "res/tex/skull.tga");
	
#pragma endregion

#pragma region models
	CThreeMaxLoader::Load3DS(&obj[0], "res/models/skull.3ds");

	PU_Obj = glGenLists(1);
	glNewList(PU_Obj+0,GL_COMPILE);
	compileModel(obj[0], 2);
	glEndList();
#pragma endregion

#pragma region init objects
	PxBoxGeometry plane(100, 0.02, 100);
	ground = createSActor(PxVec3(0, -1, 0),0,PxVec3(0,0,0),plane);
	sky = createSActor(PxVec3(0, 50, 0), 0, PxVec3(0, 0, 0), plane);
	
	player = new Player(10.f, PU_Obj + 0);
	PxBoxGeometry box(1, 4, 1);
	player->setBox(createDActor(PxVec3(player->getPos().x, player->getPos().y, player->getPos().z),0,PxVec3(0,1,0),box));
#pragma endregion

	glutWarpPointer(_width / 2, _height / 2);
	ShowCursor(false);
}

void addObj(const Vec3& pos, const string& name, const int& meshId)
{
	PickUp_Obj* ob = new PickUp_Obj(pos, name, meshId);
	PxSphereGeometry sphere(1);
	ob->setBox(createDActor(PxVec3(pos.x, pos.y, pos.z),0, PxVec3(0, 0, 0), sphere));
	PU_objects.push_back(ob);
}

void help()
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
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glPushMatrix();
		pose = ground->getGlobalPose();
		SetupGLMatrix(pose);

		glColor4f(0, 1, 0, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex3f(-100, 0, -100);
		glTexCoord2f(0, 25); glVertex3f(-100, 0, 100);
		glTexCoord2f(25, 25);	glVertex3f(100, 0, 100);
		glTexCoord2f(25, 0);	glVertex3f(100, 0, -100);
		glEnd();
	glPopMatrix();
	
	//sky
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glColor4f(1, 1, 1,1);
	glPushMatrix();
		pose = sky->getGlobalPose();
		SetupGLMatrix(pose);
		glRotatef(-90, 1, 0, 0);
		sphere1 = gluNewQuadric();
		gluQuadricDrawStyle(sphere1, GLU_FILL);
		gluQuadricTexture(sphere1, GL_TRUE);
		gluQuadricNormals(sphere1, GLU_SMOOTH);    
		gluQuadricOrientation(sphere1, GLU_INSIDE);
		gluSphere(sphere1, 200, 40, 40);
	glPopMatrix();

//PU objects
	for (int ii = 0; ii < int(PU_objects.size()); ++ii)
	{
		glPushMatrix();
			pose = PU_objects[ii]->getBox()->getGlobalPose();
			SetupGLMatrix(pose);
			glColor4f(1, 0, 1, 1);
			glCallList(PU_objects[ii]->getModel());			//mesh
		glPopMatrix();
	}

	//character
	if (player->cam->camType == Camera::TPP)
	{
		glPushMatrix();
			pose = player->getBox()->getGlobalPose();
			SetupGLMatrix(pose);
			glTranslatef(0, player->idleY, 0);
			glColor4f(0.8, 0.4, 0, player->getAlpha());
			glCallList(player->getModel());					//mesh
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
	
	player->update();
	if (player->cam->camType == Camera::TPP)
		gluLookAt(player->cam->getPos().x, player->cam->getPos().y, player->cam->getPos().z,
			player->getPos().x, player->getPos().y, player->getPos().z,
			0, 1, 0);
	else
		gluLookAt(player->cam->getPos().x, player->cam->getPos().y+player->idleY, player->cam->getPos().z,
			player->getPos().x, player->getPos().y + player->idleY, player->getPos().z,
			0, 1, 0);


#pragma region Light
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, l_pos1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	glMateriali(GL_FRONT, GL_SHININESS, 10);
	
#pragma endregion

	renderObj();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)w / h, 0.1f, 340);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	_width = w;
	_height = h;
}

void keyboard(unsigned char key, int x, int y)
{
	PX_UNUSED(x);
	PX_UNUSED(y);
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
		addObj(player->getforward() , "czaszka", PU_Obj + 0);
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
		help();
		break;
	}
}

#pragma region mouse funcs
//tracking mouse buttons
void mouse(int but, int state, int x, int y)
{
	PX_UNUSED(x);
	PX_UNUSED(y);
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
#pragma endregion

void timer(int val)
{
	render();
	glutTimerFunc(val, timer, 0);
}

// atexit func
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
	help();
	
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

	glutTimerFunc(1000 / FPS, timer, 0);

	atexit(ex);
	init();
	glutMainLoop();
	
	return 0;
}

