#pragma once
#ifndef __ENGINE_DEFINE_H__
#define __ENGINE_DEFINE_H__

#pragma warning(disable : 4251)





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
// Namespace
//----------------------------------------------------------------------------------------------------
enum enLOGLEVEL
{
	LEVEL_DEBUG,
	LEVEL_WARNG,
	LEVEL_ERROR,
	LEVEL_SYSTEM
};





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
// Instance
//----------------------------------------------------------------------------------------------------
namespace RETURNCODE
{
	const int RETCODE_ERR		= -1;
	const int RETCODE_NONE		= 0;
	const int RETCODE_TRAVEL	= 1;
	const int RETCODE_RELEASE	= 9;
	const int RETCODE_EXIT		= 9798;
}





#endif // !__ENGINE_DEFINE_H__
