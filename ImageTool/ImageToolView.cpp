
// ImageToolView.cpp: CImageToolView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageTool.h"
#endif

#include "ImageToolDoc.h"
#include "ImageToolView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MainFrm.h"
#include <atlimage.h>

// CImageToolView

IMPLEMENT_DYNCREATE(CImageToolView, CScrollView)

BEGIN_MESSAGE_MAP(CImageToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageToolView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_ZOOM1, &CImageToolView::OnViewZoom1)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM1, &CImageToolView::OnUpdateViewZoom1)
	ON_COMMAND(ID_VIEW_ZOOM2, &CImageToolView::OnViewZoom2)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM2, &CImageToolView::OnUpdateViewZoom2)
	ON_COMMAND(ID_VIEW_ZOOM3, &CImageToolView::OnViewZoom3)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM3, &CImageToolView::OnUpdateViewZoom3)
	ON_COMMAND(ID_VIEW_ZOOM4, &CImageToolView::OnViewZoom4)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM4, &CImageToolView::OnUpdateViewZoom4)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_BUTTON_PENCIL, &CImageToolView::OnButtonPencil)
	ON_COMMAND(ID_BUTTON_PENCIL, &CImageToolView::OnButtonPencil)
	ON_COMMAND(ID_BUTTON_COLOR, &CImageToolView::OnButtonColor)
	ON_COMMAND(ID_BUTTON_ERASER, &CImageToolView::OnButtonEraser)
	ON_COMMAND(ID_BUTTON_COLORFILL, &CImageToolView::OnButtonColorfill)
	ON_COMMAND(ID_BUTTON_ALLERASE, &CImageToolView::OnButtonAllerase)
	ON_COMMAND(ID_BUTTON_LINE, &CImageToolView::OnButtonLine)
	ON_COMMAND(ID_BUTTON_RIGHTTRI, &CImageToolView::OnButtonRighttri)
	ON_COMMAND(ID_BUTTON_RECT, &CImageToolView::OnButtonRect)
	ON_COMMAND(ID_BUTTON_ROUNDRECT, &CImageToolView::OnButtonRoundrect)
	ON_COMMAND(ID_BUTTON_TRAPEZOID, &CImageToolView::OnButtonTrapezoid)
	ON_COMMAND(ID_BUTTON_PENTAGON, &CImageToolView::OnButtonPentagon)
	ON_COMMAND(ID_BUTTON_HEXAGON, &CImageToolView::OnButtonHexagon)
	ON_COMMAND(ID_BUTTON_PIERECT, &CImageToolView::OnButtonPierect)
	ON_COMMAND(ID_BUTTON_HALFCIRCLE, &CImageToolView::OnButtonHalfcircle)
	ON_COMMAND(ID_BUTTON_HALFCIRCLE2, &CImageToolView::OnButtonHalfcircle2)
	ON_COMMAND(ID_BUTTON_270PIERECT, &CImageToolView::OnButton270pierect)
	ON_COMMAND(ID_BUTTON_CIRCLE, &CImageToolView::OnButtonCircle)
	ON_COMMAND(ID_BUTTON_SOLID, &CImageToolView::OnButtonSolid)
	ON_COMMAND(ID_BUTTON_DASH, &CImageToolView::OnButtonDash)
	ON_COMMAND(ID_BUTTON_DOT, &CImageToolView::OnButtonDot)
	ON_COMMAND(ID_BUTTON_DASHDOT, &CImageToolView::OnButtonDashdot)
	ON_COMMAND(ID_BUTTON_DASHDOTDOT, &CImageToolView::OnButtonDashdotdot)
	ON_COMMAND(ID_BUTTON_DEFAULT, &CImageToolView::OnButtonDefault)
	ON_COMMAND(ID_BUTTON_HORIZONTAL, &CImageToolView::OnButtonHorizontal)
	ON_COMMAND(ID_BUTTON_VERTICAL, &CImageToolView::OnButtonVertical)
	ON_COMMAND(ID_BUTTON_BDIAGONAL, &CImageToolView::OnButtonBdiagonal)
	ON_COMMAND(ID_BUTTON_FDIAGONAL, &CImageToolView::OnButtonFdiagonal)
	ON_COMMAND(ID_BUTTON_CROSS, &CImageToolView::OnButtonCross)
	ON_COMMAND(ID_BUTTON_DIAGCROSS, &CImageToolView::OnButtonDiagcross)
