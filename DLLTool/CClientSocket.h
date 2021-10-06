#pragma once
#include <afxsock.h>
class CClientSocket :
    public CSocket
{
public:
 

    CAsyncSocket* m_pListenSocket;

    void AFX_EXT_CLASS SetListenSocket(CAsyncSocket* pSocket);

    virtual void AFX_EXT_CLASS OnClose(int nErrorCode);
    virtual void AFX_EXT_CLASS OnReceive(int nErrorCode);
};

