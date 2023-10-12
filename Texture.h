#pragma once
#include <string>
#include "SDL/SDL.h"
class Texture
{
public:
	Texture();


	bool Load(const std::string& fileName);
	void Unload();

	void SetActive();

	int GetWidth() const { return mwidth; }
	int GetHeight() const { return mheight; }
	void CreateFromSurface(SDL_Surface * s);
private:


	unsigned int mtexid;
	int mwidth;
	int mheight;


};