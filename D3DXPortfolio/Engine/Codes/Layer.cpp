#include "GameObject.h"
#include "..\Headers\Layer.h"

USING(Engine)

CLayer::CLayer()
{
}

CGameObject * CLayer::Find_GameObject(const _tchar * pObjTag)
{
	auto iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTagFinder(pObjTag));
	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second;
}

CComponent * CLayer::Find_Component(const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	auto iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTagFinder(pObjTag));
	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second->Get_Component(pComponentTag, eID);
}

HRESULT CLayer::Setup_Layer()
{
	return S_OK;
}

_int CLayer::Update_Layer(_double dDeltaTime)
{
	for (auto& iter : m_mapObject)
		iter.second->Update_GameObject(dDeltaTime);

	return RETURNCODE::RETCODE_NONE;
}

_int CLayer::LateUpdate_Layer(_double dDeltaTime)
{
	for (auto& iter : m_mapObject)
		iter.second->LateUpdate_GameObject(dDeltaTime);

	return RETURNCODE::RETCODE_NONE;
}

HRESULT CLayer::Add_Object(const _tchar * pObjTag, CGameObject * pGameObject)
{
	NULL_CHECK_RETURN(pObjTag, E_FAIL);

	m_mapObject.emplace(pObjTag, pGameObject);
	return S_OK;
}

CLayer * CLayer::Create()
{
	CLayer* pInstance = new CLayer;
	if (FAILED(pInstance->Setup_Layer()))
		Safe_Release(pInstance);

	return pInstance;
}

void CLayer::Free()
{
	for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
	m_mapObject.clear();
}

