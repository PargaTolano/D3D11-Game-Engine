#pragma once
#ifndef VERTEXSTRUCTURES
#define VERTEXSTRUCTURES

#include <D3DX10math.h>

namespace Vertex
{
	struct PosNrmTex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nrm;
		D3DXVECTOR2 tex;
	};

	struct PosNrmTgBnTex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nrm;
		D3DXVECTOR3 tg;
		D3DXVECTOR3 bn;
		D3DXVECTOR2 tex;
	};
}

#endif