#include "message.h"
#include <QRegularExpression>

Message::Message(): idMsg(0), idAuteur(0), idDestinataire(0), contenu(""), sec(0), currentDate(""){}

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

void Message::translateFromBuffer(char* buffer) {
    QString bufferString(buffer);

    // Trouver les positions des différents champs
    int idMsgPos = bufferString.indexOf("I:{") + 3;
    int idAuteurPos = bufferString.indexOf("A:{") + 3;
    int idDestinatairePos = bufferString.indexOf("D:{") + 3;
    int contenuPos = bufferString.indexOf("C:{") + 3;
    int currentDatePos = bufferString.indexOf("S:{") + 3;
    int currentDatePosFin = bufferString.indexOf("}", currentDatePos);



    // Extraire les sous-chaînes correspondantes aux différents champs
    idMsg = bufferString.mid(idMsgPos, bufferString.indexOf("}", idMsgPos) - idMsgPos).toInt();
    idAuteur = bufferString.mid(idAuteurPos, bufferString.indexOf("}", idAuteurPos) - idAuteurPos).toInt();
    idDestinataire = bufferString.mid(idDestinatairePos, bufferString.indexOf("}", idDestinatairePos) - idDestinatairePos).toInt();
    contenu = bufferString.mid(contenuPos, bufferString.indexOf("}", contenuPos) - contenuPos);

    //La recuperation de la date est un peu plus complexe car il faut la separer des secondes
    QString dateAndSec = bufferString.mid(currentDatePos, currentDatePosFin - currentDatePos);
    QStringList dateAndSecSplited = dateAndSec.split('/');
    currentDate = dateAndSecSplited[0] + "/" + dateAndSecSplited[1] + "/" + dateAndSecSplited[2];
    sec = dateAndSecSplited[3].toInt();
}


