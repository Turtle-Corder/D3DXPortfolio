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

	HRESULT Add_Timer(const _tchar* pTimerTag);
	HRESULT	Update_Timer(const _tchar* pTimerTag);
	_double Get_DeltaTime(const _tchar* pTimerTag);


private:
	CTimer* Find_Timer(const _tchar* pTimerTag);


public:
	virtual void Free() override;





private:
	typedef unordered_map<const _tchar*, CTimer*> TIMERS;
	TIMERS m_Timers;
};

END

#endif // !__TIMER_MANAGER_H__
