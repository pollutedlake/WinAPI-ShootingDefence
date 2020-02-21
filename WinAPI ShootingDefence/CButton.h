#pragma once

#include <functional>	// function
using namespace std;	// function

#include "Vector2D.h"

//------ GDI+ Image ����� ���� ��� �߰�
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image ����� ���� ��� �߰�

class CButton
{
public:
	bool m_isBtnDown;
	Image* m_BtnUpImg;
	Image* m_BtnDownImg;

	Vector2D m_LT_Pos;		// Left Top Position
	Vector2D m_WH_Size;		// Width Height

	ColorMatrix m_DownCM;	// DownImg�� ���� ��
	function<void(void)> ClickCallback = NULL;		// <--- STL���� ������ �ִ� �Լ� ������ ����

public:
	CButton();
	~CButton();

	void SetBtnRect(float a_LeftPos, float a_TopPos, float a_WSize = 0.0f, float a_HSize = 0.0f);

	void Load_Rsc(const TCHAR* a_BtnUpStr, const TCHAR* a_BtnDownStr = NULL);
	void BtnRender(HDC a_hDC);
	void Destroy();

	void LBtnDown(Vector2D a_MosPos);
	bool LBtnUp();
	void OnClick_AddListener(function<void(void)> Callback = NULL);		// PointerUp
};

