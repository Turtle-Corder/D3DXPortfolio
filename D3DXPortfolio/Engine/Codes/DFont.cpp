#include "DFont.h"

USING(Engine)

CDFont::CDFont(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{

}

HRESULT CDFont::Setup_Font(const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	D3DXFONT_DESC	Font_Desc;
	ZeroMemory(&Font_Desc, sizeof(D3DXFONT_DESC));

	Font_Desc.CharSet = HANGUL_CHARSET;
	lstrcpy(Font_Desc.FaceName, pFontType);
	Font_Desc.Width = iWidth;
	Font_Desc.Height = iHeight;
	Font_Desc.Weight = iWeight;

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &Font_Desc, &m_pFont)))
	{
		MSG_BOX("Font Create Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MSG_BOX("Sprite Create Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CDFont::Render_Font(const _tchar * pString, const _vec2* vPosition, D3DXCOLOR Color)
{
	RECT	rc{ _long(vPosition->x), _long(vPosition->y) };

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	m_pFont->DrawText(m_pSprite, pString, lstrlen(pString), &rc, DT_NOCLIP, Color);

	m_pSprite->End();
}

CDFont * CDFont::Create(LPDIRECT3DDEVICE9 pDevice, const _tchar * pFontType, const _uint & iWidth, const _uint & iHeight, const _uint & iWeight)
{
	CDFont*	pInstance = new CDFont(pDevice);

	if (FAILED(pInstance->Setup_Font(pFontType, iWidth, iHeight, iWeight)))
	{
		MSG_BOX("Font Create Failed");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CDFont::Free()
{
	Safe_Release(m_pFont);
	Safe_Release(m_pSprite);
	Safe_Release(m_pDevice);
}
