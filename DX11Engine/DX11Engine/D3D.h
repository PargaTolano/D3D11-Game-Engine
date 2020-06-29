#pragma once
#ifndef D3DCLASS
#define D3DCLASS

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10math.h>

#include "AppTypes.h"

class D3D
{
private:

	HWND			hWindow;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* device;
	ID3D11DeviceContext* context;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState* alphaBlendState, * commonBlendState;

	ID3D11RasterizerState* rs_cullback, * rs_wf_callback, * rs_nocull;

	bool initialize(HWND hWnd);

	void create_rasterizer_states();

	void create_fill_cullback();

	void create_wireframe_cullback();

	void create_fill_nocull();

	void cleanup();

public:

	D3D(HWND);

	~D3D();

	ID3D11Device*		 getDevice();

	ID3D11DeviceContext* getContext();

	void StartScene();

	void EndScene();
};

#endif