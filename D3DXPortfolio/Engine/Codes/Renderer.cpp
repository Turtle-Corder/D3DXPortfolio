#include "GameObject.h"
#include "..\Headers\Renderer.h"

USING(Engine)

CRenderer::CRenderer()
{

}

HRESULT CRenderer::Setup_Renderer()
{
	return S_OK;
}

HRESULT CRenderer::Add_RenderGroup(RENDERID eType, CGameObject * pObject)
{
	if (nullptr == pObject)
		return E_FAIL;

	if (0 > eType || RENDER_END <= eType)
		return E_FAIL;

	Safe_AddRef(pObject);
	m_RenderGroups[eType].emplace_back(pObject);

	return S_OK;
}

HRESULT CRenderer::Render_Renderer()
{
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

	return S_OK;
}

HRESULT CRenderer::Render_Priority()
{
	for (auto& pObject : m_RenderGroups[RENDER_PRIORITY])
	{
		pObject->Render_Priority();
		Safe_Release(pObject);
	}

	m_RenderGroups[RENDER_PRIORITY].clear();

	return S_OK;
}

HRESULT CRenderer::Render_NoneAlpha()
{
	for (auto& pObject : m_RenderGroups[RENDER_NONEALPHA])
	{
		pObject->Render_NoneAlpha();
		Safe_Release(pObject);
	}

	m_RenderGroups[RENDER_NONEALPHA].clear();

	return S_OK;
}

HRESULT CRenderer::Render_BlendAlpha()
{
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	for (auto& pObject : m_RenderGroups[RENDER_BLNEDALPHA])
	{
		pObject->Render_BlendAlpha();
		Safe_Release(pObject);
	}

	m_RenderGroups[RENDER_BLNEDALPHA].clear();

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	return S_OK;
}

HRESULT CRenderer::Render_OnlyColor()
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (auto& pObject : m_RenderGroups[RENDER_ONLYCOLOR])
	{
		pObject->Render_OnlyColor();
		Safe_Release(pObject);
	}

	m_RenderGroups[RENDER_ONLYCOLOR].clear();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	return S_OK;
}

HRESULT CRenderer::Render_Effect()
{
	m_pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (auto& pObject : m_RenderGroups[RENDER_EFFECT])
	{
		pObject->Render_Effect();
		Safe_Release(pObject);
	}

	m_RenderGroups[RENDER_EFFECT].clear();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	m_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

HRESULT CRenderer::Render_UI()
{
	for (auto& pObject : m_RenderGroups[RENDER_UI])
	{
		pObject->Render_UI();
		Safe_Release(pObject);
	}

	m_RenderGroups[RENDER_UI].clear();

	return S_OK;
}

HRESULT CRenderer::Render_Mouse()
{
	for (auto& pObject : m_RenderGroups[RENDER_MOUSE])
	{
		pObject->Render_UI();
		Safe_Release(pObject);
	}

	m_RenderGroups[RENDER_MOUSE].clear();

	return S_OK;
}

CRenderer * CRenderer::Create()
{
	CRenderer* pInstance = new CRenderer();
	if (FAILED(pInstance->Setup_Renderer()))
		Safe_Release(pInstance);

	return pInstance;
}

void CRenderer::Free()
{
	for (_uint iCnt = 0; iCnt < RENDER_END; ++iCnt)
	{
		for_each(m_RenderGroups[iCnt].begin(), m_RenderGroups[iCnt].end(), CDeleteObj());
		m_RenderGroups[iCnt].clear();
	}
}
