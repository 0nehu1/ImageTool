#pragma once
#include "pch.h"

#include "afxdialogex.h"
#include "ImageToolDoc.h"
#include "CListenSocket.h"
// CChatServerDlg 대화 상자

class CChatServerDlg : public CDialog
{
//	DECLARE_DYNAMIC(CChatServerDlg)

public:
	CChatServerDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	CChatServerDlg(CImageToolDoc* pDoc);

	CListenSocket m_ListenSocket;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CImageToolDoc* m_pDoc;
	CListBox m_List;

	void SendData();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};
extern CImageToolDoc* theDoc1;