#pragma once
class Interactable_Obj
{
public:
	Interactable_Obj();
	Interactable_Obj(string);
	virtual ~Interactable_Obj();

protected:
	string name;

	
public:
	virtual void interact();

	const virtual string& getName();

};

