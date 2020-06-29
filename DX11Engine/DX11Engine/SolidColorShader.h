#pragma once
#ifndef SOLIDCOLORSHADERCLASS
#define SOLIDCOLORSHDERCLASS

#include "Shader.h"

class SolidColorShader : public Shader
{
private:

	////////////
	//Typedefs//
	////////////

	struct MVP
	{
		D3DXMATRIX model;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	}mvp;

	D3DXVECTOR4 color;

	ID3D11Buffer* b_MVP, * b_color;

public:

	bool Initialize(ID3D11Device*,ID3D11DeviceContext*);

	void SetParametersAndRender(ID3D11DeviceContext* context, Model*model, D3DXMATRIX m, D3DXMATRIX v, D3DXMATRIX p, D3DXVECTOR4 color);

};

#endif