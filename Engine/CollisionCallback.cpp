#include "stdafx.h"
#include "CollisionCallback.h"


CollisionCallback::CollisionCallback()
{
}


CollisionCallback::~CollisionCallback()
{
}

void CollisionCallback::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
{

	for (PxU32 i = 0; i < nbPairs; i++)
	{
		const PxContactPair& cp = pairs[i];

		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			//PxRigidActor* ac = pairHeader.actors[0];


			//	if ((pairHeader.actors[0] == ) ||
			//		(pairHeader.actors[1] == mSubmarineActor))
			//	{
			//		PxActor* otherActor = (mSubmarineActor == pairHeader.actors[0]) ?
			//			pairHeader.actors[1] : pairHeader.actors[0];

			//	break;
			//}
		}
	}
	printf("WE HAVE A CONTACT!!!");
	for (physx::PxU32 i = 0; i < nbPairs; i++)
	{
		const physx::PxContactPair& cp = pairs[i];
		if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			printf("WE HAVE A ROCKET CONTACT!!!");
		}
	}
}


