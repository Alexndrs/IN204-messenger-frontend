// Client de test hors Qt
#include <iostream>
#include <winsock2.h>

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Création du socket client
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Connexion au serveur
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Mettre l'IP du serveur ICI 147.250.234.238
    connect(clientSocket, (sockaddr *)&serverAddress, sizeof(serverAddress));

    // Envoyer des données au serveur
    const char *message = "{I:{2},A:{1},D:{2},S:{17/03/2024/64800},C:{Hello je suis les message d'id 2 envoyé de client 1 a client 2 le 17/03/2024 à 18h}}\0";
    send(clientSocket, message, strlen(message), 0);

    // Envoyer des données au serveur
    const char *autre_message = "{I:{2},A:{1},D:{2},S:{17/03/2024/64825},C:{Un deuxième message pour voir si ca marche}}\0";
    send(clientSocket, autre_message, strlen(autre_message), 0);

    // Recevoir une réponse du serveur
    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0'; // Ajouter le caractère de fin de chaîne
        std::cout << "Réponse du serveur : " << buffer << std::endl;

        // Convertir la chaîne en un entier
        int client_id = std::stoi(buffer);
        std::cout << "Identifiant du client (entier) : " << client_id << std::endl;
    }

    // Fermer le socket client
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}