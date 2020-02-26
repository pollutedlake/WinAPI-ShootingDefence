#pragma once
#include <vector>
using namespace std;

//------ GDI+ Image 사용을 위한 헤더 추가
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image 사용을 위한 헤더 추가

//------ class CMotion
class CMotion {
public:
	vector<Image*> m_ImgList;		// 프레임 로딩

public:
	CMotion() {

	}

	~CMotion() {
		for (int ii = 0; ii < m_ImgList.size(); ii++) {
			//------ GDI+ 해제
			if (m_ImgList[ii] != NULL) {
				delete m_ImgList[ii];
				m_ImgList[ii] = NULL;
			}
			//------ GDI+ 해제
		}
		m_ImgList.clear();
	}

	void LoadTexImg(const TCHAR* a_FName) {
		// 해당 결로에서 이미지 불러오기
		Image* a_pBitmap = Image::FromFile(a_FName);
		m_ImgList.push_back(a_pBitmap);
		// 해당 결로에서 이미지 불러오기
	}
};
//------ class CMotion

//------ class CAnimData
class CAnimData
{
public:
	vector<CMotion*> m_MotionList;

public:
	CAnimData();
	~CAnimData();

	void LoadAnimList(enum CT_Type a_CharType);		// 캐릭터 종류가 "몬스터"인지? "주인공"인지?
};
//------ class CAnimData

extern vector<CAnimData*> g_CharAniList;