#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CRenderer final : public CBase
{

private:
	explicit CRenderer();
	virtual ~CRenderer() = default;


public:
	HRESULT Setup_Renderer();
	HRESULT Add_RenderGroup(RENDERID eType, CGameObject* pObject);
	HRESULT Render_Renderer();


private:
	HRESULT Render_Priority();
	HRESULT Render_NoneAlpha();
	HRESULT Render_BlendAlpha();
	HRESULT Render_OnlyColor();
	HRESULT Render_Effect();
	HRESULT Render_UI();
	HRESULT Render_Mouse();


public:
	static CRenderer* Create();
	virtual void Free() override;





private:
	typedef list<CGameObject*> RENDERGROUPS;
	RENDERGROUPS m_RenderGroups[RENDER_END];

	LPDIRECT3DDEVICE9	m_pDevice	= nullptr;
};

END

#endif // !__RENDERER_H__
