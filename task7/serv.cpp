#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int serverSock, clientSock;
    sockaddr_in serverAddr, clientAddr;
    socklen_t clientSize = sizeof(clientAddr);
    char text[1000];

    // create server socket
    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    // server info
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5055);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSock, 1);

    // accept client connection
    clientSock = accept(serverSock, (sockaddr*)&clientAddr, &clientSize);
    cout << "Client connected! You can start chatting." << endl;  

   while (true) {
    memset(text, 0, sizeof(text)); 
    int r = recv(clientSock, text, sizeof(text), 0);
    if (r <= 0) break;

    cout << "Client: " << text << endl;

    cout << "Your reply: ";
    cin.getline(text, sizeof(text));
    send(clientSock, text, strlen(text), 0);
}

    close(clientSock);
    close(serverSock);
    return 0;
}
