#pragma once
#include <afxsock.h>
class CListenSocket :
    public CAsyncSocket
{
public:
  
    CPtrList m_ptrClientSocketList;
    virtual void AFX_EXT_CLASS OnAccept(int nErrorCode);
    void AFX_EXT_CLASS CloseClientSocket(CSocket* pClient);
    void AFX_EXT_CLASS SendChatDataAll(TCHAR* pszMessage);
};

