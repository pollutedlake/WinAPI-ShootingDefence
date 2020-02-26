#pragma once
#include "CAnimData.h"

class CUnit
{
public:
	enum CT_Type m_CharType;		// 캐릭터 종류가 "몬스터"인지? "나나미"인지?
	CAnimData* m_RefAniData;		// 캐릭터 타입에 따라 애니메이션 데이터를 바꿔 낄 것임

	//------ 애니메이션 관련 변수
	Image* m_SocketImg;					// 애니 소켓처럼 사용할 포인터
	enum AniState m_CurAniState;		// 현재 애니메이션 상태

	int m_NowImgCount;					// 애니 소켓처럼 사용할 이미지 카운트
	float m_EachAniDelay;				// 프레임 간격 시간
	float m_AniTickCount;				// 다음 프레임까지 시간 Add
	int m_CurAniInx;					// 진행 Ani Index
	//------ 애니메이션 관련 변수

	int m_ImgSizeX;						// 이미지의 가로 사이즈
	int m_ImgSizeY;						// 이미지의 세로 사이즈
	int m_HalfWidth = 15;				// 기본 이미지의 가로 반사이즈
	int m_HalfHeight = 15;				// 기본 아미지의 세로 반사이즈

public:
	CUnit();
	~CUnit();

	virtual void Init_Unit(HWND a_hWnd);
	virtual void Update_Unit(float a_DeltaTime);
	virtual void Render_Unit(HDC a_hDC);
	virtual void Destroy_Unit();

	void SetAni_Rsc(enum CT_Type a_CharType);
	void LoadUnitSize();
	bool ChangeState(enum AniState newState);
	void AniFrameUpdate(double a_DeltaTime);
};

