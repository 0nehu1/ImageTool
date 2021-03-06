// CChatServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "ImageTool.h"
#include "CChatServerDlg.h"
#include "afxdialogex.h"
#include "framework.h"

#include <afxodlgs.h>
#include "ImageToolView.h"
#include "CClientSocket.h"


// CChatServerDlg 대화 상자

//IMPLEMENT_DYNAMIC(CChatServerDlg, CDialogEx)

CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_CHAT, pParent)
{

}
CImageToolDoc* theDoc1;
CChatServerDlg::CChatServerDlg(CImageToolDoc* pDoc)
	:CDialog(IDD_DIALOG_CHAT, NULL)
{
	m_pDoc = pDoc;
}





void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);

	
}


BEGIN_MESSAGE_MAP(CChatServerDlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CChatServerDlg 메시지 처리기


void CChatServerDlg::SendData()
{
	
}

BOOL CChatServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();



	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	if (m_ListenSocket.Create(21000, SOCK_STREAM))
	{
		if (!m_ListenSocket.Listen())
		{
			AfxMessageBox(_T("ERROR: Listen() retuen FALSE"));
		}
	}
	else
	{
		AfxMessageBox(_T("ERROR: Failed to create server socket!"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CChatServerDlg::OnDestroy()
{
	CDialog::OnDestroy();


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	POSITION pos;

	pos = m_ListenSocket.m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while (pos != NULL)
	{
		pClient = (CClientSocket*)
			m_ListenSocket.m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
		{

			pClient->ShutDown();
			pClient->Close();

			delete pClient;
		}
	}

	m_ListenSocket.ShutDown();
	m_ListenSocket.Close();
}
