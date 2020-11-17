#include "Timer.h"
#include "..\Headers\Timer_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTimer_Manager)

CTimer_Manager::CTimer_Manager()
{
}



CTimer_Manager::~CTimer_Manager()
{
}



HRESULT CTimer_Manager::Setup_TimerManager()
{
	m_pTimers = new TIMERS;

	return S_OK;
}



_int CTimer_Manager::Update_TimeManager()
{
	for (auto& rPair : *m_pTimers)
	{
		if (FAILED(rPair.second->Update_Timer()))
			RETURNCODE::RETCODE_ERR;
	}

	return RETURNCODE::RETCODE_NONE;
}



HRESULT CTimer_Manager::Add_Timer(const wstring & strTimerTag, bool bStart)
{
	auto iter_find = m_pTimers->find(strTimerTag);
	if (iter_find != m_pTimers->end())
	{
		_LOG(LEVEL_SYSTEM, _T("Already Register Timer! \n"));
		return E_FAIL;
	}

	CTimer* pTimer = nullptr;
	pTimer = CTimer::Create();
	if (nullptr == pTimer)
	{
		_LOG(LEVEL_SYSTEM, _T("Failed to Crate Timer! \n"));
		return E_FAIL;
	}

	if (!bStart)	pTimer->Pause();
	m_pTimers->emplace(strTimerTag, pTimer);

	return S_OK;
}



HRESULT CTimer_Manager::Get_DeltaTime(const wstring & strTimerTag, float & fDeltaTime)
{
	auto iter_find = m_pTimers->find(strTimerTag);
	if (m_pTimers->end() == iter_find)
	{
		_LOG(LEVEL_SYSTEM, _T("Cant Found Timer in Get DeltaTime! \n"));
		return E_FAIL;
	}

	fDeltaTime = iter_find->second->Get_DeltaTime();
	return S_OK;
}



HRESULT CTimer_Manager::Pause(const wstring & strTimerTag)
{
	auto iter_find = m_pTimers->find(strTimerTag);
	if (m_pTimers->end() == iter_find)
	{
		_LOG(LEVEL_SYSTEM, _T("Cant Found Timer in Pause! \n"));
		return E_FAIL;
	}

	iter_find->second->Pause();
	return S_OK;
}



HRESULT CTimer_Manager::Resume(const wstring & strTimerTag)
{
	auto iter_find = m_pTimers->find(strTimerTag);
	if (m_pTimers->end() == iter_find)
	{
		_LOG(LEVEL_SYSTEM, _T("Cant Found Timer in Resume! \n"));
		return E_FAIL;
	}

	iter_find->second->Resume();
	return S_OK;
}



void CTimer_Manager::Free()
{
	for (auto& rPair : *m_pTimers)
		Safe_Delete(rPair.second);

	Safe_Delete(m_pTimers);
}
