#include "publicite.h"
#include <QMessageBox>

publicite::publicite (int Id,QString Nom, QString Description, QString Duree, QString Cible, QString Cout,QString DateHdebut,QString DateHFin, QString Realisateur)
{
this->Id=Id;
    this->Nom=Nom;
    this->Cout=Cout;
    this->Description=Description;
    this->Duree=Duree;
        this->Cible=Cible;
    this->Realisateur=Realisateur;

    this->DateHdebut=DateHdebut;
    this->DateHFin=DateHFin;
}

bool publicite::ajouter()
{
    // Validate the "Cible" attribute
        QStringList allowedCibles = {"HOMMES", "FEMMES", "ENFANTS"};
        if (!allowedCibles.contains(Cible)) {
            QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Invalid value for Cible. Cible must be : HOMMES, FEMMES or ENFANTS"));
            return false; // Return false indicating failure
        }

        // Validate the "Realisateur" attribute
            QRegExp rx("^[^0-9]+$"); // Regular expression to match strings without numbers
            if (!rx.exactMatch(Realisateur)) {
                QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Realisateur cannot contain numbers."));
                return false; // Return false indicating failure
            }

            // Validate "Duree" attribute
                if (!Duree.toInt()) {
                    QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Duree must be a valid number."));
                    return false; // Return false indicating failure
                }

                // Validate "Cout" attribute
                if (!Cout.toInt()) {
                    QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Cout must be a valid number."));
                    return false; // Return false indicating failure
                }
                // Validate "DateHdebut" attribute
                    QDateTime dateHdebut = QDateTime::fromString(DateHdebut, "yyyy-MM-dd hh:mm:ss");
                    if (!dateHdebut.isValid()) {
                        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Invalid format for DateHdebut. Format should be: yyyy-MM-dd hh:mm:ss"));
                        return false; // Return false indicating failure
                    }

                    // Validate "DateHFin" attribute
                    QDateTime dateHFin = QDateTime::fromString(DateHFin, "yyyy-MM-dd hh:mm:ss");
                    if (!dateHFin.isValid()) {
                        QMessageBox::critical(nullptr, QObject::tr("Error"), QObject::tr("Invalid format for DateHFin. Format should be: yyyy-MM-dd hh:mm:ss"));
                        return false; // Return false indicating failure
                    }

        // Requête SQL pour insérer une nouvelle publicité
        QSqlQuery query;
        QString res = QString::number(Id);

        query.prepare("INSERT INTO publicite (Id, Nom, Description, Duree, Cible, Cout, DateHdebut, DateHFin, Realisateur) VALUES (:Id, :Nom, :Description, :Duree, :Cible, :Cout, :DateHdebut, :DateHFin, :Realisateur)");
        query.bindValue(":Id", res);
        query.bindValue(":Nom", Nom);

        query.bindValue(":Description", Description);
        query.bindValue(":Duree", Duree);

        query.bindValue(":Cible", Cible);
        query.bindValue(":Cout", Cout);
        query.bindValue(":DateHdebut", DateHdebut);
        query.bindValue(":DateHFin", DateHFin);
        query.bindValue(":Realisateur", Realisateur);

        // Exécution de la requête et vérification du succès
        return query.exec();
}

bool publicite::supprimer(int Id)
{
    QSqlQuery query;
    QString res=QString::number(Id);
    query.prepare("delete from publicite where ID= :Id");
    query.bindValue(":Id", res);
    return query.exec();
}

QSqlQueryModel * publicite::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from publicite");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Description"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Duree"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Cible"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Cout"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DateHdebut"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("DateHFin"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Realisateur"));
    return model;
}

bool publicite::modifier() {
    // Requête SQL pour mettre à jour une publicité
    QSqlQuery query;
    QString res = QString::number(Id);

    query.prepare("UPDATE publicite SET Nom=:Nom, Description=:Description, Duree=:Duree, Cible=:Cible, Cout=:Cout, DateHdebut=:DateHdebut, DateHFin=:DateHFin, Realisateur=:Realisateur WHERE Id=:Id");
    query.bindValue(":Id", res);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Description", Description);
    query.bindValue(":Duree", Duree);
    query.bindValue(":Cible", Cible);
    query.bindValue(":Cout", Cout);
    query.bindValue(":DateHdebut", DateHdebut);
    query.bindValue(":DateHFin", DateHFin);
    query.bindValue(":Realisateur", Realisateur);

    // Exécution de la requête et vérification du succès
    return query.exec();
}
