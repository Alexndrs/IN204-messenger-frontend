#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include "conversation.h"
#include "message.h"
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <algorithm>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent, int idCli)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clientId = idCli;

    // Rendre le QLineEdit invisible et désactivé initialement
    ui->addConvName->setVisible(false);
    ui->addConvName->setEnabled(false);
    ui->addConvName->clear();
    ui->addConvName->setPlaceholderText("Saisir id Destinataire");

    // Connecter le signal clicked() du bouton "+" au slot createConversation()
    connect(ui->addConvBtn, &QPushButton::clicked, this, &MainWindow::createNewConversation);


    // Connecter le signal returnPressed() du composant lineEdit au slot sendMessage()
    connect(ui->MsgEdit, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);

    //Connecter le signal clicked() du bouton ">" au slot sendMessage()
    connect(ui->sendMsgBtn, &QPushButton::clicked, this, &MainWindow::sendMessage);

    //Connecter le signal clicked() du bouton "reloadBtn" au slot sendMessage()
    connect(ui->reloadBtn, &QPushButton::clicked, this, &MainWindow::reloadCurrentConv);




    // Initialisation du timer
    QTimer *timer = new QTimer(this);

    // Connexion du signal timeout() du timer à la fonction reloadCurrentConv()
    connect(timer, &QTimer::timeout, this, &MainWindow::reloadCurrentConv);

    // Définition de l'intervalle du timer à 2000 millisecondes (2 secondes)
    timer->start(2000);






    //On creer une conversation initial d'accueil entre ClientId et un identifiant -1 attribué à personne, on y ajoute les messages d'accueil
    currentConv = Conversation(clientId, -1, "Home", QVector<Message>());
    Message WelcomeMessage1(currentConv.msgIdGenerator, -1,clientId, "Hello, bienvenu sur messenger++");
    Message WelcomeMessage2(currentConv.msgIdGenerator, -1,clientId, "Tu peux écrire des messages, si la conv est longue tu peux scroll");
    Message WelcomeMessage3(currentConv.msgIdGenerator, -1,clientId, "Tu peux également créer une nouvelle conversation avec le bouton + en haut à gauche");
    Message WelcomeMessage4(currentConv.msgIdGenerator, -1,clientId, "Puis tu choisis le nom de la conversation et c'est parti ! 👌");
    Message WelcomeMessage5(currentConv.msgIdGenerator, -1,clientId, "Ton identifiant est " + QString::number(clientId));
    currentConv.addMsg(WelcomeMessage1);
    currentConv.addMsg(WelcomeMessage2);
    currentConv.addMsg(WelcomeMessage3);
    currentConv.addMsg(WelcomeMessage4);
    currentConv.addMsg(WelcomeMessage5);

    socket = new QTcpSocket(this);
    //socket->connectToHost("127.0.0.1", 8080); //remplacer par l'adress IP du serveur 147.250.231.188
    socket->connectToHost("147.250.231.188", 8080);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::onReadyRead);

    connect(socket, &QTcpSocket::connected, this, &MainWindow::onConnected);

    //Message testMsg1(currentConv.msgIdGenerator, clientId, currentConv.idSecPers, "un premier message de test");
    //Message testMsg2(currentConv.msgIdGenerator, clientId, currentConv.idSecPers, "un deuxieme message de test");
    //int bufferSize;
    //char* buffer1 = testMsg1.translateToBuffer(bufferSize);
    //qDebug() << "translateToBuffer" << buffer1 << bufferSize;
    //socket->write(buffer1, bufferSize);
    //delete[] buffer1;
    //char* buffer2 = testMsg2.translateToBuffer(bufferSize);
    //qDebug() << "translateToBuffer" << buffer2 <<bufferSize;
    //socket->write(buffer2, bufferSize);
    //delete[] buffer2;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete socket;
}

void MainWindow::onConnected() {
    qDebug() << "Connecté au serveur.";
    buildConversation(currentConv);
    openConversation(-1);

}


QList<QByteArray> splitMessages(QByteArray data){
    // Délimite plusieurs messages :
    // si data = {I:{1},A:{1}...{premier Message}}{I:{2},A:{1},...C:{deuxieme Message}}
    // On renvoie [{I:{1},A:{1}...{premier Message}}, {I:{2},A:{1},...C:{deuxieme Message}] en remarquant que "}{ delimite deux messages"
    QList<QByteArray> severalMessages;
    QByteArray message;
    for (int i = 0; i < data.size(); ++i) {
        if (data.at(i) == '}' && i < data.size() - 1 && data.at(i + 1) == '{') {
            severalMessages.append(message);
            message.clear();
        } else {
            message.append(data.at(i));
        }
    }
    if (!message.isEmpty()) {
        severalMessages.append(message);
    }
    return severalMessages;
}


