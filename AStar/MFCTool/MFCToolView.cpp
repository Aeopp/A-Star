
// MFCToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸

CMFCToolView::CMFCToolView()
	:m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CMFCToolView::~CMFCToolView()
{

	Safe_Delete(m_pTerrain); 
	CTexture_Manager::Destroy_Instance();
	CGraphic_Device::Destroy_Instance(); 
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pGraphic_Device->Render_Begin();
	m_pTerrain->Render_Terrain();
	m_pGraphic_Device->Render_End();
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
// 	// 그림을 그리는 과정은 어떻게 진행이 될까? 
// 	// 1. 후면버퍼를 비운다! 
// 	// 2. 후면버퍼에 그린다!
// 	// 3. 후면 버퍼를 전면 버퍼와 교체한다. 
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


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기


void CMFCToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWND = m_hWnd; 
	m_pGraphic_Device = CGraphic_Device::Get_Instance(); 
	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device()))
		return ; 
	SetScrollSizes(MM_TEXT, CSize((TILECX * TILEX), TILEY * (TILECY >> 1)));
	// //1.메인프레임을 얻어오자! 
	// CMainApp의 주소값을 반환해주는 전역함수.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	// 이건 타일 찍을라고 얻어온거 
	CMyForm* pMyForm = dynamic_cast<CMyForm*>(pMain->m_tSecondSplitter.GetPane(1, 0));
	// 이건 미니뷰 갱신할라고 얻어온거. 
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
// 	_vec3 vMouse = { (float)point.x, (float)point.y, 0.f };
// 	if (GetAsyncKeyState(VK_LBUTTON))
// 	{
// 		m_pTerrain->TileChange_Terrain(vMouse, 37);
// 	}
// 	InvalidateRect(nullptr, FALSE);
	CView::OnMouseMove(nFlags, point);
}
