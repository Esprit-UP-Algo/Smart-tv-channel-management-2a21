#ifndef serie_H
#define serie_H
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
#include <QSqlQueryModel>


class serieData;

class serie
{
    QString nom, date_de_diffusion,duree,type,description;
    int id;
public:
    serie(){}
    serie(int,QString,QString,QString,QString,QString);
    QString getnom(){return nom;}
    QString getdate_de_diffusion(){return date_de_diffusion;}
    QString getduree(){return duree;}
    QString gettype(){return type;}
    QString getdescription(){return description;}
    int getid(){return id;}
    void setnom(QString n){nom=n;}
    void setdate_de_diffusion(QString d){date_de_diffusion=d;}
    void settype(QString t){type=t;}
    void setdescription(QString r){description=r;}
    void setduree(QString u){duree=u;}
    void setid(int id){this->id=id;}

bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);

};

#endif // serie_H
