#include "Actor.h"

class Pacman:public Actor
{
public:
	Pacman(class Game*);

	void ActorUpdate(float) override;

	void ProcessInput(const class Input& state) override;
	void ResetPelletsAndRocks();
	class SphereComp* GetSphere(){ return msphere; }
	int GetPelletCount() const { return mpelletcount; }
	void AddPellet();
	int GetRockCount() const { return mrockcount; }
	void AddRock();
	friend class Hud;


	class Tile* GetCurrTile() override;
private:
	bool wallhit();
	void SwitchCam();
	void CheckGhostColl();

	
	class Paccam* mcam;
	class Movement* mmovie;
	class SphereComp* msphere;
	float mspeed;

	class MeshComp* mpacmodel;
	
	int mpelletcount;
	int mrockcount;

	class Actor* mhands;
	class MeshComp* mhandmodel;

	int mwinningpelletamount;

	float mradius;
};