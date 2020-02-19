#include "framework.h"
#include "CBackGround.h"
#include "GlobalValue.h"

CBackGround::CBackGround()
{
}

CBackGround::~CBackGround()
{
}

void CBackGround::BG_Init(HWND hWnd)
{
	//------ BackImg �ε�
	HDC hdc = GetDC(hWnd);		// WM_PAINT �ۿ��� HDC ������ ���
	m_BGImgDC = CreateCompatibleDC(hdc);	// <--- MainDC�� ���纻�� �����.
	m_hTexImgBMP = (HBITMAP)LoadImage(NULL, _T("./RscTrunk/bg1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	SelectObject(m_BGImgDC, m_hTexImgBMP);		// ���纻 DC�� �ε��� HBITMAP�� �ٿ��༭ �غ��Ų��.
	ReleaseDC(hWnd, hdc);		// ���� MainDC�� ������ �ش�.

	BITMAP bm;
	GetObject(m_hTexImgBMP, sizeof(BITMAP), &bm);		// ��Ʈ�� ���� ���
	m_TexImgWidth = bm.bmWidth;			// BMP ���� ���� ������ ������...
	m_TexImgHeight = bm.bmHeight;		// BMP ���� ���� ������ ������...
	//------ BackImg �ε�
}

void CBackGround::BG_Update()
{
}

void CBackGround::BG_Render(HDC a_hdc, RECT& a_RT)
{
	if (m_hTexImgBMP != NULL) {
		StretchBlt(a_hdc, 0, 0, a_RT.right, a_RT.bottom, m_BGImgDC, 0, 0, m_TexImgWidth, m_TexImgHeight, SRCCOPY);
	}		// if (g_hBackImgDC != NULL)
}

void CBackGround::BG_Destroy()
{
	if (m_BGImgDC != NULL) {
		DeleteDC(m_BGImgDC);
		m_BGImgDC = NULL;
	}

	if (m_hTexImgBMP != NULL) {
		DeleteObject(m_hTexImgBMP);
		m_hTexImgBMP = NULL;
	}
}

CBackGround g_BGround;