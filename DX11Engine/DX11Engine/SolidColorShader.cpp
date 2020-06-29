#include "SolidColorShader.h"

bool SolidColorShader::Initialize(ID3D11Device*device , ID3D11DeviceContext*context)
{
	D3D11_BUFFER_DESC mvp_desc;
	ZeroMemory(&mvp_desc, sizeof(mvp_desc));

	mvp_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mvp_desc.ByteWidth = sizeof(MVP);
	mvp_desc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT res = device->CreateBuffer(&mvp_desc,0, &b_MVP);

	if (FAILED(res))
	{
		return false;
	}

	D3D11_BUFFER_DESC color_desc;
	ZeroMemory(&color_desc, sizeof(color_desc));

	color_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	color_desc.ByteWidth = sizeof(D3DXVECTOR4);
	color_desc.Usage = D3D11_USAGE_DEFAULT;

	res = device->CreateBuffer(&color_desc, 0, &b_color);

	if (FAILED(res))
	{
		return false;
	}

	return true;
}

void SolidColorShader::SetParametersAndRender(ID3D11DeviceContext*context,Model*model, D3DXMATRIX m, D3DXMATRIX v, D3DXMATRIX p, D3DXVECTOR4 color)
{
	mvp.model		= m;
	mvp.view		= v;
	mvp.projection  = p;

	unsigned int stride = sizeof(Vertex::PosNrmTgBnTex);
	unsigned int offset = 0;

	context->IASetInputLayout(inputLayout);

	context->IASetVertexBuffers(0, 1, &model->getVertexBuffer(), &stride, &offset);
	context->IASetIndexBuffer(model->getIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->VSSetShader(VS, 0, 0);
	context->PSSetShader(PS, 0, 0);

	context->UpdateSubresource(b_MVP, 0, 0, &mvp, 0, 0);
	context->UpdateSubresource(b_color, 0, 0, &color, 0, 0);

	context->VSSetConstantBuffers(0, 1, &b_MVP);
	context->VSSetConstantBuffers(1, 1, &b_color);

	context->DrawIndexed(model->getIndexCount(), 0, 0);
}