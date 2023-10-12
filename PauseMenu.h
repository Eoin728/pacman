#pragma once
#include "Ui.h"

class Pause :public Ui
{
public:
	Pause(class Game*);
	~Pause();

	virtual void ProcessInput(const class Input& state);
	
private:
	

};