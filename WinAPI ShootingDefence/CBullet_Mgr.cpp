#include "framework.h"
#include "CBullet_Mgr.h"

CBullet_Mgr::CBullet_Mgr()
{
}

CBullet_Mgr::~CBullet_Mgr()
{
}

void CBullet_Mgr::BLMgr_Init()
{
	//------ �Ѿ� �޸�Ǯ�� �̸� ����� ����
	CBullet* a_BLNode = NULL;
	for (int aii = 0; aii < 200; aii++) {
		a_BLNode = new CBullet();
		m_BullList.push_back(a_BLNode);
	}
	//------ �Ѿ� �޸�Ǯ�� �̸� ����� ����

	m_h_brsh = CreateSolidBrush(RGB(0, 100, 255));		// brush �߰�, pen�� ���� �������
	m_h_pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	// ������(�Ǽ�), �β�(1), RGB��
}

void CBullet_Mgr::BLMgr_Update(float a_DeltaTime, HWND a_hWnd)
{
	//------ ��� �Ѿ� �̵����� ������Ʈ ó��
	static Vector2D a_CalcBVec;
	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii]->m_BLActive == false) {
			continue;
		}

		m_BullList[aii]->BulletUpdate(a_DeltaTime);
	}	// for (int aii = 0; aii < m_BullList.size(); aii++)
	//------ ��� �Ѿ� �̵����� ������Ʈ ó��
}

void CBullet_Mgr::BLMgr_Render(HDC a_hDC)
{
	if (m_h_pen == NULL || m_h_brsh == NULL) {
		return;
	}

	m_h_OldPen = SelectObject(a_hDC, m_h_pen);		// HGDIOBJ ��� GDI object�� ����
	m_h_Old_brsh = SelectObject(a_hDC, m_h_brsh);

	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii]->m_BLActive == false) {
			continue;
		}

		m_BullList[aii]->BulletRender(a_hDC);
	}	// for (m_Biter = m_StdList.begin(); m_Biter != m_StdList.end(); m_Biter++)

	SelectObject(a_hDC, m_h_OldPen);		// ���� ������ ��ü
	SelectObject(a_hDC, m_h_Old_brsh);		// ���� �귯���� ��ü
}

void CBullet_Mgr::BLMgr_Destroy()
{
	// �Ѿ� �޸�Ǯ �����ϱ�...
	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii] != NULL) {
			delete m_BullList[aii];
			m_BullList[aii] = NULL;
		}
	}
	m_BullList.clear();
	// �Ѿ� �޸�Ǯ �����ϱ�...

	if (m_h_brsh != NULL) {
		DeleteObject(m_h_brsh);		// brush object ����
		m_h_brsh = NULL;
	}

	if (m_h_pen != NULL) {
		DeleteObject(m_h_pen);		// GDI object ���� ������ �ü������ ������ ����
		m_h_pen = NULL;
	}
}

void CBullet_Mgr::SpawnBullet(Vector2D a_StartV, Vector2D a_TargetV)
{
	CBullet* a_BNode = NULL;

	for (int aii = 0; aii < m_BullList.size(); aii++) {
		if (m_BullList[aii]->m_BLActive == false) {
			a_BNode = m_BullList[aii];
			break;
		}
	}

	if (a_BNode == NULL) {
		a_BNode = new CBullet();
		m_BullList.push_back(a_BNode);
	}

	a_BNode->m_CurPos.x = a_StartV.x;
	a_BNode->m_CurPos.y = a_StartV.y;

	a_BNode->m_DirVec = a_TargetV - a_StartV;
	a_BNode->m_DirVec.Normalize();
	a_BNode->m_CurPos = a_BNode->m_CurPos + a_BNode->m_DirVec * 20.0f;
	a_BNode->m_BLActive = true;
	a_BNode->m_LifeTime = 4.0f;
}

CBullet_Mgr g_Bullet_Mgr;