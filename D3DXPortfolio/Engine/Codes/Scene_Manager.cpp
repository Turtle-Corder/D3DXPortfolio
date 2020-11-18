#include "Scene.h"
#include "..\Headers\Scene_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CScene_Manager)

CScene_Manager::CScene_Manager()
{
}

HRESULT CScene_Manager::Change_CurrentScene(_int _iSceneID, CScene * pCurrentScene)
{
	NULL_CHECK_RETURN(pCurrentScene, E_FAIL);

	if (m_iCurrSceneID != _iSceneID)
	{
		Safe_Release(m_pCurrScene);

		m_pCurrScene = pCurrentScene;
		m_iCurrSceneID = _iSceneID;
	}

	return S_OK;
}

_int CScene_Manager::Update_Scene_Manager(_double _dDeltaTime)
{
	NULL_CHECK_RETURN(m_pCurrScene, RETURNCODE::RETCODE_ERR);

	return m_pCurrScene->Update_Scene(_dDeltaTime);
}

_int CScene_Manager::LateUpdate_Scene_Manager(_double _dDeltaTime)
{
	NULL_CHECK_RETURN(m_pCurrScene, RETURNCODE::RETCODE_ERR);

	return m_pCurrScene->LateUpdate_Scene(_dDeltaTime);
}

void CScene_Manager::Free()
{
	Safe_Release(m_pCurrScene);
}
