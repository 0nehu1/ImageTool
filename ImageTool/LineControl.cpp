// LineControl.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "LineControl.h"
#include "afxdialogex.h"


// LineControl 대화 상자

IMPLEMENT_DYNAMIC(LineControl, CDialogEx)

LineControl::LineControl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LINECONTROL, pParent)
	, m_ValueLineControl(0)
{

}

LineControl::~LineControl()
{
}

void LineControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_LINECONTROL, m_SliderLineControl);
	DDX_Control(pDX, IDC_EDIT_LINECONTROL, m_EditLineControl);
	DDX_Text(pDX, IDC_EDIT_LINECONTROL, m_ValueLineControl);
	DDV_MinMaxInt(pDX, m_ValueLineControl, 0, 100);
}


BEGIN_MESSAGE_MAP(LineControl, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_LINECONTROL, &LineControl::OnEnChangeEditLinecontrol)
	ON_BN_CLICKED(IDOK, &LineControl::OnBnClickedOk)
END_MESSAGE_MAP()


// LineControl 메시지 처리기


BOOL LineControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_SliderLineControl.SetRange(0, 100);
	m_SliderLineControl.SetPos(1);
	m_SliderLineControl.SetLineSize(1);
	m_SliderLineControl.SetPageSize(2);

	m_StrSize = m_SliderLineControl.GetPos();
	CString sPos;
	sPos.Format(_T("%d"), m_StrSize);
	m_EditLineControl.SetWindowTextW(sPos);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




void LineControl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (IDC_SLIDER_LINECONTROL == pScrollBar->GetDlgCtrlID())
	{
		// Slider Control 값 읽기
		int iPos = m_SliderLineControl.GetPos();

		CString sPos;
		sPos.Format(_T("%d"), iPos);
		m_EditLineControl.SetWindowText(sPos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void LineControl::OnEnChangeEditLinecontrol()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iPos = m_SliderLineControl.GetPos();
	CString sPos;
	m_EditLineControl.GetWindowText(sPos);
	iPos = _ttoi(sPos);

	//Slider Control에 설정
	m_SliderLineControl.SetPos(iPos);

}




void LineControl::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_StrSize = m_SliderLineControl.GetPos();
	CDialogEx::OnOK();
}
