#pragma once
//#include "CollisionCallback.h"
#include "player/Player.h"
#include "Objects/Interactable_Obj.h"
#include "Objects/PickUp_Obj.h"
#include "Objects/Coin.h"
#include "labirynth gen/LabGen.h"
#include "graphics classes/Targa.hpp"
#include "graphics classes/ThreeMaxLoader.h"

class Game : public PxSimulationEventCallback
{
public:
	Game();
	~Game();

	
	struct FilterGroup
	{
		enum Enum
		{
			eWall		= (1<<0),
			ePlayer		= (1<<1),
			eOpponent	= (1<<2),
			eCoin		= (1<<3)
		};
	};

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

	vector<Interactable_Obj*> PU_objects;        //Coins/ammo 
	vector<PxRigidDynamic*> PU_destroy;		//list of object to destroy/set inactive

#pragma endregion

	void init();
	void update();

	void getColumnMajor(PxMat33 m, PxVec3 t, float * mat);
	void SetupGLMatrix(const PxTransform & pose);

	bool loadTex(const int& id, char* path);
	void compileModel(const obj_type& object, const int& texId);
	void preRender();
	void renderObj();

	template <class T>
	void addObj(const string& _name, const Vec3& pos, const int& meshId, const PxGeometry& box, PxU32 filterGroup, PxU32 filterMask);

	static PxRigidStatic* createSActor(const PxVec3& pos, const float& angle, const PxVec3& axis, const PxGeometry& geometry);
	static PxRigidDynamic* createDActor(const string& _name, const PxVec3& pos, const float& angle, const PxVec3& axis, const PxGeometry& geometry, PxU32 filterGroup, PxU32 filterMask);

	static PxFilterFlags filtershader(PxFilterObjectAttributes attributes0,
		PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,
		PxFilterData filterData1,
		PxPairFlags& pairFlags,
		const void* constantBlock,
		PxU32 constantBlockSize);

	virtual void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);
	virtual void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count) {}
	virtual void onConstraintBreak(physx::PxConstraintInfo*, physx::PxU32) {}
	virtual void onWake(physx::PxActor**, physx::PxU32) {}
	virtual void onSleep(physx::PxActor**, physx::PxU32) {}
	virtual void onAdvance(const PxRigidBody *const *bodyBuffer, const PxTransform *poseBuffer, const PxU32 count) {}
};

template<class T>
inline void Game::addObj(const string& _name, const Vec3 & pos, const int & meshId, const PxGeometry & box, PxU32 filterGroup, PxU32 filterMask)
{
	T* ob = new T(pos, _name, meshId);
	ob->setBox(createDActor(_name, PxVec3(pos.x, pos.y + 4, pos.z), 0, PxVec3(0, 0, 0), box, filterGroup, filterMask));
	PU_objects.push_back(ob);
}