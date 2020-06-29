
#include "D3D.h"
#include "Window.h"

#include "Plane.h"
#include "Cube.h"

#include "SolidColorShader.h"
#include "TextureColorShader.h"
#include "LambertShader.h"
#include "PhongShader.h"
#include "ProjectiveTextureShader.h"

#include <iostream>
#include <assert.h>

Window* window;
D3D* d3d;
Texture* tex0,*tex1;

Plane* plane;
Cube*  cube;

SolidColorShader			*scShader;
TextureColorShader			*tcShader;
LambertShader				*lShader;
PhongShader					*pShader;
ProjectiveTextureShader		*ptShader;

D3DXMATRIX m_lookAt, m_lookAt2, m_Projection, m_Rot;
D3DXMATRIX textured, translation, lambert, translationl, phong, translationp, ptexturing, translationpt;
float degPSec = 0.0f;
float rotation = 0;

bool running;

void handle_inputs()
{
	if (Input::getInstance().getKeyRef('D'))
	{
		degPSec -= 5;
	}
	else if (Input::getInstance().getKeyRef('A'))
	{
		degPSec += 5;
	}

	if (Input::getInstance().getKeyRef(VK_ESCAPE))
	{
		running = false;
	}
}

void update(float dt) 
{
	rotation += degPSec * dt;
	rotation = rotation >= 360.0f ? rotation - 360.0f : rotation;

	const float offset = 1.41421;

	D3DXMatrixRotationY(&m_Rot, rotation * 0.0174533);
	D3DXMatrixLookAtLH(&m_lookAt, &D3DXVECTOR3(0, 0, -2), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixLookAtLH(&m_lookAt2, &D3DXVECTOR3(0, 1, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixPerspectiveFovLH(&m_Projection, 90 * 0.0174533, 800.0f / 600.0f, 0.01, 100);

	D3DXMatrixTranslation(&translation, offset, 0, 0);
	D3DXMatrixMultiplyTranspose(&textured, &m_Rot, &translation);

	D3DXMatrixTranslation(&translationl, -offset, 0, 0);
	D3DXMatrixMultiplyTranspose(&lambert, &m_Rot, &translationl);

	D3DXMatrixTranslation(&translationp, 0, offset, 0);
	D3DXMatrixMultiplyTranspose(&phong, &m_Rot, &translationp);

	D3DXMatrixTranslation(&translationpt, 0, -offset, 0);
	D3DXMatrixMultiplyTranspose(&ptexturing, &m_Rot, &translationpt);

	D3DXMatrixTranspose(&m_Rot, &m_Rot);
	D3DXMatrixTranspose(&m_lookAt, &m_lookAt);
	D3DXMatrixTranspose(&m_lookAt2, &m_lookAt2);
	D3DXMatrixTranspose(&m_Projection, &m_Projection);
}

void render() 
{
	//TODO renderizar a textura

	scShader->SetParametersAndRender(d3d->getContext(), cube, m_Rot, m_lookAt, m_Projection, D3DXVECTOR4(1, 1, 0, 1));

	tcShader->SetParametersAndRender(d3d->getContext(), cube, textured, m_lookAt, m_Projection, tex1);

	lShader ->SetParametersAndRender(d3d->getContext(), cube, lambert, m_lookAt, m_Projection, tex1);

	pShader ->SetParametersAndRender(d3d->getContext(), cube, phong, m_lookAt, m_Projection, tex1);

	ptShader->SetParametersAndRender(d3d->getContext(), cube, ptexturing, m_lookAt, m_lookAt, m_Projection, tex1);
}

int main() {

	window = new Window(800, 600, L"DirectX11 Engine!!");
	d3d = new D3D(window->GetWindow());

	tex0 = new Texture();
	assert(tex0->initialize(d3d->getDevice(), L"imagen.jpg"));

	tex1 = new Texture();
	assert(tex1->initialize(d3d->getDevice(), L"skybox.jpg"));

	plane = new Plane();
	assert(plane->initialize(d3d->getDevice()));

	cube = new Cube();
	assert(cube->initialize(d3d->getDevice()));

	scShader = new SolidColorShader();
	tcShader = new TextureColorShader();
	lShader	 = new LambertShader();
	pShader  = new PhongShader();
	ptShader = new ProjectiveTextureShader();

	bool res = scShader->InitShaders(d3d->getDevice(), L"solidcolor.fx", L"solidcolor.fx");
	assert(res);
	res = scShader->Initialize(d3d->getDevice(), d3d->getContext());
	assert(res);

	res = tcShader->InitShaders(d3d->getDevice(), L"simpletexture.fx", L"simpletexture.fx");
	assert(res);
	res = tcShader->initialize(d3d->getDevice(), d3d->getContext());
	assert(res);

	res = lShader->InitShaders(d3d->getDevice(), L"lambert.fx", L"lambert.fx");
	assert(res);
	res = lShader->initialize(d3d->getDevice(), d3d->getContext());
	assert(res);

	res = pShader->InitShaders(d3d->getDevice(), L"phong.fx", L"phong.fx");
	assert(res);
	res = pShader->initialize(d3d->getDevice(), d3d->getContext());
	assert(res);

	res = ptShader->InitShaders(d3d->getDevice(), L"projective-texturing.fx", L"projective-texturing.fx");
	assert(res);
	res = ptShader->initialize(d3d->getDevice(), d3d->getContext());
	assert(res);

	window->Show();
	window->SetInputCallback	(handle_inputs);
	window->SetUpdateCallback	(update);
	window->SetRenderCallback	(render);
	window->Run(d3d);

	delete scShader;
	delete tcShader;
	delete lShader;
	delete pShader;
	delete cube;
	delete plane;
	delete tex0;
	delete d3d;
	delete window;

	return 0;
}