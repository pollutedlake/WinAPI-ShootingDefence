#include "framework.h"
#include "CHero.h"
#include "GlobalValue.h"
#include "CBullet_Mgr.h"

CHero::CHero()
{
	m_SocketImg = NULL;

	m_CurHP = 150;
	m_MaxHP = 150;
}

CHero::~CHero()
{
}

void CHero::Init_Unit(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	m_SocketImg = Image::FromFile(_T("./Nanami/front_Idle/n001.png"));

	LoadUnitSize();

	//------ 주인공 좌표 초기화 부분
	RECT a_Crt;
	GetClientRect(a_hWnd, &a_Crt);		// Main DC의 가로 세로 사이즈를 얻어오는 함수
	m_CurPos.x = (float)(a_Crt.right / 2);
	m_CurPos.y = (float)(a_Crt.bottom / 2);
	//------ 주인공 좌표 초기화 부분

	m_R_brsh = CreateSolidBrush(RGB(255, 0, 0));		// brush 추가, pen 과 같은 방식으로

	Load_Shield();
}

void CHero::Update_Unit(float a_DeltaTime, RECT& a_RT)
{
	m_DeltaTime = a_DeltaTime;

	if (GetFocus() == NULL) {
		return;
	}
	//------ 동시키 처리 방법
	static Vector2D a_KDirVec;

	a_KDirVec.x = 0.0f;
	a_KDirVec.y = 0.0f;

	if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000) {
		a_KDirVec.y -= 1;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
		a_KDirVec.y += 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
		a_KDirVec.x += 1;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000) {
		a_KDirVec.x -= 1;
	}
	//------ 동시키 처리 방법

	if (a_KDirVec.x == 0 && a_KDirVec.y == 0) {
		// 나중에 숨쉬기 애니 상태 전환
	}
	else {
		a_KDirVec.Normalize();		// 길이가 1인 벡터
		m_CurPos = m_CurPos + a_KDirVec * (a_DeltaTime * m_Speed);
	}

	HeroLimitMove(a_RT);

	//------ 총알 발사 업데이트
	m_BLCycle = m_BLCycle + a_DeltaTime;
	if (m_AttackSpeed < m_BLCycle) {
		m_BLCycle = 100.0f;
	}

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
		if (m_AttackSpeed < m_BLCycle) {
			POINT a_NewMMXZ;
			GetCursorPos(&a_NewMMXZ);				// 현재 마우스 좌표를 얻어오는 함수
			ScreenToClient(m_hWnd, &a_NewMMXZ);		// 클라이언트 화면 좌표로 변경해 주는 함수
			Vector2D a_TargetV;
			a_TargetV.x = (float)a_NewMMXZ.x;		// 마우스의 좌표
			a_TargetV.y = (float)a_NewMMXZ.y;

			g_Bullet_Mgr.SpawnBullet(m_CurPos, a_TargetV);

			m_BLCycle = 0.0f;
		}
	}
	//------ 총알 발사 업데이트

	//------ 궁극기
	static bool isSPDown = true;
	if (g_GameState == GAME_READY) {
		m_STDelay = 0.5f;
	}
	else {
		m_STDelay -= a_DeltaTime;
		if (0.0f < m_STDelay) {
			isSPDown = false;
		}
		else {
			m_STDelay = 0.0f;
		}
	}	// else

	if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) {
		if (isSPDown == true) {
			if (0 < m_SkillCount) {
				CBullet* a_BNode = NULL;
				float Radius = 100.0f;
				float Angle = 0.0f;
				static Vector2D a_CalcStartV;
				static Vector2D a_TargetV;
				//--- 12등분 16등분
				for (Angle = 0; Angle < (2.0f * 3.141592f); Angle += (3.141592f / 12)) {
					a_CalcStartV = m_CurPos;

					a_TargetV.x = a_CalcStartV.x + (Radius * cos(Angle));
					a_TargetV.y = a_CalcStartV.y + (Radius * sin(Angle));

					g_Bullet_Mgr.SpawnBullet(a_CalcStartV, a_TargetV, CT_Unit, BT_Skill1);
				}
				m_SkillCount--;
				if (m_SkillCount < 0) {
					m_SkillCount = 0;
				}
			}	// if (0 < m_SkillCount)
			isSPDown = false;
		}	// if (isSPDown == true)
	}	// if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
	else {
		isSPDown = true;
	}
	//------ 궁극기

	ShieldUpdate();
}	// void CHero::Update_Unit(float a_DeltaTime, RECT& a_RT)

void CHero::Render_Unit(HDC a_hDC)
{
	if (m_SocketImg == NULL) {
		return;
	}

	//------ HP Bar Render
	static HBRUSH h_Old_Brush;
	h_Old_Brush = (HBRUSH)SelectObject(a_hDC, m_R_brsh);
	static float a_CalcMXX = 0.0f;
	static float a_CalcMYY = (int)(m_HalfHeight + 0.8f);
	static float a_HpBSize = 50;
	static float a_CurHpSize = 0;
	a_CalcMXX = a_HpBSize / 2.0f;
	a_CurHpSize = a_HpBSize * ((float)m_CurHP / (float)m_MaxHP);

	a_CalcMYY = m_HalfHeight;

	Rectangle(a_hDC, m_CurPos.x - a_CalcMXX, m_CurPos.y - a_CalcMYY, m_CurPos.x - a_CalcMXX + a_CurHpSize, m_CurPos.y - (a_CalcMYY + 10.0f));
	SelectObject(a_hDC, h_Old_Brush);		// 기존 브러쉬로 교체
	//------ HP Bar Render

	Graphics graphics(a_hDC);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth, m_CurPos.y - (int)(m_HalfHeight * 1.2f), (float)m_ImgSizeX, (float)m_ImgSizeY);

	ShieldRender(graphics);
}

