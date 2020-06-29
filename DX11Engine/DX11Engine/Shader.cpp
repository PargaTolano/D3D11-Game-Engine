#include "Shader.h"

Shader::Shader():VS(0),PS(0),HS(0),DS(0){}

bool Shader::InitShaders(
	ID3D11Device* device,
	std::wstring vs,
	std::wstring ps,
	std::wstring hs,
	std::wstring ds,
	std::string  vsEntry,
	std::string  psEntry,
	std::string  hsEntry,
	std::string  dsEntry)
{
	ID3DBlob *vsbuff, *psbuff;

	HRESULT res = CompileD3DShader((WCHAR*)vs.c_str(), (char*)vsEntry.c_str(), (char*)"vs_5_0", &vsbuff);

	if (FAILED(res))	return false;

	device->CreateVertexShader(vsbuff->GetBufferPointer(), vsbuff->GetBufferSize(), 0, &VS);

	if (FAILED(res))	return false;

	res = CompileD3DShader((WCHAR*)ps.c_str(), (char*)psEntry.c_str(), (char*)"ps_5_0", &psbuff);

	if (FAILED(res))	return false;

	device->CreatePixelShader(psbuff->GetBufferPointer(), psbuff->GetBufferSize(), 0, &PS);

	if (FAILED(res))	return false;

	psbuff->Release();

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "BINORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

	};

	unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);

	res = device->CreateInputLayout(solidColorLayout, totalLayoutElements,
		vsbuff->GetBufferPointer(), vsbuff->GetBufferSize(), &inputLayout);

	vsbuff->Release();

	if (hs.compare(L"none") && ds.compare(L"none"))
	{
		ID3DBlob *hsbuff, *dsbuff;

		res = CompileD3DShader((WCHAR*)hs.c_str(), (char*)hsEntry.c_str(), (char*)"hs_5_0", &hsbuff);

		if (FAILED(res))	return false;

		device->CreateHullShader(hsbuff->GetBufferPointer(), hsbuff->GetBufferSize(), 0, &HS);

		if (FAILED(res))	return false;

		res = CompileD3DShader((WCHAR*)ds.c_str(), (char*)dsEntry.c_str(), (char*)"ds_5_0", &dsbuff);

		if (FAILED(res))	return false;

		device->CreateDomainShader(dsbuff->GetBufferPointer(), dsbuff->GetBufferSize(), 0, &DS);

		if (FAILED(res))	return false;
	}

	return true;
}

HRESULT Shader::CompileD3DShader(WCHAR* filePath, char* entry, char* shaderModel, ID3DBlob** buffer)
{
	//forma de compilar el shader
	DWORD shaderFlags = D3DCOMPILE_DEBUG;

	ID3DBlob* errorBuffer = 0;
	HRESULT result;

	result = D3DX11CompileFromFile(filePath, 0, 0, entry, shaderModel, shaderFlags,
		0, 0, buffer, &errorBuffer, 0);
	if (FAILED(result))
	{
		if (errorBuffer != 0)
		{
			OutputDebugStringA((char*)errorBuffer->GetBufferPointer());

			errorBuffer->Release();
		}
		return result;
	}

	if (errorBuffer != 0)
		errorBuffer->Release();

	return result;
}