bool MainWindow::msgAlreadyInCurrentConv(Message msg){
    for (int i=0; i < currentConv.getConvSize(); i++){
        if (currentConv.messages[i].idMsg == msg.idMsg && currentConv.messages[i].idAuteur == msg.idAuteur && currentConv.messages[i].idAuteur == msg.idAuteur){
            return true;
        }
    }
    return false;
}


void MainWindow::onReadyRead() {
    QByteArray data = socket->readAll();
    QList<QByteArray> severalMessages = splitMessages(data);
    for (int i=0; i < severalMessages.size(); i++){
        //qDebug() << "Message du serveur onReadyRead:" << severalMessages[i];
        //qDebug() << "Translate brute en QString: " << QString(severalMessages[i]);


        Message msgRcv;
        msgRcv.translateFromBuffer(severalMessages[i].data());

        qDebug() << "I:" << msgRcv.idMsg << "|  A:" << msgRcv.idAuteur << "|  D:" << msgRcv.idDestinataire << "|  C:" << msgRcv.contenu << "| Date:" <<msgRcv.currentDate << "| sec:" << msgRcv.sec;


        if (msgRcv.idAuteur == clientId &&  !msgAlreadyInCurrentConv(msgRcv)){
            qDebug() << "Un message envoyé";
            for (int i=0; i<conversationList.size(); i++){
                if (conversationList[i].idSecPers == msgRcv.idDestinataire){
                    conversationList[i].addMsg(msgRcv);
                }
            }
        }
        if(msgRcv.idDestinataire == clientId && !msgAlreadyInCurrentConv(msgRcv)){
            qDebug() << "Un message reçu";


            for (int i=0; i<conversationList.size(); i++){
                if (conversationList[i].idSecPers == msgRcv.idAuteur){
                    conversationList[i].addMsg(msgRcv);
                }
            }
            if (msgRcv.idAuteur == currentConv.idSecPers){
                displayMsg(msgRcv);
                currentConv.addMsg(msgRcv);
            }
        }
    }
}



Conversation MainWindow::getCurrentConv()
{
    return currentConv;
}


void MainWindow::createNewConversation(){

    // Rendre le QLineEdit visible et activé
    ui->addConvName->setVisible(true);
    ui->addConvName->setEnabled(true);

    // Connecter le signal editingFinished() pour récupérer le texte saisi
    connect(ui->addConvName, &QLineEdit::editingFinished, this, [=]() {
        QString conversationName = ui->addConvName->text();

        // Vérifier si le nom de la conversation n'est pas vide
        if (!conversationName.isEmpty()) {

            bool ok;
            int idDestinataire = conversationName.toInt(&ok);
            if (ok) {
                // La conversion en entier a réussi
                qDebug() << "ID du destinataire : " << idDestinataire;
                //pour savoir si il y avait deja des messages dans la DB entre ces utilisateur : on envoie un buffer (clientId, idDestinataire) au serveur.

                int bufferSize = snprintf(nullptr, 0, "(%d,%d)", clientId, idDestinataire) + 1;
                char* buffer = new char[bufferSize];
                snprintf(buffer, bufferSize, "(%d,%d)", clientId, idDestinataire);
                qDebug() << "buffer_a_send" << buffer;
                socket->write(buffer, bufferSize);
                delete[] buffer;

                Conversation conversation(clientId, idDestinataire, conversationName, QVector<Message>());
                buildConversation(conversation);


                // Cacher et désactiver et vider le contenu de QLineEdit après avoir récupéré le texte saisi
                ui->addConvName->setVisible(false);
                ui->addConvName->setEnabled(false);
                ui->addConvName->clear();

                openConversation(idDestinataire);

            }
            else {
                // La conversion a échoué
                qDebug() << "Erreur : le texte n'est pas un entier.";
            }
        } else {
            // Afficher un message d'erreur ou effectuer une action appropriée
            qDebug() << "Le nom de la conversation ne peut pas être vide !";
        }
    });
}

void MainWindow::buildConversation(Conversation conversation){
    // Ajouter la conversation à la liste des conversation
    // Ajouter le bouton qui permet d'accéder à la conversation dans l'interface

    conversationList.append(conversation);


    //pour savoir si il y avait deja des messages dans la DB entre clientId et le destinataire : on envoie un buffer (clientId, idDestinataire) au serveur.
    int bufferSize = snprintf(nullptr, 0, "(%d,%d)", clientId, conversation.idSecPers) + 1;
    char* buffer = new char[bufferSize];
    snprintf(buffer, bufferSize, "(%d,%d)", clientId, conversation.idSecPers);
    //qDebug() << "buffer_send" << buffer;
    socket->write(buffer, bufferSize);
    delete[] buffer;
    //On aura recevra les precedents messages si il y en a dans onReadyRead



    QPushButton *conversationButton = new QPushButton(conversation.getName(), this);
    //conversationButton->setProperty("conversationId", conversation.idSecPers);
    connect(conversationButton, &QPushButton::clicked, this, [=](){
        closeConv();
        openConversation(conversation.idSecPers);
    });

    ui->listConv->addWidget(conversationButton);
}



