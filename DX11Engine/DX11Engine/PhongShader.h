#pragma once
#ifndef PHONGSHADERCLASS
#define PHONGSHADERCLASS

#include "Shader.h"
class PhongShader :
    public Shader
{
private:

	struct MVP
	{
		D3DXMATRIX model;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	}mvp;

	ID3D11Buffer* b_MVP;

	ID3D11SamplerState* s_sampler;

public:

	bool initialize(ID3D11Device*, ID3D11DeviceContext*);

	void SetParametersAndRender(ID3D11DeviceContext* context, Model* model, const D3DXMATRIX& m, const D3DXMATRIX& v, const D3DXMATRIX& p, Texture* tex);
};

#endif