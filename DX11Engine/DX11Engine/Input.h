#pragma once
#ifndef INPUTCLASS
#define INPUTCLASS

class Input
{
public:

	static Input& getInstance()
	{
		static Input input;
		return input;
	}

	bool& getKeyRef(int i)
	{
		return keys[i];
	}
	
private:

	bool keys[256];

	float MouseX;

	float MouseY;

	Input(): keys(), MouseX(0), MouseY(0)
	{
	}
};


#endif