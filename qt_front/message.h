#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

class Message
{
public :
    int idMsg;
    int idAuteur;
    int idDestinataire;
    QString contenu;
    int sec;
    QString currentDate;

public:
    Message(int idMsg, int idAuteur,int idDestinataire, QString contenu);

    ~Message(){}

    int getMsgId();

    void editMsgContent(QString nouveauContenu);

    char* translateToBuffer(int& bufferSize);

};


#endif // MESSAGE_H
