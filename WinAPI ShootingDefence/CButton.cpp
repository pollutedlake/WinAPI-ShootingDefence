#include "CButton.h"

CButton::CButton()
{
	m_isBtnDown = false;
	m_BtnUpImg = NULL;
	m_BtnDownImg = NULL;

	m_LT_Pos.x = 100.0f;		// Left Top Postion
	m_LT_Pos.y = 100.0f;
	m_WH_Size.x = 10.0f;		// Width Height
	m_WH_Size.y = 10.0f;

	m_DownCM = { 0.72f,0.0f,0.0f,0.0f,0.0f,
				0.0f, 0.64f, 0.0f,0.0f,0.0f,
				0.0f,0.0f,0.48f,0.0f,0.0f,
				0.0f,0.0f,0.0f,1.0f,0.0f,
				0.0f,0.0f,0.0f,0.0f,1.0f };
}

CButton::~CButton()
{
}

void CButton::SetBtnRect(float a_LeftPos, float a_TopPos, float a_WSize, float a_HSize)
{
	m_LT_Pos.x = a_LeftPos;
	m_LT_Pos.y = a_TopPos;
	if (0.0f < a_WSize && 0.0f < a_HSize) {
		m_WH_Size.x = a_WSize;
		m_WH_Size.y = a_HSize;
	}
}

void CButton::Load_Rsc(const TCHAR* a_BtnUpStr, const TCHAR* a_BtnDownStr)
{
	m_isBtnDown = false;

	m_BtnUpImg = Image::FromFile(a_BtnUpStr);
	if (m_BtnUpImg != NULL) {
		m_WH_Size.x = m_BtnUpImg->GetWidth() / 2;
		m_WH_Size.y = m_BtnUpImg->GetHeight() / 2;
	}

	if (a_BtnDownStr == NULL) {
		return;
	}

	m_BtnDownImg = Image::FromFile(a_BtnDownStr);
}

void CButton::BtnRender(HDC a_hDC)
{
	Graphics graphics(a_hDC);
	if (m_isBtnDown == true) {
		if (m_BtnDownImg != NULL) {
			graphics.DrawImage(m_BtnDownImg, Rect(m_LT_Pos.x, m_LT_Pos.y, m_WH_Size.x, m_WH_Size.y), 0, 0, m_BtnDownImg->GetWidth(), m_BtnDownImg->GetHeight(), UnitPixel);
		}
		else {
			if (m_BtnUpImg != NULL) {
				ImageAttributes a_DownAB;
				a_DownAB.SetColorMatrix(&m_DownCM);
				graphics.DrawImage(m_BtnUpImg, Rect(m_LT_Pos.x, m_LT_Pos.y, m_WH_Size.x, m_WH_Size.y), 0, 0, m_BtnUpImg->GetWidth(), m_BtnUpImg->GetHeight(), UnitPixel, &a_DownAB);
			}	// if (m_BtnUpImg != NULL)
		}	// if (m_BtnDownImg == NULL)
	}
	else {
		if (m_BtnUpImg != NULL) {
			graphics.DrawImage(m_BtnUpImg, Rect(m_LT_Pos.x, m_LT_Pos.y, m_WH_Size.x, m_WH_Size.y), 0, 0, m_BtnUpImg->GetWidth(), m_BtnUpImg->GetHeight(), UnitPixel);
		}
	}	// if (m_isBtnDown == false)
}

void CButton::Destroy()
{
	if (m_BtnUpImg != NULL) {
		delete m_BtnUpImg;
		m_BtnUpImg = NULL;
	}

	if (m_BtnDownImg != NULL) {
		delete m_BtnDownImg;
		m_BtnDownImg = NULL;
	}
}

void CButton::LBtnDown(Vector2D a_MosPos)
{
	if (m_LT_Pos.x <= a_MosPos.x && a_MosPos.x <= m_LT_Pos.x + m_WH_Size.x && m_LT_Pos.y <= a_MosPos.y && a_MosPos.y <= m_LT_Pos.y + m_WH_Size.y) {
		m_isBtnDown = true;
	}
}

bool CButton::LBtnUp()
{
	if (m_isBtnDown == true) {
		m_isBtnDown = false;

		if (ClickCallback != NULL) {
			ClickCallback();
		}

		return true;
	}

	m_isBtnDown = false;
	return false;
}

void CButton::OnClick_AddListener(function<void(void)> Callback)
{
	ClickCallback = Callback;
}
