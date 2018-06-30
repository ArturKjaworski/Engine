#pragma once
#include <type_traits>
#include "player/Player.h"
#include "Objects/Interactable_Obj.h"
#include "Objects/PickUp_Obj.h"
#include "Objects/Coin.h"
#include "labirynth gen/LabGen.h"
#include "graphics classes/Targa.hpp"
#include "graphics classes/ThreeMaxLoader.h"

class Game
{
public:
	Game();
	~Game();

	//amount of objects
#define obj_amount 1
	//PickUp objects list;
	GLint PU_Obj;

#pragma region global vars for world & player
	int labSizeX = 25;
	int labSizeZ = 25;

	PxRigidStatic* ground, *sky;
	GLUquadricObj *sphere1;
	LabGen maze;

	Player* player = nullptr;

	vector<Interactable_Obj*> PU_objects;        //? not used in game del later
#pragma endregion

	void init();
	void update();

	void getColumnMajor(PxMat33 m, PxVec3 t, float * mat);
	void SetupGLMatrix(const PxTransform & pose);

	bool loadTex(const int& id, char* path);
	void compileModel(const obj_type& object, const int& texId);
	void renderObj();

	template <class T>
	void addObj(const Vec3& pos, const string& name, const int& meshId, const PxGeometry& box);

	static PxRigidStatic* createSActor(const PxVec3& pos, const float& angle, const PxVec3& axis, const PxGeometry& geometry);
	static PxRigidDynamic* createDActor(const PxVec3& pos, const float& angle, const PxVec3& axis, const PxGeometry& geometry);
};

template<class T>
inline void Game::addObj(const Vec3 & pos, const string & name, const int & meshId, const PxGeometry & box)
{
	T* ob = new T(pos, name, meshId);
	ob->setBox(createDActor(PxVec3(pos.x, pos.y + 4, pos.z), 0, PxVec3(0, 0, 0), box));
	PU_objects.push_back(ob);
}