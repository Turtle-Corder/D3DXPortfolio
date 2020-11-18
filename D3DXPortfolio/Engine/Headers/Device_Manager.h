#pragma once
#ifndef __DEVICE_MANAGER_H__
#define __DEVICE_MANAGER_H__

#include "Base.h"

BEGIN(Engine)

class CLog;
class CDevice_Manager final : public CBase
{
	DECLARE_SINGLETON(CDevice_Manager)

private:
	CDevice_Manager();
	virtual ~CDevice_Manager() = default;


public:
	LPDIRECT3DDEVICE9	Get_Device()	const;

	HRESULT Setup_GraphicDevice(HWND hWnd, _uint iWinCX, _uint iWinCY, WINMODE eDisplayMode);

	void Render_Begin(D3DXCOLOR Color);
	void Render_End();

	virtual void Free() override;
	




	//----------------------------------------------------------------------------------------------------
	// Variables
	//----------------------------------------------------------------------------------------------------
private:
	LPDIRECT3D9			m_pSDK = nullptr;
	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
};

END

#endif // !__DEVICE_MANAGER_H__
