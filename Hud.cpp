#include "Hud.h"
#include "Texture.h"
#include "Text.h"
#include "Game.h"
#include "Pacman.h"

Hud::Hud(class Game* g):Ui{g},mdrawcrosshair(true),mrockcounter{0},mpelletcounter{0}
{
	mcrosshair = new Texture();
	mcrosshair->Load("Assets/Crosshair.png");

	mrocksymbol = new Texture();
	mrocksymbol->Load("Assets/rockhud.png");

	mpelletsymbol = new Texture();
	mpelletsymbol->Load("Assets/pelletsymbol.png");


}


Hud::~Hud()
{
	delete mrocksymbol;

	delete mpelletsymbol;
	delete mcrosshair;
	
}


void Hud::Draw(class Shader* s)
{
	Vector3 h;

	//draw crosshair

	//this needs to be changed entire class popped and unpopped every time switch person modes 
	if (mdrawcrosshair)
	{
		Drawhelper(mcrosshair, h, s);
	}

	

	//amount of pellets collected and pellet symbol
	Vector3 g = Vector3(300, 300, 0);
	std::string x = std::to_string(mgame->GetPac()->GetPelletCount());

	Drawhelper(mtexty->GetText(x, Vector3(200, 200, 0)), g, s);
	int a  = mgame->GetPac()->GetRockCount();
	 g = Vector3(-300, -300, 0);



	 //draw the rockcunt amount of rocks fior visual representation
	 for (int i{ 0 }; i < a; i++)
	 {
		 g = Vector3(-300 + 8 * i, -300, 0);
		 Drawhelper(mrocksymbol, g, s);
	 }
	 g = Vector3(235, 310, 0);

	 Drawhelper(mpelletsymbol, g, s);

	
}
