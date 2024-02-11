#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDateTime>

class Message
{
public :
    int idMsg;
    int idAuteur;
    QString contenu;
    int heure;
    int min;

public:
    Message(int idMsg, int idAuteur, QString contenu);

    Message(int idMsg, int idAuteur, QString contenu, int heure, int min);

    ~Message(){}

    int getMsgId();

    void editMsgContent(QString nouveauContenu);
};


#endif // MESSAGE_H
