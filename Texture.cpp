#include "Texture.h"

#include "SOIL/SOIL.h"
#include <GL/glew.h>
#include "SDL/SDL.h"

Texture::Texture()
	:mtexid(0)
	, mwidth(0)
	, mheight(0)
{

}

bool Texture::Load(const std::string& fileName)
{
	int channels = 0;

	unsigned char* image = SOIL_load_image(fileName.c_str(),
		&mwidth, &mheight, &channels, SOIL_LOAD_AUTO);

	if (image == nullptr)
	{
		SDL_Log("SOIL failed to load image %s: %s", fileName.c_str(), SOIL_last_result());
		return false;
	}

	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	glGenTextures(1, &mtexid);
	glBindTexture(GL_TEXTURE_2D, mtexid);

	glTexImage2D(GL_TEXTURE_2D, 0, format, mwidth, mheight, 0, format,
		GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mtexid);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mtexid);
}

void Texture::CreateFromSurface(SDL_Surface* s)
{
	mwidth = s->w;
	mheight = s->h;


	glGenTextures(1, &mtexid);
	glBindTexture(GL_TEXTURE_2D, mtexid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mwidth, mheight, 0, GL_BGRA,
	GL_UNSIGNED_BYTE, s->pixels);

	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}