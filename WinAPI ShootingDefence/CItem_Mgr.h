#pragma once

#include  "CItem.h"

#include <list>
#include <vector>
using namespace std;

class CItem_Mgr
{
	//------ Item List
	list<CItem*> m_ItemList;
	list<CItem*>::iterator m_Iter;
	//------ Item List

	vector<Image*> m_ImgList;		// 아이템 이미지 리스트

public:
	CItem_Mgr();
	~CItem_Mgr();

public:
	void ItemMgr_Init();						// 초기화 함수
	void ItemMgr_Update(float a_DeltaTime);		// 아이템 연산 담당 부분
	void ItemMgr_Render(HDC a_MainDC);			// 아이템 렌더링 부분
	void ItemMgr_Destroy();						// 아이템 리소스 삭제 부분
};

extern CItem_Mgr g_ItemMgr;