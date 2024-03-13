#include "mainwindow.h"
#include "connection.h"
#include "acceuil.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c; // Une seule instance de la classe connection

    bool test = c.createConnection(); // Etablir la connexion

    acceuil w;

    if (test) { // Si la connexion est établie
        w.show();
        QMessageBox::critical(nullptr, QObject::tr("Database is open"),
                             QObject::tr("Connection successful.\nClick Cancel to exit."), QMessageBox::Cancel);

    } else { // Si la connexion a échoué
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                             QObject::tr("Connection failed.\nClick Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
