#include "CMakeProject1.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

// Реализация методов класса SharedBuffer
void SharedBuffer::add(const string& data) {
    unique_lock<mutex> lk(mtx);
    buffer.push_back(data);
    cv.notify_one();
}

string SharedBuffer::get() {
    unique_lock<mutex> lk(mtx);
    cv.wait(lk, [this] { return !buffer.empty(); });
    string data = buffer.front();
    buffer.pop_front();
    return data;
}

void inputDataThread(SharedBuffer& sharedBuffer) {
    while (true) {
        string input;
        cout << "Введите строку до 64 цифр: ";
        getline(cin, input);
        if (input.length() > 64 || input.find_first_not_of("0123456789") != string::npos) {
            cout << "Неверный ввод. Попробуйте снова." << endl;
            continue;
        }

        sort(input.begin(), input.end(), greater<char>());
        for (size_t i = 0; i < input.length(); ++i) {
            if ((input[i] - '0') % 2 == 0) {
                input.replace(i, 1, "KB");
                i += 1;
            }
        }

        sharedBuffer.add(input);
    }
}

void outputDataThread(SharedBuffer& sharedBuffer, SOCKET sockfd) {
    while (true) {
        string data = sharedBuffer.get();

        cout << "Отправленные данные: " << data << endl;

        int sum = 0;
        for (char c : data) {
            if (isdigit(c)) {
                sum += c - '0';
            }
        }

        send(sockfd, to_string(sum).c_str(), to_string(sum).length(), 0); // Отправка суммы
    }
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));

    SharedBuffer sharedBuffer;

    thread inputThread(inputDataThread, ref(sharedBuffer));
    thread outputThread(outputDataThread, ref(sharedBuffer), sockfd);

    inputThread.join();
    outputThread.join();

    closesocket(sockfd);
    WSACleanup();
    return 0;
}