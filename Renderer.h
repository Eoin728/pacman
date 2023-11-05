#pragma once
#include "Math.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "SDL/SDL.h"

struct Directionallight
{

};

class Renderer
{
public:
	Renderer(class Game*);

	void SetView(const Matrix4& view) { mview = view; }
	void Draw();

	bool Initialize(int screenheight,int screenwidth);

	class Mesh* GetMesh(const std::string& s);
	class Texture* GetTexture(const std::string& s);

	void AddMeshComp(class MeshComp*);
	void RemoveMeshComp(class MeshComp*);

	void Unload();
	void Shutdown();

	void AddWall(class Wall*);
	void RemoveWall(class Wall*);


	void SetWallColour(const Vector3& v) { mwallcolour = v;  }
	
	

	Vector3 GetTrueCentreScreenPos(const Vector3& a = Vector3::Zero);
	const int GetScreenWidth() const { return mScreenWidth; }
	const int GetScreenHeight() const { return mScreenHeight; }
	
	std::vector<class Wall*>  GetWalls() { return mwalls; }
private:
	bool LoadShaders();
	void makevertexarrays();

	Matrix4 mview;
	Matrix4 mproj;

	class Shader* mMeshshader;
	std::vector<class MeshComp*> mMeshComps;
	std::unordered_map<std::string, class Mesh*> mMeshes;

	std::unordered_map<std::string, class Texture*> mTextures;

	int mScreenHeight;
	int mScreenWidth;

	SDL_Window* mwindow;
	SDL_GLContext mcontext;

	class Game* mgame;


	//walls
	std::vector<class Wall*> mwalls;
	class Shader* mWallShader;
	Vector3 mwallcolour;
	class VertexArray* mwallvertex;
	std::vector<class Tile*> mtiles;

	class Shader* mSpriteShader;
	class VertexArray* mspriteverts;

	//lighting
	Vector3 mambient;
	void LightingTime(class Shader* s);
	Vector3 mlightdir;
	Vector3 mdiffusecolour;
	Vector3 mSpeccolour;
	float mspecpower;
};