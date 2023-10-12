#pragma once
#include <string>
#include <vector>
#include "CollisionTime.h"
class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& fileName, class Renderer* renderer);
	void Unload();
	
	class VertexArray* GetVertexArray() { return mVertexArray; }
	
	class Texture* GetTexture();
	
	float GetRadius() const { return mRadius; }
	
	const AABB GetAABB() { return maabb; }

private:
	
	 AABB maabb;
	
	class Texture * mTexture;
	
	class VertexArray* mVertexArray;
	
	float mRadius;
	

	
};