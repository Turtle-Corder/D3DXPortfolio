#pragma once
#ifndef __LAYER_H__
#define __LAYER_H__

#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CComponent;
class ENGINE_DLL CLayer : public CBase
{
private:
	explicit CLayer(void);
	virtual ~CLayer(void) = default;


public:
	CGameObject* Find_GameObject(const _tchar* pObjTag);
	CComponent* Find_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);


public:
	virtual HRESULT Setup_Layer();
	virtual _int	Update_Layer(_double dDeltaTime);
	virtual _int	LateUpdate_Layer(_double dDeltaTime);
	HRESULT			Add_Object(const _tchar* pObjTag, CGameObject* pGameObject);

public:
	static CLayer* Create();
	virtual void Free() override;





private:
	typedef unordered_map<const _tchar*, CGameObject*> GAMEOBJECTS;
	GAMEOBJECTS m_mapObject;
};

END

#endif // !__LAYER_H__
