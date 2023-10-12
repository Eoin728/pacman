#pragma once
#include "Collectible.h"

class Fruit :public Collectible
{
public:
	Fruit(class Game*);
	void SpecialMove() override;
	~Fruit();
};