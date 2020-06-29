#pragma once
#ifndef TEXTURERENDERINGCLASS
#define TEXTURERENDERINGCLASS

#include "Texture.h"

class TextureRendering
{
private:

	Texture t;

public:

	TextureRendering();

	bool initialize(ID3D11Device*, int, int);

	void shutdown();

	void SetRenderTarget(ID3D11DeviceContext*, ID3D11DepthStencilView*);
	void ClearRenderTarget(ID3D11DeviceContext*, ID3D11DepthStencilView*, float, float, float, float);
	
	ID3D11ShaderResourceView* GetShaderResourceView();

private:

	ID3D11Texture2D*			m_renderTargetTexture;
	ID3D11RenderTargetView*		m_renderTargetView;
	ID3D11ShaderResourceView*	m_shaderResourceView;
};

#endif