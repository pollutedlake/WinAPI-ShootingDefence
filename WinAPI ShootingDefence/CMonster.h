#pragma once

#include "Vector2D.h"

//------ GDI+ Image 사용을 위한 헤더 추가
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image 사용을 위한 헤더 추가

class CMonster
{
public:
	Image* m_SocketImg;		// 애니 소켓처럼 사용할 포인터

	int m_ImgSizeX;			// 이미지의 가로 사이즈
	int m_ImgSizeY;			// 이미지의 세로 사이즈
	int m_HalfWidth = 15;	// 기본 이미지의 가로 반사이즈
	int m_HalfHeight = 15;	// 기본 이미지의 세로 반사이즈

	enum CT_Type m_CharType;		// 캐릭터 종류가 "몬스터"인지? "나나미"인지?
	bool m_isActive;
	float m_MaxHP = 100.0f;
	float m_CurHP = 100.0f;

	//--- 몬스터 좌표 계산용 변수들...
	Vector2D m_CurPos;
	float m_Speed = 150.0f;
	Vector2D m_DirVec;
	float m_HalfColl = 17;		// 몬스터의 충돌 반경
	//--- 몬스터 좌표 계산용 변수들...

public:
	CMonster();
	~CMonster();

public:
	void Init_Unit();
	void Update_Unit(float a_DeltaTime, class CHero& a_Hero);
	void Render_Unit(HDC a_hDC, HBRUSH& a_R_brsh);
	void Destroy_Unit();

	void LoadUnitSize();
	void Spawn(float a_XX, float a_YY);
	void TakeDamage(float a_Value = 10.0f);
};

