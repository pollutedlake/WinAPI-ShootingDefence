#pragma once

#include "Vector2D.h"

//------ GDI+ Image 사용을 위한 헤더 추가
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image 사용을 위한 헤더 추가

enum ItemType {
	IT_Gold = 0,
	IT_Silver,
	IT_Potion,
	IT_Length
};

class CItem
{
public:
	ItemType m_IT_Type;
	float m_Duration;
	Vector2D m_CurPos;
	float m_HalfWidth;
	float m_HalfHeight;
	Vector2D m_CalcVec;
	Image* m_ItemImg;

public:
	CItem();
	~CItem();

	bool ItemUpdate(float a_DeltaTime);
	void ItemRender(HDC a_hDC);
};

