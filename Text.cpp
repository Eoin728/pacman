#include "Text.h"
#include "Texture.h"
Text::Text():mfont{nullptr}
{

}
Text::~Text()
{

}

//for now maybe bot sure tgho

bool Text::Load(const std::string& s,int size)
{
	TTF_Font* font = TTF_OpenFont(s.c_str(), size);
	if (!font)
	{
		SDL_Log("failed load %s",s.c_str());
		return false;
	}
	mfont = font;
	return true;
}
void Text::Unload()
{
}

//size between this function and other are not needed one has to change
class Texture* Text::GetText(const std::string& s, const Vector3& col)
{
	SDL_Color c;
	c.r = static_cast<Uint8>(col.x);
	c.g = static_cast<Uint8>(col.y);
	c.b = static_cast<Uint8>(col.z);
	c.a = 255;
	
	//Load("Assets/Carlito-Regular.ttf", 52);

	SDL_Surface* surface = TTF_RenderText_Blended(mfont, s.c_str(), c);
	//SDL_Surface* surface = TTF_RenderText_Shaded(mfont, "MO", c, c);
	if (surface)
	{
		Texture* t = new Texture();
		t->CreateFromSurface(surface);
		SDL_FreeSurface(surface);
		return t;

	}
	return nullptr;
}