#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "GL/glew.h"
#include "Vertexarray.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"


#include "Pacman.h"

MeshComp::MeshComp(class Actor* a):Component{a},mMesh{nullptr},misvisible{true}
{

	mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}
MeshComp::~MeshComp()
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
	
}

void MeshComp::Draw(class Shader* s)
{
	if (mMesh)
	{
		
		s->SetMatrixUniform("uworldtrans", mOwner->GetWorldTrans());
	

		Texture* t = mMesh->GetTexture();
		if (t)
		{
			t->SetActive();
		}

		VertexArray* va = mMesh->GetVertexArray();
		va->SetActive();


		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}
	
}
