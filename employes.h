#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QDate>
#include <QString>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
QT_CHARTS_USE_NAMESPACE

class employes
{
    int cin;
    QString nom,prenom,adr_mail,adr_physique,mot_de_passe,genre;
    int num_telephone,rib;
    QString poste;
    int salaire,employes_id ;
    QString date_embauche,date_naissance;

public:
    employes();
    employes(int cin,QString nom,QString prenom ,QString adr_mail,QString adr_physique ,QString mot_de_passe ,QString genre,int num_telephone ,int rib,QString poste,int salaire,int employes_id,QString date_embauche,QString date_naissance);
    //getters
        int getCIN() const {return cin;}
        QString getNom() const {return nom;}
        QString getPrenom() const {return prenom;}
        QString getAdresseMail() const {return adr_mail;}
        QString getAdressePhysique() const {return adr_physique;}
        QString getMotDePasse() const {return mot_de_passe;}
        int getNumeroTelephone() const {return num_telephone;}
        QString getGenre() const {return genre;}
        int getRIB() const {return rib;}
        QString getposte() const {return poste;}
        int getSalaire() const {return salaire;}
        int getEmployesId() const {return employes_id;}
        QString getDateEmbauche() const {return date_embauche;}
        QString getNaissance() const {return date_naissance;}

        //setters
            void setID(int newid){employes_id=newid;}
            void setCIN(int newCIN) { cin = newCIN; }
            void setNom(const QString newNom) { nom = newNom; }
            void setPrenom(const QString newPrenom) { prenom = newPrenom; }
            void setAdresseMail(const QString newAdresseMail) { adr_mail = newAdresseMail; }
            void setAdressePhysique(const QString newAdressePhysique) { adr_physique = newAdressePhysique; }
            void setRIB(int newRib) { rib = newRib; }
           void setGenre(const QString newGenre) { genre = newGenre; }
            void setMotDePasse(const QString newMotDePasse) { mot_de_passe = newMotDePasse; }
            void setNumeroTelephone(int newNumeroTelephone) { num_telephone = newNumeroTelephone; }
            void setPoste(const QString newPoste) { poste = newPoste; }
            void setSalaire(int newSalaire) { salaire = newSalaire; }
           void setDateEmbauche(const QString newDateEmbauche) { date_embauche = newDateEmbauche; }
            void setNaissance(const QString newDateNaissance) { date_naissance = newDateNaissance; }

            //methode
            QSqlQueryModel * afficher();
                bool ajouter();
                bool supprimer(int);
                bool modifier();
                bool existe();
                bool load(int employes_id);
                QSqlQueryModel * rechercherParNom(const QString &Nom);
                QSqlQueryModel* TriDateEmbauche();
                QSqlQueryModel* TriSalaire();
                QSqlQueryModel* TriDateNaissance();





};

#endif // EMPLOYES_H
