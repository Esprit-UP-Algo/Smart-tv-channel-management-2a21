#ifndef PUBLICITE_H
#define PUBLICITE_H

#include <QString>
#include<QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>


class publicite
{
private: QString Nom, Cout, Description, Duree, Realisateur, Cible, DateHdebut, DateHFin;
    int Id;
public:
    publicite() {};
    publicite(int Id,QString Nom,QString Description,QString Duree,QString Cible,QString Cout, QString DateHdebut, QString DateHFin, QString Realisateur);
    // Setters for the publicite class
    void setId(int I) { this->Id = I; }
    void setNom(QString n) { Nom = n; }
    void setCout(QString Co) { Cout = Co; }
    void setDescription(QString Des) { Description = Des; }
    void setDuree(QString Du) { Duree = Du; }
    void setRealisateur(QString Re) { Realisateur = Re; }
    void setDateHdebut(QString dateTimeD) { DateHdebut = dateTimeD; }
    void setDateHFin(QString dateTimeF) { DateHFin = dateTimeF; }
    void setCible(QString Ci) { Cible = Ci; }



    int getId() {return Id; }
    QString getNom() {return Nom; }
    QString getCout() {return Cout; }
    QString getDescription() {return Description; }
    QString getDuree() {return Duree; }
    QString getCible() {return Cible; }
    QString getRealisateur() {return Realisateur; }
    QString getDateHdebut() {return DateHdebut; };
    QString getDateHFin() {return DateHFin; };
    bool ajouter();
    QSqlQueryModel *afficher();
    bool modifier();
    bool supprimer(int);

};

#endif // PUBLICITE_H
