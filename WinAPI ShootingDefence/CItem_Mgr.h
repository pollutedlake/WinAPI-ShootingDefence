#pragma once

#include  "CItem.h"

#include <list>
#include <vector>
using namespace std;

class CItem_Mgr
{
	//------ Item List
	list<CItem*> m_ItemList;
	list<CItem*>::iterator m_Iiter;
	//------ Item List

	vector<Image*> m_ImgList;		// ������ �̹��� ����Ʈ

public:
	CItem_Mgr();
	~CItem_Mgr();

public:
	void ItemMgr_Init();						// �ʱ�ȭ �Լ�
	void ItemMgr_Update(float a_DeltaTime);		// ������ ���� ��� �κ�
	void ItemMgr_Render(HDC a_MainDC);			// ������ ������ �κ�
	void ItemMgr_Destroy();						// ������ ���ҽ� ���� �κ�

	void SpawnItem(Vector2D a_StartV, bool a_isBoss = false);		// ������ ����
	void ReSrcClear();												// ���带 �Ѿ �� �ʵ忡 �ѷ��� �ִ� ��� ������ ���� �Լ�
};

extern CItem_Mgr g_ItemMgr;