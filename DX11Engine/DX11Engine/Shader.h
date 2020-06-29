#pragma 
#ifndef SHADER_BASE
#define SHADER_BASE

#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <d3dx10math.h>

#include <string>
#include "Model.h"
#include "Texture.h"

class Shader
{
private:

	HRESULT CompileD3DShader(WCHAR* filePath, char* entry, char* shaderModel, ID3DBlob** buffer);

protected:

	ID3D11VertexShader* VS;
	ID3D11HullShader* HS;
	ID3D11DomainShader* DS;
	ID3D11PixelShader* PS;

	ID3D11InputLayout* inputLayout;

public:

	Shader();

	bool InitShaders(
		ID3D11Device*		 device,
		std::wstring vs, 
		std::wstring ps,
		std::wstring hs     = L"none",
		std::wstring ds     = L"none",
		std::string  vsEntry= "vert",
		std::string  psEntry= "pix", 
		std::string  hsEntry= "hull", 
		std::string  dsEntry= "dom" );

};

#endif