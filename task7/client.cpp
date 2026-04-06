#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int sock;
    sockaddr_in serverAddr;
    char text[1000];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5055);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    while (true) {
        cout << "Your message: "; 
        cin.getline(text, sizeof(text));
        send(sock, text, strlen(text), 0);

        int r = recv(sock, text, sizeof(text), 0);
        if (r <= 0) break;

        cout << "Server: " << text << endl;
    }

    close(sock);
    return 0;
}
