#include "Water.h"

bool Water::LoadMesh(uint side_lenght, uint divisions, uint uvTiles)
{
	float xyStep = side_lenght / (divisions - 1);
	float uvStep = divisions / (uvTiles - 1);

	u_v_count = divisions * divisions;
	pVert = new (std::nothrow) Vertex::PosNrmTgBnTex[u_v_count];

	if (!pVert)
		return false;

	for (uint i = 0; i < divisions; ++i)
	{
		for (uint j = 0; j < divisions; ++j)
		{
			pVert[i * divisions + j].pos = D3DXVECTOR3( xyStep*j - ((float)side_lenght/2.0f), 0, xyStep * i - ((float)side_lenght / 2.0f));
			pVert[i * divisions + j].tex = D3DXVECTOR2( uvStep * j, uvStep * i);

			pVert[i * divisions + j].nrm = D3DXVECTOR3(0, 0, 0);
			pVert[i * divisions + j].tg  = D3DXVECTOR3(0, 0, 0);
			pVert[i * divisions + j].bn  = D3DXVECTOR3(0, 0, 0);
		}
	}

	return true;
}

bool Water::LoadIndices(uint divisions)
{
	u_i_count = (divisions - 1) * (divisions - 1) * 6;
	unsigned int counter = 0;
	for (int i = 0; i < divisions - 1; ++i)
	{
		for (int j = 0; j < divisions - 1; ++j)
		{
			int lowerLeft = i * divisions + j;
			int lowerRight = i * divisions + (j + 1);
			int topLeft = (i + 1) * divisions + j;
			int topRight = (i + 1) * divisions + (j + 1);

			pInd[counter++] = lowerLeft;
			pInd[counter++] = topLeft;
			pInd[counter++] = lowerRight;

			pInd[counter++] = lowerRight;
			pInd[counter++] = topLeft;
			pInd[counter++] = topRight;
		}
	}
	return true;
}

Water::Water(uint side_lenght, uint divisions, uint uvTiles)
{
	LoadMesh(side_lenght, divisions, uvTiles);
	LoadIndices(divisions);
}

bool Water::initialize(ID3D11Device* device	)
{
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
	delete pVert;

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
	delete pInd;

	return true;
}
