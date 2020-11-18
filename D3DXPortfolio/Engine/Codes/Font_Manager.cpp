#include "DFont.h"
#include "..\Headers\Font_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFont_Manager)

CFont_Manager::CFont_Manager()
{
}

HRESULT CFont_Manager::Setup_FontManager()
{
	return S_OK;
}

HRESULT CFont_Manager::Add_Font(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFontTag, const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	CDFont* pInstance = nullptr;
	pInstance = Find_Font(pFontTag);
	if (nullptr != pInstance)
		return E_FAIL;

	pInstance = CDFont::Create(pDevice, pFontType, iWidth, iHeight, iWeight);
	NULL_CHECK_RETURN(pInstance, E_FAIL);

	m_mapFonts.emplace(pFontTag, pInstance);
	return S_OK;
}

void CFont_Manager::Render_Font(const _tchar * pFontTag, const _tchar * pString, const _vec2 * pPos, D3DXCOLOR Color)
{
	CDFont* pFont = Find_Font(pFontTag);
	NULL_CHECK(pFont);

	pFont->Render_Font(pString, pPos, Color);
}

CDFont * CFont_Manager::Find_Font(const _tchar * pFontTag)
{
	auto iter = find_if(m_mapFonts.begin(), m_mapFonts.end(), CTagFinder(pFontTag));
	if (iter == m_mapFonts.end())
		return nullptr;

	return iter->second;
}

void CFont_Manager::Free()
{
	for_each(m_mapFonts.begin(), m_mapFonts.end(), CDeleteMap());
	m_mapFonts.clear();
}
