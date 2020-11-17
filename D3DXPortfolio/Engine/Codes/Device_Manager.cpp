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



LPD3DXFONT CDevice_Manager::Get_Font() const
{
	return m_pFont;
}



LPD3DXSPRITE CDevice_Manager::Get_Sprite() const
{
	return m_pSprite;
}



HRESULT CDevice_Manager::Setup_GraphicDevice(HWND hWnd, _uint iWinCX, _uint iWinCY, DISPLAY_MODE eDisplayMode)
{
	if (nullptr == hWnd)
		return E_FAIL;

	D3DCAPS9 DeviceCap;
	ZeroMemory(&DeviceCap, sizeof(D3DCAPS9));

	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCap)))
	{
		_LOG(enLOGLEVEL::LEVEL_SYSTEM, _T("Failed To Create SDK \n"));
		return E_FAIL;
	}


	DWORD vp = 0;
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
		_LOG(LEVEL_SYSTEM, _T("Failed To Create Device \n"));
		return E_FAIL;
	}

	//--------------------------------------------------
	// SPRITE
	//--------------------------------------------------
	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		_LOG(LEVEL_SYSTEM, _T("Failed To Create Sprite"));
		return E_FAIL;
	}


	//--------------------------------------------------
	// FONT
	//--------------------------------------------------	
	D3DXFONT_DESC tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESC));
	tFontInfo.Height = 8;
	tFontInfo.Width = 8;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, _T("�ü�"));
	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		_LOG(LEVEL_SYSTEM, _T("Failed To Create Font"));
		return E_FAIL;
	}

	return S_OK;
}



void CDevice_Manager::Free()
{
	if (Safe_Release(m_pFont))
		_LOG(enLOGLEVEL::LEVEL_SYSTEM, _T("Failed To Release Font"));

	if (Safe_Release(m_pSprite))
		_LOG(enLOGLEVEL::LEVEL_SYSTEM, _T("Failed To Release Sprite"));

	if (Safe_Release(m_pDevice))
		_LOG(enLOGLEVEL::LEVEL_SYSTEM, _T("Failed To Release Device"));

	if (Safe_Release(m_pSDK))
		_LOG(enLOGLEVEL::LEVEL_SYSTEM, _T("Failed To Release SDK"));
}
