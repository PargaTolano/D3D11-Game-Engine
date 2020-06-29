#include "TextureColorShader.h"

bool TextureColorShader::initialize(ID3D11Device* device, ID3D11DeviceContext* context)
{
	D3D11_BUFFER_DESC mvp_desc;
	ZeroMemory(&mvp_desc, sizeof(mvp_desc));

	mvp_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mvp_desc.ByteWidth = sizeof(MVP);
	mvp_desc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT res = device->CreateBuffer(&mvp_desc, 0, &b_MVP);

	if (FAILED(res))
	{
		return false;
	}

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory(&colorMapDesc, sizeof(colorMapDesc));
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	res = device->CreateSamplerState(&colorMapDesc, &s_sampler);

	if (FAILED(res))
	{
		return false;
	}

	return true;
}

void TextureColorShader::SetParametersAndRender(ID3D11DeviceContext* context, Model* model, const D3DXMATRIX& m, const D3DXMATRIX& v, const D3DXMATRIX& p, Texture* tex)
{
	mvp.model = m;
	mvp.view = v;
	mvp.projection = p;

	unsigned int stride = sizeof(Vertex::PosNrmTgBnTex);
	unsigned int offset = 0;

	context->IASetInputLayout(inputLayout);

	context->IASetVertexBuffers(0, 1, &model->getVertexBuffer(), &stride, &offset);
	context->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->VSSetShader(VS, 0, 0);
	context->PSSetShader(PS, 0, 0);

	context->PSSetShaderResources(0, 1, tex->GetShaderResourceView());

	context->UpdateSubresource(b_MVP, 0, 0, &mvp, 0, 0);

	context->VSSetConstantBuffers(0, 1, &b_MVP);

	context->DrawIndexed(model->getIndexCount(), 0, 0);
}