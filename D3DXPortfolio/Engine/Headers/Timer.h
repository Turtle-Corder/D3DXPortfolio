#pragma once
#ifndef __TIMER_H__
#define __TIMER_H__

#include "Base.h"

BEGIN(Engine)

class CTimer final : public CBase
{
private:
	explicit CTimer();
	~CTimer() = default;


public:
	virtual HRESULT Setup_Timer();
	virtual HRESULT Update_Timer();
	_float Get_DeltaTime();

	void Pause();
	void Resume();


public:
	static CTimer* Create();
	virtual void Free() override;





protected:
	_bool			m_bPause;
	LARGE_INTEGER	m_CpuTick;
	LARGE_INTEGER	m_PreTime;
	LARGE_INTEGER	m_CurTime;

	_float			m_fDeltaTime;

};

END

#endif // !__TIMER_H__
