
// ImageToolView.h: CImageToolView 클래스의 인터페이스
//

#pragma once
#include <vector>
#include <memory>
#pragma once
enum DRAW_MODE {
	PENCIL_MODE, LINE_MODE, ELLIPSE_MODE, RECTANGLE_MODE, ERASER_MODE
	, TRIANGLE_MODE, RIGHTTRIANGLE_MODE, ROUNDRECT_MODE, PIERECT_MODE, HALFCIRCLE_HORIZONTAL_MODE, HALFCIRCLE_VERTICAL_MODE
	, PIERECT270_MODE, PENTAGON_MODE, HEXAGON_MODE, OCTAGON_MODE, TRAPEZOID_MODE
};
enum PEN_MODE { SOLID_MODE, DASH_MODE, DOT_MODE, DASHDOT_MODE, DASHDOTDOT_MODE };

class CImageToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageToolView() noexcept;
	DECLARE_DYNCREATE(CImageToolView)

// 특성입니다.
public:
	CImageToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	void SetScrollSizeToFit(void);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 이미지 확대 배율
	int m_nZoom;
	afx_msg void OnViewZoom1();
	afx_msg void OnUpdateViewZoom1(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom2();
	afx_msg void OnUpdateViewZoom2(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom3();
	afx_msg void OnUpdateViewZoom3(CCmdUI* pCmdUI);
	afx_msg void OnViewZoom4();
	afx_msg void OnUpdateViewZoom4(CCmdUI* pCmdUI);
//	afx_msg void OnPaint();

public:

	CPoint m_ptStart;
	CPoint m_ptPrev;
	bool m_bFirst;
	bool m_bLButtonDown;
	bool m_bContextMenu;
	bool m_bHatch;
	CPoint m_ptData[100];

	int m_nCount;
	COLORREF m_PenColor;
	COLORREF m_BrushColor;
	int m_nPenMode;
	int m_nDrawMode;
	int m_nHatchStyle;
	int m_nPenSize;
	



	std::shared_ptr<Gdiplus::Bitmap> m_canvasAfterDrawing;
	std::shared_ptr<Gdiplus::Bitmap> m_canvasDuringDraw;
	CRect m_picture;

	

	//afx_msg void OnFileOpen();
	
	

	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnButtonPencil();
	afx_msg void OnButtonColor();
	afx_msg void OnButtonEraser();
	afx_msg void OnButtonColorfill();
	afx_msg void OnButtonAllerase();
	afx_msg void OnButtonLine();
	afx_msg void OnButtonRighttri();
	afx_msg void OnButtonRect();
	afx_msg void OnButtonRoundrect();
	afx_msg void OnButtonTrapezoid();
	afx_msg void OnButtonPentagon();
	afx_msg void OnButtonHexagon();
	afx_msg void OnButtonPierect();
	afx_msg void OnButtonHalfcircle();
	afx_msg void OnButtonHalfcircle2();
	afx_msg void OnButton270pierect();
	afx_msg void OnButtonCircle();
	afx_msg void OnButtonSolid();
	afx_msg void OnButtonDash();
	afx_msg void OnButtonDot();
	afx_msg void OnButtonDashdot();
	afx_msg void OnButtonDashdotdot();
	afx_msg void OnButtonDefault();
	afx_msg void OnButtonHorizontal();
	afx_msg void OnButtonVertical();
	afx_msg void OnButtonBdiagonal();
	afx_msg void OnButtonFdiagonal();
	afx_msg void OnButtonCross();
	afx_msg void OnButtonDiagcross();
};

#ifndef _DEBUG  // ImageToolView.cpp의 디버그 버전
inline CImageToolDoc* CImageToolView::GetDocument() const
   { return reinterpret_cast<CImageToolDoc*>(m_pDocument); }
#endif

