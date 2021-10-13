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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
			if (0 == _tcscmp(pszMessage, _T(".noise")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnTest();
			  
			}

			else if (0 == _tcscmp(pszMessage, _T(".point1")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnTestPoint();

			}
			else if (0 == _tcscmp(pszMessage, _T(".point2")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnTestPoint2();

			}
		}
	}
}
