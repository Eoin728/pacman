#pragma once
#include <vector>

class Game
{
public:
	enum State
	{
		Paused,
		NotPaused,
		Dead
	};


	Game();

	bool Initialize();
	void Runloop();

	void AddActor(class Actor*);
	void RemoveActor(class Actor*);

	
	void AddGhost(class Ghost*);
	void RemoveGhost(class Ghost*);

	void AddUi(class Ui*);
	void SetState(State a); 


	void Shutdown();
	void UnloadData();

	class Renderer* GetRenderer() { return mRenderer; }

	class Maze* GetMaze() { return mMaze; }
	class Pacman* GetPac() { return mpac; }
	const std::vector<class Ui*>& GetUis() const { return mui; }

	
	std::vector<class Ghost*>& GetGhosts() { return mGhosts; }

	class Hud* GetHud() { return mhud; }
private:
	class Renderer* mRenderer;
	
	void processinput();
	void update();
	void genoutput();

	void LoadData();

	class Maze* mMaze;

	std::vector<class Actor*> mcurractors;
	std::vector<class Actor*> mpendactors;

	float mticks;
	bool misrunning;
	bool misupdatingactors;

	class Pacman* mpac;

	std::vector<class Ghost*> mGhosts;

	class Input* minput;

	State mstate;
	class Hud* mhud;
	//ui stuff
	std::vector<class Ui*> mui;



};