#pragma once
#ifndef __DFONT_H__
#define __DFONT_H__

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CDFont : public CBase
{
private:
	explicit CDFont(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CDFont() = default;


public:
	HRESULT Setup_Font(const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight);
	void Render_Font(const _tchar* pString, const _vec2* vPosition, D3DXCOLOR Color);


public:
	static CDFont* Create(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight);
	virtual void Free() override;

private:
	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
	LPD3DXFONT			m_pFont = nullptr;
	LPD3DXSPRITE		m_pSprite = nullptr;

};

END

#endif // !__DFONT_H__
