#pragma once
#include <string>
#include "SDL/SDL_ttf.h"
#include "Math.h"

class Text
{
public:
	Text();
	~Text();

	bool Load(const std::string& s,int);
	void Unload();

	class Texture* GetText(const std::string& s, const Vector3& col);

private:
	TTF_Font *mfont;


};