#include "Ui.h"
#include "Game.h"
#include "GL/glew.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "SDL/SDL.h"
#include "Text.h"
#include "Input.h"

Ui::Ui( Game* g):mgame{g},mstate{Ui::Alive}
{
	g->AddUi(this);

	mhighlighttex = g->GetRenderer()->GetTexture("Assets/highlighted.png");
	mnonhighlighttex = g->GetRenderer()->GetTexture("Assets/nonhighlight.png");

	mtexty = new Text();
	mtexty->Load("Assets/AmaticSC-Regular.ttf", 52);

	minteractheight = mhighlighttex->GetHeight();
	 minteractwidth = mhighlighttex->GetWidth();
}

Ui::~Ui()
{
	for (auto x : minteracts)
	{
		delete x;
	}
	mtexty->Unload();
	delete mtexty;
}


void Ui::Drawhelper(Texture * t,Vector3& a,class Shader* s)
{


	float sf[4][4] =
	{
		{ t->GetWidth(), 0.0f, 0.0f, 0.0f},
		{ 0.0f, t->GetHeight(), 0.0f, 0.0f},
		{ 0.0f, 0.0f, 1, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
	};
	Matrix4 scaleMat = Matrix4(sf);


	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(a.x, a.y, 0.0f));
	
	Matrix4 world = scaleMat * transMat;
	s->SetMatrixUniform("uworldtrans", world);

	t->SetActive();

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


}




void Ui::Draw(class Shader* s)
{

	//do this once in renderer maybe?
//	glEnable(GL_TEXTURE_2D); glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (auto x : minteracts)
	{
		Texture* t;
		if (x->mhighlighted)
		{
			t = mhighlighttex;
		}
		else
		{
			t = mnonhighlighttex;
		}
		Drawhelper(t, x->mpos, s);

		//draw text
		Drawhelper(x->mtexture, x->mpos, s);


	}
}

void Ui::ProcessInput(const class Input& state)
{
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	x -= mgame->GetRenderer()->GetScreenWidth() * 0.5;
	y -= mgame->GetRenderer()->GetScreenHeight() * 0.5f; 
	
	//WTF IS THIS
	y *= -1;

	for (auto g : minteracts)
	{
		if (g->ContainsPoint(Vector3(x, y, 0)))
		{
		
			g->mhighlighted = true;
		}
		else
		{
			
			g->mhighlighted = false;
		}


		if (state.GetMouseButtonState(SDL_BUTTON_LEFT) == Input::pressed && g->mhighlighted)
		{
			g->mfunc();
		}
	}



}


void Ui::AddInteract(class Interact* i)
{
	minteracts.emplace_back(i);
}

Interact::Interact(class Ui * u,const Vector3& pos, const Vector3& dim, class Texture * t, std::function<void()> a):mpos{pos},mtexture{t}, mhighlighted{false},mfunc{a}
{
	
	mdim.x = dim.x / 2;
	mdim.y = dim.y / 2;
	u->AddInteract(this);
}

bool Interact::ContainsPoint(const Vector3& a)
{
	Vector3 rightup = mpos + mdim;
	Vector3 rightdown = mpos - mdim;

	return !(
		a.x > rightup.x ||
		a.x < rightdown.x ||
		a.y > rightup.y ||
		a.y < rightdown.y
		);

}

Interact::~Interact()
{
	delete mtexture;
}