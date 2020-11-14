#pragma once
#ifndef __BASE_H__
#define __BASE_H__

#include "Engine_Include.h"
#include "Log.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected:
	CBase(void);
	virtual ~CBase(void) = default;


public:
	_int AddRef(void);
	_int Release(void);


protected:
	virtual void Free(void) = 0;





	//----------------------------------------------------------------------------------------------------
	// Variables
	//----------------------------------------------------------------------------------------------------
protected:
	_int	m_iRefCnt	= 0;
	_bool	m_bIsClone	= false;
};

END

#endif // !__BASE_H__
