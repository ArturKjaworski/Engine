#include "stdafx.h"
#include "Game.h"

GLuint tex[obj_amount + 3];
obj_type obj[obj_amount];

#pragma region Physx
static PxDefaultErrorCallback gDefaultErrorCallback;
static PxDefaultAllocator gDefaultAllocatorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene = NULL;
#pragma endregion

Game::Game()
{
	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());

	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

	gDispatcher = PxDefaultCpuDispatcherCreate(1);
	sceneDesc.cpuDispatcher = gDispatcher;

	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	gScene = gPhysics->createScene(sceneDesc);

	init();
}

Game::~Game()
{
	delete player;

	for (int i = 0; i<int(PU_objects.size()); ++i)
	{
		if (PU_objects[i] != nullptr)
		{
			delete (PU_objects[i]);
			PU_objects[i] = nullptr;
		}
	}
	PU_objects.clear();

	//physx
	gScene->release();
	gDispatcher->release();
	gPhysics->release();
	gFoundation->release();
}

void Game::init()
{
#pragma region textures
	glGenTextures(obj_amount + 3, tex);

	loadTex(0, "res/tex/grass.tga");
	loadTex(1, "res/tex/sky.tga");
	loadTex(2, "res/tex/wall.tga");
	loadTex(3, "res/tex/skull.tga");

#pragma endregion

#pragma region models
	CThreeMaxLoader::Load3DS(&obj[0], "res/models/skull.3ds");

	PU_Obj = glGenLists(1);
	glNewList(PU_Obj + 0, GL_COMPILE);
	compileModel(obj[0], 3);
	glEndList();
#pragma endregion

#pragma region init objects
	//labirynth
	maze = LabGen(labSizeX, labSizeZ);
	maze.setWall(&Game::createSActor);

	//sky, ground
	PxBoxGeometry plane(LabField::size / 2 * labSizeX, 0.02, LabField::size / 2 * labSizeZ);
	ground = createSActor(PxVec3(-LabField::size / 2 + labSizeX * LabField::size / 2, 0, -LabField::size / 2 + labSizeZ * LabField::size / 2), 0, PxVec3(0, 0, 0), plane);
	sky = createSActor(PxVec3(0, 50, 0), 0, PxVec3(0, 0, 0), plane);

	PxSphereGeometry sphere(1);
	for (int ii = 0; ii < maze.getSize(); ++ii)
	{
		addObj<Coin>(Vec3(maze.getF_pos(ii)), "coin", -1, sphere);
		PU_objects[ii]->getBox()->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, true);
	}

#pragma region player
	if (player == nullptr)
	{
		player = new Player(10.f, PU_Obj + 0);
		PxBoxGeometry box(1, 4, 1);
		player->setBox(createDActor(PxVec3(player->getPos().x, player->getPos().y, player->getPos().z), 0.f, PxVec3(0, 1, 0), box));
	}
	else
	{
		delete player;
		player = new Player(10.f, PU_Obj + 0);
		PxBoxGeometry box(1, 4, 1);
		player->setBox(createDActor(PxVec3(player->getPos().x, player->getPos().y, player->getPos().z), 0.f, PxVec3(0, 1, 0), box));
	}

#pragma endregion

#pragma endregion
}

void Game::update()
{
	gScene->simulate(SIM_TIME);
	gScene->fetchResults(true);

	player->update();

	if (player->cam->camType == Camera::TPP)
		gluLookAt(player->cam->getPos().x, player->cam->getPos().y, player->cam->getPos().z,
			player->getPos().x, player->getPos().y, player->getPos().z,
			0, 1, 0);
	else
		gluLookAt(player->cam->getPos().x, player->cam->getPos().y + player->idleY, player->cam->getPos().z,
			player->getPos().x, player->getPos().y + player->idleY, player->getPos().z,
			0, 1, 0);

	renderObj();
}

#pragma region matrix transformation
// By Muhammad Mobeen Movania
void Game::getColumnMajor(PxMat33 m, PxVec3 t, float* mat)
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

