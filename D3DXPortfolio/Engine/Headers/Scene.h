#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "Base.h"

BEGIN(Engine)

class ENGINE_DLL CScene abstract : public CBase
{
private:
	explicit CScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CScene() = default;


public:
	virtual HRESULT Setup_Scene() = 0;
	virtual _int Update_Scene(_double dDeltaTime) = 0;
	virtual _int LateUpdate_Scene(_double dDeltaTime) = 0;

public:
	virtual void Free() override;





protected:
	LPDIRECT3DDEVICE9 m_pDevice;
};

END

#endif // !__SCENE_H__

