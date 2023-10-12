#pragma once
#include "Movement.h"
#include "SDL/SDL.h"

#include "Math.h"
***REMOVED***

class Input
{
public:
	enum State
	{
		pressed,
		released,
		held,
		none
	};

	Input();
	~Input();
	State GetKeyboardState(SDL_Scancode s) const;
	void Update();
	void UpdatePrev();
	State GetMouseButtonState(int x) const;

	

	//maybe actually set it here centralise and that
	void SetMouseRelative(bool x) { ismouserelative = x; }
private:

	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];

	Uint32 mcurrmouse;
	Uint32 mprevmouse;



	bool ismouserelative;
};