#include "..\Headers\Timer.h"

USING(Engine)

CTimer::CTimer()
{
}



HRESULT CTimer::Setup_Timer()
{
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_PreTime);
	QueryPerformanceCounter(&m_CurTime);

	m_fDeltaTime = 0.f;
	m_bPause = false;

	return S_OK;
}



HRESULT CTimer::Update_Timer()
{
	if (m_bPause)
		return S_OK;

	QueryPerformanceCounter(&m_CurTime);

	m_fDeltaTime = (_float)(m_CurTime.QuadPart - m_PreTime.QuadPart) / m_CpuTick.QuadPart;
	m_PreTime = m_CurTime;

	return S_OK;
}



_float CTimer::Get_DeltaTime()
{
	return m_fDeltaTime;
}



void CTimer::Pause()
{
	m_bPause = true;
	m_fDeltaTime = 0.f;
}



void CTimer::Resume()
{
	m_bPause = false;
	QueryPerformanceCounter(&m_PreTime);
}



CTimer * CTimer::Create()
{
	CTimer* pInstance = nullptr;
	pInstance = new CTimer;
	if (FAILED(pInstance->Setup_Timer()))
	{
		_LOG(LEVEL_SYSTEM, _T("Failed To Create Timer \n"));
		Safe_Delete(pInstance);
	}

	return pInstance;
}



void CTimer::Free()
{
}
