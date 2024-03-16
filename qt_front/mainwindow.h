#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVector>
#include <QDateTime>
#include "conversation.h"
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int convIdGenerator = 0;

private:
    QTcpSocket *socket;
    int clientId;
    Conversation currentConv;
    QVector<Conversation> conversationList;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Conversation getCurrentConv();


public slots:
    //public slots permet d'appeler ces methodes dans la fonction connect de Qt
    void onConnected();
    void onReadyRead();
    void createNewConversation();
    void buildConversation(Conversation conversation);
    void openConversation(int idConv);
    void displayMsg(Message message);
    void closeConv();
    void sendMessage();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
