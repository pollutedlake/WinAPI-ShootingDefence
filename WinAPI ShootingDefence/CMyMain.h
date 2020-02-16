#pragma once
class CMyMain
{
	ULONG_PTR m_gdiplusToken = NULL;

	HWND m_hWnd = NULL;
	RECT m_Rect;

	//------ BackDC 생성용 변수
	HDC m_hBackDC = NULL;
	HBITMAP m_hBackBitmap = NULL;
	//------ BackDC 생성용 변수

	//------ 델타 타임을 얻기 위한 변수
	double m_DeltaTime;
	DWORD m_LastTime = 0;
	DWORD m_CurTime = 0;
	//------ 델타 타임을 얻기 위한 변수

public:
	CMyMain();
	~CMyMain();

public:
	void MainInit(HWND hWnd);
	void MainUpdate(HWND hWnd);
	void MainRender(HWND hWnd);
	void MainDestroy();
};

extern CMyMain g_CMyMain;		// 변수의 선언
