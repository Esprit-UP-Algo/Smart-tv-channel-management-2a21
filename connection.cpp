#include "connection.h"

Connection::Connection() {
    // Constructeur de la classe, aucune initialisation particulière nécessaire ici
}

bool Connection::createConnection() {
    // Connexion à la base de données
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;

    // Spécifiez le nom de la base de données
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("Ali");
    db.setPassword("14355379");
    // Ouvrir la connexion
    if (db.open())
        test=true;

    return test;
}

void Connection::closeConnection() {
    db.close();
}
