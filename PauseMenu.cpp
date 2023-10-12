#include "PauseMenu.h"
#include "Game.h"
#include "Input.h"
#include "Text.h"
#include "Renderer.h"
#include "Texture.h"
Pause::Pause(class Game* g):Ui{g}
{
	
	Texture* t;
	g->SetState(Game::Paused);
	

	 t = mtexty->GetText("resume", mmenucolour);
	new Interact(this,Vector3(0.0f, 100.0f, 0.0f), Vector3(minteractwidth, minteractheight, 0.0f),t, [this]() {SetState(Ui::Dead); });
	

	t = mtexty->GetText("quit", mmenucolour);
	new Interact(this,Vector3(0.0f, -100.0f, 0.0f), Vector3(minteractwidth, minteractheight, 0.0f), t, [this]() {mgame->SetState(Game::Dead); });

}

Pause::~Pause()
{
	mgame->SetState(Game::NotPaused);
}

void Pause::ProcessInput(const class Input& state)
{
	Ui::ProcessInput(state);
	if (state.GetKeyboardState(SDL_SCANCODE_ESCAPE) == Input::released)
	{
		SetState(Ui::Dead);
	}
}

