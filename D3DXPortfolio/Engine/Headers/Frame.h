#pragma once
#ifndef __FRAME_H__
#define __FRAME_H__

#include "Base.h"

BEGIN(Engine)

class CFrame : public CBase
{
private:
	explicit CFrame();
	virtual ~CFrame() = default;

public:
	HRESULT Setup_Frame(const _double& dFramePerSecond);
	_bool Update_Frame(const _double& dDeltaTime);


public:
	static CFrame* Create(const _double& dFramePerSecond);
	virtual void Free() override;





private:
	_double m_dFramePerSecond = 0.0;
	_double m_dAccDeltaTime = 0.0;
};

END

#endif // !__FRAME_H__
