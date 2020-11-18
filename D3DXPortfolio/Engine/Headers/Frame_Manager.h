#pragma once
#ifndef __FRAME_MANAGER_H__
#define __FRAME_MANAGER_H__

#include "Base.h"

BEGIN(Engine)

class CFrame;
class CFrame_Manager final : public CBase
{
	DECLARE_SINGLETON(CFrame_Manager)

private:
	CFrame_Manager();
	virtual ~CFrame_Manager() = default;

public:
	HRESULT Setup_FrameManager(HWND hWnd);

	HRESULT Add_Frame(const _tchar* pFrameTag, const _double& dFramePerSecond);
	_bool Update_Frame(const _tchar* pFrameTag, const _double& dDeltaTime);

	//void Render_FrameManager();


private:
	CFrame* Find_Frame(const _tchar* pFrameTag);


public:
	virtual void Free() override;





private:
	typedef unordered_map<const _tchar*, CFrame*> FRAMES;
	FRAMES m_mapFrames;

	//--------------------------------------------------
	// 출력용 / 디버깅용으로 남겨두자
	//--------------------------------------------------
	HWND	m_hWnd = NULL;
	int		m_iFPS;
	TCHAR	m_szFPS[32];

	// 1초를 확인 하기 위한 변수
	double m_dSecElapseTime;
};

END

#endif // !__FRAME_MANAGER_H__