END_MESSAGE_MAP()

// CImageToolView 생성/소멸

CImageToolView::CImageToolView() noexcept
	:m_nZoom(1),
	m_nDrawMode(0)
	//, m_nHatchStyle(0)
	, m_ptStart(0)
	, m_ptPrev(0)
	//, m_bFirst(false)
	, m_bLButtonDown(false)
	//, m_bContextMenu(false)
	, m_bHatch(false)
	, m_nCount(0)
	, m_nPenMode(0)
	, m_nPenSize(1)
{
	m_bContextMenu = true;
	m_bFirst = true;

	for (int i = 0; i < 100; i++)
	{
		m_ptData[i] = 0;
	}
	//같은 거 memset(m_ptData, 0, sizeof(CPoint) * 100);


	m_PenColor = RGB(0, 0, 0); //black
	m_BrushColor = RGB(255, 255, 255); //white
}

CImageToolView::~CImageToolView()


{
}

BOOL CImageToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageToolView 그리기

void CImageToolView::OnDraw(CDC* pDC)
{
	CImageToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	if (pDoc->m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();
		pDoc->m_Dib.Draw(pDC->m_hDC,0,0,w*m_nZoom,h*m_nZoom);
	}
}

void CImageToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	SetScrollSizeToFit();
	
}


void CImageToolView::SetScrollSizeToFit(void)
{
	CSize sizeTotal;

	CImageToolDoc* pDoc = GetDocument();
	if (pDoc-> m_Dib.IsValid())
	{
		int w = pDoc->m_Dib.GetWidth();
		int h = pDoc->m_Dib.GetHeight();

		sizeTotal.cx = w * m_nZoom;
		sizeTotal.cy = h * m_nZoom;

	}
	else
	{
		sizeTotal.cx = sizeTotal.cy = 100;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	ResizeParentToFit(FALSE);
	//ResizeParentToFit(FALSE); 
	// // ResizeParentToFit() 가급적으로 TRUE 인자를 주는 것이 좋다. 인자를 주지 않는경우 기본적으로 TRUE로 지정						  
	// TRUE인 경우 불러온 영상의 크기가 차일드 프레임보다 작은 경우에만 프레임의 크기를 영상의 크기에 맞춘다.
}


// CImageToolView 인쇄


void CImageToolView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageToolView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageToolView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageToolView 진단

#ifdef _DEBUG
void CImageToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageToolDoc* CImageToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageToolDoc)));
	return (CImageToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageToolView 메시지 처리기


BOOL CImageToolView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CBrush br;
	//br.CreateHatchBrush(HS_DIAGCROSS, RGB(200, 200, 200));
	//FillOutsideRect(pDC, &br);
	CRect rect;

	GetClientRect(rect);

	pDC->FillSolidRect(rect, RGB(255, 255, 255));

	return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);
	//return TRUE;
}


void CImageToolView::OnViewZoom1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 1;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom1(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 1);
}


void CImageToolView::OnViewZoom2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 2;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom2(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 2);
}


void CImageToolView::OnViewZoom3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 3;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom3(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 3);
}


void CImageToolView::OnViewZoom4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nZoom = 4;
	SetScrollSizeToFit();
	Invalidate(TRUE);
}


void CImageToolView::OnUpdateViewZoom4(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_nZoom == 4);
}



