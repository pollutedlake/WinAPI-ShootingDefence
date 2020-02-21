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

	StoreInit();
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
	}	// if (g_GameState == GAME_READY)
	else if (g_GameState == NEXT_LEVEL) {
		if ((GetAsyncKeyState('N') & 0x8000)) {
			if (isSPDown == true) {
				if (NextLevelFunc != NULL) {
					NextLevelFunc();		// 다음단계 진행
				}

				isSPDown = false;
			}	// if (isSPDown == true)
		}	// else if (VK_Key == 'N')
		else {
			isSPDown = true;
		}

		//------ Mouse LButtonDown 처리
		static bool isMsLDown = true;
		if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
			if (isMsLDown == true) {
				LBtnDown(a_hWnd);
				isMsLDown = false;
			}	// if (isMsLDown == true)
		}
		else {
			if (isMsLDown == false) {
				LBtnUp();
				isMsLDown = true;
			}	// if (isMsLDown == false)
		}
		//------ Mouse LButtonDown 처리
	}
	else if (g_GameState == GAME_OVER) {
		if ((GetAsyncKeyState('R') & 0x8000)) {
			if (isSPDown == true) {
				if (ReSetGameFunc != NULL) {
					ReSetGameFunc();		// 다음단계 진행
				}

				isSPDown = false;
			}	// if (isSPDown == true)
		}	// else if (VK_Key == 'R')
		else {
			isSPDown = true;
		}
	}	// else if (g_GameState == GAME_OVER)
}	// void CUI_Manager::UIMgr_Update(HWND a_hWnd, float a_DeltaTime, void(*NextLevelFunc)(), void(*ReSetGameFunc)())

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
	else if (g_GameState == NEXT_LEVEL) {
		SetBkMode(a_MainDC, TRANSPARENT);		// 텍스쳐 배경을 뺀다.
		SetTextAlign(a_MainDC, TA_CENTER);		// 글씨 정렬함수 중앙 정렬
		m_OldFont = (HFONT)SelectObject(a_MainDC, hFont_100);
		SetTextColor(a_MainDC, RGB(128, 128, 128));
		_stprintf_s(a_StrBuff, _T("%d 단계 Clear"), g_DiffLevel - 1);
		TextOut(a_MainDC, (a_RT.right / 2), 110, a_StrBuff, (int)_tcslen(a_StrBuff));

		SelectObject(a_MainDC, hFont_50);

		SetTextColor(a_MainDC, RGB(100, 50, 34));
		wsprintf(a_StrBuff, L"Kill : %d", g_Hero.m_KillCount);
		TextOut(a_MainDC, (a_RT.right / 2) - 10, 270, a_StrBuff, (int)_tcslen(a_StrBuff));

		wsprintf(a_StrBuff, _T("다음단계 : %d 단계"), g_DiffLevel);
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

		_tcscpy_s(a_StrBuff, _T("[다음 단계 시작은 [N]키를 누르세요]"));
		TextOut(a_MainDC, (a_RT.right / 2), (a_RT.bottom * 0.7f), a_StrBuff, (int)_tcslen(a_StrBuff));

		//------ 원래대로 ...
		SelectObject(a_MainDC, m_OldFont);
		SetTextColor(a_MainDC, RGB(0, 0, 0));
		SetTextAlign(a_MainDC, TA_LEFT);
		SetBkMode(a_MainDC, OPAQUE);
		//------ 원래대로 ...

		StoreRender(a_MainDC, graphics, a_RT);
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

	StoreDestroy();
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

void CUI_Manager::StoreInit()
{
	//------ Shop 초기화
	m_ShopOnOff = true;
	m_ShopBase = NULL;
	m_AlphaCM = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.5f, 0.0f,
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	//------ Shop 초기화

	//------ Shop Image 로딩
	m_ShopBase = Image::FromFile(_T("./RscTrunk/WhiteGB.png"));

	m_HumanF = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));

	m_CloseBtn.Load_Rsc(_T("./RscTrunk/btn_close_f.png"), _T("./RscTrunk/btn_close_n.png"));
	// OnClick_AddListener
	// 이벤트 함수 등록... 람다식으로...
	CButton* a_RefBtn = &m_CloseBtn;
	m_CloseBtn.OnClick_AddListener([this, a_RefBtn]() {
		m_ShopOnOff = false;
		});

	//------ [0]
	m_ShopBG[0] = Image::FromFile(_T("./RscTrunk/itemshop_frame_n.png"));
	m_Image[0] = Image::FromFile(_T("./RscTrunk/item_life.png"));
	m_CoinImg[0] = Image::FromFile(_T("./RscTrunk/itemshop_coin.png"));
	m_AddBtn[0].Load_Rsc(_T("./RscTrunk/itemshop_btn_green_f.png"), _T("./RscTrunk/itemshop_btn_green_n.png"));
	if (m_AddBtn[0].m_BtnUpImg != NULL) {
		m_AddBtn[0].m_WH_Size.x = ((float)m_AddBtn[0].m_BtnUpImg->GetWidth() / 1.7f);
		m_AddBtn[0].m_WH_Size.y = m_AddBtn[0].m_BtnUpImg->GetHeight() / 2;
	}
	m_AddBtn[0].OnClick_AddListener(CHero::BuyHP);
	//------ [0]

	//------ [1]
	m_ShopBG[1] = Image::FromFile(_T("./RscTrunk/itemshop_frame_n.png"));
	m_Image[1] = Image::FromFile(_T("./RscTrunk/item_bomb.png"));
	m_CoinImg[1] = Image::FromFile(_T(".\\RscTrunk\\itemshop_coin.png"));

	m_AddBtn[1].Load_Rsc(_T(".\\RscTrunk\\itemshop_btn_green_f.png"), _T(".\\RscTrunk\\itemshop_btn_green_n.png"));
	if (m_AddBtn[1].m_BtnUpImg != NULL)
	{
		m_AddBtn[1].m_WH_Size.x = ((float)m_AddBtn[1].m_BtnUpImg->GetWidth() / 1.7f);
		m_AddBtn[1].m_WH_Size.y = m_AddBtn[1].m_BtnUpImg->GetHeight() / 2;
	}
	m_AddBtn[1].OnClick_AddListener(CHero::BuySkill);
	//------ [1]

	//------ [2]
	m_ShopBG[2] = Image::FromFile(_T(".\\RscTrunk\\itemshop_frame_n.png"));
	m_Image[2] = Image::FromFile(_T(".\\RscTrunk\\item_shield.png"));
	m_CoinImg[2] = Image::FromFile(_T(".\\RscTrunk\\itemshop_coin.png"));

	m_AddBtn[2].Load_Rsc(_T(".\\RscTrunk\\itemshop_btn_green_f.png"), _T(".\\RscTrunk\\itemshop_btn_green_n.png"));
	if (m_AddBtn[2].m_BtnUpImg != NULL)
	{
		m_AddBtn[2].m_WH_Size.x = ((float)m_AddBtn[2].m_BtnUpImg->GetWidth() / 1.7f);
		m_AddBtn[2].m_WH_Size.y = m_AddBtn[2].m_BtnUpImg->GetHeight() / 2;
	}
	m_AddBtn[2].OnClick_AddListener(CHero::BuyShield);
	//------ [2]
	//------ Shop Image 로딩
}

