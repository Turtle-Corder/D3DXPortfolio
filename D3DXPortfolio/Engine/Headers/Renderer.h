#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CRenderer final : public CBase
{
public:
	enum enRENDER_TYPE
	{
		RENDER_PRIORITY,
		RENDER_NONEALPHA,
		RENDER_BLNEDALPHA,
		RENDER_ONLYCOLOR,
		RENDER_EFFECT,
		RENDER_UI,
		RENDER_MOUSE,
		RENDER_END,
	};


private:
	explicit CRenderer(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite, LPD3DXFONT pFont, HWND hWnd);
	virtual ~CRenderer() = default;


public:
	HRESULT Setup_Renderer();
	HRESULT Add_RendererList(CRenderer::enRENDER_TYPE eType, CGameObject* pObject);
	HRESULT Render_Renderer();


private:
	HRESULT Render_Priority();
	HRESULT Render_NoneAlpha();
	HRESULT Render_BlendAlpha();
	HRESULT Render_OnlyColor();
	HRESULT Render_Effect();
	HRESULT Render_UI();


public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite, LPD3DXFONT pFont, HWND hWnd = nullptr);
	virtual void Free() override;





private:
	typedef list<CGameObject*> GAMEOBJECTS;
	GAMEOBJECTS m_GameObjects[RENDER_END];

	HWND m_hWnd = nullptr;

	LPDIRECT3DDEVICE9	m_pDevice	= nullptr;
	LPD3DXSPRITE		m_pSprite	= nullptr;
	LPD3DXFONT			m_pFont		= nullptr;

};

END

#endif // !__RENDERER_H__
