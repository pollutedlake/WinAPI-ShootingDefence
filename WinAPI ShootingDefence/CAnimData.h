#pragma once
#include <vector>
using namespace std;

//------ GDI+ Image ����� ���� ��� �߰�
#include <Ole2.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;
//------ GDI+ Image ����� ���� ��� �߰�

//------ class CMotion
class CMotion {
public:
	vector<Image*> m_ImgList;		// ������ �ε�

public:
	CMotion() {

	}

	~CMotion() {
		for (int ii = 0; ii < m_ImgList.size(); ii++) {
			//------ GDI+ ����
			if (m_ImgList[ii] != NULL) {
				delete m_ImgList[ii];
				m_ImgList[ii] = NULL;
			}
			//------ GDI+ ����
		}
		m_ImgList.clear();
	}

	void LoadTexImg(const TCHAR* a_FName) {
		// �ش� ��ο��� �̹��� �ҷ�����
		Image* a_pBitmap = Image::FromFile(a_FName);
		m_ImgList.push_back(a_pBitmap);
		// �ش� ��ο��� �̹��� �ҷ�����
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

	void LoadAnimList(enum CT_Type a_CharType);		// ĳ���� ������ "����"����? "���ΰ�"����?
};
//------ class CAnimData

extern vector<CAnimData*> g_CharAniList;