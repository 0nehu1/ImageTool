#pragma once


// LineControl 대화 상자

class LineControl : public CDialogEx
{
	DECLARE_DYNAMIC(LineControl)

public:
	LineControl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~LineControl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LINECONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SliderLineControl;
	CEdit m_EditLineControl;
	int m_ValueLineControl;
	int m_StrSize;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditLinecontrol();
	afx_msg void OnBnClickedOk();
};
