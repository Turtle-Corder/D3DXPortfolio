#pragma once
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "Base.h"

BEGIN(Engine)

class CScene;
class CScene_Manager : public CBase
{
	DECLARE_SINGLETON(CScene_Manager)

private:
	explicit CScene_Manager();
	virtual ~CScene_Manager() = default;


public:
	HRESULT Change_CurrentScene(_int _iSceneID, CScene* pCurrentScene);
	_int Update_Scene_Manager(_double DeltaTime);
	_int LateUpdate_Scene_Manager(_double DeltaTime);


public:
	virtual void Free() override;





private:
	CScene* m_pCurrScene	= nullptr;
	_int	m_iCurrSceneID	= -1;
};

END

#endif // !__SCENE_MANAGER_H__
