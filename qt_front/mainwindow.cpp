#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include "conversation.h"
#include "message.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,currentConv(0, 1001, 1002, "Home", QVector<Message>())
{
    ui->setupUi(this);

    clientId = 1001;
    buildConversation(currentConv);
    openConversation(0);

    // Rendre le QLineEdit invisible et désactivé initialement
    ui->addConvName->setVisible(false);
    ui->addConvName->setEnabled(false);
    ui->addConvName->clear();
    ui->addConvName->setPlaceholderText("Saisir nom conversation");



    // Connecter le signal clicked() du bouton "+" au slot createConversation()
    connect(ui->addConvBtn, &QPushButton::clicked, this, &MainWindow::createNewConversation);


    // Connecter le signal returnPressed() du composant lineEdit au slot sendMessage()
    connect(ui->MsgEdit, &QLineEdit::returnPressed, this, &MainWindow::sendMessage);

    // Connecter le signal clicked() du bouton ">" au slot sendMessage()
    connect(ui->sendMsgBtn, &QPushButton::clicked, this, &MainWindow::sendMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Conversation MainWindow::getCurrentConv()
{
    return currentConv;
}


void MainWindow::createNewConversation(){
    //Conversation conversation(1, 1001, 1002, "Conversation 1", QVector<Message>());

    // Rendre le QLineEdit visible et activé
    ui->addConvName->setVisible(true);
    ui->addConvName->setEnabled(true);

    // Connecter le signal editingFinished() pour récupérer le texte saisi
    connect(ui->addConvName, &QLineEdit::editingFinished, this, [=]() {
        QString conversationName = ui->addConvName->text();

        // Vérifier si le nom de la conversation n'est pas vide
        if (!conversationName.isEmpty()) {
            Conversation conversation(++convIdGenerator, 1001, 1002, conversationName, QVector<Message>());
            buildConversation(conversation);


            // Cacher et désactiver et vider le contenu de QLineEdit après avoir récupéré le texte saisi
            ui->addConvName->setVisible(false);
            ui->addConvName->setEnabled(false);
            ui->addConvName->clear();

            openConversation(1);
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


    QPushButton *conversationButton = new QPushButton(conversation.getName(), this);
    conversationButton->setProperty("conversationId", conversation.idConv);
    connect(conversationButton, &QPushButton::clicked, this, [=](){
        closeConv();
        openConversation(conversation.idConv);
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


void MainWindow::openConversation(int idConv){


    qDebug() << "Tailles des conversations :";
    for (const Conversation &conversation : conversationList) {
        qDebug() << "Conversation" << conversation.idConv << ": " << conversation.messages.size();
    }




    //load la conv
    for (int i=0; i<conversationList.size(); i++){
        if (conversationList[i].idConv == idConv){
            currentConv = conversationList[i];
        }
    }

    //load conv messages
    for (int i = 0; i < currentConv.getConvSize(); i++) {
        Message message = currentConv.messages[i];
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

    Message newMsg(currentConv.msgIdGenerator, clientId, message);

    currentConv.addMsg(newMsg);
    conversationList[currentConv.idConv] = currentConv;
    displayMsg(newMsg);


    qDebug() << "Tailles des conversations :";
    for (const Conversation &conversation : conversationList) {
        qDebug() << "Conversation" << conversation.idConv << ": " << conversation.messages.size();
    }

    qDebug() << "currentConvSize" << currentConv.messages.size();

    // Effacer le texte du QLineEdit après l'avoir envoyé
    ui->MsgEdit->clear();
}


