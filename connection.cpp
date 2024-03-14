#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet");//inserer le nom de la source de données
db.setUserName("hed");//inserer nom de l'utilisateur
db.setPassword("hed");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;



    return  test;
}
