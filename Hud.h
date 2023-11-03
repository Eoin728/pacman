#pragma once
#include "Ui.h"

class Hud :public Ui
{
public:
	Hud(class Game* g);
	~Hud();
	void Draw(class Shader*) override;

	void SwitchDrawCrosshair() { mdrawcrosshair = !mdrawcrosshair; }
private:
	class Texture* mrockcounter;
	class Texture* mrocksymbol;

	class Texture* mpelletsymbol;
	class Texture* mpelletcounter;

	class Texture* mcrosshair;
	bool mdrawcrosshair;
	std::vector<class Texture*> mtexs;

};