void CImageToolView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CScrollView::OnPaint()을(를) 호출하지 마십시오.

	CImageToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CPen pen, * oldpen;
	switch (m_nPenMode)
	{
	case 0:
		pen.CreatePen(PS_SOLID, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 1:
		pen.CreatePen(PS_DASH, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 2:
		pen.CreatePen(PS_DOT, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 3:
		pen.CreatePen(PS_DASHDOT, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 4:
		pen.CreatePen(PS_DASHDOTDOT, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;

	}

	oldpen = dc.SelectObject(&pen);		//pen 객체 등록
	dc.SetROP2(R2_COPYPEN);				//COPTPEN으로 설정

	CBrush brush, * oldbrush;

	if (m_bHatch)		//brush 객체 생성
		brush.CreateHatchBrush(m_nHatchStyle, m_BrushColor);
	else				//brush 객체 등록
		brush.CreateSolidBrush(m_BrushColor);

	oldbrush = dc.SelectObject(&brush);
	CRect PieRect(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
	switch (m_nDrawMode)
	{
	case PENCIL_MODE:

		break;
	case LINE_MODE:
		dc.MoveTo(m_ptStart);
		dc.LineTo(m_ptPrev);
		break;
	case ELLIPSE_MODE:
		dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;
	case RECTANGLE_MODE:
		dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
		break;

	case ROUNDRECT_MODE:
		dc.RoundRect(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y, 50, 50);
		break;

	case PIERECT_MODE:
		dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, m_ptStart.y), CPoint(m_ptStart.x, PieRect.CenterPoint().y));
		//pDC->Pie(PieRect, CPoint(m_ptStart.x, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, m_ptStart.y));
		break;
	case HALFCIRCLE_HORIZONTAL_MODE:
		dc.Pie(PieRect, CPoint(m_ptPrev.x, PieRect.CenterPoint().y), CPoint(m_ptStart.x, PieRect.CenterPoint().y));
		//pDC->Pie(PieRect, CPoint(m_ptStart.x, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, m_ptStart.y));
		break;
	case HALFCIRCLE_VERTICAL_MODE:
		dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, m_ptStart.y), CPoint(PieRect.CenterPoint().x, m_ptPrev.y));
		break;
	case PIERECT270_MODE:
		dc.Pie(PieRect, CPoint(m_ptStart.x, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, m_ptStart.y));
		break;

	case TRIANGLE_MODE:

		//POINT arPt1[4] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x , m_ptPrev.y},{ m_ptPrev.x, m_ptPrev.y} };
		POINT arPt1[4] = { {m_ptStart.x,m_ptStart.y},{ (m_ptPrev.x - m_ptStart.x), m_ptPrev.y},{ m_ptPrev.x, m_ptPrev.y} };
		dc.Polygon(arPt1, 3);

		break;

	}
	switch (m_nDrawMode)
	{
	case RIGHTTRIANGLE_MODE:
		POINT arPt2[4] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x, m_ptPrev.y},{ m_ptPrev.x, m_ptPrev.y} };
		dc.Polygon(arPt2, 3);
		break;
	}
	switch (m_nDrawMode)
	{
	case PENTAGON_MODE:
		POINT arPt1[6] = {
		{m_ptStart.x,m_ptStart.y}, {m_ptStart.x, m_ptPrev.y}, { (m_ptPrev.x + m_ptStart.x) / 2, m_ptPrev.y + (m_ptPrev.y - m_ptStart.y) / 2 }, { m_ptPrev.x, m_ptPrev.y },{m_ptPrev.x,m_ptStart.y} };
		dc.Polygon(arPt1, 5);
		break;
	}
	switch (m_nDrawMode)
	{
	case HEXAGON_MODE:
		POINT arPt1[7] = {
				{m_ptStart.x,m_ptStart.y}, {m_ptStart.x, (m_ptStart.y + m_ptPrev.y) / 2},{(m_ptStart.x + m_ptPrev.x) / 2,m_ptPrev.y},
				{m_ptPrev.x,m_ptPrev.y},{m_ptPrev.x, (m_ptStart.y + m_ptPrev.y) / 2},{(m_ptStart.x + m_ptPrev.x) / 2,m_ptStart.y}
		};
		dc.Polygon(arPt1, 6);
		break;
	}

	switch (m_nDrawMode)
	{
	case OCTAGON_MODE:
		POINT arPt1[9] = {
				{m_ptStart.x,(m_ptStart.y + m_ptPrev.y) / 3},{m_ptStart.x,((m_ptStart.y + m_ptPrev.y) / 3) * 2},
				{(m_ptStart.x + m_ptPrev.x) / 3,m_ptPrev.y},{((m_ptStart.x + m_ptPrev.x) / 3) * 2 ,m_ptPrev.y},
				{m_ptPrev.x,((m_ptStart.y + m_ptPrev.y) / 3) * 2},{m_ptPrev.x,(m_ptStart.y + m_ptPrev.y) / 3},
				{((m_ptStart.x + m_ptPrev.x) / 3) * 2 ,m_ptStart.y},{(m_ptStart.x + m_ptPrev.x) / 3,m_ptStart.y}
		};
		dc.Polygon(arPt1, 8);
		break;
	}


	switch (m_nDrawMode)
	{
	case TRAPEZOID_MODE:
		POINT arPt1[5] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x, m_ptPrev.y},
			{ m_ptPrev.x, m_ptPrev.y},{(m_ptStart.x + m_ptPrev.x) / 2,m_ptStart.y} };

		dc.Polygon(arPt1, 4);

		break;
	}

	dc.SelectObject(oldpen);		//이전 pen으로 설정
	dc.SelectObject(oldbrush);		//이전 brush로 설정
	pen.DeleteObject();				//pen 객체 삭제
	brush.DeleteObject();			//brush 객체 삭제
	//Invalidate(false);
	//Invalidate();
}



void CImageToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	CString strPoint;
	strPoint.Format(_T("마우스 위치 x:%d, y:%d"), point.x, point.y);


	//사용 위해 protected->public

	//======================================================
	CClientDC dc(this);							//클라이언트 객체 얻음
	CPen pen, * oldpen;
	switch (m_nPenMode)
	{
	case 0:
		pen.CreatePen(PS_SOLID, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 1:
		pen.CreatePen(PS_DASH, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 2:
		pen.CreatePen(PS_DOT, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 3:
		pen.CreatePen(PS_DASHDOT, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;
	case 4:
		pen.CreatePen(PS_DASHDOTDOT, m_nPenSize, m_PenColor);	//pen 객체 생성
		break;

	}	//Pen 객체 생성
	oldpen = dc.SelectObject(&pen);				//Pen 객체 등록

	//dc.SetROP2(R2_NOTXORPEN);					//R2_NOTXORPEN으로 설정
	//dc.SetROP2(R2_COPYPEN);				
	CBrush brush, * oldbrush;

	if (m_bHatch)
		brush.CreateHatchBrush(m_nHatchStyle, m_PenColor); //Hatch Brush 객체 생성
	else
		brush.CreateSolidBrush(m_PenColor);				 //Solid Brush 객체 생성

	oldbrush = dc.SelectObject(&brush);

	switch (m_nDrawMode)
	{
	case PENCIL_MODE:						//직선 그리기
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.MoveTo(m_ptPrev);
			dc.LineTo(point);			//현재 직선 그림
			m_ptPrev = point;			//이전 점에 현재 점을 저장

		}
		break;

	case LINE_MODE:						//직선 그리기
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptPrev);		//이전 직선 지움
			dc.MoveTo(m_ptStart);
			dc.LineTo(point);			//현재 직선 그림
			m_ptPrev = point;			//이전 점에 현재 점을 저장

		}
		break;

	case ERASER_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_COPYPEN);
			pen.DeleteObject();					//pen 객체 삭제
			brush.DeleteObject();				//brush 객체 삭제
			CPen pen;
			CBrush brush(RGB(255, 255, 255));
			//현재 직선 그림
			pen.CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
			dc.SelectObject(&pen);
			dc.SelectObject(&brush);
			//dc.SelectObject(&brush);
			dc.Ellipse(point.x - 15, point.y - 15, point.x + 15, point.y + 15);


			m_ptPrev = point;			//이전 점에 현재 점을 저장
		}

	case ELLIPSE_MODE:					//원 그리기
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Ellipse(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;			//이전 점에 현재 점을 저장
		}
		break;

	case RECTANGLE_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.Rectangle(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Rectangle(m_ptStart.x, m_ptStart.y, point.x, point.y);
			m_ptPrev = point;
		}
		break;
	case ROUNDRECT_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.RoundRect(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y, 50, 50);
			dc.RoundRect(m_ptStart.x, m_ptStart.y, point.x, point.y, 50, 50);
			m_ptPrev = point;
		}
		break;
	case TRAPEZOID_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);

			POINT arPt1[5] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x, m_ptPrev.y},{ m_ptPrev.x, m_ptPrev.y},{(m_ptStart.x + m_ptPrev.x) / 2,m_ptStart.y} };
			POINT arPt2[5] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x, point.y},{point.x, point.y},{(m_ptStart.x + point.x) / 2,m_ptStart.y} };

			dc.Polygon(arPt1, 4);
			dc.Polygon(arPt2, 4);
			m_ptPrev = point;

		}



	case PIERECT_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			CRect PieRect(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, m_ptStart.y), CPoint(m_ptStart.x, PieRect.CenterPoint().y));
			dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, m_ptStart.y), CPoint(m_ptStart.x, PieRect.CenterPoint().y));
			//dc.Pie(PieRect, CPoint(m_ptStart.x, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, m_ptStart.y));
			//dc.Pie(PieRect, CPoint(m_ptStart.x, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, m_ptStart.y));
			//dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, PieRect.top), CPoint(point.x, point.y));
			m_ptPrev = point;
		}
	case PIERECT270_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			CRect PieRect(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);

			dc.Pie(PieRect, CPoint(m_ptStart.x, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, m_ptStart.y));
			dc.Pie(PieRect, CPoint(m_ptStart.x, PieRect.CenterPoint().y), CPoint(PieRect.CenterPoint().x, m_ptStart.y));

			m_ptPrev = point;
		}
		break;
	case HALFCIRCLE_HORIZONTAL_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			CRect PieRect(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Pie(PieRect, CPoint(m_ptPrev.x, PieRect.CenterPoint().y), CPoint(m_ptStart.x, PieRect.CenterPoint().y));
			dc.Pie(PieRect, CPoint(m_ptPrev.x, PieRect.CenterPoint().y), CPoint(m_ptStart.x, PieRect.CenterPoint().y));

			m_ptPrev = point;
		}
		break;
	case HALFCIRCLE_VERTICAL_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);
			CRect PieRect(m_ptStart.x, m_ptStart.y, m_ptPrev.x, m_ptPrev.y);
			dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, m_ptStart.y), CPoint(PieRect.CenterPoint().x, m_ptPrev.y));
			dc.Pie(PieRect, CPoint(PieRect.CenterPoint().x, m_ptStart.y), CPoint(PieRect.CenterPoint().x, m_ptPrev.y));

			m_ptPrev = point;
		}
		break;
	case TRIANGLE_MODE:
		if (m_bLButtonDown)
		{

			dc.SetROP2(R2_NOTXORPEN);

			//POINT arPt1[4] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x  , m_ptPrev.y},{ m_ptPrev.x, m_ptPrev.y} };
			//POINT arPt2[4] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x , point.y},{point.x, point.y} };

			POINT arPt1[4] = { {m_ptStart.x, m_ptStart.y}, { (m_ptPrev.x - m_ptStart.x), m_ptPrev.y }, { m_ptPrev.x, m_ptPrev.y } };
			POINT arPt2[4] = { {m_ptStart.x, m_ptStart.y}, { (point.x - m_ptStart.x), point.y }, { point.x, point.y } };
			dc.Polygon(arPt1, 3);
			dc.Polygon(arPt2, 3);

			m_ptPrev = point;
		}
		break;

	case RIGHTTRIANGLE_MODE:
		if (m_bLButtonDown)
		{
			dc.SetROP2(R2_NOTXORPEN);

			POINT arPt1[4] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x, m_ptPrev.y},{ m_ptPrev.x, m_ptPrev.y} };
			POINT arPt2[4] = { {m_ptStart.x,m_ptStart.y},{m_ptStart.x, point.y},{point.x, point.y} };

			dc.Polygon(arPt1, 3);
			dc.Polygon(arPt2, 3);
			m_ptPrev = point;
		}
		break;
	case PENTAGON_MODE:
		if (m_bLButtonDown)
		{
			POINT arPt1[6] = {
		 {m_ptStart.x,m_ptStart.y}, {m_ptStart.x, m_ptPrev.y}, { (m_ptPrev.x + m_ptStart.x) / 2, m_ptPrev.y + (m_ptPrev.y - m_ptStart.y) / 2 },
				{ m_ptPrev.x, m_ptPrev.y },{m_ptPrev.x,m_ptStart.y} };
			POINT arPt2[6] = {
			{m_ptStart.x,m_ptStart.y}, {m_ptStart.x, point.y}, { (point.x + m_ptStart.x) / 2, point.y + (point.y - m_ptStart.y) / 2 },
				{ point.x, point.y },{point.x,m_ptStart.y} };

			dc.Polygon(arPt1, 5);
			dc.Polygon(arPt2, 5);

			m_ptPrev = point;
		}
		break;
	case HEXAGON_MODE:
		if (m_bLButtonDown)
		{
			POINT arPt1[7] = {
				{m_ptStart.x,m_ptStart.y}, {m_ptStart.x, (m_ptStart.y + m_ptPrev.y) / 2},{(m_ptStart.x + m_ptPrev.x) / 2,m_ptPrev.y},
				{m_ptPrev.x,m_ptPrev.y},{m_ptPrev.x, (m_ptStart.y + m_ptPrev.y) / 2},{(m_ptStart.x + m_ptPrev.x) / 2,m_ptStart.y}

			};
			POINT arPt2[7] = {

				{m_ptStart.x,m_ptStart.y}, {m_ptStart.x, (m_ptStart.y + point.y) / 2},{(m_ptStart.x + point.x) / 2,point.y},
				{point.x,point.y},{point.x, (m_ptStart.y + point.y) / 2},{(m_ptStart.x + point.x) / 2,m_ptStart.y} };

			dc.Polygon(arPt1, 6);
			dc.Polygon(arPt2, 6);

			m_ptPrev = point;
		}
		break;

	case OCTAGON_MODE:
		if (m_bLButtonDown)
		{
			POINT arPt1[9] = {
				{m_ptStart.x,(m_ptStart.y + m_ptPrev.y) / 3},{m_ptStart.x,((m_ptStart.y + m_ptPrev.y) / 3) * 2},
				{(m_ptStart.x + m_ptPrev.x) / 3,m_ptPrev.y},{((m_ptStart.x + m_ptPrev.x) / 3) * 2 ,m_ptPrev.y},
				{m_ptPrev.x,((m_ptStart.y + m_ptPrev.y) / 3) * 2},{m_ptPrev.x,(m_ptStart.y + m_ptPrev.y) / 3},
				{((m_ptStart.x + m_ptPrev.x) / 3) * 2 ,m_ptStart.y},{(m_ptStart.x + m_ptPrev.x) / 3,m_ptStart.y}
			};
			POINT arPt2[9] = {
				{m_ptStart.x,(m_ptStart.y + point.y) / 3},{m_ptStart.x,((m_ptStart.y + point.y) / 3) * 2},
				{(m_ptStart.x + point.x) / 3,point.y},{((m_ptStart.x + point.x) / 3) * 2 ,point.y},
				{point.x,((m_ptStart.y + point.y) / 3) * 2},{point.x,(m_ptStart.y + point.y) / 3},
				{((m_ptStart.x + point.x) / 3) * 2 ,m_ptStart.y},{(m_ptStart.x + point.x) / 3,m_ptStart.y}
			};

			dc.Polygon(arPt1, 8);
			dc.Polygon(arPt2, 8);

			m_ptPrev = point;
		}
		break;
	}

	pen.DeleteObject();					//pen 객체 삭제
	brush.DeleteObject();				//brush 객체 삭제
	//Invalidate(FALSE);
	CScrollView::OnMouseMove(nFlags, point);
}



void CImageToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bFirst)
	{
		m_ptStart = m_ptPrev = 0;
		m_bLButtonDown = false;
		m_nCount = 0;
		for (int i = 0; i < 100; i++)
			m_ptData[i] = 0;
		Invalidate(false);		//화면갱신
	}

	switch (m_nDrawMode)
	{
	case PENCIL_MODE:
	case LINE_MODE:						//직선 그리기
	case ELLIPSE_MODE:					//원 그리기
	case RECTANGLE_MODE:
	case TRIANGLE_MODE:
	case RIGHTTRIANGLE_MODE:
	case PENTAGON_MODE:
	case HEXAGON_MODE:
	case OCTAGON_MODE:
	case ROUNDRECT_MODE:
	case PIERECT_MODE:
	case HALFCIRCLE_HORIZONTAL_MODE:
	case HALFCIRCLE_VERTICAL_MODE:
	case PIERECT270_MODE:
	case ERASER_MODE:
	case TRAPEZOID_MODE:
		m_bLButtonDown = true;			//왼쪽 버튼 눌림
		m_ptStart = m_ptPrev = point;	//시작 점과 이전 점에 현재 점을 저장
		m_bFirst = false;				//처음 그리는 것 -> false
		//m_bHatch = true;
		//Invalidate(false);
		break;
	}

	//러버밴드 때문에 추가
	RECT rectClient;					//구조체 변수 선언
	SetCapture();						//마우스 캡처
	GetClientRect(&rectClient);			//클라이언트 영역 받음
	ClientToScreen(&rectClient);		//스크린 좌표계 변환
	::ClipCursor(&rectClient);			//마우스 이동 범위를 클라이언트 영역으로 제한


	CScrollView::OnLButtonDown(nFlags, point);
}



