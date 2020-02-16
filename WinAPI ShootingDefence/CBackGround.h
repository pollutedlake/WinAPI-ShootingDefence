#pragma once
class CBackGround
{
	HDC m_BGImgDC;
	HBITMAP m_hTexImgBMP;		// 로딩된 BMP 파일의 핸들
	int m_TexImgWidth;			// 이미지의 가로 사이즈
	int m_TexImgHeight;			// 이미지의 세로 사이즈

public:
	CBackGround();
	~CBackGround();

public:
	void BG_Init(HWND hWnd);					// 초기화 함수
	void BG_Update();							// 게임의 연산 담당 부분
	void BG_Render(HDC a_hdc, RECT& a_RT);		// 게임의 그리기 부분
	void BG_Destroy();							// 종료 처리 부분
};

extern CBackGround g_BGround;