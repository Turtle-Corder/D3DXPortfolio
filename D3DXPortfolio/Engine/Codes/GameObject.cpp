#include "Management.h"
#include "Component.h"
#include "..\Headers\GameObject.h"

USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	Safe_AddRef(m_pDevice);
}

CGameObject::CGameObject(const CGameObject & rhs)
	: m_pDevice(rhs.m_pDevice)
{
	Safe_AddRef(m_pDevice);
}

void CGameObject::Free()
{
	for (_uint iCnt = 0; iCnt < ID_END; ++iCnt)
	{
		for_each(m_mapComponents[iCnt].begin(), m_mapComponents[iCnt].end(), CDeleteMap());
		m_mapComponents[iCnt].clear();
	}

	Safe_Release(m_pDevice);
}


//----------------------------------------------------------------------------------------------------
// Component
//----------------------------------------------------------------------------------------------------
CComponent * CGameObject::Find_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
	auto iter = find_if(m_mapComponents[eID].begin(), m_mapComponents[eID].end(), CTagFinder(pComponentTag));
	if (iter == m_mapComponents[eID].end())
		return nullptr;

	return iter->second;
}


//----------------------------------------------------------------------------------------------------
// Dead
//----------------------------------------------------------------------------------------------------
_bool CGameObject::IsDead()
{
	return m_bDead;
}

void CGameObject::Set_Dead()
{
	m_bDead = true;
}


//----------------------------------------------------------------------------------------------------
// Active
//----------------------------------------------------------------------------------------------------
_bool CGameObject::IsActive()
{
	return m_bActive;
}

void CGameObject::Set_Active()
{
	m_bActive = true;
}

void CGameObject::Set_DeActive()
{
	m_bActive = false;
}


//----------------------------------------------------------------------------------------------------
// Render
//----------------------------------------------------------------------------------------------------
HRESULT CGameObject::Render_Priority()
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Render_NoneAlpha()
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Render_BlendAlpha()
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Render_OnlyColor()
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Render_Effect()
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Render_UI()
{
	return E_NOTIMPL;
}

HRESULT CGameObject::Take_Damage()
{
	return E_NOTIMPL;
}
