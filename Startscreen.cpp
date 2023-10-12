#include "Startscreen.h"
#include "Text.h"
#include "Texture.h"
#include "Game.h"
#include "Input.h"
#include "Renderer.h"
#include "Maze.h"

Startscreen::Startscreen(class Game*g):Ui{g},mmessage{nullptr}
{

	g->SetState(Game::Paused);

	float pos = g->GetMaze()->GetTileNum() * g->GetMaze()->GetTileSize() * 0.5;

	Vector3 eye = Vector3(pos - 50.0f,pos,pos * 1.5);

	float 	mpitch = Math::HalfPi;
	
	Quaternion q(Vector3::UnitY, mpitch);

	Vector3 target = Vector3::Transform(Vector3::UnitX, q);
	target = 1000.0f * target + eye;

	Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

	Matrix4 view = Matrix4::CreateView(eye, target, up);

	g->GetRenderer()->SetView(view);

}
Startscreen::~Startscreen()
{
	mgame->SetState(Game::NotPaused);
	
}

void Startscreen::ProcessInput(const class Input& state)
{
	if (state.GetMouseButtonState(SDL_BUTTON_LEFT) == Input::pressed)
	{
		SetState(Ui::Dead);
	}
	else if (state.GetKeyboardState(SDL_SCANCODE_SPACE) == Input::pressed)
	{
	
		mgame->GetMaze()->MakeNewMaze();
	}
}


void Startscreen::Draw(class Shader* s)
{
	Vector3 f = Vector3(0, 200, 0);
	Ui::Draw(s);
	Drawhelper(mtexty->GetText("Press space to make new maze", Vector3(255, 255, 255)), f, s);
	f = Vector3(0, 100, 0);
	Drawhelper(mtexty->GetText("Press mouse to play", Vector3(255, 255, 255)), f, s);

}