void CUI_Manager::StoreRender(HDC a_MainDC, Graphics& graphics, RECT& a_RT)
{
	if (m_ShopOnOff == false) {
		return;
	}

	if (m_ShopBase != NULL) {
		ImageAttributes AlphaAB;
		AlphaAB.SetColorMatrix(&m_AlphaCM);
		graphics.DrawImage(m_ShopBase, Rect(0.0f, 0.0f, a_RT.right, a_RT.bottom), 0, 0, m_ShopBase->GetWidth(), m_ShopBase->GetHeight(), UnitPixel, &AlphaAB);
	}

	m_OldFont = (HFONT)SelectObject(a_MainDC, m_Font_26Godic);

	SetTextColor(a_MainDC, RGB(186, 255, 149));
	// SetTextAlign(a_MainDC, TA_CENTER);		// 글씨 정렬함수 중앙정렬

	UserInfoPanel(a_MainDC, graphics, a_RT);	// 유저 정보 렌더링

	SetBkMode(a_MainDC, TRANSPARENT);			// 텍스쳐 배경을 뺀다.

	static float m_SpXX;
	static float m_SpYY;
	static float m_Paddle = 50.0f;
	static float m_Dx = 200.0f;
	static float m_Dy = 350.0f;
	m_SpXX = a_RT.right / 2 - 350.0f;
	m_SpYY = a_RT.bottom / 4 - 50.0f;

	SetTextColor(a_MainDC, RGB(255, 255, 255));

	static float a_CalcSpXX = 0.0f;
	static float a_CalcSpYY = 0.0f;

	static float a_ItmSpXX = 0.0f;
	static float a_ItmSpYY = 0.0f;
	
	static float a_BtnSpXX = 0.0f;
	static float a_BtnSpYY = 0.0f;

	for (int i = 0; i < 3; i++) {
		a_CalcSpXX = m_SpXX + (i * (m_Dx + m_Paddle));
		a_CalcSpYY = m_SpYY;

		graphics.DrawImage(m_ShopBG[i], Rect(a_CalcSpXX, a_CalcSpYY, m_Dx, m_Dy), 0, 0, m_ShopBG[i]->GetWidth(), m_ShopBG[i]->GetHeight(), UnitPixel);

		a_ItmSpXX = a_CalcSpXX + (m_Dx / 2) - (m_Image[i]->GetWidth() / 4);
		a_ItmSpYY = a_CalcSpYY + 30;

		graphics.DrawImage(m_Image[i], Rect(a_ItmSpXX, a_ItmSpYY, (m_Image[i]->GetWidth() / 2), (m_Image[i]->GetHeight() / 2)), 0, 0, m_Image[i]->GetWidth(), m_Image[i]->GetHeight(), UnitPixel);

		//------ 설명
		if (i == 0) {
			TextOutA(a_MainDC, a_CalcSpXX + 70.0f, a_CalcSpYY + 110.0f, "HP+30", (int)strlen("HP+30"));
		}
		else if (i == 1) {
			TextOutA(a_MainDC, a_CalcSpXX + 70.0f, a_CalcSpYY + 110.0f, "Skill+1", (int)strlen("Skill+1"));
		}
		else if (i == 2) {
			TextOutA(a_MainDC, a_CalcSpXX + 70.0f, a_CalcSpYY + 110.0f, "Shield+1", (int)strlen("Shield+1"));
		}
		//------ 설명

		//------ 가격
		graphics.DrawImage(m_CoinImg[i], Rect(a_CalcSpXX + 30.0f, a_CalcSpYY + 165.0f, (m_CoinImg[i]->GetWidth() * 0.9f), (m_CoinImg[i]->GetHeight() * 0.9f)), 0, 0, m_CoinImg[i]->GetWidth(), m_CoinImg[i]->GetHeight(), UnitPixel);

		SelectObject(a_MainDC, m_HumanF);
		if (i == 0) {
			TextOutA(a_MainDC, a_CalcSpXX + 100.0f, a_CalcSpYY + 160.0f, "100", (int)strlen("100"));
		}
		else if (i == 1) {
			TextOutA(a_MainDC, a_CalcSpXX + 100.0f, a_CalcSpYY + 160.0f, "150", (int)strlen("150"));
		}
		else if (i == 2) {
			TextOutA(a_MainDC, a_CalcSpXX + 100.0f, a_CalcSpYY + 160.0f, "200", (int)strlen("200"));
		}
		SelectObject(a_MainDC, m_Font_26Godic);
		//------ 가격
		
		//------ 버튼 그리기
		if (m_AddBtn[i].m_BtnUpImg != NULL) {
			a_BtnSpXX = a_CalcSpXX + (m_Dx / 2) - ((m_AddBtn[i].m_BtnUpImg->GetWidth() / 1.72f) / 2.0);
			a_BtnSpYY = a_CalcSpYY + (m_Dy - 100);

			m_AddBtn[i].SetBtnRect(a_BtnSpXX, a_BtnSpYY);		// 버튼 위치 다시 대입
			m_AddBtn[i].BtnRender(a_MainDC);

			TextOutA(a_MainDC, a_BtnSpXX + 53, a_BtnSpYY + 16, "ADD+", (int)strlen("ADD+"));
		}
		//------ 버튼 그리기
	}	// for (int i = 0; i < 3; i++)

	m_CloseBtn.SetBtnRect(a_RT.right - 100, 15);	// 버튼 위치 다시 대입
	m_CloseBtn.BtnRender(a_MainDC);

	SetTextColor(a_MainDC, RGB(0, 0, 0));
	SetBkMode(a_MainDC, OPAQUE);		// 텍스트 배경 원래대로...
	SelectObject(a_MainDC, m_OldFont);
}

