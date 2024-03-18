#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load an application style
    QFile styleFile( "./styles.qss" );
    styleFile.open( QFile::ReadOnly );

    // Apply the loaded stylesheet
    QString style( styleFile.readAll() );
    a.setStyleSheet( style );

    int clientId = 0; // Valeur par défaut du clientId, vous pouvez le modifier selon vos besoins

    if (argc > 1) {
        clientId = QString(argv[1]).toInt();
    }

    MainWindow w(nullptr, clientId);
    w.show();
    return a.exec();
}
