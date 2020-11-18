#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__

#include "Base.h"

BEGIN(Engine)

class CTimer final : public CBase
{
private:
	explicit CTimer();
	virtual ~CTimer() = default;


public:
	virtual HRESULT Setup_Timer();
	virtual HRESULT Update_Timer();
	_double Get_DeltaTime();


public:
	static CTimer* Create();
	virtual void Free() override;





protected:
	LARGE_INTEGER	m_FrameTime;
	LARGE_INTEGER	m_FixTime;
	LARGE_INTEGER	m_LastTime;
	LARGE_INTEGER	m_CpuTick;

	_double			m_dDeltaTime = 0.0;

};

END

#endif // !__TIMER_H__
