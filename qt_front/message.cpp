#include "message.h"

Message::Message(int idMsg, int idAuteur, QString contenu) : idMsg(idMsg), idAuteur(idAuteur), contenu(contenu)
{
    // Obtenir l'heure actuelle du système
    QDateTime currentTime = QDateTime::currentDateTime();

    // Initialiser heure et min avec l'heure actuelle
    heure = currentTime.time().hour();
    min = currentTime.time().minute();
}

Message::Message(int idMsg, int idAuteur, QString contenu, int heure, int min) : idMsg(idMsg), idAuteur(idAuteur),contenu(contenu), heure(heure), min(min){}

int Message::getMsgId(){
    return Message::idMsg;
}

void Message::editMsgContent(QString nouveauContenu){
    Message::contenu = nouveauContenu;
}