void CImageToolView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bLButtonDown)
	{
		if (m_nDrawMode == PENCIL_MODE || m_nDrawMode == LINE_MODE || m_nDrawMode == ELLIPSE_MODE || m_nDrawMode == RECTANGLE_MODE
			|| m_nDrawMode == TRIANGLE_MODE || m_nDrawMode == RIGHTTRIANGLE_MODE || m_nDrawMode == ROUNDRECT_MODE
			|| m_nDrawMode == PIERECT_MODE || m_nDrawMode == HALFCIRCLE_HORIZONTAL_MODE || m_nDrawMode == HALFCIRCLE_VERTICAL_MODE
			|| m_nDrawMode == PIERECT270_MODE || m_nDrawMode == ERASER_MODE || m_nDrawMode == PENTAGON_MODE || m_nDrawMode == HEXAGON_MODE
			|| m_nDrawMode == OCTAGON_MODE || m_nDrawMode == TRAPEZOID_MODE)
		{
			m_bLButtonDown = false;
			m_bFirst = true;
			//m_bHatch = true;
			ReleaseCapture();		//마우스 캡처 해제
			::ClipCursor(NULL);		//마우스 클립 해제
			Invalidate(false);		//화면 갱신
		}
	}
	CScrollView::OnLButtonUp(nFlags, point);
}




