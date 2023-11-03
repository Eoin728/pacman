#include "Text.h"
#include "Texture.h"
Text::Text():mfont{nullptr}
{

}
Text::~Text()
{

}

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

//this 
void Text::Unload()
{
	TTF_CloseFont(mfont);
}


class Texture* Text::GetText(const std::string& s, const Vector3& col)
{
	SDL_Color c;
	c.r = static_cast<Uint8>(col.x);
	c.g = static_cast<Uint8>(col.y);
	c.b = static_cast<Uint8>(col.z);
	c.a = 255;
	
	

	SDL_Surface* surface = TTF_RenderText_Blended(mfont, s.c_str(), c);
	
	if (surface)
	{
		Texture* t = new Texture();
		t->CreateFromSurface(surface);
		SDL_FreeSurface(surface);
		return t;

	}
	return nullptr;
}