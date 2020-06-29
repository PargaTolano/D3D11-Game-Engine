#include "Plane.h"

bool Plane::initialize(ID3D11Device* device) {

	u_v_count = 4;
	pVert = new (std::nothrow) Vertex::PosNrmTgBnTex[u_v_count];
	
	if (!pVert)
	{
		MessageBox(0, L"No hay suficiente memoria para crear vertices del plano", L"Error", MB_OK);
		return false;
	}

	//Left Top
	pVert[0] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, 0.5, 0),	//Pos
		D3DXVECTOR3(0 , 0, 1),		//Nrm
		D3DXVECTOR3(0,0,0),			//Tg
		D3DXVECTOR3(0,0,0),			//Bn
		D3DXVECTOR2(0,0)			//Tex
	};

	//D3DXVec3Normalize(&pVert[0].nrm, &pVert[0].pos);

	//Right Top
	pVert[1] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(0.5, 0.5, 0),	//Pos
		D3DXVECTOR3(0 , 0, 1),		//Nrm
		D3DXVECTOR3(1,0,0),			//Tg
		D3DXVECTOR3(0,1,0),			//Bn
		D3DXVECTOR2(1,0)			//Tex
	};

	//D3DXVec3Normalize(&pVert[1].nrm, &pVert[1].pos);

	//Left Bottom
	pVert[2] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, -0.5, 0),	//Pos
		D3DXVECTOR3(0 , 0, 1),		//Nrm
		D3DXVECTOR3(1,0,0),			//Tg
		D3DXVECTOR3(0,1,0),			//Bn
		D3DXVECTOR2(0,1)			//Tex
	};

	//D3DXVec3Normalize(&pVert[2].nrm, &pVert[2].pos);

	//Right Bottom
	pVert[3] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3( 0.5, -0.5, 0),	//Pos
		D3DXVECTOR3(0 , 0, 1),		//Nrm
		D3DXVECTOR3(1,0,0),			//Tg
		D3DXVECTOR3(0,1,0),			//Bn
		D3DXVECTOR2(1,1)			//Tex
	};

	//D3DXVec3Normalize(&pVert[3].nrm, &pVert[3].pos);

	u_i_count =  6;
	pInd = new (std::nothrow) uint[u_i_count];

	if (!pInd)
	{
		MessageBox(0, L"No hay suficiente memoria para crear indices del plano", L"Error", MB_OK);
		return false;
	}

	pInd[0] = 0;
	pInd[1] = 1;
	pInd[2] = 2;

	pInd[3] = 2;
	pInd[4] = 1;
	pInd[5] = 3;

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(Vertex::PosNrmTgBnTex) * u_v_count;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = pVert;

	HRESULT res = device->CreateBuffer(&vertexDesc, &resourceData, &b_vertex);

	if (FAILED(res))
	{
		MessageBox(0, L"Error al crear vertex buffer", L"Error", MB_OK);
		return false;
	}

	D3D11_BUFFER_DESC indexDesc;
	ZeroMemory(&indexDesc, sizeof(indexDesc));
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.ByteWidth = sizeof(uint) * u_i_count;
	indexDesc.CPUAccessFlags = 0;

	resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = pInd;

	res = device->CreateBuffer(&indexDesc, &resourceData, &b_index);

	if (FAILED(res))
	{
		MessageBox(0, L"Error al crear index buffer", L"Error", MB_OK);
		return false;
	}

	return true;
}