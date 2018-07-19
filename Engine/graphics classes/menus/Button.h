#pragma once
class Button
{
public:
	Button(const Vec3& pos, const Vec3& _size, const string& _name);
	~Button();

	string name;
	//x,y,y
	Vec3 size;
	//left down corner
	Vec3 pos;
	bool active;
	
	bool onPointer(const int&x, const int& y);
	bool onClick(const int& x, const int& y);

	void render();

};

