#include "CMakeProject2.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <chrono>
#include <thread>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sockfd, 5);

    SOCKET clientfd;
    char buffer[1024] = { 0 };

    while (true) {
        cout << "Ожидание подключения..." << endl;
        clientfd = accept(sockfd, NULL, NULL);
        if (clientfd == INVALID_SOCKET) {
            cout << "Ошибка приема подключения. Попытка восстановления..." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            continue;
        }

        cout << "Соединение восстановлено." << endl;

        while (true) {
            memset(buffer, 0, sizeof(buffer));
            int bytes_read = recv(clientfd, buffer, sizeof(buffer), 0);
            if (bytes_read <= 0) {
                cout << "Ошибка приема данных или соединение закрыто. Попытка восстановления..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                break;
            }

            cout << "Полученные данные: " << buffer << endl;

            int num = atoi(buffer);
            int len = strlen(buffer);

            if (len > 2 && (num % 32 == 0)) {
                cout << "Данные корректны." << endl;
            }
            else {
                cout << "Ошибка: данные некорректны." << endl;
            }
        }
        closesocket(clientfd);  // Закрытие старого клиентского соединения
    }

    closesocket(sockfd);
    WSACleanup();
    return 0;
}
