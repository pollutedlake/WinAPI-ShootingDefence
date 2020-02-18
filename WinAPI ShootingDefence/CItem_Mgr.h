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

	vector<Image*> m_ImgList;		// 아이템 이미지 리스트

public:
	CItem_Mgr();
	~CItem_Mgr();

public:
	void ItemMgr_Init();						// 초기화 함수
	void ItemMgr_Update(float a_DeltaTime);		// 아이템 연산 담당 부분
	void ItemMgr_Render(HDC a_MainDC);			// 아이템 렌더링 부분
	void ItemMgr_Destroy();						// 아이템 리소스 삭제 부분

	void SpawnItem(Vector2D a_StartV, bool a_isBoss = false);		// 아이템 스폰
	void ReSrcClear();												// 라운드를 넘어갈 때 필드에 뿌려져 있는 모든 아이템 삭제 함수
};

extern CItem_Mgr g_ItemMgr;