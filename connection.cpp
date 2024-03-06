#include "connection.h"
#include<QDebug>
#include<QMessageBox>

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("TELEvue");
db.setUserName("fatmabk");
db.setPassword("14664958");

if (db.open())
test=true;

    return  test;
}
void  Connection::closeConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("TELEvue");
    db.setUserName("fatmabk");
    db.setPassword("14664958");
    db.close();}
