#include "connection.h"
#include<QDebug>
#include<QMessageBox>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Projet_televue");
db.setUserName("monjik");
db.setPassword("0000");

if (db.open())
test=true;

    return  test;
}
void  Connection::closeConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Projet_televue");
    db.setUserName("monjik");
    db.setPassword("0000");
    db.close();}
