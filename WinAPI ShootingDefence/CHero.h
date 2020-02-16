#pragma once
#include "Vector2D.h"

//------ GDI+ Image ����� ���� ��� �߰�
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image ����� ���� ��� �߰�

class CHero
{
	Image* m_SocketImg;		// �ִ� ����ó�� ����� ������

	HWND m_hWnd;
	float m_Speed = 300.0f;

	int m_ImgSizeX;			// �̹����� ���� ������
	int m_ImgSizeY;			// �̹����� ���� ������
	int m_HalfWidth = 15;	// �⺻ �̹����� ���� �ݻ�����
	int m_HalfHeight = 15;	// �⺻ �̹����� ���� �ݻ�����

	//------ ���� ���� ����
	float m_DeltaTime = 0.0f;
	//------ ���� ���� ����

	float m_AttackSpeed = 0.1f;		// ���ݼӵ�
	float m_BLCycle = 0.0f;

public:
	Vector2D m_CurPos;
	float m_HalfColl = 20.0f;		// ���ΰ��� �浹 �ݰ�

public:
	CHero();
	~CHero();

public:
	void Init_Unit(HWND a_hWnd);
	void Update_Unit(float a_DeltaTime, RECT& a_RT);
	void Render_Unit(HDC a_hdc);
	void Destroy_Unit();

	void HeroLimitMove(RECT& a_RT);
	void LoadUnitSize();
};

extern CHero g_Hero;