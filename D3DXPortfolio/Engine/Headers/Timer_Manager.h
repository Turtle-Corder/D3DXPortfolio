#pragma once
#ifndef __TIMER_MANAGER_H__
#define __TIMER_MANAGER_H__

#include "Base.h"

BEGIN(Engine)

class CTimer;
class CTimer_Manager final : public CBase
{
	DECLARE_SINGLETON(CTimer_Manager)

private:
	CTimer_Manager();
	~CTimer_Manager() = default;


public:
	HRESULT Setup_TimerManager();
	_int	Update_TimeManager();

	HRESULT Add_Timer(const wstring& strTimerTag, bool bStart);
	HRESULT Get_DeltaTime(const wstring& strTimerTag, float& fDeltaTime);

	HRESULT Pause(const wstring& strTimerTag);
	HRESULT Resume(const wstring& strTimerTag);


public:
	virtual void Free() override;





private:
	typedef unordered_map<wstring, CTimer*> TIMERS;
	TIMERS* m_pTimers = nullptr;
};

END

#endif // !__TIMER_MANAGER_H__
