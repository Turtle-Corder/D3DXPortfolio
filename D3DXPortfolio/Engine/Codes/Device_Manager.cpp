#include "..\Headers\Device_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CDevice_Manager)

CDevice_Manager::CDevice_Manager()
{
}



LPDIRECT3DDEVICE9 CDevice_Manager::Get_Device() const
{
	return m_pDevice;
}



HRESULT CDevice_Manager::Setup_GraphicDevice(HWND hWnd, _uint iWinCX, _uint iWinCY, WINMODE eDisplayMode)
{
	if (nullptr == hWnd)
		return E_FAIL;

	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		return E_FAIL;
	}


	_ulong vp = 0;
	if (DeviceCap.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;


	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.BackBufferWidth = iWinCX;
	d3dpp.BackBufferHeight = iWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	d3dpp.Windowed = eDisplayMode;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	//--------------------------------------------------
	// SDK
	//--------------------------------------------------
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &m_pDevice)))
	{
		return E_FAIL;
	}


	return S_OK;
}

void CDevice_Manager::Render_Begin(D3DXCOLOR Color)
{
	m_pDevice->Clear(0,
		nullptr,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		Color,
		1.f,
		0);

	m_pDevice->BeginScene();
}

void CDevice_Manager::Render_End()
{
	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}



void CDevice_Manager::Free()
{
	if (Safe_Release(m_pDevice));

	if (Safe_Release(m_pSDK));
}
