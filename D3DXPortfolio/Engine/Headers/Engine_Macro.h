#pragma once
#ifndef __ENGINE_DEFINE_H__
#define __ENGINE_DEFINE_H__





//----------------------------------------------------------------------------------------------------
// DLL
//----------------------------------------------------------------------------------------------------
#ifdef __ENGINE_EXPORTS__
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif // __ENGINE_EXPORTS__





//----------------------------------------------------------------------------------------------------
// Namespace
//----------------------------------------------------------------------------------------------------
#define BEGIN(Name) namespace Name	{
#define END							}
#define USING(Name)	using namespace Name;





//----------------------------------------------------------------------------------------------------
// Validate Check
//----------------------------------------------------------------------------------------------------
#define NULL_CHECK( _ptr)	\
{if( _ptr == 0){__asm { int 3 };return;}}


#define NULL_CHECK_RETURN( _ptr, _return)	\
{if( _ptr == 0){__asm { int 3 };return _return;}}


#define NULL_CHECK_MSG( _ptr, _message )		\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };}}


#define NULL_CHECK_RETURN_MSG( _ptr, _return, _message )	\
{if( _ptr == 0){MessageBox(NULL, _message, L"System Message",MB_OK);__asm { int 3 };return _return;}}


#define FAILED_CHECK(_hr)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, L"Failed", L"System Error",MB_OK); __asm { int 3 }; return E_FAIL;}


#define FAILED_CHECK_RETURN(_hr, _return)	if( ((HRESULT)(_hr)) < 0 )		\
{ MessageBox(NULL, L"Failed", L"System Error",MB_OK); __asm { int 3 }; return _return;}


#define FAILED_CHECK_MSG( _hr, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, _message, L"System Message",MB_OK); __asm { int 3 };return E_FAIL;}


#define FAILED_CHECK_RETURN_MSG( _hr, _return, _message)	if( ((HRESULT)(_hr)) < 0 )	\
{ MessageBox(NULL, _message, L"System Message",MB_OK); __asm { int 3 };return _return;}





//----------------------------------------------------------------------------------------------------
// Instance
//----------------------------------------------------------------------------------------------------

//--------------------------------------------------
// 복사 생성자, 대입연산자 방지
//--------------------------------------------------
#define NO_COPY(ClassName)								\
private:												\
	ClassName(const ClassName&) = delete;				\
	ClassName& operator=(const ClassName&) = delete;


//--------------------------------------------------
// 싱글톤 정의 매크로
//--------------------------------------------------
#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public:													\
	static	ClassName* Get_Instance();					\
	_int	Destroy_Instance();							\
														\
private:												\
	static	ClassName*	m_pInstance;


//--------------------------------------------------
// 싱글톤 선언 매크로 - BASE
//--------------------------------------------------
#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if(nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
														\
	return m_pInstance;									\
}														\
														\
_int ClassName::Destroy_Instance()						\
{														\
	_int iRefCnt = 0;									\
	if(m_pInstance)										\
		iRefCnt = m_pInstance->Release();				\
														\
	if(0 == iRefCnt)									\
		m_pInstance = nullptr;							\
														\
	return iRefCnt;										\
}


//--------------------------------------------------
// 싱글톤 선언 매크로 - NOBASE
//--------------------------------------------------
#define IMPLEMENT_SINGLETON_NOBASE(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::Get_Instance()					\
{														\
	if(nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
														\
	return m_pInstance;									\
}														\
														\
_int ClassName::Destroy_Instance()						\
{														\
	if(m_pInstance)										\
	{													\
		delete m_pInstance;								\
		m_pInstance = nullptr;							\
	}													\
}




//----------------------------------------------------------------------------------------------------
// RETURN CODE
//----------------------------------------------------------------------------------------------------
namespace RETURNCODE
{
	const int RETCODE_ERR = -1;
	const int RETCODE_NONE = 0;
	const int RETCODE_TRAVEL = 1;
	const int RETCODE_RELEASE = 9;
	const int RETCODE_EXIT = 9798;
}





#endif // !__ENGINE_DEFINE_H__
