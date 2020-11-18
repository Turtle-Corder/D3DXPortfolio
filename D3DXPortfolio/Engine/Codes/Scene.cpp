#include "..\Headers\Scene.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	Safe_AddRef(pDevice);
}

HRESULT CScene::Setup_Scene()
{
	return S_OK;
}

_int CScene::Update_Scene(_double dDeltaTime)
{
	return _int();
}

_int CScene::LateUpdate_Scene(_double dDeltaTime)
{
	return _int();
}

void CScene::Free()
{
	Safe_Release(m_pDevice);
}
