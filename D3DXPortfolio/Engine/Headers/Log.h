#pragma once
#ifndef __LOG_H__
#define __LOG_H__

#include "Engine_Include.h"

BEGIN(Engine)

extern enLOGLEVEL	g_enLogLevel;
extern TCHAR		g_szLogBuff[1024];

ENGINE_DLL void Log(TCHAR* szLog, enLOGLEVEL enLevel);



#define _LOG_LEVEL(LogLevel)														\
do																					\
{																					\
	if (0 > LogLevel || enLOGLEVEL::LEVEL_SYSTEM < LogLevel)						\
		g_enLogLevel = LEVEL_DEBUG;													\
	else																			\
		g_enLogLevel = LogLevel;													\
} while (0)



#define _LOG_DIRECTORY(FilePath)													\
do																					\
{																					\
	ZeroMemory(g_szLogBuff, sizeof(TCHAR) * 1024);									\
	StringCchCopy(g_szLogBuff, _countof(g_szLogBuff), FilePath);					\
} while (0)




#define _LOG(LogLevel, fmt, ...)													\
do																					\
{																					\
	if(g_enLogLevel <= LogLevel)													\
	{																				\
		StringCchPrintf(g_szLogBuff, _countof(g_szLogBuff), fmt, ##__VA_ARGS__);	\
		Log(g_szLogBuff, LogLevel);													\
		MessageBox(0, g_szLogBuff, _T("LOG"), MB_OK);								\
	}																				\
} while (0)



//class CLog
//{
//	DECLARE_SINGLETON(CLog)
//
//private:
//	CLog(void);
//	~CLog(void);
//
//
//public:
//	enum enLOGLEVEL
//	{
//		LEVEL_DEBUG,
//		LEVEL_WARNG,
//		LEVEL_ERROR,
//		LEVEL_SYSTEM
//	};
//
//
//public:
//	HRESULT Set_Directory(const TCHAR* szFilePath);
//	HRESULT Set_Level(enLOGLEVEL enLogLevel);
//	HRESULT Log(const TCHAR* szType, enLOGLEVEL enLogLevel, const TCHAR* szStringFormat, ...);
////	HRESULT LogHex(const TCHAR* szType, enLOGLEVEL enLogLevel, const TCHAR* szLog, BYTE* pByte, _int iByteLen);
//
//
//
//
//
//	//----------------------------------------------------------------------------------------------------
//	// Variables
//	//----------------------------------------------------------------------------------------------------
//private:	
//	enLOGLEVEL	m_enCurrLevel;
//	TCHAR		m_szFilePath[MAX_PATH - 32];
//
//	// Extends
//	CRITICAL_SECTION	m_csLog;
//	LONG				m_lLogCount = 0;
//
//	// tag
//	TCHAR *m_arrLogLevel[] =
//	{
//		_T("DEBUG"),
//		_T("WARNG"),
//		_T("ERROR"),
//		_T("SYSTEM"),
//	};
//};



END

#endif // !__LOG_H__
