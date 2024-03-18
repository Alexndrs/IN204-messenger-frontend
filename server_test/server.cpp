// Serveur
#include <iostream>
#include <winsock2.h>
#include <vector>
#include <string>
#include <cstring>

// Définition d'une structure pour stocker les informations des clients
struct ClientInfo
{
    SOCKET socket;
    int id;
};

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Création du socket serveur
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Liaison du socket à une adresse et un port
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(8080);
    bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress));

    // Attente de connexions entrantes
    listen(serverSocket, SOMAXCONN);

    std::vector<ClientInfo> clients; // Vector pour stocker les informations des clients
    int nextClientId = 1;            // Identifiant du prochain client

    while (true)
    {
        // Accepter les connexions entrantes
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        // Créer un objet ClientInfo pour stocker les informations du client
        ClientInfo clientInfo;
        clientInfo.socket = clientSocket;
        clientInfo.id = nextClientId++;

        // Ajouter le client à la liste
        clients.push_back(clientInfo);

        int client_id = clientInfo.id;
        // Envoyer l'identifiant du client au client lui-même
        send(clientSocket, reinterpret_cast<char *>(&client_id), sizeof(client_id), 0);

        // Lire les données du client
        while (true)
        {
            char buffer[1024];
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesRead <= 0)
            {
                // Le client a fermé la connexion ou une erreur s'est produite
                std::cout << "Le client a fermé la connexion ou une erreur s'est produite" << std::endl;
                break;
            }
            std::cout << "Message du client " << clientInfo.id << ":" << buffer << std::endl;

            //// Envoyer une réponse au client
            // send(clientSocket, "Message recu", sizeof("Message recu"), 0);
        }

        // Fermer le socket du client
        closesocket(clientSocket);
    }

    // Fermer le socket du serveur
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}