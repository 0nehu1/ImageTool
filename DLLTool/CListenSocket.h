#pragma once
#include <afxsock.h>
#include "..\ImageTool\ImageToolDoc.h"

class CListenSocket :
    public CAsyncSocket
{
public:
    CImageToolDoc* Image;
    CPtrList m_ptrClientSocketList;
    virtual void AFX_EXT_CLASS OnAccept(int nErrorCode);
    void AFX_EXT_CLASS CloseClientSocket(CSocket* pClient);
    void AFX_EXT_CLASS SendChatDataAll(TCHAR* pszMessage);
};

