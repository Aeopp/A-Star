
// MFCToolView.cpp : CMFCToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "Single_Texture.h"
#include "Texture_Manager.h"
#include "Terrain.h"
#include "MainFrm.h"
#include "MiniView.h"
#include "MyForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CScrollView)
HWND g_hWND; 
BEGIN_MESSAGE_MAP(CMFCToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCToolView ����/�Ҹ�

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CMFCToolView::~CMFCToolView()
{

	Safe_Delete(m_pTerrain); 
	CTexture_Manager::Destroy_Instance();
	CGraphic_Device::Destroy_Instance(); 
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView �׸���

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pGraphic_Device->Render_Begin();
	m_pTerrain->Render_Terrain();
	m_pGraphic_Device->Render_End();
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
// 	// �׸��� �׸��� ������ ��� ������ �ɱ�? 
// 	// 1. �ĸ���۸� ����! 
// 	// 2. �ĸ���ۿ� �׸���!
// 	// 3. �ĸ� ���۸� ���� ���ۿ� ��ü�Ѵ�. 
// 	m_fAngle += 5.f; 
// 	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile",20 );
// 	if (nullptr == pTexInfo)
// 	{
// 		return; 
// 	}
// 	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
// 	float fCenterY = static_cast<float>(pTexInfo->tImageInfo.Height >> 1); 
// 	D3DXMATRIX matScale, matRotZ, matTrans, matWorld; 
// // 
// 	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
// 	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
// 	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
// 	matWorld = matScale * matRotZ * matTrans; 
// 	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
// 	m_pGraphic_Device->Render_Begin(); 
// 	
// 	m_pGraphic_Device->Get_Sprite()->SetTransform(&matWorld);
// 	m_pGraphic_Device->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255,255, 255, 255));
// 	m_pGraphic_Device->Render_End(); 
}


// CMFCToolView �μ�

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMFCToolView ����

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView �޽��� ó����


void CMFCToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	g_hWND = m_hWnd; 
	m_pGraphic_Device = CGraphic_Device::Get_Instance(); 
	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device()))
		return ; 
	SetScrollSizes(MM_TEXT, CSize((TILECX * TILEX), TILEY * (TILECY >> 1)));
	// //1.������������ ������! 
	// CMainApp�� �ּҰ��� ��ȯ���ִ� �����Լ�.
	CMainFrame* pMain = (CMainFrame*)::AfxGetApp()->GetMainWnd();

	RECT rcMain = {};
	pMain->GetWindowRect(&rcMain); 
	::SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top);

	RECT rcView = {}; 
	GetClientRect(&rcView); 
	
	DWORD dwWidth = rcMain.right - rcView.right;
	DWORD dwHeight = rcMain.bottom - rcView.bottom; 

	pMain->SetWindowPos(nullptr, 0, 0, WINCX + dwWidth, WINCY + dwHeight, SWP_NOZORDER);

	//if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::SINGLE_TEX, L"../Texture/Cube.png", L"Cube")))
	//	return; 

	if (FAILED(CTexture_Manager::Get_Instance()->Insert_Texture(CTexture_Manager::MULTI_TEX, L"../Texture/Stage/Terrain/Tile/Tile%d.png", L"Terrain", L"Tile", 38)))
		return; 

	if (nullptr == m_pTerrain)
	{
		m_pTerrain = new CTerrain; 
		m_pTerrain->Ready_Terrain();
		m_pTerrain->Set_View(this);

	}

}


void CMFCToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	// �̰� Ÿ�� ������� ���°� 
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMain->m_tSecondSplitter.GetPane(1, 0));
	// �̰� �̴Ϻ� �����Ҷ�� ���°�. 
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMain->m_tSecondSplitter.GetPane(0, 0));

	int iDrawID = pMyForm->m_tMapTool.m_iDrawID;

	_vec3 vMouse = { (float)point.x + GetScrollPos(0), (float)point.y + GetScrollPos(1), 0.f };
	m_pTerrain->TileChange_Terrain(vMouse, iDrawID, 1);
	
	
	InvalidateRect(nullptr, FALSE); 
	pMiniView->InvalidateRect(nullptr, FALSE);


	CView::OnLButtonDown(nFlags, point);
}


void CMFCToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
// 	_vec3 vMouse = { (float)point.x, (float)point.y, 0.f };
// 	if (GetAsyncKeyState(VK_LBUTTON))
// 	{
// 		m_pTerrain->TileChange_Terrain(vMouse, 37);
// 	}
// 	InvalidateRect(nullptr, FALSE);
	CView::OnMouseMove(nFlags, point);
}
