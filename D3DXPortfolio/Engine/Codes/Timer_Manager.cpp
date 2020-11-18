#include "Timer.h"
#include "..\Headers\Timer_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTimer_Manager)

CTimer_Manager::CTimer_Manager()
{
}



HRESULT CTimer_Manager::Setup_TimerManager()
{
	return S_OK;
}



HRESULT CTimer_Manager::Add_Timer(const _tchar * pTimerTag)
{
	CTimer* pInstance = Find_Timer(pTimerTag);
	if (nullptr != pInstance)
		return E_FAIL;

	pInstance = CTimer::Create();
	NULL_CHECK_RETURN(pInstance, E_FAIL);

	m_Timers.emplace(pTimerTag, pInstance);
	return S_OK;
}



HRESULT CTimer_Manager::Update_Timer(const _tchar * pTimerTag)
{
	CTimer* pInstance = Find_Timer(pTimerTag);
	NULL_CHECK(pInstance);

	return pInstance->Update_Timer();
}



_double CTimer_Manager::Get_DeltaTime(const _tchar * pTimerTag)
{
	CTimer* pInstance = Find_Timer(pTimerTag);
	NULL_CHECK_RETURN(pInstance, 0.0);

	return pInstance->Get_DeltaTime();
}



CTimer * CTimer_Manager::Find_Timer(const _tchar * pTimerTag)
{
	auto iter = find_if(m_Timers.begin(), m_Timers.end(), CTagFinder(pTimerTag));
	if (iter == m_Timers.end())
		return nullptr;

	return iter->second;
}



void CTimer_Manager::Free()
{
	for_each(m_Timers.begin(), m_Timers.end(), CDeleteMap());
	m_Timers.clear();
}
