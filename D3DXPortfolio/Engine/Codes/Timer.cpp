#include "..\Headers\Timer.h"

USING(Engine)

CTimer::CTimer()
{
}



HRESULT CTimer::Setup_Timer()
{
	QueryPerformanceFrequency(&m_CpuTick);
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	return S_OK;
}



HRESULT CTimer::Update_Timer()
{
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_FixTime.QuadPart >= m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_FixTime = m_FrameTime;
	}

	m_dDeltaTime = _double(m_FrameTime.QuadPart - m_LastTime.QuadPart) / _double(m_CpuTick.QuadPart);

	m_LastTime = m_FrameTime;

	return S_OK;
}



_double CTimer::Get_DeltaTime()
{
	return m_dDeltaTime;
}



CTimer * CTimer::Create()
{
	CTimer* pInstance = nullptr;
	pInstance = new CTimer;
	if (FAILED(pInstance->Setup_Timer()))
	{
		Safe_Release(pInstance);
	}

	return pInstance;
}



void CTimer::Free()
{
}
