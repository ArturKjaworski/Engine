#include "stdafx.h"
#include "PickUp_Obj.h"


PickUp_Obj::PickUp_Obj()
{
	cout << "PickUp bez par\n";
}

PickUp_Obj::PickUp_Obj(string ptr)
{
	name = ptr;
}

void PickUp_Obj::interact()
{
	cout << "\nPickUp interact()\n";
}
