#include "Renderer.h"
#include "Texture.h"
#include "GL/glew.h"
#include "Shader.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Wall.h"
#include "Vertexarray.h"
#include "Tile.h"
#include "Game.h"
#include "Ui.h"
#include "Ghost.h"


//ambient between 0 and 1 i think maybe doybkle check idk 
Renderer::Renderer(class Game* v) :mgame{ v }, mwallcolour(Vector3::UnitZ),mambient{Vector3(0.0,0.1,0.2)},mlightdir(Vector3(0,0.5,0.65)),mspecpower(0),mSpeccolour(Vector3(0.9,0.9,0.0)),mdiffusecolour{Vector3(0.82,0.82,0.82)}
{

}

#include "Startscreen.h"
void Renderer::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//enable depth buffering 

	glEnable(GL_DEPTH_TEST);
	

	mMeshshader->SetActive();
	mMeshshader->SetMatrixUniform("uviewproj", mview * mproj);
	LightingTime(mMeshshader);
	for (auto m : mMeshComps)
	{
	
		if (m->IsVisible())
		{
			m->Draw(mMeshshader);
		}
	}
	//draw walls
	mwallvertex->SetActive();
	mWallShader->SetActive();
	//mWallShader->SetVectorUniform("ucolour", mwallcolour);
	mWallShader->SetMatrixUniform("uviewproj", mview * mproj);

	mwallcolour = Vector3::UnitZ;
	for (auto ghost : mgame->GetGhosts())
	{
		if (ghost->IsHunting())
		{
			mwallcolour = Vector3::UnitX; break;
		}
	}
	
	mWallShader->SetVectorUniform("ucolour", mwallcolour);
for (auto w : mwalls)
	{
	mWallShader->SetMatrixUniform("uworldtrans", w->GetWorld());
	
	glDrawElements(GL_TRIANGLES, mwallvertex->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
			
	}
glDisable(GL_DEPTH_TEST);
// Enable alpha blending on the color buffer
glEnable(GL_BLEND);
glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
	//draw ui
mSpriteShader->SetActive();
mspriteverts->SetActive();
float mat[4][4] =
{
	{2.0f / mScreenWidth,0.0f,0.0f,0.0f},
	{0.0f,2.0f / mScreenHeight,0.0f,0.0f},
	{0.0f,0.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f,1.0f}
};


mSpriteShader->SetMatrixUniform("uviewproj", Matrix4(mat));
glEnable(GL_TEXTURE_2D); glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
for (auto y : mgame->GetUis())
{

	y->Draw(mSpriteShader);
}



	SDL_GL_SwapWindow(mwindow);

}

bool Renderer::Initialize(int screenwidth, int screenheight)
{
	
	mScreenHeight = screenheight;
	mScreenWidth = screenwidth;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mwindow = SDL_CreateWindow("Mazetime", 100, 100,
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);
	if (!mwindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}



	// Create an OpenGL context
	mcontext = SDL_GL_CreateContext(mwindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	glGetError();
	
	// Make sure we can create/compile shaders
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	
	makevertexarrays();

	
	return true;
}

 Mesh* Renderer::GetMesh(const std::string& s)
{
	auto iter = mMeshes.find(s);
	if (iter != mMeshes.end())
		return iter->second;

	Mesh* m = new Mesh();
	
	if (m->Load(s,this))
	{
		mMeshes.emplace(s, m); 
		return m;
			
	}
	delete m;
	return  nullptr;
}


void  Renderer::AddMeshComp(class MeshComp*m)
{
	mMeshComps.emplace_back(m);
}
void  Renderer::RemoveMeshComp(class MeshComp*m)
{
	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), m);

	if (iter != mMeshComps.end())
	{
		std::iter_swap(mMeshComps.end() - 1, iter);
		mMeshComps.pop_back();
	}
}

