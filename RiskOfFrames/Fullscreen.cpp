#include "stdafx.h"
#include "Fullscreen.h"

Fullscreen::Fullscreen() {}
Fullscreen::~Fullscreen() {}

bool Fullscreen::Toggle(bool toggle) {
	HWND window = FindWindow(NULL, L"Risk of Rain 2");
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC scd;
	IDXGISwapChain* swapChain = NULL;
	ID3D11Device* device = NULL;
	ID3D11DeviceContext* ctx = NULL;

	scd.BufferDesc.Width = 1920;
	scd.BufferDesc.Height = 1080;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 2;
	scd.OutputWindow = window;
	scd.Windowed = ((GetWindowLongPtr(window, GWL_STYLE) & WS_POPUP) != 0) ? false : true;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &scd, &swapChain, &device, 0, &ctx))) {
		Console::Warn("D3D11CreateDeviceAndSwapChain() failed");
		return false;
	} else {
		Console::Log(Helpers::VariableText("swapChain: %x", swapChain));
	}


	if (FAILED(swapChain->ResizeTarget(&scd.BufferDesc))) {
		Console::Warn("ResizeTarget() failed");
		return false;
	}

	if (FAILED(swapChain->SetFullscreenState(toggle, nullptr))) {
		Console::Warn("SetFullscreenState() failed");
		return false;
	}

	Sleep(10);
	if (FAILED(swapChain->ResizeBuffers(scd.BufferCount, scd.BufferDesc.Width, scd.BufferDesc.Height, scd.BufferDesc.Format, scd.Flags))) {
		Console::Warn("ResizeBuffers() failed");
		return false;
	}

	return true;
}