void CImageToolView::OnButtonPencil()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 0;

	//스테이터스 바 표시
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("연필 그리기"));
}


void CImageToolView::OnButtonColor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor(m_PenColor, CC_FULLOPEN);
	if (dlgColor.DoModal() == IDOK)
	{
		m_PenColor = dlgColor.GetColor();
	}
}


void CImageToolView::OnButtonEraser()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 4;
}


void CImageToolView::OnButtonColorfill()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CColorDialog dlgColor(m_BrushColor, CC_FULLOPEN);
	if (dlgColor.DoModal() == IDOK)
	{
		m_BrushColor = dlgColor.GetColor();
	}
}


void CImageToolView::OnButtonAllerase()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Invalidate(TRUE);
}


void CImageToolView::OnButtonLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 1;

	//스테이터스 바 표시
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("직선 그리기"));
}


void CImageToolView::OnButtonRighttri()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 6;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("직각삼각형 그리기"));

}


void CImageToolView::OnButtonRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 3;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("사각형 그리기"));
}


void CImageToolView::OnButtonRoundrect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 7;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("둥근사각형 그리기"));
}


void CImageToolView::OnButtonTrapezoid()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 15;
}


void CImageToolView::OnButtonPentagon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 12;
}


void CImageToolView::OnButtonHexagon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 13;
}


