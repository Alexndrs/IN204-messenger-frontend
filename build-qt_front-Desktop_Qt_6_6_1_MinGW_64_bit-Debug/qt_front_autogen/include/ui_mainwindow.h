/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *convListContainer;
    QPushButton *addConvBtn;
    QLineEdit *addConvName;
    QScrollArea *scrollArea_2;
    QWidget *scrollConv;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *listConv;
    QSpacerItem *verticalSpacer;
    QWidget *verticalLayoutWidget_2;
    QGridLayout *gridLayout;
    QFrame *Messagesframe;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrolling;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *messageList;
    QHBoxLayout *horizontalLayout;
    QLineEdit *MsgEdit;
    QPushButton *sendMsgBtn;
    QLabel *convName;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(801, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,stop: 0 rgba(43,51,74,1),stop: 1 rgba(22,21,24,1));\n"
"	border-radius : 150px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(11, 11, 241, 581));
        convListContainer = new QVBoxLayout(verticalLayoutWidget);
        convListContainer->setObjectName("convListContainer");
        convListContainer->setContentsMargins(0, 0, 0, 0);
        addConvBtn = new QPushButton(verticalLayoutWidget);
        addConvBtn->setObjectName("addConvBtn");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addConvBtn->sizePolicy().hasHeightForWidth());
        addConvBtn->setSizePolicy(sizePolicy);
        addConvBtn->setStyleSheet(QString::fromUtf8(""));

        convListContainer->addWidget(addConvBtn);

        addConvName = new QLineEdit(verticalLayoutWidget);
        addConvName->setObjectName("addConvName");

        convListContainer->addWidget(addConvName);

        scrollArea_2 = new QScrollArea(verticalLayoutWidget);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea_2->setWidgetResizable(true);
        scrollConv = new QWidget();
        scrollConv->setObjectName("scrollConv");
        scrollConv->setGeometry(QRect(0, 0, 237, 506));
        verticalLayout_4 = new QVBoxLayout(scrollConv);
        verticalLayout_4->setObjectName("verticalLayout_4");
        listConv = new QVBoxLayout();
        listConv->setObjectName("listConv");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        listConv->addItem(verticalSpacer);


        verticalLayout_4->addLayout(listConv);

        scrollArea_2->setWidget(scrollConv);

        convListContainer->addWidget(scrollArea_2);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(259, 11, 531, 581));
        gridLayout = new QGridLayout(verticalLayoutWidget_2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        Messagesframe = new QFrame(verticalLayoutWidget_2);
        Messagesframe->setObjectName("Messagesframe");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Messagesframe->sizePolicy().hasHeightForWidth());
        Messagesframe->setSizePolicy(sizePolicy1);
        Messagesframe->setFrameShape(QFrame::StyledPanel);
        Messagesframe->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(Messagesframe);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(Messagesframe);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrolling = new QWidget();
        scrolling->setObjectName("scrolling");
        scrolling->setGeometry(QRect(0, 0, 503, 464));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrolling->sizePolicy().hasHeightForWidth());
        scrolling->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(scrolling);
        verticalLayout_2->setObjectName("verticalLayout_2");
        messageList = new QVBoxLayout();
        messageList->setObjectName("messageList");

        verticalLayout_2->addLayout(messageList);

        scrollArea->setWidget(scrolling);

        verticalLayout->addWidget(scrollArea);


        gridLayout->addWidget(Messagesframe, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        MsgEdit = new QLineEdit(verticalLayoutWidget_2);
        MsgEdit->setObjectName("MsgEdit");
        MsgEdit->setEnabled(true);
        QFont font;
        font.setFamilies({QString::fromUtf8("Montserrat Medium")});
        font.setPointSize(22);
        font.setWeight(QFont::Black);
        font.setKerning(false);
        MsgEdit->setFont(font);

        horizontalLayout->addWidget(MsgEdit);

        sendMsgBtn = new QPushButton(verticalLayoutWidget_2);
        sendMsgBtn->setObjectName("sendMsgBtn");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Montserrat Black")});
        font1.setPointSize(22);
        font1.setBold(true);
        sendMsgBtn->setFont(font1);

        horizontalLayout->addWidget(sendMsgBtn);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        convName = new QLabel(verticalLayoutWidget_2);
        convName->setObjectName("convName");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Montserrat SemiBold")});
        font2.setBold(true);
        font2.setItalic(true);
        convName->setFont(font2);

        gridLayout->addWidget(convName, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addConvBtn->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        sendMsgBtn->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        convName->setText(QCoreApplication::translate("MainWindow", "Hello world", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
