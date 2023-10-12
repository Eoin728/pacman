#pragma once

class VertexArray
{
public:
	VertexArray(const float* verts, unsigned int numVerts,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
	unsigned int GetNumIndices() const { return mnumindices; }
	unsigned int GetNumVerts() const { return mnumverts; }
private:
	
	unsigned int mnumverts;

	unsigned int mnumindices;

	unsigned int mVertexBuffer;

	unsigned int mIndexBuffer;

	unsigned int mVertexArray;
};