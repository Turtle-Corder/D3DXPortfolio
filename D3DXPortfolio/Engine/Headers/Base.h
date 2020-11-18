#pragma once
#ifndef __BASE_H__
#define __BASE_H__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	explicit CBase(void);
	virtual ~CBase(void) = default;


public:
	_int AddRef(void);
	_int Release(void);


protected:
	virtual void Free(void) = 0;





	//----------------------------------------------------------------------------------------------------
	// Variables
	//----------------------------------------------------------------------------------------------------
private:
	_int	m_iRefCnt	= 0;
};

END

#endif // !__BASE_H__
