#include "framework.h"
#include "CHero.h"
#include "CBullet_Mgr.h"

CHero::CHero()
{
}

CHero::~CHero()
{
}

void CHero::Init_Unit(HWND a_hWnd)
{
	m_hWnd = a_hWnd;

	m_SocketImg = Image::FromFile(_T("./Nanami/front_Idle/n001.png"));

	LoadUnitSize();

	//------ ���ΰ� ��ǥ �ʱ�ȭ �κ�
	RECT a_Crt;
	GetClientRect(a_hWnd, &a_Crt);		// Main DC�� ���� ���� ����� ������ �Լ�
	m_CurPos.x = (float)(a_Crt.right / 2);
	m_CurPos.y = (float)(a_Crt.bottom / 2);
	//------ ���ΰ� ��ǥ �ʱ�ȭ �κ�
}

void CHero::Update_Unit(float a_DeltaTime, RECT& a_RT)
{
	m_DeltaTime = a_DeltaTime;

	if (GetFocus() == NULL) {
		return;
	}
	//------ ����Ű ó�� ���
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
	//------ ����Ű ó�� ���

	if (a_KDirVec.x == 0 && a_KDirVec.y == 0) {
		// ���߿� ������ �ִ� ���� ��ȯ
	}
	else {
		a_KDirVec.Normalize();		// ���̰� 1�� ����
		m_CurPos = m_CurPos + a_KDirVec * (a_DeltaTime * m_Speed);
	}

	HeroLimitMove(a_RT);

	//------ �Ѿ� �߻� ������Ʈ
	m_BLCycle = m_BLCycle + a_DeltaTime;
	if (m_AttackSpeed < m_BLCycle) {
		m_BLCycle = 100.0f;
	}

	if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
		if (m_AttackSpeed < m_BLCycle) {
			POINT a_NewMMXZ;
			GetCursorPos(&a_NewMMXZ);				// ���� ���콺 ��ǥ�� ������ �Լ�
			ScreenToClient(m_hWnd, &a_NewMMXZ);		// Ŭ���̾�Ʈ ȭ�� ��ǥ�� ������ �ִ� �Լ�
			Vector2D a_TargetV;
			a_TargetV.x = (float)a_NewMMXZ.x;		// ���콺�� ��ǥ
			a_TargetV.y = (float)a_NewMMXZ.y;

			g_Bullet_Mgr.SpawnBullet(m_CurPos, a_TargetV);

			m_BLCycle = 0.0f;
		}
	}
	//------ �Ѿ� �߻� ������Ʈ

	//------ �ñر�
	static bool isSPDown = true;
	if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) {
		if (isSPDown == true) {
			CBullet* a_BNode = NULL;
			float Radius = 100.0f;
			float Angle = 0.0f;
			static Vector2D a_CalcStartV;
			static Vector2D a_TargetV;
			//--- 12��� 16���
			for (Angle = 0; Angle < (2.0f * 3.141592f); Angle += (3.141592f / 12)) {
				a_CalcStartV = m_CurPos;

				a_TargetV.x = a_CalcStartV.x + (Radius * cos(Angle));
				a_TargetV.y = a_CalcStartV.y + (Radius * sin(Angle));

				g_Bullet_Mgr.SpawnBullet(a_CalcStartV, a_TargetV);
			}

			isSPDown = false;
		}	// if (isSPDown == true)
	}	// if ((GetAsyncKeyState(VK_SPACE) & 0x8000))
	else {
		isSPDown = true;
	}
	//------ �ñر�
}	// void CHero::Update_Unit(float a_DeltaTime, RECT& a_RT)

void CHero::Render_Unit(HDC a_hdc)
{
	if (m_SocketImg == NULL) {
		return;
	}

	Graphics graphics(a_hdc);
	graphics.DrawImage(m_SocketImg, m_CurPos.x - m_HalfWidth, m_CurPos.y - (int)(m_HalfHeight * 1.2f), (float)m_ImgSizeX, (float)m_ImgSizeY);
}

void CHero::Destroy_Unit()
{
	if (m_SocketImg != NULL) {
		delete m_SocketImg;
		m_SocketImg = NULL;
	}
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

CHero g_Hero;