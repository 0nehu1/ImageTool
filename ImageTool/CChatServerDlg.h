#pragma once
#include "pch.h"
#include "..\DLLTool\CListenSocket.h"
#include "afxdialogex.h"
// CChatServerDlg 대화 상자

class CChatServerDlg : public CDialog
{
//	DECLARE_DYNAMIC(CChatServerDlg)

public:
	CChatServerDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	
	CListenSocket m_ListenSocket;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CHAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_List;
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};
