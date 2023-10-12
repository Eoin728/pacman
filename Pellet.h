#pragma once
#include "Collectible.h"

class Pellet :public Collectible
{
public:
	Pellet(class Game*);
	void SpecialMove() override;

};