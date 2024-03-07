#include "serie.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>


serie::serie(int id,QString nom,QString type,QString date_de_diffusion,QString duree,QString description)
{
    this->id=id;
    this->nom=nom;
    this->date_de_diffusion=date_de_diffusion;
    this->type=type;
    this->duree=duree;
    this->description=description;

}
bool serie::ajouter(){
    QSqlQuery query;

    QString res=QString::number(id);

       query.prepare("INSERT INTO serie (id, nom, type, date_de_diffusion,duree,description) VALUES (:id, :nom, :date_de_diffusion, :type, :duree, :description)");
       query.bindValue(":id",id);
       query.bindValue(":date_de_diffusion",date_de_diffusion);
       query.bindValue(":type",type);
       query.bindValue(":duree",duree);
       query.bindValue(":description",description);
       query.bindValue(":nom",nom);

       return query.exec();

}
QSqlQueryModel * serie::afficher(){
       QSqlQueryModel * model = new QSqlQueryModel();
       model->setQuery("SELECT id, nom, prenom FROM serie");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("date_de_diffusion"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("duree"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(5, Qt::Horizontal, QObject::tr("description"));
return model;
}
bool serie::supprimer(int id){
       QSqlQuery query;
       QString res=QString::number(id);
       query.prepare("DELETE FROM serie WHERE id = :id");
       query.bindValue(":id", res);
       return query.exec();

}
