#include "Texture.h"

Texture::~Texture()
{
	if(srv)
		srv->Release();
	srv.Reset();
}

bool Texture::initialize(ID3D11Device* device, std::wstring path)
{
	HRESULT res = D3DX11CreateShaderResourceViewFromFile(device, path.c_str(), 0, 0, &srv, 0);

	if (FAILED(res))
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView** Texture::GetShaderResourceView()
{
	return srv.GetAddressOf();
}