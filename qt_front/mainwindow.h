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


private:
    QTcpSocket *socket;
    int clientId;
    Conversation currentConv;
    QVector<Conversation> conversationList;

public:
    MainWindow(QWidget *parent = nullptr, int idCli=1);
    ~MainWindow();
    Conversation getCurrentConv();
    bool msgAlreadyInCurrentConv(Message msg);

public slots:
    //public slots permet d'appeler ces methodes dans la fonction connect de Qt
    void onConnected();
    void onReadyRead();
    void createNewConversation();
    void buildConversation(Conversation conversation);
    void openConversation(int idDestinataire);
    void displayMsg(Message message);
    void closeConv();
    void sendMessage();
    void reloadCurrentConv();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
