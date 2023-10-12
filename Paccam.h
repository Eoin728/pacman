#pragma once
#include "Component.h"


class Paccam:public Component
{
public:
	Paccam(class Actor*);

	void Update(float delta) override;

	void SetPitch(float x) { mpitchspeed = x; }

private:
	float mmaxpitch;
	float mpitchspeed;
	float mpitch;
};

class ThirdCam :public Paccam
{
public:
	ThirdCam(class Actor*);

	void Update(float delta) override;

private:
	float mbackdis;
	float mfordis;
	float mupdis;
};