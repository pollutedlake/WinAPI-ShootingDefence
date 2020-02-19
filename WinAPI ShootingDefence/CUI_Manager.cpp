#include "framework.h"
#include "CUI_Manager.h"
#include "CHero.h"
#include "GlobalValue.h"

CUI_Manager::CUI_Manager()
{
}

CUI_Manager::~CUI_Manager()
{
}

void CUI_Manager::UIMgr_Init()
{
	DWORD a_CalcRGB = RGB(125, 179, 229);
	h_Pen = CreatePen(PS_SOLID, 1, a_CalcRGB);
	h_Brush = CreateSolidBrush(a_CalcRGB);

	m_Font_26Godic = CreateFont(26, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));
	hFont_100 = CreateFont(100, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
	hFont_50 = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("바탕"));

	m_GUIBack = Image::FromFile(_T("./RscTrunk/Tui1.png"));
	m_HP_Icon = Image::FromFile(_T("./RscTrunk/HP.png"));
}

void CUI_Manager::UIMgr_Update(HWND a_hWnd, float a_DeltaTime, void(*NextLevelFunc)(), void(*ReSetGameFunc)())
{
	m_DeltaTime = a_DeltaTime;

	static bool isSPDown = true;
	if (g_GameState == GAME_READY) {
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) {
			if (isSPDown == true) {
				g_GameState = GAME_START;

				isSPDown = false;
			}	// if (isSPDown == true)
		}	// if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
		else {
			isSPDown = true;
		}
	}
}

void CUI_Manager::UIMgr_Render(HDC a_MainDC, RECT& a_RT)
{
	Graphics graphics(a_MainDC);

	static bool blink = false;		// 깜빡임 용도
	static float a_TimeTic = 0;
	static TCHAR a_StrBuff[128];

	if (g_GameState != GAME_START) {
		//------ DC 화면 지우기
		h_OldBrush = (HBRUSH)SelectObject(a_MainDC, h_Brush);
		h_OldPen = (HPEN)SelectObject(a_MainDC, h_Pen);
		Rectangle(a_MainDC, 0, 0, a_RT.right, a_RT.bottom);
		SelectObject(a_MainDC, h_OldBrush);
		SelectObject(a_MainDC, h_OldPen);
		//------ DC 화면 지우기
	}

	if (g_GameState == GAME_READY) {
		SetBkMode(a_MainDC, TRANSPARENT);
		SetTextAlign(a_MainDC, TA_CENTER);
		m_OldFont = (HFONT)SelectObject(a_MainDC, hFont_100);
		SetTextColor(a_MainDC, RGB(128, 128, 128));
		_tcscpy_s(a_StrBuff, _T("슈팅 디펜스"));
		TextOut(a_MainDC, (a_RT.right / 2), 160, a_StrBuff, (int)_tcslen(a_StrBuff));

		SelectObject(a_MainDC, hFont_50);

		a_TimeTic = a_TimeTic + m_DeltaTime;
		if (1.0f <= a_TimeTic) {
			blink = !blink;
			a_TimeTic = 0.0f;
		}
		if (blink) {
			SetTextColor(a_MainDC, RGB(0, 99, 177));
		}
		else {
			SetTextColor(a_MainDC, RGB(0, 0, 0));
		}

		_tcscpy_s(a_StrBuff, _T("[시작하려면 [Space]키를 누르세요]"));
		TextOut(a_MainDC, (a_RT.right / 2), (a_RT.bottom * 0.7f), a_StrBuff, (int)_tcslen(a_StrBuff));

		//------ 원래대로 ...
		SelectObject(a_MainDC, m_OldFont);
		SetTextColor(a_MainDC, RGB(0, 0, 0));
		SetTextAlign(a_MainDC, TA_LEFT);
		SetBkMode(a_MainDC, OPAQUE);
		//------ 원래대로 ...
	}
	else if (g_GameState == GAME_START) {
		UserInfoPanel(a_MainDC, graphics, a_RT);
	}
	else if (g_GameState == GAME_OVER) {
		SetBkMode(a_MainDC, TRANSPARENT);		// 텍스쳐 배경을 뺀다.
		SetTextAlign(a_MainDC, TA_CENTER);		// 글씨 정렬함수 중앙 정렬
		m_OldFont = (HFONT)SelectObject(a_MainDC, hFont_100);
		SetTextColor(a_MainDC, RGB(128, 128, 128));
		TextOut(a_MainDC, (a_RT.right / 2), 110, _T("GAME OVER"), (int)_tcslen(_T("GAME OVER")));

		SelectObject(a_MainDC, hFont_50);

		SetTextColor(a_MainDC, RGB(100, 50, 34));
		wsprintf(a_StrBuff, L"Kill : %d", g_Hero.m_KillCount);
		TextOut(a_MainDC, (a_RT.right / 2) - 10, 270, a_StrBuff, (int)_tcslen(a_StrBuff));

		wsprintf(a_StrBuff, _T("난이도 : %d 단계"), g_DiffLevel);
		TextOut(a_MainDC, (a_RT.right / 2) - 10, 320, a_StrBuff, (int)_tcslen(a_StrBuff));

		a_TimeTic = a_TimeTic + m_DeltaTime;
		if (1.0f <= a_TimeTic) {
			blink = !blink;
			a_TimeTic = 0.0f;
		}
		if (blink) {
			SetTextColor(a_MainDC, RGB(0, 99, 177));
		}
		else {
			SetTextColor(a_MainDC, RGB(0, 0, 0));
		}

		TextOut(a_MainDC, (a_RT.right / 2), (a_RT.bottom * 0.7f), _T("[다시 시작하려면 [R]키를 누르세요]"), (int)_tcslen(_T("[다시 시작하려면 [R]키를 누르세요]")));

		//------ 원래대로 ...
		SelectObject(a_MainDC, m_OldFont);
		SetTextColor(a_MainDC, RGB(0, 0, 0));
		SetTextAlign(a_MainDC, TA_LEFT);
		SetBkMode(a_MainDC, OPAQUE);
		//------ 원래대로 ...
	}
}

