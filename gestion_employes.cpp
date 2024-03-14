#include <QString>
#include <QMessageBox>
#include <QApplication>
#include<iostream>
#include <QFileDialog>
#include <QPdfWriter>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QTextTable>
#include <QTextCursor>
#include <QTextTableCell>
#include <QTextFrame>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QBarSeries>
#include <QBarSet>
#include <QDebug>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QFont>
#include <QDate>

QT_CHARTS_USE_NAMESPACE
#include "employes.h"
#include "gestion_employes.h"
#include "ui_gestion_employes.h"

gestion_employes::gestion_employes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gestion_employes)
{
    ui->setupUi(this);
    ui->tableView->setModel(emp.afficher());
    ui->tableView->resizeColumnsToContents();
}

gestion_employes::~gestion_employes()
{
    delete ui;
}

QString gestion_employes::getSelectedGender()
{
    QButtonGroup genderButtonGroup;
    genderButtonGroup.addButton(ui->homme);
    genderButtonGroup.addButton(ui->femme);

    QAbstractButton* selectedButton = genderButtonGroup.checkedButton();

    if (selectedButton == ui->homme) {
        return "Homme";
    } else if (selectedButton == ui->femme) {
        return "Femme";
    } else {
        return "Non spécifié";
    }
}

void gestion_employes::on_ajouter_clicked()//ajouter
{
    int employes_id=ui->employes_id->text().toInt();
    int cin=ui->cin->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString adr_mail=ui->adr_mail->text();
    QString adr_physique=ui->adr_physique->text();
    QString genre = getSelectedGender();
    QString mot_de_passe=ui->mot_de_passe->text();
    int num_telephone=ui->num_telephone->text().toInt();
    int salaire=ui->salaire->text().toInt();
    int rib=ui->rib->text().toInt();
    QString poste=ui->poste->text();
    QString date_embauche=ui->date_embauche->date().toString();
    QString date_naissance=ui->date_naissance->date().toString();

    if (nom.isEmpty() || prenom.isEmpty() || adr_mail.isEmpty() || genre.isEmpty() || ui->num_telephone->text().isEmpty() || adr_physique.isEmpty() || mot_de_passe.isEmpty()|| ui->cin->text().isEmpty()||ui->poste->text().isEmpty()||ui->employes_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->rib->text().isEmpty())
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
       return;
    }

    if (salaire <= 0)
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
       return;
    }
    QRegExp regex("^[a-zA-Z0-9]+$");

    if (!regex.exactMatch(mot_de_passe))
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Mot de passe non valide. Utilisez uniquement des lettres et des chiffres."), QMessageBox::Cancel);
        return;
    }
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

    if (!emailRegex.exactMatch(adr_mail)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Adresse mail non valide. Utilisez le format abc@abc.abc."), QMessageBox::Cancel);
        return;
    }


    QRegExp nomPrenomRegex("^[a-zA-Z ]+$");

    if (!nomPrenomRegex.exactMatch(nom) || !nomPrenomRegex.exactMatch(prenom))
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le nom et le prénom doivent contenir uniquement des lettres et des espaces."), QMessageBox::Cancel);
      return;
    }
    /*QDate dateActuelle = QDate::currentDate();
    if (date_embauche > dateActuelle)
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("La date d'embauche ne peut pas être ultérieure à la date actuelle."), QMessageBox::Cancel);
      return;
    }
    if (date_naissance > dateActuelle)
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("La date de naissance ne peut pas être ultérieure à la date actuelle."), QMessageBox::Cancel);
      return;
    }*/
    if (nom.length() < 3 || prenom.length() < 3)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le nom et le prénom doivent comporter au moins 3 caractères."), QMessageBox::Cancel);
        return;
    }

    if (QString::number(cin).length() != 8)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le cin doivent être des nombres de 8 chiffres."), QMessageBox::Cancel);
        return;
    }

    if (QString::number(num_telephone).length() != 8) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le numéro de téléphone doit comporter 8 chiffres."), QMessageBox::Cancel);
        return;
    }
    if (QString::number(rib).length() != 4) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le RIB doit comporter 4 chiffres."), QMessageBox::Cancel);
        return;
    }
    employes e( cin, nom, prenom , adr_mail, adr_physique , mot_de_passe , genre, num_telephone , rib, poste, salaire, employes_id, date_embauche, date_naissance);

    if (e.existe()) {

        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("l'ID de cet employes existe deja."), QMessageBox::Cancel);
        return;
    }
    bool test=e.ajouter();
    if(test)
    {
        ui->employes_id->setText("");
        ui->cin->setText("");
        ui->nom->setText("");
        ui->prenom->setText("");
        ui->adr_mail->setText("");
        ui->adr_physique->setText("");
        ui->mot_de_passe->setText("");
        ui->date_naissance->setDate(QDate::currentDate());
        ui->date_embauche->setDate(QDate::currentDate());
        ui->num_telephone->setText("");
        ui->rib->setText("");
        ui->salaire->setText("");
        ui->poste->setText("");
        ui->tableView->setModel(emp.afficher());
        ui->tableView->resizeColumnsToContents();
        QMessageBox::information(nullptr,QObject::tr("ok"),
                QObject::tr("ajout effectué.\n ""click Cancel to exit."),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not Ok"),QObject::tr("ajout non effectué.\n""click Cancel to exit."),QMessageBox::Cancel);


}

void gestion_employes::on_sup_clicked()//supprimer
{
employes f;
int id = ui->supprimer->text().toInt();
bool test = f.supprimer(id);
if (test) {
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                             QObject::tr("Suppression effectuée.\n"
                                         "Click Ok to exit."), QMessageBox::Ok);
} else {
    QMessageBox::critical(nullptr, QObject::tr("Not ok"),
                          QObject::tr("Échec de la suppression.\n"
                                      "L'employe n'existe pas dans la base de données."),
                          QMessageBox::Cancel);
}
ui->tableView->setModel(f.afficher());
}

