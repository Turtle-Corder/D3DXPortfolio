#include "..\Headers\Frame.h"

USING(Engine)

CFrame::CFrame()
{
}

HRESULT CFrame::Setup_Frame(const _double & dFramePerSecond)
{
	m_dFramePerSecond = 1.0 / dFramePerSecond;
	return S_OK;
}

_bool CFrame::Update_Frame(const _double & dDeltaTime)
{
	m_dAccDeltaTime += dDeltaTime;
	if (m_dAccDeltaTime >= m_dFramePerSecond)
	{
		m_dAccDeltaTime = 0.0;
		return true;
	}

	return false;
}

CFrame * CFrame::Create(const _double & dFramePerSecond)
{
	CFrame* pInstance = new CFrame;
	if (FAILED(pInstance->Setup_Frame(dFramePerSecond)))
		Safe_Release(pInstance);

	return pInstance;
}

void CFrame::Free()
{
}

