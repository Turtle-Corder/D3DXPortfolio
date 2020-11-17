#pragma once
#ifndef __MANAGEMENT_H__
#define __MANAGEMENT_H__

#include "Frame_Manager.h"
#include "Device_Manager.h"
#include "Timer_Manager.h"
#include "Renderer.h"

BEGIN(Engine)

class CManagement final : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	CManagement();
	virtual ~CManagement() = default;

	//----------------------------------------------------------------------------------------------------
	// Function
	//----------------------------------------------------------------------------------------------------
public:
	HRESULT Setup_Engine(HWND hWnd, _uint iFramePerSec, _uint iWinCX, _uint iWinCY, CDevice_Manager::DISPLAY_MODE eDisplayMode, _uint iSceneCnt, const wstring& strAppTimerTag);
	virtual void Free() override;
	static _uint Release_Engine();

	_int	Update_Engine();
	HRESULT Render_Engine();


	//--------------------------------------------------
	// 장치
	//--------------------------------------------------
	LPDIRECT3DDEVICE9	Get_Device()	const;
	LPD3DXSPRITE		Get_Sprite()	const;
	LPD3DXFONT			Get_Font()		const;


	//--------------------------------------------------
	// 프레임
	//--------------------------------------------------
	_bool Lock_FrameManager();
	void Render_FrameManager();


	//--------------------------------------------------
	// 타이머
	//--------------------------------------------------
	HRESULT Add_Timer(const wstring& strTimerTag, _bool bStart = true);
	HRESULT Get_DeltaTime(const wstring& strTimerTag, _float& fDeltaTime);

	HRESULT Pause(const wstring& strTimerTag);
	HRESULT Resume(const wstring& strTimerTag);


	//--------------------------------------------------
	// 렌더러
	//--------------------------------------------------
	HRESULT Add_RendererList(CRenderer::enRENDER_TYPE eType, CGameObject* pObject);


	//--------------------------------------------------
	// 씬
	//--------------------------------------------------
	HRESULT Change_CurrentScene(_uint _iSceneID, CScene* pCurrentScene);
	_int Get_CurrentSceneID();
	HRESULT Set_SceneEvent(_int _iEventNo);


	//--------------------------------------------------
	// 오브젝트
	//--------------------------------------------------
	CGameObject* Get_GameObject(_int _iSceneID, const wstring& _strLayerTag, _uint _iIndex = 0);
	CComponent* Get_Component(_int _iSceneID, const wstring& _strLayerTag, const wstring& _strComponentTag, _uint _iIndex = 0);
	HRESULT Add_GameObject_Prototype(_int _iSceneID, const wstring& _strPrototypeTag, CGameObject* _pPrototype);
	HRESULT Add_GameObject_InLayer(_int _iFromSceneID, const wstring& _strPrototypeTag, _int _iToSceneID, const wstring& _strLayerTag, void* _pArg = nullptr);
	HRESULT Add_GameObject_InLayer(CGameObject** _pOut, _int _iFromSceneID, const wstring& _strPrototypeTag, _int _iToSceneID, const wstring& _strLayerTag, void* _pArg = nullptr);


	//--------------------------------------------------
	// 컴포넌트
	//--------------------------------------------------
	HRESULT Add_Component_Prototype(_int _iSceneID, const wstring& _strPrototypeTag, CComponent* _pPrototype);
	CComponent* Clone_Component(_int _iSceneID, const wstring& _strPrototypeTag, void* _pArg = nullptr);


	//--------------------------------------------------
	// 키 입력
	//--------------------------------------------------
	_bool Key_Pressing(_int _key);
	_bool Key_Down(_int _key);
	_bool Key_Up(_int _key);





	//----------------------------------------------------------------------------------------------------
	// 변수
	//----------------------------------------------------------------------------------------------------
private:
	CDevice_Manager*	m_pDevice_Manager = nullptr;
	CFrame_Manager*		m_pFrame_Manager = nullptr;
	CTimer_Manager*		m_pTimer_Manager = nullptr;

	CRenderer*			m_pRenderer = nullptr;

	wstring				m_strAppTimerTag;
	_bool				m_bWaitDown = false;
	_int				m_iUpdate_Result = 0;
};

END

#endif // !__MANAGEMENT_H__
