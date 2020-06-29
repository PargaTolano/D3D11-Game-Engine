#pragma once
#ifndef TEXTURECLASS
#define TEXTURECLASS

#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <d3dx10math.h>

#include <wrl.h>
#include <string>
#include "AppTypes.h"

class Texture
{
private:

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;

public:

	Texture() = default;

	~Texture();

	bool initialize(ID3D11Device*, std::wstring);

	ID3D11ShaderResourceView** GetShaderResourceView();
};

#endif