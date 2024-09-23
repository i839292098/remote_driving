#include <hpsocket/HPSocket.h>
#include <iostream>

// 车端通信
class CTcpServerListener4Vehicle : public CTcpServerListener
{
public:
    void PrintInfo(ITcpServer *pSender, CONNID dwConnID)
    {
        char buffer[20];
        char *ipAddr = buffer;
        int ipLen;
        USHORT port;

        pSender->GetListenAddress(ipAddr, ipLen, port);
        std::cout << std::string(ipAddr, 0, ipLen) << ":" << port << " " << "<-  [" << dwConnID << "] ";

        pSender->GetRemoteAddress(dwConnID, ipAddr, ipLen, port);
        std::cout << std::string(ipAddr, 0, ipLen) << ":" << port << " ";
    }

    virtual EnHandleResult OnAccept(ITcpServer *pSender, CONNID dwConnID, UINT_PTR soClient)
    {
        PrintInfo(pSender, dwConnID);
        std::cout << "tcp client 车端连接成功" << std::endl;
        return HR_OK;
    }

    virtual EnHandleResult OnClose(ITcpServer *pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
    {
        PrintInfo(pSender, dwConnID);
        std::cout << "tcp client 车端断开连接" << std::endl;
        pSender->SetConnectionExtra(dwConnID, NULL);
        return HR_OK;
    }

    virtual EnHandleResult OnReceive(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength)
    {
        // std::string msg_Data((char *)pData, 0, iLength);

        // TODO

        return HR_OK;
    }
};

// 驾驶舱通信
class CTcpServerListener4Cockpit : public CTcpServerListener
{
public:
    void PrintInfo(ITcpServer *pSender, CONNID dwConnID)
    {
        char buffer[20];
        char *ipAddr = buffer;
        int ipLen;
        USHORT port;

        pSender->GetListenAddress(ipAddr, ipLen, port);
        std::cout << std::string(ipAddr, 0, ipLen) << ":" << port << " " << "<-  [" << dwConnID << "] ";

        pSender->GetRemoteAddress(dwConnID, ipAddr, ipLen, port);
        std::cout << std::string(ipAddr, 0, ipLen) << ":" << port << " ";
    }

    virtual EnHandleResult OnAccept(ITcpServer *pSender, CONNID dwConnID, UINT_PTR soClient)
    {
        PrintInfo(pSender, dwConnID);
        std::cout << "tcp client 驾驶舱连接成功" << std::endl;
        return HR_OK;
    }

    virtual EnHandleResult OnClose(ITcpServer *pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
    {
        PrintInfo(pSender, dwConnID);
        std::cout << "tcp client 驾驶舱断开连接" << std::endl;
        pSender->SetConnectionExtra(dwConnID, NULL);
        return HR_OK;
    }

    virtual EnHandleResult OnReceive(ITcpServer *pSender, CONNID dwConnID, const BYTE *pData, int iLength)
    {
        // std::string msg_Data((char *)pData, 0, iLength);

        // TODO

        return HR_OK;
    }
};