void CUI_Manager::UIMgr_Destroy()
{
	if (h_Pen != NULL) {
		DeleteObject(h_Pen);
		h_Pen = NULL;
	}

	if (h_Brush != NULL) {
		DeleteObject(h_Brush);
		h_Brush = NULL;
	}

	if (hFont_100 != NULL) {
		DeleteObject(hFont_100);
		hFont_100 = NULL;
	}

	if (hFont_50 != NULL) {
		DeleteObject(hFont_50);
		hFont_50 = NULL;
	}

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
	if (m_GUIBack != NULL) {
		graphics.DrawImage(m_GUIBack, 5.0f, 5.0f, (float)m_GUIBack->GetWidth(), (float)m_GUIBack->GetHeight());
	}

	//------ 주인공 HP 표시와 Kill 수 표시
	m_OldFont = (HFONT)SelectObject(a_MainDC, m_Font_26Godic);
	SetTextColor(a_MainDC, RGB(187, 255, 149));
	SetTextAlign(a_MainDC, TA_LEFT);
	SetBkMode(a_MainDC, TRANSPARENT);		// 텍스쳐 배경을 뺀다.

	//------ HP Bar Render
	if (m_HP_Icon != NULL) {
		graphics.DrawImage(m_HP_Icon, 15.0f, 12.0f, (float)m_HP_Icon->GetWidth(), (float)m_HP_Icon->GetHeight());
	}

	_stprintf_s(m_StrBuff, L" : Hp %d / %d", (int)g_Hero.m_CurHP, (int)g_Hero.m_MaxHP);
	TextOut(a_MainDC, 42, 10, m_StrBuff, (int)_tcslen(m_StrBuff));
	//------ HP Bar Render

	SetTextColor(a_MainDC, RGB(255, 149, 149));
	_stprintf_s(m_StrBuff, L"Kill : %d", g_Hero.m_KillCount);
	TextOut(a_MainDC, 15, 37, m_StrBuff, (int)_tcslen(m_StrBuff));
	//------ 주인공 HP 표시와 Kill 수 표시

	SetTextColor(a_MainDC, RGB(149, 231, 255));
	_stprintf_s(m_StrBuff, L"Skill : %d Shild : %d", g_Hero.m_SkillCount, g_Hero.m_ShieldCount);
	TextOut(a_MainDC, 15, 66, m_StrBuff, (int)_tcslen(m_StrBuff));

	SetTextColor(a_MainDC, RGB(255, 226, 149));
	_stprintf_s(m_StrBuff, L"Money : %d", g_Hero.m_MyMoney);
	TextOut(a_MainDC, 15, 94, m_StrBuff, (int)_tcslen(m_StrBuff));

	SetBkMode(a_MainDC, OPAQUE);		// 텍스트 배경 원래대로...
	SetTextColor(a_MainDC, RGB(0, 0, 0));

	SetTextAlign(a_MainDC, TA_CENTER);		// 글씨 정렬함수 중앙 정렬
	_stprintf_s(m_StrBuff, _T("<%d 단계> TimeOut : %d"), g_DiffLevel, g_TimeOut);
	TextOut(a_MainDC, (a_RT.right / 2) - 10, 13, m_StrBuff, (int)_tcslen(m_StrBuff));

	SetTextAlign(a_MainDC, TA_LEFT);		// 원래대로...

	SelectObject(a_MainDC, m_OldFont);
}

CUI_Manager g_GUI_Mgr;