void CImageToolView::OnButtonPierect()
{
	m_nDrawMode = 8;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("부채꼴 그리기"));
}


void CImageToolView::OnButtonHalfcircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 9;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("반원(가로) 그리기"));
}


void CImageToolView::OnButtonHalfcircle2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 10;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("반원(세로) 그리기"));
}


void CImageToolView::OnButton270pierect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 11;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("270도 부채꼴 그리기"));
}


void CImageToolView::OnButtonCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nDrawMode = 2;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->m_wndStatusBar.SetWindowText(_T("원 그리기"));
}


void CImageToolView::OnButtonSolid()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nPenMode = 0;
}


void CImageToolView::OnButtonDash()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nPenMode = 1;
}


void CImageToolView::OnButtonDot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nPenMode = 2;
}


void CImageToolView::OnButtonDashdot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nPenMode = 3;
}


void CImageToolView::OnButtonDashdotdot()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_nPenMode = 4;
}


void CImageToolView::OnButtonDefault()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bHatch = false;
}


void CImageToolView::OnButtonHorizontal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bHatch = true;
	m_nHatchStyle = HS_HORIZONTAL;
	if (m_BrushColor == RGB(255, 255, 255))
		m_BrushColor = BLACK_BRUSH;
}


void CImageToolView::OnButtonVertical()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bHatch = true;
	m_nHatchStyle = HS_VERTICAL;
	if (m_BrushColor == RGB(255, 255, 255))
		m_BrushColor = BLACK_BRUSH;
}


void CImageToolView::OnButtonBdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bHatch = true;
	m_nHatchStyle = HS_BDIAGONAL;
	if (m_BrushColor == RGB(255, 255, 255))
		m_BrushColor = BLACK_BRUSH;
}


void CImageToolView::OnButtonFdiagonal()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bHatch = true;
	m_nHatchStyle = HS_FDIAGONAL;
	if (m_BrushColor == RGB(255, 255, 255))
		m_BrushColor = BLACK_BRUSH;
}


void CImageToolView::OnButtonCross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bHatch = true;
	m_nHatchStyle = HS_CROSS;
	if (m_BrushColor == RGB(255, 255, 255))
		m_BrushColor = BLACK_BRUSH;
}


void CImageToolView::OnButtonDiagcross()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bHatch = true;
	m_nHatchStyle = HS_DIAGCROSS;
	if (m_BrushColor == RGB(255, 255, 255))
		m_BrushColor = BLACK_BRUSH;
}
