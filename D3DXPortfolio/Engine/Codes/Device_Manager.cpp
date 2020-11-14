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

HRESULT CDevice_Manager::Setup_GraphicDevice(HWND _hWnd, _uint _iWinCX, _uint _iWinCY, DISPLAY_MODE _eDisplayMode)
{
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
