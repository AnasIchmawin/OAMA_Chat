#include <iostream>
#include <winsock2.h>
#include <vector>
#include <thread>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")

std::mutex clientsMutex;

struct ClientInfo {
    SOCKET socket;
    std::string name;
};

void HandleClient(ClientInfo client, std::vector<ClientInfo>& clients) {
    char buffer[1024];
    int bytesRead;

    do {
        bytesRead = recv(client.socket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            buffer[bytesRead] ='\0'; // Null-terminate the received data
            std::cout << client.name << ": " << buffer << "\n";
            // Check if the message includes a recipient
            std::string recipient;
            size_t recipientPos = std::string(buffer).find(":");
            if (recipientPos != std::string::npos) {
                recipient = std::string(buffer, 0, recipientPos);
                std::string message = std::string(buffer, recipientPos + 1,sizeof(buffer));

                // Send the message to the specified recipient
                std::lock_guard<std::mutex> lock(clientsMutex);
                for (const auto& otherClient : clients) {
                    if (otherClient.name == recipient) {
                        send(otherClient.socket, (client.name + ": " + message).c_str(), bytesRead + client.name.size() + 2, 0);
                        break;
                    }
                }
            }
            else {
                // Broadcast the message to all clients
                std::lock_guard<std::mutex> lock(clientsMutex);
                for (const auto& otherClient : clients) {
                    if (otherClient.socket != client.socket) {
                        send(otherClient.socket, (client.name + ": " + buffer).c_str(), bytesRead + client.name.size() + 2, 0);
                    }
                }
            }
        }
        else if (bytesRead == 0) {
            std::cout << client.name << " disconnected.\n";
        }
        else {
            std::cerr << "Receive failed with error: " << WSAGetLastError() << "\n";
        }

    } while (bytesRead > 0);

    // Remove the disconnected client
    std::lock_guard<std::mutex> lock(clientsMutex);
    clients.erase(std::remove_if(clients.begin(), clients.end(),
        [client](const ClientInfo& c) { return c.socket == client.socket; }), clients.end());

    // Cleanup for a specific client
    closesocket(client.socket);
}

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }

    // Create socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Bind the socket
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(12345); // Use any available port

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 12345...\n";

    // Vector to store client information
    std::vector<ClientInfo> clients;

    while (true) {
        // Accept a connection
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed with error: " << WSAGetLastError() << "\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected: " << clientSocket << "\n";

        // Get client name
        char clientName[256];
        int nameLength = recv(clientSocket, clientName, sizeof(clientName), 0);
        if (nameLength > 0) {
            clientName[nameLength] ='\0';
        }

        // Create a thread to handle the client
        std::thread clientThread(HandleClient, ClientInfo{ clientSocket, clientName }, std::ref(clients));

        // Detach the thread, allowing it to run independently
        clientThread.detach();

        // Add the client info to the vector
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.push_back(ClientInfo{ clientSocket, clientName });
    }

    // Cleanup for the server (This won't be reached in this example)
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}