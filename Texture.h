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

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
	void CreateFromSurface(SDL_Surface * s);
private:

	//these cariable names are straight stolen klmao
	unsigned int mTextureID;
	int mWidth;
	int mHeight;


};