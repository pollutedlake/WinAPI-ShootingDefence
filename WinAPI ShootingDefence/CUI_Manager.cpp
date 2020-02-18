#include "framework.h"
#include "CUI_Manager.h"

CUI_Manager::CUI_Manager()
{
}

CUI_Manager::~CUI_Manager()
{
}

void CUI_Manager::UIMgr_Init()
{
	m_Font_26Godic = CreateFont(26, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("¸¼Àº °íµñ"));

	m_GUIBack = Image::FromFile(_T("./RscTrunk/Tui1.png"));
	m_HP_Icon = Image::FromFile(_T("./RscTrunk/HP.png"));
}

void CUI_Manager::UIMgr_Update(HWND a_hWnd, float a_DeltaTime, void(*NextLevelFunc)(), void(*ReSetGameFunc)())
{
}

void CUI_Manager::UIMgr_Render(HDC a_MainDC, RECT& a_RT)
{
	Graphics graphics(a_MainDC);

	UserInfoPanel(a_MainDC, graphics, a_RT);
}

void CUI_Manager::UIMgr_Destroy()
{
	if (m_Font_26Godic != NULL) {
		DeleteObject(m_Font_26Godic);
		m_Font_26Godic = NULL;
	}

	if (m_GUIBack != NULL) {
		delete m_GUIBack;
		m_GUIBack = NULL;
	}
}

void CUI_Manager::UserInfoPanel(HDC a_MainDC, Graphics& graphics, RECT& a_RT)
{
}

CUI_Manager g_GUI_Mgr;