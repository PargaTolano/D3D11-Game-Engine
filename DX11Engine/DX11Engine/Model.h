#pragma once
#ifndef MODELBASECLASS
#define MODELBASECLASS

#include <d3d11.h>
#include <d3dx11.h>
#include <new>

#include "Vertex.h"
#include "AppTypes.h"

class Model
{ 
protected:

	ID3D11Buffer*				b_vertex;
	ID3D11Buffer*				b_index;

	Vertex::PosNrmTgBnTex*		pVert;
	uint*						pInd;

	uint					    u_v_count;
	uint						u_i_count;

public:

	Model();

	virtual bool initialize(ID3D11Device*) = 0;
	
	ID3D11Buffer*& getVertexBuffer();

	ID3D11Buffer*& getIndexBuffer();

	uint getVertexCount();

	uint getIndexCount();
};

#endif