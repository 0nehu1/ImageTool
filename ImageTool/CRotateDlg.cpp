// CRotateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "CRotateDlg.h"
#include "afxdialogex.h"


// CRotateDlg 대화 상자

IMPLEMENT_DYNAMIC(CRotateDlg, CDialogEx)

CRotateDlg::CRotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ROTATE, pParent)
	, m_nRotate(0)
	, m_fAngle(0)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_ROTATE1, m_nRotate);
	DDX_Text(pDX, IDC_ANGLE, m_fAngle);
	DDV_MinMaxFloat(pDX, m_fAngle, 0, 360);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ROTATE4, &CRotateDlg::OnBnClickedRotate4)
	ON_EN_SETFOCUS(IDC_ANGLE, &CRotateDlg::OnEnSetfocusAngle)
END_MESSAGE_MAP()


// CRotateDlg 메시지 처리기


void CRotateDlg::OnBnClickedRotate4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nRotate = 3;
	UpdateData(FALSE);
}


void CRotateDlg::OnEnSetfocusAngle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_ANGLE);
	pEdit->SetSel(0, -1);
	pEdit->SetFocus();
}
