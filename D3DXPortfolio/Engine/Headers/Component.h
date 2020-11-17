#pragma once
#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CComponent abstract : public CBase
{
protected:
	explicit CComponent(LPDIRECT3DDEVICE9 pDevice);
	explicit CComponent(const CComponent& rOther);
	virtual ~CComponent() = default;


public:
	virtual HRESULT Setup_Component_Prototype() = 0;
	virtual HRESULT Setup_Component(void* _pArg) = 0;

	virtual CComponent* Clone_Component(void* _pArg) = 0;
	virtual void Free() override;





protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
};

END

#endif // !__COMPONENT_H__
