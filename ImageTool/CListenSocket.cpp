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
			if (0 == _tcscmp(pszMessage, _T(".noise")) || 0 == _tcscmp(pszMessage, _T(".���������")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnTest();
			  
			}

			else if (0 == _tcscmp(pszMessage, _T(".point1"))|| 0 == _tcscmp(pszMessage, _T(".������1")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnTestPoint();

			}
			else if (0 == _tcscmp(pszMessage, _T(".point2")) || 0 == _tcscmp(pszMessage, _T(".������2")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnTestPoint2();

			}
			else if (0 == _tcscmp(pszMessage, _T(".sobel")) || 0 == _tcscmp(pszMessage, _T(".�Һ�����ũ")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnEdgeSobel();

			}
			else if (0 == _tcscmp(pszMessage, _T(".roberts")) || 0 == _tcscmp(pszMessage, _T(".�ι�������ũ")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnEdgeRoberts();

			}
			else if (0 == _tcscmp(pszMessage, _T(".prewitt")) || 0 == _tcscmp(pszMessage, _T(".����������ũ")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnEdgePrewitt();

			}
			else if (0 == _tcscmp(pszMessage, _T(".binary")) || 0 == _tcscmp(pszMessage, _T(".����ȭ")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnSegmentBinarization();

			}
			else if (0 == _tcscmp(pszMessage, _T(".label")) || 0 == _tcscmp(pszMessage, _T(".���̺�")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnSegmentLabeling();

			}
			else if (0 == _tcscmp(pszMessage, _T(".gray")) || 0 == _tcscmp(pszMessage, _T(".�׷��̽�����")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnColorGrayscale();
			}
			else if (0 == _tcscmp(pszMessage, _T(".mean")) || 0 == _tcscmp(pszMessage, _T(".��հ�")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterMean();
			}
			else if (0 == _tcscmp(pszMessage, _T(".weight")) || 0 == _tcscmp(pszMessage, _T(".������հ�")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterWeightedMean();
			}
			else if (0 == _tcscmp(pszMessage, _T(".gaussian")) || 0 == _tcscmp(pszMessage, _T(".����þ�")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterGaussian();
			}
			else if (0 == _tcscmp(pszMessage, _T(".laplacian")) || 0 == _tcscmp(pszMessage, _T(".���ö�þ�")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterLaplacian();
			}
			else if (0 == _tcscmp(pszMessage, _T(".unsharp")) || 0 == _tcscmp(pszMessage, _T(".�����")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterUnsharpMask();
			}
			else if (0 == _tcscmp(pszMessage, _T(".highboost")) || 0 == _tcscmp(pszMessage, _T(".���̺ν�Ʈ")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterHighboost();
			}
			else if (0 == _tcscmp(pszMessage, _T(".addnoise")) || 0 == _tcscmp(pszMessage, _T(".�����߰�")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnAddNoise();
			}
			else if (0 == _tcscmp(pszMessage, _T(".median")) || 0 == _tcscmp(pszMessage, _T(".�̵��")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterMedian();
			}
			else if (0 == _tcscmp(pszMessage, _T(".diffusion")) || 0 == _tcscmp(pszMessage, _T(".���漺")))
			{
				CImageToolDoc* pView = (CImageToolDoc*)((CFrameWnd*)AfxGetMainWnd())->GetActiveFrame()->GetActiveDocument();
				pView->OnFilterDiffusion();
			}
		}
	}
}
