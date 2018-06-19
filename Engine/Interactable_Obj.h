#pragma once

class Interactable_Obj
{
public:
	Interactable_Obj();
	Interactable_Obj(const string);
	Interactable_Obj(const float&, const float&, const float&, const string, const int&);
	Interactable_Obj(const Vec3&, const string, const int& meshId);
	virtual ~Interactable_Obj();
	
protected:
	string* name;
	GLint model;
	GLuint tex;
	Vec3 pos;
	PxRigidBody* box;
	
public:
	virtual void interact();

	const virtual string getName();
	PxRigidBody* getBox();
	int getModel();

	void setBox(PxRigidBody*);
};

