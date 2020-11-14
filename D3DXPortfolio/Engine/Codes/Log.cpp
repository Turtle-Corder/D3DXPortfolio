#include "..\Headers\Log.h"

USING(Engine)

enLOGLEVEL	g_enLogLevel = LEVEL_WARNG;
TCHAR	g_szLogBuff[1024] = _T("");



void Log(TCHAR * szLog, enLOGLEVEL enLevel)
{
	TCHAR szTimeInfo[32];
	time_t timer;
	struct tm TM;

	time(&timer);
	if (localtime_s(&TM, &timer) != 0) return;

	ZeroMemory(szTimeInfo, sizeof(TCHAR) * 32);
	StringCchPrintf(szTimeInfo, _countof(szTimeInfo), _T("[%02d/%02d/%02d %02d:%02d:%02d]"),
		TM.tm_mon + 1, TM.tm_mday, TM.tm_year + 1900, TM.tm_hour, TM.tm_min, TM.tm_sec);

	if (3 <= (_int)enLevel)
	{
		_tprintf(_T("%s %s"), szTimeInfo, szLog);
	}

	FILE *fp;
	TCHAR szFileName[16];
	ZeroMemory(szFileName, sizeof(TCHAR) * 16);
	StringCchPrintf(szFileName, _countof(szFileName), _T("%4d%2d Log.txt"), TM.tm_year + 1900, TM.tm_mon + 1);

	if (_tfopen_s(&fp, szFileName, _T("a")) != 0) return;

	_ftprintf_s(fp, _T("%s"), szTimeInfo);
	_ftprintf_s(fp, _T("%s "), szLog);
	fclose(fp);
}



//IMPLEMENT_SINGLETON_NOBASE(CLog)
//CLog::CLog()
//{
//	InitializeCriticalSection(&m_csLog);
//}
//
//
//
//CLog::~CLog(void)
//{
//	DeleteCriticalSection(&m_csLog);
//}
//
//
//
//HRESULT CLog::Set_Directory(const TCHAR * szFilePath)
//{
//	ZeroMemory(m_szFilePath, sizeof(TCHAR) * (MAX_PATH - 32));
//	StringCchPrintf(m_szFilePath, _countof(m_szFilePath), szFilePath);
//
//	return S_OK;
//}
//
//
//
//HRESULT CLog::Set_Level(enLOGLEVEL enLogLevel)
//{
//	m_enCurrLevel = enLogLevel;
//
//	return S_OK;
//}
//
//
//
//HRESULT CLog::Log(const TCHAR * szType, enLOGLEVEL enLogLevel, const TCHAR * szStringFormat, ...)
//{
//	time_t timer;
//	struct tm TM;
//	TCHAR szTimeInfo[32];
//
//	FILE* fp;
//	TCHAR szFileName[MAX_PATH];
//
//	HRESULT hrFileName;
//	errno_t errFileOpen;
//	HRESULT hrLog;
//
//	TCHAR szLogBuff[256];
//	va_list va;
//	LONG lLogCount;
//
//
//	if (m_enCurrLevel > enLogLevel)
//		return;
//
//	EnterCriticalSection(&m_csLog);
//	
//	ZeroMemory(szFileName, sizeof(TCHAR) * MAX_PATH);
//	ZeroMemory(szTimeInfo, sizeof(TCHAR) * 32);
//	ZeroMemory(szLogBuff, sizeof(TCHAR) * 256);
//
//
//	do 
//	{
//		//--------------------------------------------------
//		// ī����
//		//--------------------------------------------------
//		lLogCount = InterlockedIncrement(&m_lLogCount);
//
//
//		//--------------------------------------------------
//		// �ð�
//		//--------------------------------------------------
//		time(&timer);
//		if (0 != localtime_s(&TM, &timer))
//		{
//			// ������ �����ϰ� �ֿܼ��� ���
//			_tprintf(_T("Console > Failed to Get Localtime! \n"));
//			break;
//		}
//
//
//		//--------------------------------------------------
//		// ���ϸ�
//		//--------------------------------------------------
//		hrFileName = StringCchPrintf(szFileName, _countof(szFileName), _T("%s%04d%02d_%s.txt"), m_szFilePath, TM.tm_year + 1900, TM.tm_mon + 1, szType);
//		if (FAILED(hrFileName))
//		{
//			// UNDONE ���ϸ��� ���۸� �ʰ��� ��� ����ó�� �ʿ�
//			Log(_T("LOG"), LEVEL_SYSTEM, _T("Name Overflow!\n"));
//			break;
//		}
//
//
//		//--------------------------------------------------
//		// �ð����� ���ۿ� ����
//		//--------------------------------------------------
//		StringCchPrintf(szTimeInfo, _countof(szTimeInfo), _T("%04d-%02d-%02d %02d:%02d:%02d"),
//			TM.tm_year + 1900, TM.tm_mon + 1, TM.tm_mday, TM.tm_hour, TM.tm_min, TM.tm_sec);
//
//
//		//--------------------------------------------------
//		// ���� ����
//		//--------------------------------------------------
//		while (1)
//		{
//			errFileOpen = _tfopen_s(&fp, szFileName, _T("a"));
//			if (errFileOpen != 0)
//			{
//				//--------------------------------------------------
//				// ������ ������ ���� ������ ��õ�
//				//--------------------------------------------------
//				if (errFileOpen == ENOENT)
//				{
//					_tmkdir(m_szFilePath);
//				}
//
//				continue;
//			}
//
//
//			do
//			{
//				//--------------------------------------------------
//				// ���۷� ���� �Է�(+��������)
//				//--------------------------------------------------
//				va_start(va, szStringFormat);
//				hrLog = StringCchVPrintf(szLogBuff, _countof(szLogBuff), szStringFormat, va);
//				va_end(va);
//
//
//				//--------------------------------------------------
//				// ���۸� �ѱ� ���
//				//--------------------------------------------------
//				if (FAILED(hrLog))
//				{
//					Log(_T("LOG"), LEVEL_ERROR, _T("Log OverFlow!\n"));
//					//break;
//				}
//
//
//				//--------------------------------------------------
//				// ���Ͽ� ����
//				//--------------------------------------------------
//				_ftprintf_s(fp, _T("[%s] [%s / %s / %09ld] %s\n"), szType, szTimeInfo, m_arrLogLevel[enLogLevel], lLogCount, szLogBuff);
//
//			} while (0);
//
//
//			fclose(fp);
//			break;
//		}
//
//	} while (0);
//
//
//	// �ֿܼ� ���
//	//	_tprintf(_T("[%s] [%s] %s\n"), szType, szTimeInfo, szLogBuff);
//
//	LeaveCriticalSection(&m_csLog);
//
//	return S_OK;
//}
//
//
//
//HRESULT CLog::LogHex(const TCHAR * szType, enLOGLEVEL enLogLevel, const TCHAR * szLog, BYTE * pByte, _int iByteLen)
//{
//	return E_NOTIMPL;
//}
