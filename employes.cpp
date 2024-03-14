#include "employes.h"
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>
employes::employes()
{

}
employes::employes(int cin,QString nom, QString prenom, QString adr_mail,QString adr_physique ,QString mot_de_passe,QString genre, int num_telephone,int rib , QString poste,int employes_id, int salaire, QString date_embauche,QString date_naissance)
{
        this->cin = cin;
        this->nom = nom;
        this->prenom = prenom;
        this->adr_mail = adr_mail;
        this->adr_physique = adr_physique;
        this->genre = genre;
        this->mot_de_passe = mot_de_passe;
        this->num_telephone = num_telephone;
        this->employes_id = employes_id;
        this->salaire = salaire;
        this->poste = poste;
        this->rib = rib;
        this->date_embauche = date_embauche;
        this->date_naissance = date_naissance;
}

bool employes::ajouter()
{
    QSqlQuery query;
    QString ch_id = QString::number(employes_id);
    QString ch_salaire = QString::number(salaire);
    QString ch_rib = QString::number(rib);
    QString ch_num_telephone = QString::number(num_telephone);
    QString ch_cin = QString::number(cin);


    query.prepare("INSERT INTO employes (CIN,NOM,PRENOM, ADR_MAIL, ADR_PHYSIQUE,MOT_DE_PASSE, GENRE, NUM_TELEPHONE,RIB,POSTE, EMPLOYES_ID,SALAIRE, DATE_EMBAUCHE,DATE_NAISSANCE)"
                  "VALUES (:CIN,:NOM,:PRENOM,:ADR_MAIL,:ADR_PHYSIQUE,:MOT_DE_PASSE,:GENRE,:NUM_TELEPHONE,:RIB,:POSTE,:EMPLOYES_ID,:SALAIRE,:DATE_EMBAUCHE,:DATE_NAISSANCE)");
    query.bindValue(":CIN",cin);
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":ADR_MAIL",adr_mail);
    query.bindValue(":ADR_PHYSIQUE",adr_physique);
    query.bindValue(":MOT_DE_PASSE",mot_de_passe);
    query.bindValue(":GENRE",genre);
    query.bindValue(":NUM_TELEPHONE",ch_num_telephone);
    query.bindValue(":RIB",ch_rib);
    query.bindValue(":POSTE",poste);
    query.bindValue(":EMPLOYES_ID",ch_id);
    query.bindValue(":SALAIRE",ch_salaire);
    query.bindValue(":DATE_NAISSANCE",date_naissance);
    query.bindValue(":DATE_EMBAUCHE",date_embauche);
    return query.exec();

}
QSqlQueryModel *employes::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM employes");
    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL : " << model->lastError().text();
    }

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse_mail"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse_physique"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("mot_de_passe"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("genre"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("num_telephone"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("rib"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Poste"));
    model->setHeaderData(10,Qt::Horizontal,QObject::tr("employes_id"));
    model->setHeaderData(11,Qt::Horizontal,QObject::tr("salaire"));
    model->setHeaderData(12,Qt::Horizontal,QObject::tr("date_embauche"));
    model->setHeaderData(13,Qt::Horizontal,QObject::tr("date_naissance"));
    return model;
}

bool employes::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM employes WHERE EMPLOYES_ID=:id");
    query.bindValue(":id", res);
    if (!query.exec()) {
        return false;  // Failed to execute the query
    }
    if (query.numRowsAffected() == 0) {
        return false;  // No rows were affected
    }
    return true;
}


bool employes::existe()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isValid()) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM employes WHERE employes_id = :employes_id");
        query.bindValue(":employes_id", employes_id);

        if (query.exec() && query.next()) {
            int count = query.value(0).toInt();


            return count > 0;
        }
    }

    return false;
}

