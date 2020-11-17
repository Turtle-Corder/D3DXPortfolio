#include "GameObject.h"
#include "..\Headers\Renderer.h"

USING(Engine)

CRenderer::CRenderer(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite, LPD3DXFONT pFont, HWND hWnd)
	: m_pDevice(pDevice)
	, m_pSprite(pSprite)
	, m_pFont(pFont)
	, m_hWnd(hWnd)
{
	Safe_AddRef(pFont);
	Safe_AddRef(pSprite);
	Safe_AddRef(pDevice);
}

HRESULT CRenderer::Setup_Renderer()
{
	return S_OK;
}

HRESULT CRenderer::Add_RendererList(CRenderer::enRENDER_TYPE eType, CGameObject * pObject)
{
	if (nullptr == pObject)
		return E_FAIL;

	if (0 > eType || RENDER_END <= eType)
		return E_FAIL;

	Safe_AddRef(pObject);
	m_GameObjects[eType].emplace_back(pObject);

	return S_OK;
}

HRESULT CRenderer::Render_Renderer()
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();

	if (FAILED(Render_Priority()))
		return E_FAIL;

	if (FAILED(Render_NoneAlpha()))
		return E_FAIL;

	if (FAILED(Render_OnlyColor()))
		return E_FAIL;

	if (FAILED(Render_BlendAlpha()))
		return E_FAIL;

	if (FAILED(Render_Effect()))
		return E_FAIL;

	if (FAILED(Render_UI()))
		return E_FAIL;

	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, m_hWnd, nullptr);
}

HRESULT CRenderer::Render_Priority()
{
	for (auto& pObject : m_GameObjects[RENDER_PRIORITY])
	{
		pObject->Render_Priority();
		Safe_Release(pObject);
	}

	m_GameObjects[RENDER_PRIORITY].clear();

	return S_OK;
}

HRESULT CRenderer::Render_NoneAlpha()
{
	for (auto& pObject : m_GameObjects[RENDER_NONEALPHA])
	{
		pObject->Render_NoneAlpha();
		Safe_Release(pObject);
	}

	m_GameObjects[RENDER_NONEALPHA].clear();

	return S_OK;
}

HRESULT CRenderer::Render_BlendAlpha()
{
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (auto& pObject : m_GameObjects[RENDER_BLNEDALPHA])
	{
		pObject->Render_BlendAlpha();
		Safe_Release(pObject);
	}

	m_GameObjects[RENDER_BLNEDALPHA].clear();

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return S_OK;
}

HRESULT CRenderer::Render_OnlyColor()
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (auto& pObject : m_GameObjects[RENDER_ONLYCOLOR])
	{
		pObject->Render_OnlyColor();
		Safe_Release(pObject);
	}

	m_GameObjects[RENDER_ONLYCOLOR].clear();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

HRESULT CRenderer::Render_Effect()
{
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (auto& pObject : m_GameObjects[RENDER_EFFECT])
	{
		pObject->Render_Effect();
		Safe_Release(pObject);
	}

	m_GameObjects[RENDER_EFFECT].clear();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//--------------------------------------------------
	// UI ·»´õÇÏ°í..
	//--------------------------------------------------
	for (auto& pObject : m_GameObjects[RENDER_UI])
	{
		pObject->Render_UI();
		Safe_Release(pObject);
	}

	m_GameObjects[RENDER_UI].clear();


	//--------------------------------------------------
	// ¸¶¿ì½º ·»´õ / Sprite BeginÇÑ ±è¿¡..
	//--------------------------------------------------
	for (auto& pObject : m_GameObjects[RENDER_MOUSE])
	{
		pObject->Render_UI();
		Safe_Release(pObject);
	}

	m_GameObjects[RENDER_MOUSE].clear();

	m_pSprite->End();

	return S_OK;
}

CRenderer * CRenderer::Create(LPDIRECT3DDEVICE9 pDevice, LPD3DXSPRITE pSprite, LPD3DXFONT pFont, HWND hWnd)
{
	if (nullptr == pDevice || nullptr == pSprite || nullptr == pFont)
		return nullptr;

	CRenderer* pInstance = new CRenderer(pDevice, pSprite, pFont, hWnd);
	if (FAILED(pInstance->Setup_Renderer()))
	{
		_LOG(LEVEL_SYSTEM, _T("Failed To Create CRenderer! \n"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CRenderer::Free()
{
	for (_int iCnt = 0; iCnt < RENDER_END; ++iCnt)
	{
		for (auto& pObject : m_GameObjects[iCnt])
			Safe_Release(pObject);

		m_GameObjects[iCnt].clear();
	}

	Safe_Release(m_pFont);
	Safe_Release(m_pSprite);
	Safe_Release(m_pDevice);
}
