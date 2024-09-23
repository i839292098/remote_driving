#include <iostream>
#include <thread>
#include "tcp_server.cpp"
#include "websocket_server.cpp"

CTcpServerListener4Vehicle listenner1;
CTcpServerListener4Cockpit listenner2;
CTcpServerPtr tcpServer4Vehicle(&listenner1);
CTcpServerPtr tcpServer4Cockpit(&listenner2);
WebSocketServer wsServer;

int main(int argc, char *argv[]) {
    std::thread t1([]() {
        int vehiclePort = 8000;
        while (!tcpServer4Vehicle->Start("192.168.3.216", vehiclePort)) {
            printf("TCP-%d vehicle 端口启动失败\n", vehiclePort);
            std::cout << SYS_GetLastError() << ": " << SYS_GetLastErrorStr() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
        printf("TCP-%d vehicle 端口启动成功\n", vehiclePort);

        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        tcpServer4Vehicle->Stop(); });

    std::thread t2([]() {
        int cockpitPort = 8001;
        while (!tcpServer4Cockpit->Start("192.168.3.216", cockpitPort)) {
            printf("TCP-%d cockpit 端口启动失败\n", cockpitPort);
            std::cout << SYS_GetLastError() << ": " << SYS_GetLastErrorStr() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
        printf("TCP-%d cockpit 端口启动成功\n", cockpitPort);

        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        tcpServer4Cockpit->Stop(); });

    std::thread t3([]() { 
        wsServer.run(8002); 
    });

    t1.join();
    t2.join();
    t3.join();
    return -1;
}