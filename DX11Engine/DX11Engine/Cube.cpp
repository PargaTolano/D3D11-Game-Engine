#include "Cube.h"

bool Cube::initialize(ID3D11Device*device) {

	u_v_count = 14;
	pVert = new Vertex::PosNrmTgBnTex[u_v_count];

	//Left back Top
	pVert[0] = Vertex::PosNrmTgBnTex
	{ 
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.25, 0)  //Tex
	};
	D3DXVec3Normalize(&pVert[0].nrm, &pVert[0].pos);
	//Right back Top
	pVert[1] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(0.5, 0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.5, 0)  //Tex
	};
	D3DXVec3Normalize(&pVert[1].nrm, &pVert[1].pos);
	//Left back Top 2
	pVert[2] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(   0,   0,   0), //Tg
		D3DXVECTOR3(   0,   0,   0), //Bn
		D3DXVECTOR2(   0, 1.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[2].nrm, &pVert[2].pos);
	//Left Front Top
	pVert[3] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, 0.5, -0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.25, 1.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[3].nrm, &pVert[3].pos);
	//Right Front Top
	pVert[4] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3( 0.5, 0.5, -0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.5, 1.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[4].nrm, &pVert[4].pos);
	//Right Back Top
	pVert[5] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(0.5, 0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.75, 1.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[5].nrm, &pVert[5].pos);
	//Left Back Top 3
	pVert[6] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(1, 1.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[6].nrm, &pVert[6].pos);
	//Left Back Bottom
	pVert[7] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, -0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0, 2.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[7].nrm, &pVert[7].pos);
	//Right Front Bottom
	pVert[8] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, -0.5, -0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.25, 2.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[8].nrm, &pVert[8].pos);
	//Left Front Bottom
	pVert[9] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(0.5, -0.5, -0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.5 , 2.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[9].nrm, &pVert[9].pos);
	//Right Back Bottom
	pVert[10] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(0.5, -0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.75, 2.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[10].nrm, &pVert[10].pos);
	//Left Back Bottom
	pVert[11] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, -0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(1, 2.0 / 3.0)  //Tex
	};
	D3DXVec3Normalize(&pVert[11].nrm, &pVert[11].pos);
	//Left Back Bottom
	pVert[12] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(-0.5, -0.5, 0.5), //Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5), //Nrm
		D3DXVECTOR3(0,0,0), //Tg
		D3DXVECTOR3(0,0,0), //Bn
		D3DXVECTOR2(0.25, 1)  //Tex
	};
	D3DXVec3Normalize(&pVert[12].nrm, &pVert[12].pos);
	//Left Back Bottom
	pVert[13] = Vertex::PosNrmTgBnTex
	{
		D3DXVECTOR3(0.5, -0.5, 0.5),	//Pos
		D3DXVECTOR3(-0.5, 0.5, 0.5),	//Nrm
		D3DXVECTOR3(0,0,0),				//Tg
		D3DXVECTOR3(0,0,0),				//Bn
		D3DXVECTOR2(0.5, 1)			//Tex
	};
	D3DXVec3Normalize(&pVert[13].nrm, &pVert[13].pos);

	u_i_count = 36;
	pInd = new uint[(int)u_i_count];

	pInd[0] = 0;
	pInd[1] = 1;
	pInd[2] = 3;	
	pInd[3] = 3;
	pInd[4] = 1;
	pInd[5] = 4;

	pInd[6]  = 2;
	pInd[7]  = 3;
	pInd[8]  = 7;
	pInd[9]  = 7;
	pInd[10] = 3;
	pInd[11] = 8;

	pInd[12] = 3;
	pInd[13] = 4;
	pInd[14] = 8;
	pInd[15] = 8;
	pInd[16] = 4;
	pInd[17] = 9;

	pInd[18] = 4;
	pInd[19] = 5;
	pInd[20] = 9;
	pInd[21] = 9;
	pInd[22] = 5;
	pInd[23] = 10;

	pInd[24] = 5;
	pInd[25] = 6;
	pInd[26] = 10;
	pInd[27] = 10;
	pInd[28] = 6;
	pInd[29] = 11;

	pInd[30] = 8;
	pInd[31] = 9;
	pInd[32] = 12;
	pInd[33] = 12;
	pInd[34] = 9;
	pInd[35] = 13;

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