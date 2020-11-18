#include "Frame.h"
#include "..\Headers\Frame_Manager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CFrame_Manager)

CFrame_Manager::CFrame_Manager()
	: m_iFPS(0), m_szFPS(_T("")), m_dSecElapseTime(0.0)
{
}



HRESULT CFrame_Manager::Setup_FrameManager(HWND hWnd)
{
	if (nullptr == hWnd)
		return E_FAIL;

	m_hWnd = hWnd;

	return S_OK;
}



HRESULT CFrame_Manager::Add_Frame(const _tchar * pFrameTag, const _double & dFramePerSecond)
{
	CFrame* pInstance = Find_Frame(pFrameTag);
	if (pInstance != pInstance)
		return E_FAIL;

	pInstance = CFrame::Create(dFramePerSecond);
	NULL_CHECK_RETURN(pInstance, E_FAIL);

	m_mapFrames.emplace(pFrameTag, pInstance);
	return S_OK;
}



_bool CFrame_Manager::Update_Frame(const _tchar * pFrameTag, const _double & dDeltaTime)
{
	CFrame* pInstance = Find_Frame(pFrameTag);
	NULL_CHECK_RETURN(pInstance, E_FAIL);

	return pInstance->Update_Frame(dDeltaTime);
}



CFrame * CFrame_Manager::Find_Frame(const _tchar * pFrameTag)
{
	auto iter = find_if(m_mapFrames.begin(), m_mapFrames.end(), CTagFinder(pFrameTag));
	if (iter == m_mapFrames.end())
		return nullptr;

	return iter->second;
}



//void CFrame_Manager::Render_FrameManager()
//{
//	++m_iFPS;
//	if (m_dSecElapseTime > 1.0)
//	{
//		StringCchPrintf(m_szFPS, _countof(m_szFPS), _T("FPS:%d"), m_iFPS);
//		m_dSecElapseTime -= 1.0;
//		m_iFPS = 0;
//
//		SetWindowText(m_hWnd, m_szFPS);
//	}
//}



void CFrame_Manager::Free()
{
	for_each(m_mapFrames.begin(), m_mapFrames.end(), CDeleteMap());
	m_mapFrames.clear();
}
