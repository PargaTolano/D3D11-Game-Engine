#include "D3D.h"

bool D3D::initialize(HWND hWnd)
{
	this->hWindow = hWnd;

	RECT dimensions;
	GetClientRect(hWnd, &dimensions);
	unsigned int width = dimensions.right - dimensions.left;
	unsigned int heigth = dimensions.bottom - dimensions.top;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
	};
	unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
	};
	unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = heigth;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	HRESULT result;
	unsigned int driver = 0, creationFlags = D3D11_CREATE_DEVICE_DEBUG;
	for (driver = 0; driver < totalDriverTypes; driver++)
	{
		result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
			creationFlags, featureLevels, totalFeaturesLevels,
			D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
			&device, &featureLevel, &context);

		if (SUCCEEDED(result))
		{
			driverType = driverTypes[driver];
			break;
		}
	}

	if (FAILED(result))
	{
		return false;
	}

	ID3D11Texture2D* backBufferTexture;
	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
	if (FAILED(result))
	{
		return false;
	}

	result = device->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
	if (backBufferTexture)
		backBufferTexture->Release();

	if (FAILED(result))
	{
		return false;
	}

	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)width;
	viewport.Height = (FLOAT)heigth;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	context->RSSetViewports(1, &viewport);

	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = width;
	depthTexDesc.Height = heigth;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;

	result = device->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
	if (FAILED(result))
	{
		MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = depthTexDesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	result = device->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
	if (FAILED(result))
	{
		MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
		return false;
	}

	create_rasterizer_states();

	//rs_cullback	rs_nocull   rs_wf_callback

	context->RSSetState(rs_nocull);

	context->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

	return true;
}

void D3D::create_rasterizer_states()
{
	create_fill_cullback();
	create_wireframe_cullback();
	create_fill_nocull();
}

void D3D::create_fill_cullback() {
	D3D11_RASTERIZER_DESC rasterdesc;
	ZeroMemory(&rasterdesc, sizeof(rasterdesc));
	rasterdesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterdesc.CullMode = D3D11_CULL_BACK;
	rasterdesc.FrontCounterClockwise = FALSE;
	rasterdesc.DepthBias = 0;
	rasterdesc.DepthBiasClamp = 0.0;
	rasterdesc.SlopeScaledDepthBias = 0.0;
	rasterdesc.DepthClipEnable = TRUE;
	rasterdesc.ScissorEnable = FALSE;
	rasterdesc.MultisampleEnable = FALSE;
	rasterdesc.AntialiasedLineEnable = FALSE;

	device->CreateRasterizerState(&rasterdesc, &rs_cullback);
}

void D3D::create_wireframe_cullback() {
	D3D11_RASTERIZER_DESC rasterdesc;
	ZeroMemory(&rasterdesc, sizeof(rasterdesc));
	rasterdesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rasterdesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	rasterdesc.FrontCounterClockwise = FALSE;
	rasterdesc.DepthBias = 0;
	rasterdesc.DepthBiasClamp = 0.0;
	rasterdesc.SlopeScaledDepthBias = 0.0;
	rasterdesc.DepthClipEnable = TRUE;
	rasterdesc.ScissorEnable = FALSE;
	rasterdesc.MultisampleEnable = FALSE;
	rasterdesc.AntialiasedLineEnable = FALSE;

	device->CreateRasterizerState(&rasterdesc, &rs_wf_callback);
}

void D3D::create_fill_nocull() {
	D3D11_RASTERIZER_DESC rasterdesc;
	ZeroMemory(&rasterdesc, sizeof(rasterdesc));
	rasterdesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterdesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	rasterdesc.FrontCounterClockwise = FALSE;
	rasterdesc.DepthBias = 0;
	rasterdesc.DepthBiasClamp = 0.0;
	rasterdesc.SlopeScaledDepthBias = 0.0;
	rasterdesc.DepthClipEnable = TRUE;
	rasterdesc.ScissorEnable = FALSE;
	rasterdesc.MultisampleEnable = FALSE;
	rasterdesc.AntialiasedLineEnable = FALSE;

	device->CreateRasterizerState(&rasterdesc, &rs_nocull);
}

void D3D::cleanup()
{
	if (depthTexture)
		depthTexture->Release();
	if (depthStencilView)
		depthStencilView->Release();
	if (backBufferTarget)
		backBufferTarget->Release();
	if (swapChain)
		swapChain->Release();
	if (context)
		context->Release();
	if (device)
		device->Release();

	depthTexture = 0;
	depthStencilView = 0;
	device = 0;
	context = 0;
	swapChain = 0;
	backBufferTarget = 0;
}

void D3D::StartScene()
{
	float clearColor[4] = { 0.15, 0.15, 0.15, 1.0f };
	context->ClearRenderTargetView(backBufferTarget, clearColor);
	context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void D3D::EndScene()
{
	swapChain->Present(1, 0);
}

D3D::D3D(HWND hWindow)
{
	initialize(hWindow);
}

D3D::~D3D()
{
	cleanup();
}

ID3D11Device* D3D::getDevice()
{
	return this->device;
}

ID3D11DeviceContext* D3D::getContext()
{
	return this->context;
}