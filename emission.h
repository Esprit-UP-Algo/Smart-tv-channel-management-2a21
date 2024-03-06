#ifndef EMISSION_H
#define EMISSION_H
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQueryModel>


class emissionData;

class emission
{
    QString nom, date_diffusion,type,description;
    int duree,id;
public:
    emission(){}
    emission(QString,QString,int,QString,QString);
    int getid() { return id; }
    QString getnom(){return nom;}
    QString getdate_diffusion(){return date_diffusion;}
    QString gettype(){return type;}
    QString getdescription(){return description;}
    int getduree(){return duree;}

    void setid(int id) { this->id = id; }
    void setnom(QString n){nom=n;}
    void setdate_diffusion(QString d){date_diffusion=d;}
    void settype(QString t){type=t;}
    void setdescription(QString des){description=des;}
    void setduree(int duree){this->duree=duree;}

bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier(int);
};


#endif // EMISSION_H