void MainWindow::closeConv(){
    // retire tous les messages dans messageList : il faut tenir compte de la structure et supprimer tous les elements internes
    // la structure est la suivante :
    //      messageList (QVBoxLayout)
    //          |-> QHBoxLayout                             <Doit être delete
    //          |       |-> Spacer (premier Widget)       <Doit être delete
    //          |       |-> QLabel (second Widget)        <Doit être delete
    //          |->QHBoxLayout                              <Doit être delete
    //          ...

    QLayoutItem *child;
    while ((child = ui->messageList->takeAt(0)) != nullptr) {
        QHBoxLayout *layout = dynamic_cast<QHBoxLayout*>(child);
        if (layout) {
            QLayoutItem *innerChild;
            while ((innerChild = layout->takeAt(0)) != nullptr) {
                delete innerChild->widget(); // Supprime le widget de l'item
                delete innerChild; // Supprime l'item lui-même
            }
            delete layout; // Supprime le QHBoxLayout lui-même
        } else {
            delete child; // Supprime l'item lui-même
        }
    }

    ui->convName->clear();
    ui->MsgEdit->clear();

}


bool compareMessages(const Message &msg1, const Message &msg2) {
    // Comparaison par date
    if (msg1.currentDate != msg2.currentDate) {
        return msg1.currentDate < msg2.currentDate;
    }
    // Si les dates sont égales, comparaison par seconde dans la journée
    return msg1.sec < msg2.sec;
}

QVector<Message> sortMessages(const QVector<Message> &messages) {
    QVector<Message> sortedMessages = messages;
    // Tri des messages en utilisant la fonction de comparaison personnalisée
    std::sort(sortedMessages.begin(), sortedMessages.end(), compareMessages);
    return sortedMessages;

}


void MainWindow::openConversation(int idDestinataire){


    //qDebug() << "Tailles des conversations :";
    //for (const Conversation &conversation : conversationList) {
    //    qDebug() << "Conversation" << conversation.idConv << ": " << conversation.messages.size();
    //}


    //load la conv
    for (int i=0; i<conversationList.size(); i++){
        if (conversationList[i].idSecPers == idDestinataire){
            currentConv = conversationList[i];
        }
    }

    QVector<Message> sortedMessages = sortMessages(currentConv.messages);
    for (const Message &message : sortedMessages) {
        displayMsg(message);
    }

    ui->convName->setText(currentConv.getName());
}

void MainWindow::displayMsg(Message message){

    // Créer le layout horizontal pour le message
    QHBoxLayout *messageLayout = new QHBoxLayout;

    // Créer et configurer le QLabel pour afficher le contenu du message
    QLabel *contentLabel = new QLabel(message.contenu);
    contentLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    if (message.idAuteur == clientId){
        // Ajouter un espaceur horizontal
        messageLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        //Puis le label
        messageLayout->addWidget(contentLabel);
    }
    else{
        //Ajoute le label
        messageLayout->addWidget(contentLabel);
        // puis un espaceur horizontal
        messageLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    }
    // Ajouter le layout horizontal contenant le message à votre messageList
    ui->messageList->addLayout(messageLayout);
}


void MainWindow::sendMessage() {
    // Récupérer le message depuis le composant QLineEdit (MsgEdit)
    QString message = ui->MsgEdit->text();

    Message newMsg(currentConv.msgIdGenerator, clientId, currentConv.idSecPers, message);
    //Message otherTestMsg(currentConv.msgIdGenerator, clientId, currentConv.idSecPers, "Un deuxieme message a la suite de l'autre pour voir si on peut enchainer");


    // Envoyer le nouveau msg au serveur
    int bufferSize;
    char* buffer = newMsg.translateToBuffer(bufferSize);
    qDebug() << "translateToBuffer" << buffer;
    socket->write(buffer, bufferSize);
    delete[] buffer;


    currentConv.addMsg(newMsg);
    qDebug() << currentConv.getConvSize();
    for (int i=0; i<conversationList.size(); i++){
        if (conversationList[i].idSecPers == currentConv.idSecPers){
            qDebug() << "ajout d'un msg";
            conversationList[i] = currentConv;
        }
    }
    displayMsg(newMsg);


    // Effacer le texte du QLineEdit après l'avoir envoyé
    ui->MsgEdit->clear();
}

void MainWindow::reloadCurrentConv(){

    //On reload la DB en envoyant (clientId, currentConv.idSecPers)
    int bufferSize = snprintf(nullptr, 0, "(%d,%d)", clientId, currentConv.idSecPers) + 1;
    char* buffer = new char[bufferSize];
    snprintf(buffer, bufferSize, "(%d,%d)", clientId, currentConv.idSecPers);
    //qDebug() << "buffer_send" << buffer;
    socket->write(buffer, bufferSize);
    delete[] buffer;
    //On aura recevra les messages si il y en a dans onReadyRead
}