void Game::SetupGLMatrix(const PxTransform &pose) {
	float glmat[16];	//4x4 ogl matrix
	PxMat33 m = PxMat33(pose.q);  //Quat of obj
	getColumnMajor(m, pose.p, glmat); //set val in mat for obj
	glMultMatrixf(glmat);
}
#pragma endregion

#pragma region tex & model funcs
bool Game::loadTex(const int & id, char * path)
{
	glBindTexture(GL_TEXTURE_2D, tex[id]);
	if (!LoadTGATexture(path))
	{
		puts("blad podczas wczytywania tekstury");
		return false;
	}
	return true;
}

void Game::compileModel(const obj_type & object, const int & texId)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texId + 1);

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
#pragma endregion

#pragma region render obejcts
void Game::renderObj()
{
	PxTransform pose;
	//ground
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glPushMatrix();
	pose = ground->getGlobalPose();
	SetupGLMatrix(pose);

	glColor4f(0, 1, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);		glVertex3f(0 - LabField::size * (labSizeX) / 2, 0, 0 - LabField::size * (labSizeZ) / 2);
	glTexCoord2f(0, 25);	glVertex3f(0 - LabField::size * (labSizeX) / 2, 0, LabField::size * (labSizeZ) / 2);
	glTexCoord2f(25, 25);	glVertex3f(LabField::size * (labSizeX) / 2, 0, LabField::size * (labSizeZ) / 2);
	glTexCoord2f(25, 0);	glVertex3f(LabField::size * (labSizeX) / 2, 0, 0 - LabField::size * (labSizeZ) / 2);
	glEnd();
	glPopMatrix();


	//sky
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glColor4f(1, 1, 1, 1);
	glPushMatrix();
	pose = sky->getGlobalPose();
	pose.p = player->getBox().getGlobalPose().p;
	SetupGLMatrix(pose);
	glRotatef(-90, 1, 0, 0);
	sphere1 = gluNewQuadric();
	gluQuadricDrawStyle(sphere1, GLU_FILL);
	gluQuadricTexture(sphere1, GL_TRUE);
	gluQuadricNormals(sphere1, GLU_SMOOTH);
	gluQuadricOrientation(sphere1, GLU_INSIDE);
	gluSphere(sphere1, 500, 40, 40);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, tex[2]);
	maze.render();

	//PU objects
	for (int ii = 0; ii < int(PU_objects.size()); ++ii)
	{
		glPushMatrix();
		pose = PU_objects[ii]->getBox()->getGlobalPose();
		SetupGLMatrix(pose);
		glColor4f(1, 0, 1, 1);
		if (PU_objects[ii]->getModel() > -1)
			glCallList(PU_objects[ii]->getModel());			//mesh
		else
			glutSolidSphere(.5, 40, 40);
		glPopMatrix();
	}

	//character
	if (player->cam->camType == Camera::TPP)
	{
		glPushMatrix();
		pose = player->getBox().getGlobalPose();
		SetupGLMatrix(pose);
		glTranslatef(0, player->idleY, 0);
		glColor4f(0.8, 0.4, 0, player->getAlpha());
		glCallList(player->getModel());					//mesh
		glPopMatrix();
	}
}

#pragma endregion

#pragma region create actors
PxRigidStatic * Game::createSActor(const PxVec3 & pos, const float & angle, const PxVec3 & axis, const PxGeometry & geometry)
{
	PxQuat kwat(angle*PI / 180, axis);
	PxTransform t(pos, kwat);

	PxMaterial* m = gPhysics->createMaterial(.5f, .5f, .5f);
	PxRigidStatic* actor = PxCreateStatic(*gPhysics, t, geometry, *m);

	gScene->addActor(*actor);
	return actor;
}
PxRigidDynamic * Game::createDActor(const PxVec3 & pos, const float & angle, const PxVec3 & axis, const PxGeometry & geometry)
{
	PxQuat kwat(angle*PI / 180, axis);
	PxTransform t(pos, kwat);

	PxMaterial* m = gPhysics->createMaterial(0.5, 0.5, 0.5);
	PxRigidDynamic* actor = PxCreateDynamic(*gPhysics, t, geometry, *m, 10.0f);
	gScene->addActor(*actor);

	return actor;
}
#pragma endregion