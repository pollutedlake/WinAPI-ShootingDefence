#include "framework.h"
#include "GlobalValue.h"
#include "CAnimData.h"

CAnimData::CAnimData()
{
	for (int ii = 0; ii < AniLength; ii++) {
		CMotion* a_Node = new CMotion();
		m_MotionList.push_back(a_Node);
	}
}

CAnimData::~CAnimData()
{
	for (int ii = 0; ii < m_MotionList.size(); ii++) {
		if (m_MotionList[ii] != NULL) {
			delete m_MotionList[ii];
			m_MotionList[ii] = NULL;
		}
	}
	m_MotionList.clear();
}

void CAnimData::LoadAnimList(CT_Type a_CharType)
{
	if (a_CharType == CT_Nanami) {
		m_MotionList[(int)Idle]->LoadTexImg(_T("Nanami/front_Idle/n001.png"));
		m_MotionList[(int)Idle]->LoadTexImg(_T("Nanami/front_Idle/n002.png"));

		m_MotionList[(int)Front_Walk]->LoadTexImg(_T("Nanami/front_walk/n010.png"));
		m_MotionList[(int)Front_Walk]->LoadTexImg(_T("Nanami/front_walk/n011.png"));
		m_MotionList[(int)Front_Walk]->LoadTexImg(_T("Nanami/front_walk/n012.png"));
		m_MotionList[(int)Front_Walk]->LoadTexImg(_T("Nanami/front_walk/n013.png"));


		m_MotionList[(int)Back_Walk]->LoadTexImg(_T("Nanami/back_walk/n040.png"));
		m_MotionList[(int)Back_Walk]->LoadTexImg(_T("Nanami/back_walk/n041.png"));
		m_MotionList[(int)Back_Walk]->LoadTexImg(_T("Nanami/back_walk/n042.png"));
		m_MotionList[(int)Back_Walk]->LoadTexImg(_T("Nanami/back_walk/n043.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("Nanami/left_walk/n030.png"));
		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("Nanami/left_walk/n031.png"));
		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("Nanami/left_walk/n032.png"));
		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("Nanami/left_walk/n033.png"));

		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("Nanami/right_walk/n020.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("Nanami/right_walk/n021.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("Nanami/right_walk/n022.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("Nanami/right_walk/n023.png"));
	}
	else if (a_CharType == CT_Zombie4) {
		m_MotionList[(int)Idle]->LoadTexImg(_T("./MonsterImg/Zombi4.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("./MonsterImg/Zombi4.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("./MonsterImg/Zombi4_R.png"));
	}
	else if (a_CharType == CT_Zombie1) {
		m_MotionList[(int)Idle]->LoadTexImg(_T("./MonsterImg/Zombi1.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("./MonsterImg/Zombi1.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("./MonsterImg/Zombi1_R.png"));
	}
	else if (a_CharType == CT_Zombie2) {
		m_MotionList[(int)Idle]->LoadTexImg(_T("./MonsterImg/Zombi2.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("./MonsterImg/Zombi2.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("./MonsterImg/Zombi2_R.png"));
	}
	else if (a_CharType == CT_Zombie6) {
		m_MotionList[(int)Idle]->LoadTexImg(_T("./MonsterImg/Zombi6.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("./MonsterImg/Zombi6.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("./MonsterImg/Zombi6_R.png"));
	}
	else if (a_CharType == CT_Zombie3) {
		m_MotionList[(int)Idle]->LoadTexImg(_T("./MonsterImg/Zombi3.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("./MonsterImg/Zombi3.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("./MonsterImg/Zombi3_R.png"));
	}
	else if (a_CharType == CT_Boss) {
		m_MotionList[(int)Idle]->LoadTexImg(_T("./MonsterImg/Front/Megapack III Void Gargoyle.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("./MonsterImg/Front/Megapack III Void Gargoyle.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("./MonsterImg/Side/Megapack III Void Gargoyle.png"));
	}
	else {
		m_MotionList[(int)Idle]->LoadTexImg(_T("./MonsterImg/Zombi8.png"));

		m_MotionList[(int)Left_Walk]->LoadTexImg(_T("./MonsterImg/Zombi8.png"));
		m_MotionList[(int)Right_Walk]->LoadTexImg(_T("./MonsterImg/Zombi8_R.png"));
	}
}

vector<CAnimData*> g_CharAniList;