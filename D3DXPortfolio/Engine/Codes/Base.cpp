#include "..\Headers\Base.h"

USING(Engine)

CBase::CBase()
{
}



_int CBase::AddRef(void)
{
	return ++m_iRefCnt;
}



_int CBase::Release(void)
{
	if (0 == m_iRefCnt)
	{
		Free();
		delete this;
		return 0;
	}

	return m_iRefCnt--;
}
