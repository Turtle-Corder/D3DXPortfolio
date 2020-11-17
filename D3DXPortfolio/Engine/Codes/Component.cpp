#include "..\Headers\Component.h"

USING(Engine)

CComponent::CComponent(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	Safe_AddRef(m_pDevice);
}

CComponent::CComponent(const CComponent & rOther)
	: m_pDevice(rOther.m_pDevice)
{
	m_bIsClone = true;
	Safe_Release(m_pDevice);
}

void CComponent::Free()
{
	Safe_Release(m_pDevice);
}