bool Renderer::LoadShaders()
{
	mMeshshader = new Shader();

	if (!mMeshshader->Load("Meshshader.vert", "meshshader.frag"))
	{
		return false;
	}
  mview = Matrix4::CreateView(Vector3(10, 200, 0), Vector3(11, 200, 0), Vector3::UnitZ);
	mview = Matrix4::CreateView(Vector3(1,0,4000), Vector3(0,0,3900), Vector3::UnitZ);
	mproj = Matrix4::CreateProj(10.0f, 10000.0f,Math::ToRadians(70.0f), mScreenHeight, mScreenWidth);
	



	mMeshshader->SetMatrixUniform("uviewproj", mview * mproj);
	
	
	//walls
	mWallShader = new Shader();
	
	if (!mWallShader->Load("Wallshader.vert", "Wallshader.frag"))
	{
		return false;
	}
	mWallShader->SetMatrixUniform("uviewproj", mview * mproj);
	mWallShader->SetVectorUniform("ucolour", mwallcolour);


	//sprites
	
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("SpriteShader.vert", "SpriteShader.frag"))
	{
		return false;
	}

	float mat[4][4] =
	{
		{2.0f / mScreenWidth,0.0f,0.0f,0.0f},
		{0.0f,2.0f / mScreenHeight,0.0f,0.0f},
		{0.0f,0.0f,1.0f,0.0f},
		{0.0f,0.0f,1.0f,1.0f}
	};


	mSpriteShader->SetMatrixUniform("uviewproj",Matrix4(mat) );






	return true;
}


 Texture* Renderer::GetTexture(const std::string& s)
{
	 auto iter = mTextures.find(s);
	 if (iter != mTextures.end())
		 return iter->second;

	 Texture* t = new Texture();
	 if (t->Load(s))
	 {
		 mTextures.emplace(s, t);
		 return t;
	 }
	 delete t;
	 return nullptr;
}

 void Renderer::Unload()
 {
	 
	 for (auto i : mTextures)
	 {
		 i.second->Unload();
		 delete i.second;
	 }
	 mTextures.clear();

	 
	 for (auto i : mMeshes)
	 {
		 i.second->Unload();
		 delete i.second;
	 }
	 mMeshes.clear();

 }
 void Renderer::Shutdown()
 {
	 mMeshshader->Unload();
	 delete mMeshshader;

	  delete mWallShader;
	  delete mSpriteShader;
	  delete mspriteverts;
	
	 SDL_GL_DeleteContext(mcontext);
	 SDL_DestroyWindow(mwindow);


 }

 void Renderer::AddWall(class Wall*x)
 {
	
	 mwalls.emplace_back(x);
 }
 void Renderer::RemoveWall(class Wall*x)
 {
	 auto iter = std::find(mwalls.begin(), mwalls.end(), x);
	 mwalls.erase(iter);
	// std::iter_swap(mwalls.end() - 1, iter);
	// mwalls.pop_back();
 }

 void Renderer::makevertexarrays()
 {
	 float verts[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f,
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f,
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f,
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f
	 };

	 unsigned int i[] = {
		 0, 1, 2,
		 2, 3, 0
	 };

	 mspriteverts = new VertexArray(verts, 4, i, 6);

	 mwallvertex = GetMesh("Assets/Wall.txt")->GetVertexArray();



 }

 void Renderer::AddTile(class Tile* j)
 {


	 mtiles.emplace_back(j);
 }

 Vector3 Renderer::GetTrueCentreScreenPos(const Vector3& a)
 {
	 Vector3 g = a;
	 g.x /= (mScreenWidth) * 0.5f;
	 g.y /= (mScreenHeight) * 0.5f;
	 Matrix4 vi = mview * mproj;
	
	 
	 vi.Invert();

	 Vector3 b = Vector3::Transform(g, vi);

	 return b;
 }

 void Renderer::LightingTime(class Shader* s)
 {
	 Matrix4 i = mview;
	 i.Invert();
	 Vector3 b;
	 b.x = i.mat[3][0];
	 b.y = i.mat[3][1];
	 b.z = i.mat[3][2];
	 s->SetVectorUniform("ucamerapos", b);

	 s->SetVectorUniform("uambient", mambient);
	 s->SetVectorUniform("ulightdir", mlightdir);
	 s->SetVectorUniform("udiffusecolour", mdiffusecolour);
	 s->SetVectorUniform("uspeccolour", mSpeccolour);
	 s->SetFloatUniform("uspecpower", mspecpower);


 }