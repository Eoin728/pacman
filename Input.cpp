#include "Input.h"
#include <memory>
Input::Input():ismouserelative{false}
{
	mCurrState = SDL_GetKeyboardState(NULL);
	// Clear previous state memory
	memset(mPrevState, 0,
		SDL_NUM_SCANCODES);
	mcurrmouse = 0;
	mprevmouse = 0;

}

Input::~Input()
{

}

Input::State Input::GetKeyboardState(SDL_Scancode s) const
{
	if (mPrevState[s] == 1)
	{
		if (mCurrState[s] == 1)
		{
			return Input::held;
		}
		else
		{
			return Input::released;
		}
	}
	else
	{
		if (mCurrState[s] == 1)
		{
			return Input::pressed;
		}
		else
		{
			return Input::none;
		}
	}
}
void Input::Update()
{
	
	mCurrState = SDL_GetKeyboardState(NULL);

	//perhaps get x and y here idk

	//also try using get relative mouse mode function
	if (ismouserelative)
		mcurrmouse = SDL_GetRelativeMouseState(nullptr, nullptr);
	else
		mcurrmouse = SDL_GetMouseState(nullptr, nullptr);
}

void Input::UpdatePrev()
{
	memcpy(mPrevState, mCurrState, SDL_NUM_SCANCODES);

	mprevmouse = mcurrmouse;
}

Input::State Input::GetMouseButtonState(int x) const
{
	int bitmask = SDL_BUTTON(x);

	if ((bitmask & mprevmouse) == 0)
	{
		if ((bitmask & mcurrmouse) == 0)
		{
			return none;
		}
		else
		{
			return pressed;
		}
	}
	else
	{
		if ((bitmask & mcurrmouse) == 0)
		{
			return released;
		}
		else
		{
			return held;
		}
	}




}