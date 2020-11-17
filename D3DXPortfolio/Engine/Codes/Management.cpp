#include "..\Headers\Management.h"

USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
	: m_pFrame_Manager(CFrame_Manager::Get_Instance())
	, m_pDevice_Manager(CDevice_Manager::Get_Instance())
	, m_pTimer_Manager(CTimer_Manager::Get_Instance())
{
	Safe_AddRef(m_pFrame_Manager);
	Safe_AddRef(m_pDevice_Manager);
	Safe_AddRef(m_pTimer_Manager);
}



void CManagement::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pTimer_Manager);
	Safe_Release(m_pDevice_Manager);
	Safe_Release(m_pFrame_Manager);
}



_uint CManagement::Release_Engine()
{
	_int iRefCnt = 0;
	if (iRefCnt = CManagement::Get_Instance()->Destroy_Instance())
	{
		_LOG(LEVEL_SYSTEM, _T("Failed To Destroy CManagement"));
		return iRefCnt;
	}

	


	return iRefCnt;
}



_int CManagement::Update_Engine(void)
{
	_float fDeltaTime = 0.f;

	if (nullptr == m_pDevice_Manager)
		return RETURNCODE::RETCODE_ERR;


	//--------------------------------------------------
	// Exit
	//--------------------------------------------------
	if (m_bWaitDown)
		return RETURNCODE::RETCODE_EXIT;


	//--------------------------------------------------
	// Timer
	//--------------------------------------------------
	if (m_iUpdate_Result = m_pTimer_Manager->Update_TimeManager())
		return RETURNCODE::RETCODE_ERR;

	if (FAILED(m_pTimer_Manager->Get_DeltaTime(m_strAppTimerTag, fDeltaTime)))
		return RETURNCODE::RETCODE_ERR;


	//--------------------------------------------------
	// Update
	//--------------------------------------------------


	return _int();
}



HRESULT CManagement::Render_Engine(void)
{
	//--------------------------------------------------
	// 씬 변경으로인한 Frame Skip
	//--------------------------------------------------
	if (RETURNCODE::RETCODE_TRAVEL == m_iUpdate_Result)
	{
		m_iUpdate_Result = RETURNCODE::RETCODE_NONE;
		return S_OK;
	}

	if (nullptr == m_pRenderer)
		return E_FAIL;

	if (FAILED(m_pRenderer->Render_Renderer()))
		return E_FAIL;


	return S_OK;
}



LPDIRECT3DDEVICE9 CManagement::Get_Device() const
{
	if (nullptr == m_pDevice_Manager)
		return nullptr;

	return m_pDevice_Manager->Get_Device();
}



LPD3DXSPRITE CManagement::Get_Sprite() const
{
	if (nullptr == m_pDevice_Manager)
		return nullptr;

	return m_pDevice_Manager->Get_Sprite();
}



LPD3DXFONT CManagement::Get_Font() const
{
	if (nullptr == m_pDevice_Manager)
		return nullptr;

	return m_pDevice_Manager->Get_Font();
}



_bool CManagement::Lock_FrameManager()
{
	if (nullptr == m_pFrame_Manager)
		return false;

	return m_pFrame_Manager->Lock_FrameManager();
}



void CManagement::Render_FrameManager()
{
	if (nullptr == m_pFrame_Manager)
		return;

	m_pFrame_Manager->Render_FrameManager();
}



HRESULT CManagement::Add_Timer(const wstring & strTimerTag, _bool bStart)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Add_Timer(strTimerTag, bStart);
}



HRESULT CManagement::Get_DeltaTime(const wstring & strTimerTag, _float & fDeltaTime)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Get_DeltaTime(strTimerTag, fDeltaTime);
}



HRESULT CManagement::Pause(const wstring & strTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Pause(strTimerTag);
}



HRESULT CManagement::Resume(const wstring & strTimerTag)
{
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	return m_pTimer_Manager->Resume(strTimerTag);
}



HRESULT CManagement::Setup_Engine(HWND hWnd, _uint iFramePerSec, _uint iWinCX, _uint iWinCY, CDevice_Manager::DISPLAY_MODE eDisplayMode, _uint iSceneCnt, const wstring & strAppTimerTag)
{
	if (nullptr == m_pFrame_Manager		||
		nullptr == m_pDevice_Manager	||
		nullptr == m_pTimer_Manager)
		return E_FAIL;

	if (FAILED(m_pFrame_Manager->Setup_FrameManager(hWnd, iFramePerSec)))
		return E_FAIL;

	if (FAILED(m_pDevice_Manager->Setup_GraphicDevice(hWnd, iWinCX, iWinCY, eDisplayMode)))
		return E_FAIL;

	if (FAILED(m_pTimer_Manager->Setup_TimerManager()))
		return E_FAIL;

	m_strAppTimerTag = strAppTimerTag;
	if (FAILED(m_pTimer_Manager->Add_Timer(strAppTimerTag, true)))
		return E_FAIL;

	m_pRenderer = CRenderer::Create(m_pDevice_Manager->Get_Device(), m_pDevice_Manager->Get_Sprite(), m_pDevice_Manager->Get_Font(), hWnd);
	if (nullptr == m_pRenderer)
		return E_FAIL;

	// comp, obj

	return S_OK;
}



HRESULT CManagement::Add_RendererList(CRenderer::enRENDER_TYPE eType, CGameObject * pObject)
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Add_RendererList(eType, pObject);
}
