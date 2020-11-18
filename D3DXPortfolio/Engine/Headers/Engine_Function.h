#pragma once
#ifndef __ENGINE_FUNCTION_H__
#define __ENGINE_FUNCTION_H__





//----------------------------------------------------------------------------------------------------
// 메모리 해제
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// 단일
//--------------------------------------------------
template<typename T>
void Safe_Delete(T& ptr)
{
	if (nullptr != ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}


//--------------------------------------------------
// 배열
//--------------------------------------------------
template<typename T>
void Safe_Delete_Array(T& ptr)
{
	if (nullptr != ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}





//----------------------------------------------------------------------------------------------------
// 레퍼런스 카운터
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// 증가
//--------------------------------------------------
template<typename T>
_int Safe_AddRef(T& ptr)
{
	_int iRefCnt = 0;
	if (nullptr != ptr)
		iRefCnt = ptr->AddRef();

	return iRefCnt;
}


//--------------------------------------------------
// 감소
//--------------------------------------------------
template<typename T>
_int Safe_Release(T& ptr)
{
	_int iRefCnt = 0;
	if (nullptr != ptr)
	{
		iRefCnt = ptr->Release();
		if (0 == iRefCnt)
			ptr = nullptr;
	}

	return iRefCnt;
}





//----------------------------------------------------------------------------------------------------
// Compare 함수객체
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// 문자열 비교
//--------------------------------------------------
class CTagFinder
{
public:
	explicit CTagFinder(const _tchar* pTag) : m_pTargetTag(pTag) { }
	~CTagFinder() { }

public:
	template<typename T>
	bool operator()(const T& pair)
	{
		if (0 == lstrcmpW(m_pTargetTag, pair.first))
			return true;

		return false;
	}

private:
	const _tchar*		m_pTargetTag = nullptr;
};


//--------------------------------------------------
// 컨테이너 해제용
//--------------------------------------------------
class CDeleteObj
{
public:
	explicit CDeleteObj(void) {}
	~CDeleteObj(void) {}

public:
	template <typename T>
	void operator () (T& pInstance)
	{
		_ulong dwRefCnt = 0;

		dwRefCnt = pInstance->Release();
		if (0 == dwRefCnt)
			pInstance = nullptr;
	}
};

class CDeleteMap
{
public:
	explicit CDeleteMap(void) {}
	~CDeleteMap(void) {}
public: 	
	template <typename T>
	void operator () (T& Pair)
	{
		_ulong dwRefCnt = 0;

		dwRefCnt = Pair.second->Release();
		if (0 == dwRefCnt)
			Pair.second = NULL;
	}
};





#endif // !__ENGINE_FUNCTION_H__