void gestion_employes::on_modifier1_clicked()//ajouter
{
    int employes_id=ui->employes_id->text().toInt();
    int cin=ui->cin->text().toInt();
    QString nom=ui->nom->text();
    QString prenom=ui->prenom->text();
    QString adr_mail=ui->adr_mail->text();
    QString adr_physique=ui->adr_physique->text();
    QString genre = getSelectedGender();
    QString mot_de_passe=ui->mot_de_passe->text();
    int num_telephone=ui->num_telephone->text().toInt();
    int salaire=ui->salaire->text().toInt();
    int rib=ui->rib->text().toInt();
    QString poste=ui->poste->text();
    QString date_embauche=ui->date_embauche->date().toString();
    QString date_naissance=ui->date_naissance->date().toString();

    if (nom.isEmpty() || prenom.isEmpty() || adr_mail.isEmpty() || genre.isEmpty() || ui->num_telephone->text().isEmpty() || adr_physique.isEmpty() || mot_de_passe.isEmpty()|| ui->cin->text().isEmpty()||ui->poste->text().isEmpty()||ui->employes_id->text().isEmpty()||ui->salaire->text().isEmpty()||ui->rib->text().isEmpty())
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Tous les champs doivent être remplis."));
       return;
    }

    if (salaire <= 0)
    {
       QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le salaire doit être supérieur à zéro."));
       return;
    }
    QRegExp regex("^[a-zA-Z0-9]+$");

    if (!regex.exactMatch(mot_de_passe))
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Mot de passe non valide. Utilisez uniquement des lettres et des chiffres."), QMessageBox::Cancel);
        return;
    }
    QRegExp emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,4}$");

    if (!emailRegex.exactMatch(adr_mail)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Adresse mail non valide. Utilisez le format abc@abc.abc."), QMessageBox::Cancel);
        return;
    }


    QRegExp nomPrenomRegex("^[a-zA-Z ]+$");

    if (!nomPrenomRegex.exactMatch(nom) || !nomPrenomRegex.exactMatch(prenom))
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le nom et le prénom doivent contenir uniquement des lettres et des espaces."), QMessageBox::Cancel);
      return;
    }
    /*QDate dateActuelle = QDate::currentDate();
    if (date_embauche > dateActuelle)
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("La date d'embauche ne peut pas être ultérieure à la date actuelle."), QMessageBox::Cancel);
      return;
    }
    if (date_naissance > dateActuelle)
    {
      QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("La date de naissance ne peut pas être ultérieure à la date actuelle."), QMessageBox::Cancel);
      return;
    }*/
    if (nom.length() < 3 || prenom.length() < 3)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le nom et le prénom doivent comporter au moins 3 caractères."), QMessageBox::Cancel);
        return;
    }

    if (QString::number(cin).length() != 8)
    {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le cin doivent être des nombres de 8 chiffres."), QMessageBox::Cancel);
        return;
    }

    if (QString::number(num_telephone).length() != 8) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le numéro de téléphone doit comporter 8 chiffres."), QMessageBox::Cancel);
        return;
    }
    if (QString::number(rib).length() != 4) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"), QObject::tr("Le RIB doit comporter 4 chiffres."), QMessageBox::Cancel);
        return;
    }
    employes e( cin, nom, prenom , adr_mail, adr_physique , mot_de_passe , genre, num_telephone , rib, poste, salaire, employes_id, date_embauche, date_naissance);


    bool test=e.modifier();
    if(test)
    {
        ui->nom->setText("");
        ui->prenom->setText("");
        ui->adr_mail->setText("");
        ui->mot_de_passe->setText("");
        ui->cin->setText("");
        ui->adr_physique->setText("");
        ui->employes_id->setText("");
        ui->salaire->setText("");
        ui->poste->setText("");
        ui->rib->setText("");
        ui->date_embauche->setDate(QDate::currentDate());
        ui->date_naissance->setDate(QDate::currentDate());
        ui->tableView->setModel(emp.afficher());
        ui->tableView->resizeColumnsToContents();
        QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Modification effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else if(!test) {
         QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("Modification non effectuée. Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);

 }else {
    QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'existe pas. Modification non effectuée. Cliquez sur Cancel pour quitter."), QMessageBox::Cancel);
}
}

void gestion_employes::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QModelIndex idIndex = ui->tableView->model()->index(row, 0);
    int employes_id = ui->tableView->model()->data(idIndex).toInt();

    employes e;


    if (e.load(employes_id)) {

        ui->nom->setText(e.getNom());
        ui->prenom->setText(e.getPrenom());
        ui->adr_mail->setText(e.getAdresseMail());
        ui->adr_physique->setText(e.getAdressePhysique());
        /*if (e.getGenre() == "Homme") {
                    ui->homme->setChecked(true);
                    ui->femme->setChecked(false);
                } else if (e.getGenre() == "Femme") {
                    ui->homme->setChecked(false);
                    ui->femme->setChecked(true);
                }*/
        ui->mot_de_passe->setText(e.getMotDePasse());
        ui->cin->setText(QString::number(e.getCIN()));
        ui->num_telephone->setText(QString::number(e.getNumeroTelephone()));
        ui->salaire->setText(QString::number(e.getSalaire()));
        ui->poste->setText(e.getposte());
        ui->rib->setText(QString::number(e.getRIB()));
        ui->employes_id->setText(QString::number(employes_id));
        /*ui->date_embauche->setDate(e.getDateEmbauche());
        ui->date_naissance->setDate(e.getNaissance());*/

    } else {

        QMessageBox::critical(nullptr, QObject::tr("Erreur"), QObject::tr("L'employé n'a pas été trouvé."), QMessageBox::Ok);
    }
}
void gestion_employes::on_recherche_clicked()
{
       QString nomRecherchee = ui->recherche_par_nom->text();

       QSqlQueryModel *results = emp.rechercherParNom(nomRecherchee);

       if (results)
       {
           ui->tableView->setModel(results);
           ui->tableView->resizeColumnsToContents();
       }
       else
       {
           QMessageBox::critical(this, "Erreur", "La recherche a échoué. Veuillez réessayer.");
       }
}
void gestion_employes::on_TriDateEmbauche_clicked()//tri
{
    QSqlQueryModel *sortedModel=emp.TriDateEmbauche();
    ui->tableView->setModel(sortedModel);
    ui->tableView->resizeColumnsToContents();
}

void gestion_employes::on_TriSalaire_clicked()//tri
{
    QSqlQueryModel *sortedModel=emp.TriSalaire();
    ui->tableView->setModel(sortedModel);
    ui->tableView->resizeColumnsToContents();
}
void gestion_employes::on_TriDateNaissance_clicked()//tri
{
    QSqlQueryModel *sortedModel=emp.TriDateNaissance();
    ui->tableView->setModel(sortedModel);
    ui->tableView->resizeColumnsToContents();
}
