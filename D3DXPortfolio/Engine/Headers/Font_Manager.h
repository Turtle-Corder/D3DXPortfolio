#pragma once
#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include "Base.h"

BEGIN(Engine)

class CDFont;
class CFont_Manager : public CBase
{
	DECLARE_SINGLETON(CFont_Manager)

private:
	explicit CFont_Manager();
	virtual ~CFont_Manager() = default;

public:
	HRESULT Setup_FontManager();

	HRESULT Add_Font(LPDIRECT3DDEVICE9 pDevice, const _tchar* pFontTag, const _tchar* pFontType, const _uint& iWidth, const _uint& iHeight, const _uint& iWeight);
	void Render_Font(const _tchar* pFontTag, const _tchar* pString, const _vec2* pPos, D3DXCOLOR Color);


private:
	CDFont* Find_Font(const _tchar* pFontTag);


public:
	virtual void Free() override;




private:
	typedef unordered_map<const _tchar*, CDFont*> FONTS;
	FONTS m_mapFonts;
};

END

#endif // !__FONT_MANAGER_H__
