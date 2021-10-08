#include "pch.h"
#include "CListenSocket.h"
#include "CClientSocket.h"
#include "..\ImageTool\ImageToolDoc.h"

void AFX_EXT_CLASS CListenSocket::OnAccept(int nErrorCode)
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

void AFX_EXT_CLASS CListenSocket::CloseClientSocket(CSocket* pClient)
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

void AFX_EXT_CLASS CListenSocket::SendChatDataAll(TCHAR* pszMessage)
{
	POSITION pos;
	pos = m_ptrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;
	TCHAR test[1024] = _T(".detect");

	while (pos != NULL)
	{
		pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
		{
			pClient->Send(pszMessage, lstrlen(pszMessage) * 2);
			if (0 == _tcscmp(pszMessage, _T(".detect")))
			{
				// ����
				
				AfxMessageBox(_T("�ȳ��ϼ���"));

				//CImageToolDoc* pMain = (CImageToolDoc*)AfxGetMainWnd();
				//pMain->OnTest();
			}
		}
	}
}
