#include "conversation.h"

Conversation::Conversation(int idConv, int idFirstPers, int idSecPers, QString convName, QVector<Message> messages)
    : idConv(idConv), idFirstPers(idFirstPers), idSecPers(idSecPers), convName(convName), messages(messages){}

int Conversation::getConvSize(){
    return messages.size();
}

QString Conversation::getName(){
    return convName;
}


void Conversation::editName(QString newName){
    convName = newName;
}

void Conversation::addMsg(Message newMsg){
    messages.append(newMsg);
    msgIdGenerator++;
}

void Conversation::editMsg(int idMsg, QString newContent){
    for (int i = 0; i < messages.size(); ++i) {
        Message message = messages[i];
        if (message.getMsgId() == idMsg){
            message.editMsgContent(newContent);
            return ;
        }
    }
}
void Conversation::deleteMsg(int idMsg){
    for (int i = 0; i < messages.size(); ++i) {
        Message message = messages[i];
        if (message.getMsgId() == idMsg){
            messages.remove(i);
            return ;
        }
    }
}