void CUI_Manager::StoreDestroy()
{
	//------ Shop 리소스 제거
	if (m_ShopBase != NULL) {
		delete m_ShopBase;
		m_ShopBase;
	}

	for (int aa = 0; aa < 3; aa++) {
		m_AddBtn[aa].Destroy();

		if (m_ShopBG[aa] != NULL) {
			delete m_ShopBG[aa];
			m_ShopBG[aa] = NULL;
		}

		if (m_Image[aa] != NULL) {
			delete m_Image[aa];
			m_Image[aa] = NULL;
		}

		if (m_CoinImg[aa] != NULL) {
			delete m_CoinImg[aa];
			m_CoinImg[aa] = NULL;
		}
	}

	if (m_HumanF != NULL) {
		DeleteObject(m_HumanF);
		m_HumanF = NULL;
	}
	//------ Shop 리소스 제거
}

void CUI_Manager::LBtnDown(HWND a_hWnd)
{
	if (m_ShopOnOff == false) {
		return;
	}

	POINT a_NewMMXZ;
	GetCursorPos(&a_NewMMXZ);		// 현재 마우스 좌표를 얻어오는 함수
	ScreenToClient(a_hWnd, &a_NewMMXZ);		// 클라이언트 화면 좌표로 변경해 주는 함수
	Vector2D a_TargetV;
	a_TargetV.x = (float)a_NewMMXZ.x;		// 마우스의 좌표
	a_TargetV.y = (float)a_NewMMXZ.y;

	static RECT a_cRT;
	GetClientRect(a_hWnd, &a_cRT);
	m_CloseBtn.SetBtnRect(a_cRT.right - 100, 15);		// 버튼 위치 다시 대입
	m_CloseBtn.LBtnDown(a_TargetV);

	static float a_CalcSpXX = 0.0f;
	static float a_CalcSpYY = 0.0f;
	
	static float a_BtnSpXX = 0.0f;
	static float a_BtnSpYY = 0.0f;

	float m_SpXX;
	float m_SpYY;
	float m_Paddle = 50.0f;
	float m_Dx = 200.0f;
	float m_Dy = 350.0f;
	m_SpXX = a_cRT.right / 2 - 350.0f;
	m_SpYY = a_cRT.bottom / 4 - 50.0f;

	for (int i = 0; i < 3; i++) {
		a_CalcSpXX = m_SpXX + (i * (m_Dx + m_Paddle));
		a_CalcSpYY = m_SpYY;

		a_BtnSpXX = a_CalcSpXX + (m_Dx / 2) - ((m_AddBtn[i].m_BtnUpImg->GetWidth() / 1.72f) / 2.0f);
		a_BtnSpYY = a_CalcSpYY + (m_Dy - 100);

		m_AddBtn[i].SetBtnRect(a_BtnSpXX, a_BtnSpYY);	// 버튼 위치 다시 대입
		m_AddBtn[i].LBtnDown(a_TargetV);
	}
}

void CUI_Manager::LBtnUp()
{
	m_CloseBtn.LBtnUp();
	for (int i = 0; i < 3; i++) {
		m_AddBtn[i].LBtnUp();
	}
}

CUI_Manager g_GUI_Mgr;