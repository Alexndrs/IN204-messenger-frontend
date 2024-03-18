#include "message.h"

Message::Message(int idMsg, int idAuteur, int idDestinataire, QString contenu) : idMsg(idMsg), idAuteur(idAuteur), idDestinataire(idDestinataire), contenu(contenu)
{
    // Obtenir l'heure actuelle du système
    QDateTime currentTime = QDateTime::currentDateTime();

    // la seconde de la journee
    sec = 3600 * currentTime.time().hour() + 60 * currentTime.time().minute() + currentTime.time().second();

    // Date
    QDate dateNow = QDate::currentDate();
    currentDate = dateNow.toString("dd/MM/yyyy");
}

int Message::getMsgId(){
    return Message::idMsg;
}

void Message::editMsgContent(QString nouveauContenu){
    Message::contenu = nouveauContenu;
}

char* Message::translateToBuffer(int& bufferSize) {
    QString formattedString = QString("{I:{%1},A:{%2},D:{%3},S:{%4/%5},C:{%6}}")
                         .arg(idMsg)
                         .arg(idAuteur)
                         .arg(idDestinataire)
                         .arg(currentDate)
                         .arg(sec)
                         .arg(contenu);

    // Allouer un nouveau tableau de caractères pour stocker le contenu de QString
    bufferSize = formattedString.length() + 1;
    char* buffer = new char[bufferSize];

    // Copier le contenu de QString dans le tableau de caractères
    strcpy(buffer, formattedString.toLatin1().constData());

    // Ajouter un caractère nul de fin de chaîne
    buffer[formattedString.length()] = '\0';

    return buffer;
}


