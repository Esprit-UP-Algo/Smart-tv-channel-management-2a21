#include "emission.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>

emission::emission(QString nom,QString date_diffusion,int duree,QString type,QString description)
{
    this->nom=nom;
    this->date_diffusion=date_diffusion;
    this->type=type;
    this->duree=duree;
    this->description=description;
}

bool emission::ajouter(){
    QSqlQuery query;
    query.prepare("INSERT INTO emission (nom, date_diffusion, duree, type, description) "
                  "VALUES (:nom, :date_diffusion, :duree, :type, :description)");
    query.bindValue(":nom", nom);
    query.bindValue(":date_diffusion", date_diffusion);
    query.bindValue(":duree", duree);  // Add colon here
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    return query.exec();
}


QSqlQueryModel * emission::afficher(){

       QSqlQueryModel * model = new QSqlQueryModel();
       model->setQuery("SELECT id, nom, date_diffusion,duree,type,description FROM emission");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_diffusion"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Duree"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("Type"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("Description"));
return model;
}

bool emission::supprimer(int id){
       QSqlQuery query;
       QString res=QString::number(id);
       query.prepare("DELETE FROM emission WHERE id = :id");
       query.bindValue(":id", res);
       return query.exec();
}

bool emission::modifier(int id){
    QSqlQuery query;
    query.prepare("UPDATE emission SET nom = :nom, date_diffusion = :date_diffusion, duree = :duree, type = :type, description = :description WHERE id = :id");
     query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":date_diffusion", date_diffusion);
    query.bindValue(":duree", duree);  // Add colon here
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    return query.exec();
}