void CHero::Destroy_Unit()
{
	if (m_SocketImg != NULL) {
		delete m_SocketImg;
		m_SocketImg = NULL;
	}

	if (m_R_brsh != NULL) {
		DeleteObject(m_R_brsh);		// brush object 제거
		m_R_brsh = NULL;
	}

	ShieldDestroy();
}

void CHero::HeroLimitMove(RECT& a_RT)
{
	static float a_CalcXXX = 0.0f;
	static float a_CalcYYY = 0.0f;

	a_CalcXXX = 15;
	if (m_CurPos.x < a_CalcXXX) {
		m_CurPos.x = a_CalcXXX;
	}

	if ((float)(a_RT.right - a_CalcXXX) < m_CurPos.x) {
		m_CurPos.x = (float)(a_RT.right - a_CalcXXX);
	}

	a_CalcYYY = 30;
	if (m_CurPos.y < a_CalcYYY) {
		m_CurPos.y = a_CalcYYY;
	}

	if ((float)(a_RT.bottom - a_CalcYYY) < m_CurPos.y) {
		m_CurPos.y = (float)(a_RT.bottom - a_CalcYYY);
	}
}

void CHero::LoadUnitSize()
{
	if (m_SocketImg == NULL) {
		return;
	}

	m_ImgSizeX = m_SocketImg->GetWidth();
	m_ImgSizeY = m_SocketImg->GetHeight();

	m_HalfWidth = m_ImgSizeX / 2;
	m_HalfHeight = m_ImgSizeY / 2;
}

void CHero::Load_Shield()
{
	if (m_Shield != NULL) {
		return;
	}

	m_Shield = Image::FromFile(_T("./RscTrunk/Shield1.png"));
}

void CHero::ShieldUpdate()
{
	//------ 쉴드 스킬 발동
	static bool isSkDown = true;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
		if (isSkDown == true) {
			// 쉴드 발동
			if (0 < m_ShieldCount) {
				if (m_SdOnTime <= 0.0f) {
					m_SdOnTime = m_SdDuration;
					m_ShieldCount--;
					if (m_ShieldCount < 0) {
						m_ShieldCount = 0;
					}
				}
			}
			// 쉴드 발동

			isSkDown = false;
		}
	}
	else {
		isSkDown = true;
	}
	//------ 쉴드 스킬 발동
}

void CHero::ShieldRender(Graphics& graphics)
{
	//------ Shield 렌더링
	if (m_Shield == NULL) {
		return;
	}

	if (0.0f < m_SdOnTime) {
		m_SdOnTime = m_SdOnTime - m_DeltaTime;
		static float a_EffTime = 0.0f;
		static float a_CalcSize = 0.0f;
		static Vector2D a_SdCen;
		if ((m_SdDuration - 0.2f) <= m_SdOnTime) {
			a_EffTime = (m_SdDuration - m_SdOnTime) / 0.2f;		// (m_SdDuration - m_SdOnTime) 변화값은 0.0f ~ 0.2f
		}
		else if (m_SdOnTime <= 0.2f) {
			a_EffTime = m_SdOnTime / 0.2f;		// (m_SdDuration - m_SdOnTime) 변화값은 0.2f ~ 0.0f
		}
		else {
			a_EffTime = 1.0f;
		}
		a_CalcSize = 500.0f * a_EffTime;
		m_SdHalfSize = a_CalcSize / 2.0f;

		graphics.DrawImage(m_Shield, Rect(m_CurPos.x - m_SdHalfSize + 1.0f, m_CurPos.y - m_SdHalfSize, a_CalcSize, a_CalcSize), 0, 0, m_Shield->GetWidth(), m_Shield->GetHeight(), UnitPixel);
	}
	//------ Shield 렌더링
}

void CHero::ShieldDestroy()
{
	if (m_Shield != NULL) {
		delete m_Shield;
		m_Shield = NULL;
	}
}

void CHero::TakeDamage(float a_Damage)
{
	// 몬스터가 주인공 공격
	m_CurHP = m_CurHP - (int)a_Damage;

	if (m_CurHP <= 0) {		// 사망처리
		g_GameState = GAME_OVER;
		m_CurHP = 0;
	}
}

void CHero::BuyHP()
{
	if (g_Hero.m_MyMoney < 100) {		// static 함수이기 때문에 g_Hero로 접근
		return;
	}

	if (g_Hero.m_CurHP < g_Hero.m_MaxHP) {
		g_Hero.m_CurHP = g_Hero.m_CurHP + 30.0f;
		if (g_Hero.m_CurHP > g_Hero.m_MaxHP) {
			g_Hero.m_CurHP = g_Hero.m_MaxHP;
		}
		g_Hero.m_MyMoney -= 100;
	}	// if (g_Hero.m_CurHP > g_Hero.m_MaxHP)
}

void CHero::BuySkill()
{
	if (g_Hero.m_MyMoney >= 150) {
		g_Hero.m_SkillCount++;
		g_Hero.m_MyMoney -= 150;
	}	// if (g_Hero.m_MyMoney >= 150)
}

void CHero::BuyShield()
{
	if (g_Hero.m_MyMoney >= 200) {
		g_Hero.m_ShieldCount++;
		g_Hero.m_MyMoney -= 200;
	}	// if (g_Hero.m_MyMoney >= 200)
}

CHero g_Hero;