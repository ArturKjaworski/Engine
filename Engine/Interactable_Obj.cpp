#include "stdafx.h"
#include "Interactable_Obj.h"


Interactable_Obj::Interactable_Obj()
{
	cout << "Interactable bez ptr\n";
}

Interactable_Obj::Interactable_Obj(string ptr) : name(ptr)
{
	cout << "Interactable z ptr\n";
}

Interactable_Obj:: ~Interactable_Obj()
{
	
}

void Interactable_Obj::interact()
{
	cout << "\nInteractable_Obj interact()\n";

}

const string& Interactable_Obj::getName() 
{
	return name;
}
