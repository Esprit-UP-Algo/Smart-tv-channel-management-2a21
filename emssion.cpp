#include "emssion.h"
#include "ui_emssion.h"
#include "../acceuilprincipale/principale.h"
#include "emission.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QTableView>
#include <QComboBox>
#include <QSqlQuery>


emssion::emssion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::emssion)
{
    ui->setupUi(this);
    ui->tableView1->setModel(etmp.afficher());
    connect(ui->modifier, &QPushButton::clicked, this, &emssion::onModifierClicked);
}


emssion::~emssion()
{
    delete ui;
}


void emssion::on_pushButton_3_clicked()
{
    principale *principaleWindow = new principale(this);
    principaleWindow->show();
    this->hide();
}

void emssion::on_modifier_2_clicked()
{
    int duree=ui->cin_4->text().toInt();
    QString nom=ui->cin_3->text();
    QString date_diffusion=ui->dateTimeEdit->text();
    QString type=ui->comboBox_2->currentText();
    QString description=ui->poste_2->text();

    if (nom.isEmpty() || date_diffusion.isEmpty() || duree <= 0 || type.isEmpty() || description.isEmpty()) {
           QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
           return;
       }

    emission e(nom, date_diffusion, duree, type, description);


    bool test=e.ajouter();

    if(test)
    {
        ui->tableView1->setModel(etmp.afficher());
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("ajout effectue\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

              }
                  else
                      QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("ajout non effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tableView1->setModel(etmp.afficher());
    emssion *emssionWindow = new emssion(this);
    emssionWindow->show();
    this->hide();

   }
}

void emssion::on_sup_clicked()
{
    int id=ui->supprimer->text().toInt();
        bool test=etmp.supprimer(id);

        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("supprission effectue\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

              }
                  else
                      QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("supprission non effectue.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

        ui->tableView1->setModel(etmp.afficher());
        emssion *emssionWindow = new emssion(this);
        emssionWindow->show();
        this->hide();
}


void emssion::onModifierClicked() {

    ui->tabWidget->setCurrentIndex(2);
    int id=ui->supprimer->text().toInt();
    QSqlQuery query;
        query.prepare("SELECT nom, date_diffusion, duree, type, description FROM emission WHERE id = :id");
        query.bindValue(":id", id);
        if (query.exec() && query.next()) {
                QString nom = query.value(0).toString();
                QString date_diffusion = query.value(1).toString();
                int duree = query.value(2).toInt();
                QString type = query.value(3).toString();
                QString description = query.value(4).toString();

                // Afficher les données dans les champs correspondants
                ui->cin_5->setText(nom);
                ui->dateTimeEdit->setDateTime(QDateTime::fromString(date_diffusion, "yyyy-MM-dd HH:mm:ss"));
                ui->cin_6->setText(QString::number(duree));
                ui->comboBox_3->setCurrentText(type);
                ui->poste_3->setText(description);

            } else {
                // Gérer l'erreur si l'enregistrement avec l'ID spécifié n'est pas trouvé
                QMessageBox::warning(this, "Erreur", "Enregistrement non trouvé dans la base de données.");
            }


}

void emssion::on_modifier_4_clicked()
{
    int id = ui->supprimer->text().toInt();
    int duree = ui->cin_6->text().toInt();
    QString nom = ui->cin_5->text();
    QString date_diffusion = ui->dateTimeEdit->text();
    QString type = ui->comboBox_3->currentText();
    QString description = ui->poste_3->text();

    if (nom.isEmpty() || date_diffusion.isEmpty() || duree <= 0 || type.isEmpty() || description.isEmpty()) {
            QMessageBox::critical(this, "Erreur", "Veuillez remplir tous les champs.");
            return;
        }
    emission e(nom, date_diffusion, duree, type, description);

    bool test = e.modifier(id);

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                              QObject::tr("Modification effectuée."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Échec de la modification."), QMessageBox::Cancel);
    }
    ui->tableView1->setModel(etmp.afficher());
    emssion *emssionWindow = new emssion(this);
    emssionWindow->show();
    this->hide();
}