bool employes::modifier()
{
        QSqlQuery query;
        QString ch_id = QString::number(employes_id);
        QString ch_salaire = QString::number(salaire);
        QString ch_rib = QString::number(rib);
        QString ch_num_telephone = QString::number(num_telephone);
        QString ch_cin = QString::number(cin);


        query.prepare("UPDATE employes SET CIN = :CIN, NOM = :NOM, PRENOM = :PRENOM, ADR_MAIL = :ADR_MAIL, ADR_PHYSIQUE=:ADR_PHYSIQUE, MOT_DE_PASSE = :MOT_DE_PASSE ,GENRE = :GENRE,  NUM_TELEPHONE = :NUM_TELEPHONE, RIB=:RIB, POSTE = :POSTE, SALAIRE = :SALAIRE, DATE_EMBAUCHE = :DATE_EMBAUCHE, DATE_NAISSANCE = :DATE_NAISSANCE WHERE EMPLOYES_ID = :EMPLOYES_ID");

        query.bindValue(":CIN",cin);
        query.bindValue(":NOM",nom);
        query.bindValue(":PRENOM",prenom);
        query.bindValue(":ADR_MAIL",adr_mail);
        query.bindValue(":ADR_PHYSIQUE",adr_physique);
        query.bindValue(":MOT_DE_PASSE",mot_de_passe);
        query.bindValue(":GENRE",genre);
        query.bindValue(":NUM_TELEPHONE",ch_num_telephone);
        query.bindValue(":RIB",ch_rib);
        query.bindValue(":POSTE",poste);
        query.bindValue(":EMPLOYES_ID",ch_id);
        query.bindValue(":SALAIRE",ch_salaire);
        query.bindValue(":DATE_NAISSANCE",date_naissance);
        query.bindValue(":DATE_EMBAUCHE",date_embauche);
        return query.exec();
}

bool employes::load(int employes_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM employes WHERE employes_id = :id");
    query.bindValue(":id", employes_id);

    if (query.exec() && query.first()) {
        employes_id = query.value("employes_id").toInt();
        cin = query.value("cin").toInt();
        nom = query.value("nom").toString();
        prenom = query.value("prenom").toString();
        adr_mail = query.value("adr_mail").toString();
        adr_physique = query.value("adr_physique").toString();
        genre = query.value("genre").toString();
        mot_de_passe = query.value("mot_de_passe").toString();
        num_telephone = query.value("num_telephone").toInt();
        salaire = query.value("salaire").toInt();
        poste = query.value("Poste").toString();
        rib = query.value("RIB").toInt();
        /*date_embauche = query.value("Date d'embauche").toDate();
        date_naissance = query.value("Date de naissance").toDate();*/


        return true;
    }
    return false;
}
QSqlQueryModel *employes::rechercherParNom(const QString &nom)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("SELECT * FROM employes WHERE nom = :nom");
    query.bindValue(":nom", nom);

    if (query.exec())
    {
        model->setQuery(query);
        return model;
    }
    else
    {
        qDebug() << "Recherche par nom échouée : " << query.lastError();
        delete model;
        return nullptr;
    }
}

QSqlQueryModel* employes::TriDateEmbauche()
{
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes ORDER BY date_embauche ASC");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse_mail"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse_physique"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("mot_de_passe"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("genre"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("num_telephone"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("rib"));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr("Poste"));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr("employes_id"));
        model->setHeaderData(11,Qt::Horizontal,QObject::tr("salaire"));
        model->setHeaderData(12,Qt::Horizontal,QObject::tr("date_embauche"));
        model->setHeaderData(13,Qt::Horizontal,QObject::tr("date_naissance"));
        return model;
}
QSqlQueryModel* employes::TriSalaire()
{

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes ORDER BY salaire ASC");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse_mail"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse_physique"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("mot_de_passe"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("genre"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("num_telephone"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("rib"));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr("Poste"));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr("employes_id"));
        model->setHeaderData(11,Qt::Horizontal,QObject::tr("salaire"));
        model->setHeaderData(12,Qt::Horizontal,QObject::tr("date_embauche"));
        model->setHeaderData(13,Qt::Horizontal,QObject::tr("date_naissance"));
        return model;
}
QSqlQueryModel* employes::TriDateNaissance()
{

        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT * FROM employes ORDER BY date_naissance ASC");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse_mail"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("adresse_physique"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("mot_de_passe"));
        model->setHeaderData(6,Qt::Horizontal,QObject::tr("genre"));
        model->setHeaderData(7,Qt::Horizontal,QObject::tr("num_telephone"));
        model->setHeaderData(8,Qt::Horizontal,QObject::tr("rib"));
        model->setHeaderData(9,Qt::Horizontal,QObject::tr("Poste"));
        model->setHeaderData(10,Qt::Horizontal,QObject::tr("employes_id"));
        model->setHeaderData(11,Qt::Horizontal,QObject::tr("salaire"));
        model->setHeaderData(12,Qt::Horizontal,QObject::tr("date_embauche"));
        model->setHeaderData(13,Qt::Horizontal,QObject::tr("date_naissance"));
        return model;
}
