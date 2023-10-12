#pragma once

#include "Math.h"
#include <string>
#include <vector>
#include <functional>


//perhaps do not use vectors for pos and stuff
// or maybe make a 2d vector class idk
//the name for this is terrible
class Interact
{
public:
	
	Interact(class Ui* u,const Vector3& pos,const Vector3&, class Texture*,std::function<void()>);
	~Interact();
	friend class Ui;
	
	bool ContainsPoint(const Vector3& a);

private:
	 Vector3 mpos;
	 std::string mtext;
	 Vector3 mdim;
	 bool mhighlighted;
	 class Texture* mtexture;
	 std::function<void()> mfunc;
};



class Ui
{
public:
	enum State
	{
		Dead,
		Alive
	};
	Ui(class Game*);
	virtual ~Ui();

	virtual void Draw(class Shader*);
	virtual void ProcessInput(const class Input& state);
	virtual void Update();

	void AddInteract(class Interact* i);

	State GetState() { return mstate; }
	void SetState(State x) { mstate = x; }

	void Drawhelper(class Texture* t,class Vector3& a, class Shader* s);
protected:
	class Game* mgame;
private:
	std::vector<Interact*> minteracts;
protected:
	class Texture* mhighlighttex;
	class Texture* mnonhighlighttex;

	class Text* mtexty;
	State mstate;

	//colours
	const Vector3 mmenucolour = Vector3(255, 140, 0.0f);

	int minteractheight;
	int minteractwidth;
};