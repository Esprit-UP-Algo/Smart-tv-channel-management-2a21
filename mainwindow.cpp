#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serie.h" // Si nécessaire pour la classe "serie"
#include <QMessageBox>
#include <QSqlQuery> // Pour QSqlQuery
#include <QSqlError> // Pour gérer les erreurs de requête SQL
#include <QDateTime> // Pour QDateTime
#include <QTableView> // Si vous utilisez QTableView dans votre interface utilisateur
#include <QMainWindow>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  QWidget *page1Widget = ui->stackedWidget->widget(0);
   QWidget *page2Widget = ui->stackedWidget->widget(1);
     ui-> stackedWidget->addWidget(page1Widget);
     ui-> stackedWidget->addWidget(page2Widget);


     // Set initial page
     ui->stackedWidget->setCurrentWidget(page1Widget);
     connect(ui->Next, &QPushButton::clicked, this, [=](){
         ui->stackedWidget->setCurrentWidget(page2Widget);
     });
     connect(ui->Prev, &QPushButton::clicked, this, [=](){
         ui->stackedWidget->setCurrentWidget(page1Widget);
     });
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_Ajouter_Button_clicked()
{
    // Vérifier la saisie de l'ID (doit être un entier positif)
    bool okId;
    int id = ui->Id_serie->text().toInt(&okId);
    if (!okId || id <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                              QObject::tr("ID invalide. Veuillez saisir un entier positif."),
                              QMessageBox::Cancel);
        return;
    }

    // Vérifier la saisie du nom (longueur maximale de 8 caractères)
    QString nom = ui->Nom_serie->text();
    if (nom.length() > 8) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                              QObject::tr("Nom invalide. La longueur maximale est de 8 caractères."),
                              QMessageBox::Cancel);
        return;
    }

    bool okDuree;
    int duree = ui->Duree->text().toInt(&okDuree);
    if (!okDuree || duree <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                              QObject::tr("Durée invalide. Veuillez saisir un entier positif."),
                              QMessageBox::Cancel);
        return;
    }

    QString description = ui->Description->text();
    QStringList lines = description.split('\n');
    if ( description.length() > 300) {
           QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                                 QObject::tr("Description invalide. Veuillez saisir entre 3 et 300 caractères."),
                                 QMessageBox::Cancel);
           return;
       }
    QSqlQuery query;
    QDateTime Date = ui->Date_Diffusion->dateTime();
    QString Type = ui->Type_Box->currentText();

    query.prepare("INSERT INTO serie (ID, NOM, TYPE, DATE_DE_DIFFUSION, DUREE, DESCRIPTION) "
                  "VALUES (:id, :nom, :type, :DateDiffusion, :duree, :Description)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", Type);
    query.bindValue(":DateDiffusion", Date.toString(Qt::ISODate));
    query.bindValue(":duree", duree);
    query.bindValue(":Description", description);

    if (query.exec()) {

        QMessageBox::information(nullptr, QObject::tr("Ajouter"),
                                 QObject::tr("Ajout avec succès.\n"
                                             "Click Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                              QObject::tr("Échec d'ajout : %1.\n"
                                          "Click Cancel to exit.").arg(query.lastError().text()),
                              QMessageBox::Cancel);
    }
    QSqlQuery query1("SELECT * FROM serie");

    ui->Table_Serie->clearContents();
    ui->Table_Serie->setRowCount(0);

    int row = 0;
    while (query1.next()) {
        int id = query1.value(0).toInt();
        QString nom = query1.value(1).toString();
        QString type = query1.value(2).toString();
        QDateTime dateDiffusion = query1.value(3).toDateTime();
        int duree = query1.value(4).toInt();
        QString description = query1.value(5).toString();

        ui->Table_Serie->insertRow(row);
        ui->Table_Serie->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        ui->Table_Serie->setItem(row, 1, new QTableWidgetItem(nom));
        ui->Table_Serie->setItem(row, 2, new QTableWidgetItem(dateDiffusion.toString(Qt::ISODate)));
        ui->Table_Serie->setItem(row, 3, new QTableWidgetItem(QString::number(duree)));
        ui->Table_Serie->setItem(row, 4, new QTableWidgetItem(type));
        ui->Table_Serie->setItem(row, 5, new QTableWidgetItem(description));

        row++;
    }
}


void MainWindow::on_supprimer_button_clicked()
{
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment supprimer cette série ?",
                                          QMessageBox::Yes | QMessageBox::No);

    if (confirmation == QMessageBox::No) {
        return;
    }

    QSqlQuery query;
    int id = ui->Supprimer_Field->text().toInt();
    query.prepare("DELETE FROM serie WHERE ID = :id");
    query.bindValue(":id", id);
    if (query.exec())
    {
        QMessageBox::information(nullptr, QObject::tr("Suppression"), QObject::tr("Suppression réussie.\nClick cancel to exit"), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Suppression"), QObject::tr("Échec de la suppression : %1.\nClick Cancel to exit.").arg(query.lastError().text()), QMessageBox::Cancel);
    }
}


void MainWindow::on_Modifier_button_clicked()
{
    bool okId;
    int id = ui->Id_serie->text().toInt(&okId);
    if (!okId || id <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                              QObject::tr("ID invalide. Veuillez saisir un entier positif."),
                              QMessageBox::Cancel);
        return;
    }

    QString nom = ui->Nom_serie->text();
    if (nom.length() > 8) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                              QObject::tr("Nom invalide. La longueur maximale est de 8 caractères."),
                              QMessageBox::Cancel);
        return;
    }

    bool okDuree;
    int duree = ui->Duree->text().toInt(&okDuree);
    if (!okDuree || duree <= 0) {
        QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                              QObject::tr("Durée invalide. Veuillez saisir un entier positif."),
                              QMessageBox::Cancel);
        return;
    }

    QString description = ui->Description->text();
    QStringList lines = description.split('\n');
    if ( description.length() > 300) {
           QMessageBox::critical(nullptr, QObject::tr("Ajouter"),
                                 QObject::tr("Description invalide. Veuillez saisir entre 3 et 300 caractères."),
                                 QMessageBox::Cancel);
           return;
       }
       QMessageBox::StandardButton confirmation;
       confirmation = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment mettre à jour cette série ?",
                                             QMessageBox::Yes | QMessageBox::No);

       if (confirmation == QMessageBox::No) {
           // L'utilisateur a annulé l'opération de mise à jour
           return;
       }

       QSqlQuery query;

       QDateTime Date = ui->Date_Diffusion->dateTime();
       int Duree = ui->Duree->text().toInt();
       QString Type = ui->Type_Box->currentText();
       QString Description = ui->Description->text();

       query.prepare("UPDATE serie SET NOM = :nom, TYPE = :type, DATE_DE_DIFFUSION = :DateDiffusion, DUREE = :duree, DESCRIPTION = :Description WHERE ID = :id");
       query.bindValue(":id", id);
       query.bindValue(":nom", nom);
       query.bindValue(":type", Type);
       query.bindValue(":DateDiffusion", Date.toString(Qt::ISODate));
       query.bindValue(":duree", Duree);
       query.bindValue(":Description", Description);

       if (query.exec())
       {
           QMessageBox::information(nullptr, QObject::tr("Mise à jour"), QObject::tr("Mise à jour réussie.\nClick Cancel to exit"), QMessageBox::Cancel);
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("Mise à jour"), QObject::tr("Échec de la mise à jour : %1.\nClick Cancel to exit.").arg(query.lastError().text()), QMessageBox::Cancel);
       }

}


