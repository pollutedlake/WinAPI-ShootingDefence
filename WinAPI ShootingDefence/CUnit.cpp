#include "framework.h"
#include "GlobalValue.h"
#include "CUnit.h"

CUnit::CUnit()
{
	m_SocketImg = NULL;
	m_RefAniData = NULL;

	m_CurAniState = AS_None;
	m_NowImgCount = 0;
	m_CurAniInx = 0;		// 진행 Ani Index
	m_AniTickCount = 0;		// 다음 프레임까지 시간 Add
	m_EachAniDelay = 0.2f;	// 프레임 간격 시간
}

CUnit::~CUnit()
{
}

void CUnit::Init_Unit(HWND a_hWnd)
{
}

void CUnit::Update_Unit(float a_DeltaTime)
{
	//------ 애니메이션 프레임 계산 부분
	AniFrameUpdate(a_DeltaTime);
	//------ 애니메이션 프레임 계산 부분
}

void CUnit::Render_Unit(HDC a_hDC)
{
}

void CUnit::Destroy_Unit()
{
}

void CUnit::LoadUnitSize()
{
	if (m_SocketImg == NULL) {
		return;
	}

	m_ImgSizeX = m_SocketImg->GetWidth();		// 기본 이미지의 가로 사이즈
	m_ImgSizeY = m_SocketImg->GetHeight();		// 기본 이미지의 세로 사이즈

	m_HalfWidth = m_ImgSizeX / 2;				// 기본 이미지의 가로 반사이즈
	m_HalfHeight = m_ImgSizeY / 2;				// 기본 이미지의 세로 반사이즈
}

void CUnit::AniFrameUpdate(double a_DeltaTime)
{
	//------ 애니메이션 프레임 계산 부분
	if (m_CurAniState == AS_None) {
		return;
	}

	if (m_NowImgCount <= 0) {		// 애니 소켓에 뭔가 꼽혀 있는지 확인해 보는 안전장치
		return;
	}

	m_AniTickCount = m_AniTickCount + a_DeltaTime;
	if (m_EachAniDelay < m_AniTickCount) {		// 다음 프레임
		m_CurAniInx++;
		if (m_NowImgCount <= m_CurAniInx) {		// 마지막 프레임일 때
			m_CurAniInx = 0;
		}

		m_SocketImg = m_RefAniData->m_MotionList[(int)m_CurAniState]->m_ImgList[m_CurAniInx];

		m_AniTickCount = 0;
	}
	//------ 애니메이션 프레임 계산 부분
}

bool CUnit::ChangeState(AniState newState)
{
	if (m_CurAniState == newState) {
		return false;
	}

	if (newState <= AS_None || AniLength <= newState) {
		return false;
	}

	if (m_RefAniData == NULL) {
		return false;
	}

	if (m_RefAniData->m_MotionList[(int)newState]->m_ImgList.size() <= 0) {
		return false;
	}

	m_NowImgCount = m_RefAniData->m_MotionList[(int)newState]->m_ImgList.size();
	m_CurAniInx = 0;
	m_AniTickCount = 0;

	if (newState == Idle) {
		m_EachAniDelay = 0.4f;
	}
	else {
		m_EachAniDelay = 0.12f;
	}

	m_SocketImg = m_RefAniData->m_MotionList[(int)newState]->m_ImgList[0];		// 첫 이미지 대입

	m_CurAniState = newState;

	return true;
}

void CUnit::SetAni_Rsc(CT_Type a_CharType)
{
	if (a_CharType <= CT_None || CT_Length <= a_CharType) {
		return;
	}

	m_CharType = a_CharType;

	if (a_CharType < g_CharAniList.size()) {
		m_RefAniData = g_CharAniList[(int)a_CharType];
	}

	ChangeState(Idle);

	LoadUnitSize();
}

