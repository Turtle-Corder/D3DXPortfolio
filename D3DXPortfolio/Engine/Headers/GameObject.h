#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Base.h"

BEGIN(Engine)

class CComponent;
class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pDevice);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;


public:
	CComponent*	Find_Component(const _tchar* pComponentTag, COMPONENTID eID);


public:
	_bool			IsDead();
	void			Set_Dead();

	_bool			IsActive();
	virtual void	Set_Active();
	virtual void	Set_DeActive();

	virtual HRESULT Setup_GameObject_Prototype() = 0;
	virtual HRESULT Setup_GameObject(void* _pArg) = 0;
	virtual _int Update_GameObject(_double _dDeltaTime) = 0;
	virtual _int LateUpdate_GameObject(_double _dDeltaTime) = 0;

	virtual HRESULT Render_Priority();
	virtual HRESULT Render_NoneAlpha();
	virtual HRESULT Render_BlendAlpha();
	virtual HRESULT Render_OnlyColor();
	virtual HRESULT Render_Effect();
	virtual HRESULT Render_UI();

	virtual HRESULT Take_Damage();


public:
	virtual CGameObject* Clone_GameObject(void* pArg) = 0;
	virtual void Free() override;





protected:
	typedef unordered_map<const _tchar*, CComponent*> COMPONENTS;
	COMPONENTS m_mapComponents[ID_END];

	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	_bool m_bActive = false;
	_bool m_bDead	= false;
};

END

#endif // !__GAMEOBJECT_H__
