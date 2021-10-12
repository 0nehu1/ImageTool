#include "pch.h"
#include "CListenSocket.h"
#include "CClientSocket.h"
#include "..\ImageTool\ImageToolDoc.h"



void AFX_EXT_CLASS CListenSocket::OnAccept(int nErrorCode)
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
				// 같다
				
			//	AfxMessageBox(_T("안녕하세요"));

				//CImageToolDoc* pMain = (CImageToolDoc*)AfxGetMainWnd();
				//pMain->OnTest();
				//CImageToolDoc* pDoc = (CImageToolDoc*)GetActiveDocument();
				//CImageToolDoc* pDoc = (CImageToolDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
			
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				//pView->OnTestPoint();
				
				typedef void  (*fp_OnTestExe)();
				fp_OnTestExe OnTestExe;

				HINSTANCE hExe = GetModuleHandle(NULL);
				OnTestExe = (fp_OnTestExe)GetProcAddress(hExe, "OnHarrisCorner");

				OnTestExe();


				//CImageToolDoc* pMain = (CImageToolDoc*)AfxGetApp()->GetMainWnd();
				//CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				//pView->OnTestExe();

				// 
				//CFrameWnd* pMainWnd = (CFrameWnd*)AfxGetMainWnd();
				//CImageToolDoc* pDoc = (CImageToolDoc*)pMainWnd->GetActiveDocument();
				//pDoc->OnTestExe();
			}
		}
	}
}

