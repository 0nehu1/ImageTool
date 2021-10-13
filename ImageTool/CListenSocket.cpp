#include "CListenSocket.h"
#include "CClientSocket.h"
//#include "ImageToolView.h"
#include "ImageToolDoc.h"



CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}

void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CClientSocket* pClient = new CClientSocket;
	if (Accept(*pClient))
	{
		pClient->SetListenSocket(this);
		m_ptrClientSocketList.AddTail(pClient);
	}
	else
	{
		delete pClient;
		AfxMessageBox(_T("ERROR: Failed to accept new client!"));
	}


	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::CloseClientSocket(CSocket* pClient)
{
	POSITION pos;
	pos = m_ptrClientSocketList.Find(pClient);
	if (pos != NULL)
	{
		if (pClient != NULL)
		{
			pClient->ShutDown();
			pClient->Close();
		}

		m_ptrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
}

void CListenSocket::SendChatDataAll(TCHAR* pszMessage)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while (pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
		{
			pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
			if (0 == _tcscmp(pszMessage, _T(".detect")))
			{
				//메인프레임을 통해서 CTestView 를 받는다.
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
			   //도큐먼트의 m_strText안에 현재 대화상자의 m_strText를 연결시킨다.
		       pView->OnTest();
			   //데이타를 다이얼로그 리소스로 전송
			}
		}
	}
}
