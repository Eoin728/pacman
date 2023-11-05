#pragma once
#include "Ui.h"

class Endscreen :public Ui
{
public:
	enum State
	{
		Won,Lost
	};
	Endscreen(class Game* g,State s);
	


	void Draw(class Shader* s) override;

private:
	Texture* mmessage;
};