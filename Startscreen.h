#pragma once
#include "Ui.h"

class Startscreen:public Ui
{
public:
	Startscreen(class Game*);
	~Startscreen();

	void ProcessInput(const class Input& state) override;
	void Draw(class Shader* s);
private:
	class Texture* mmessage;


};