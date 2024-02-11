#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QString>
#include <QVector>
#include "Message.h"

class Conversation
{

private:
    int idFirstPers;
    int idSecPers;
    QString convName;
public:
    QVector<Message> messages;
    int msgIdGenerator = 0; //On incrémente de 1 pour generer un nouvel id de msg pour cette conv
    int idConv;

public:
    // Constructeur prenant tous les paramètres
    Conversation(int idConv, int idFirstPers, int idSecPers, QString convName, QVector<Message> messages);

    QString getName();
    int getConvSize();
    void editName(QString newName);
    void addMsg(Message newMsg);
    void editMsg(int idMsg, QString newContent);
    void deleteMsg(int idMsg);
};


#endif // CONVERSATION_H
