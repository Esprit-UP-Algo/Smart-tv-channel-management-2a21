#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "publicite.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    ui->tableView->setModel(Pubmp.afficher());

    connect(ui->tri, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_tri_currentIndexChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    // Récupération des informations saisies dans les 9 champs

    int Id = ui->lineEdit_ID->text().toInt();
    QString nomQString = ui->lineEdit_nom->text();
    QString descriptionQString = ui->lineEdit_description->text();
    QString coutQString = ui->lineEdit_cout->text();

    QString cibleQString = ui->lineEdit_cible->text();
    QString dureeQString = ui->lineEdit_duree->text();
    QString realisateurQString = ui->lineEdit_realisateur->text();

    QString DateHdebutQString = ui->lineEditD->text();
    QString DateHFinQString = ui->lineEditF->text();

    publicite p(Id, nomQString,  descriptionQString, dureeQString, cibleQString, coutQString, DateHdebutQString, DateHFinQString, realisateurQString);

    bool test=p.ajouter();


    // Affichage d'un message en fonction du succès de l'ajout
    if (test) {
        ui->tableView->setModel(Pubmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué, La pub a été ajouté avec succès."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectué. La pub n'a pas ete ajouté"), QMessageBox::Cancel);
    }

}

void MainWindow::on_supprimer_clicked()
{
    int Id =ui->lineEditSupp->text().toInt();
    bool test=Pubmp.supprimer(Id);
    if(test)
    {
        ui->tableView->setModel(Pubmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Suppression Pub effectué, La pub a été supprimé avec succès."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Suppression non effectué. La pub"
                                                                          "  n'a pas ete supprimé"), QMessageBox::Cancel);

}


void MainWindow::on_modifier_clicked()
{

        // Get the selected row index
        QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
        if (selectedIndexes.isEmpty()) {
            QMessageBox::warning(this, tr("Error"), tr("No row selected."));
            return;
        }

        // Get the ID of the selected row
        int selectedRow = selectedIndexes.at(0).row();
        QModelIndex idIndex = ui->tableView->model()->index(selectedRow, 0);
        int id = ui->tableView->model()->data(idIndex).toInt();

        // Retrieve the data of the selected row
        QModelIndex nomIndex = ui->tableView->model()->index(selectedRow, 1);
        QModelIndex descriptionIndex = ui->tableView->model()->index(selectedRow, 2);
        QModelIndex dureeIndex = ui->tableView->model()->index(selectedRow, 3);
        QModelIndex cibleIndex = ui->tableView->model()->index(selectedRow, 4);
        QModelIndex coutIndex = ui->tableView->model()->index(selectedRow, 5);
        QModelIndex dateHdebutIndex = ui->tableView->model()->index(selectedRow, 6);
        QModelIndex dateHFinIndex = ui->tableView->model()->index(selectedRow, 7);
        QModelIndex realisateurIndex = ui->tableView->model()->index(selectedRow, 8);

        QString nom = ui->tableView->model()->data(nomIndex).toString();
        QString description = ui->tableView->model()->data(descriptionIndex).toString();
        QString duree = ui->tableView->model()->data(dureeIndex).toString();
        QString cible = ui->tableView->model()->data(cibleIndex).toString();
        QString cout = ui->tableView->model()->data(coutIndex).toString();
        QString dateHdebut = ui->tableView->model()->data(dateHdebutIndex).toString();
        QString dateHFin = ui->tableView->model()->data(dateHFinIndex).toString();
        QString realisateur = ui->tableView->model()->data(realisateurIndex).toString();

        // Populate the fields in your UI with the data of the selected row
        ui->lineEdit_ID_2->setText(QString::number(id));
        ui->lineEdit_nom_2->setText(nom);
        ui->lineEdit_description_2->setText(description);
        ui->lineEdit_cout_2->setText(cout);
        ui->lineEdit_cible_2->setText(cible);
        ui->lineEdit_duree_2->setText(duree);
        ui->lineEdit_realisateur_2->setText(realisateur);
        ui->lineEditD_2->setText(dateHdebut);
        ui->lineEditF_2->setText(dateHFin);


}

void MainWindow::on_sup_clicked()
{

}

void MainWindow::on_btnpdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "", tr("PDF Files (*.pdf)"));
    if (!fileName.isEmpty()) {
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        QPainter painter(&printer);
        // Calculate the total width of the table
        int totalWidth = ui->tableView->verticalHeader()->width();
        for (int column = 0; column < ui->tableView->model()->columnCount(); ++column)
            totalWidth += ui->tableView->columnWidth(column);

        // Set the width of the printer to fit the entire table
        qreal scaleFactor = printer.pageRect().width() / qreal(totalWidth);
        painter.scale(scaleFactor, scaleFactor);
        ui->tableView->render(&painter);
    }
}


void MainWindow::on_tri_currentIndexChanged(int index)
{
    QString columnName;
    switch(index) {
        case 1: // TRI SELON DUREE
            columnName = "Duree";
            break;
        case 2: // TRI SELON COUT
            columnName = "Cout";
            break;
        case 3: // TRI SELON DATE DEBUT
            columnName = "DateHdebut";
            break;
        default:
            return;
    }

    // Sort the model based on the selected column
    ui->tableView->sortByColumn(index, Qt::AscendingOrder);
}

void MainWindow::on_searchButton_clicked()
{
    QString searchName = ui->lineEdit_search->text();
    QSqlQueryModel *searchModel = new QSqlQueryModel();
    searchModel->setQuery("SELECT * FROM publicite WHERE Nom LIKE '%" + searchName + "%'");
    ui->tableView->setModel(searchModel);
}

void MainWindow::on_confirmer_clicked()
{

        // Retrieve the modified data from the UI
        int id = ui->lineEdit_ID_2->text().toInt();
        QString nom = ui->lineEdit_nom_2->text();
        QString description = ui->lineEdit_description_2->text();
        QString duree = ui->lineEdit_duree_2->text();
        QString cible = ui->lineEdit_cible_2->text();
        QString cout = ui->lineEdit_cout_2->text();
        QString dateHdebut = ui->lineEditD_2->text();
        QString dateHFin = ui->lineEditF_2->text();
        QString realisateur = ui->lineEdit_realisateur_2->text();

        // Update the data in the database
        publicite p(id, nom, description, duree, cible, cout, dateHdebut, dateHFin, realisateur);
        bool success = p.modifier();

        if (success) {
            QMessageBox::information(this, tr("Success"), tr("Data updated successfully."));
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to update data."));
        }

        // Refresh the table view to reflect the changes
        ui->tableView->setModel(Pubmp.afficher());


}
