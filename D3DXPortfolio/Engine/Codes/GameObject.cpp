#include "Management.h"
#include "Component.h"
#include "..\Headers\GameObject.h"

USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	Safe_AddRef(m_pDevice);
}

CGameObject::CGameObject(const CGameObject & rOther)
	: m_pDevice(rOther.m_pDevice)
{
	Safe_AddRef(m_pDevice);
}

void CGameObject::Free()
{
	for (auto& rPair : m_Components)
		Safe_Release(rPair.second);

	m_Components.clear();

	Safe_Release(m_pDevice);
}


//----------------------------------------------------------------------------------------------------
// Component
//----------------------------------------------------------------------------------------------------
HRESULT CGameObject::Add_Component(_int iSceneID, const wstring & strPrototypeTag, const wstring & strComponentTag, CComponent ** ppComponent, void * pArg)
{
	auto iter_find = m_Components.find(strComponentTag);
	if (m_Components.end() != iter_find)
		return E_FAIL;

	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	CComponent* pClone = pManagement->Clone_Component(iSceneID, strPrototypeTag, pArg);
	if (nullptr == pClone)
		return E_FAIL;

	m_Components.emplace(strComponentTag, pClone);
	if (nullptr != ppComponent)
	{
		*ppComponent = pClone;
		Safe_AddRef(pClone);
	}

	return S_OK;
}


CComponent * CGameObject::Get_Component(const wstring & strComponentTag)
{
	auto iter_find = m_Components.find(strComponentTag);
	if (iter_find == m_Components.end())
		return nullptr;

	return iter_find->second;
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
