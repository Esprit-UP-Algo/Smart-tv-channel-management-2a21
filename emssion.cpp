#include "emssion.h"
#include "ui_emssion.h"
#include "../acceuilprincipale/principale.h"
#include "emission.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QTableView>
#include <QComboBox>
#include <QSqlQuery>
#include <QTextDocument>
#include <QPrinter>
#include <QSqlQueryModel>
#include <QFile>
#include <QFileDialog>
#include <QtCharts>
#include <QChartView>
#include "graphview.h"

emssion::emssion(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::emssion)
{
    ui->setupUi(this);
    ui->tableView1->setModel(etmp.afficher());
    connect(ui->modifier, &QPushButton::clicked, this, &emssion::onModifierClicked);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(etmp.afficher());
    ui->tableView1->setModel(proxyModel);
    ui->tableView1->setMinimumSize(900, 600);
    for (int i = 0; i < ui->tableView1->model()->columnCount(); ++i) {
        ui->tableView1->setColumnWidth(i, 140);}
    connect(ui->pushButton_5, &QPushButton::clicked, this, &emssion::on_pushButton_5_clicked);


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
    QString nom = ui->cin_3->text();
        QString date_diffusion = ui->dateTimeEdit->text();
        int duree = ui->cin_4->text().toInt();
        QString type = ui->comboBox_2->currentText();
        QString description = ui->poste_2->text();
        QDateTime now = QDateTime::currentDateTime();

        QString nowAsString = now.toString("M/d/yyyy h:mm AP");

        if (nom.isEmpty() || date_diffusion.isEmpty() || duree <= 0 || type.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
            return;
        }
        if (date_diffusion < nowAsString) {
            QMessageBox::warning(this, "Erreur", "La date de diffusion ne peut pas être antérieure à la date actuelle.");
            return;
        }

        emission e(nom, date_diffusion, duree, type, description);
        bool test = e.ajouter();

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué.\nClick Ok to exit."), QMessageBox::Ok);
        } else {
            QMessageBox::warning(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout non effectué.\nClick Ok to exit."), QMessageBox::Ok);
        }


        ui->tableView1->setModel(etmp.afficher());


        emssion *emssionWindow = new emssion(this);
        emssionWindow->show();
        this->hide();
}

void emssion::on_sup_clicked()
{
    int id = ui->supprimer->text().toInt();

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM nom_de_table WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    int count = 0;
    if (query.next()) {
        count = query.value(0).toInt();
    }

    if (count == 0) {

        QMessageBox::warning(this, tr("Erreur"), tr("L'ID spécifié n'existe pas."));
        return;
    } else {

        bool test = etmp.supprimer(id);
        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Suppression effectuée\n"
                                                 "Cliquez sur OK pour quitter."), QMessageBox::Ok);
        } else {
            QMessageBox::warning(nullptr, QObject::tr("Pas OK"),
                                  QObject::tr("Suppression non effectuée.\n"
                                              "Cliquez sur OK pour quitter."), QMessageBox::Ok);
        }
    }


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
                ui->cin_5->setText(nom);
                ui->dateTimeEdit_2->setDateTime(QDateTime::fromString(date_diffusion, "M/d/yyyy h:mm AP"));
                ui->cin_6->setText(QString::number(duree));
                ui->comboBox_3->setCurrentText(type);
                ui->poste_3->setText(description);

            } else {

                QMessageBox::warning(this, "Erreur", "Enregistrement non trouvé dans la base de données.");
            }


}

void emssion::on_modifier_4_clicked()
{
    int id = ui->supprimer->text().toInt();
        int duree = ui->cin_6->text().toInt();
        QString nom = ui->cin_5->text();
        QString date_diffusion = ui->dateTimeEdit_2->text();
        QString type = ui->comboBox_3->currentText();
        QString description = ui->poste_3->text();

        if (nom.isEmpty() || date_diffusion.isEmpty() || duree <= 0 || type.isEmpty()) {
            QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
            return;
        }
        emission e(nom, date_diffusion, duree, type, description);

        bool test = e.modifier(id);

        if(test)
        {
            ui->tableView1->setModel(etmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("Modification effectuée."), QMessageBox::Ok);
            ui->tableView1->setModel(etmp.afficher());
            emssion *emssionWindow = new emssion(this);
            emssionWindow->show();
            this->hide();
        }
        else
        {
            QMessageBox::warning(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Échec de la modification."), QMessageBox::Ok);
        }
}


void emssion::on_comboBox_activated(int index)
{
    int column = index;
        proxyModel->sort(column, Qt::AscendingOrder);
}

void emssion::on_pushButton_5_clicked()
{
        QString searchText = ui->recherche_par_nom->text(); // Assuming lineEdit_recherche_par_nom is your QLineEdit for search input
        proxyModel->setFilterKeyColumn(1); // Replace YOUR_NAME_COLUMN_INDEX with the actual index of the name column in your model
        proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive); // Makes the search case-insensitive
        proxyModel->setFilterFixedString(searchText);
}

void emssion::on_generer_pdf_clicked()
{
    QSqlQueryModel *model = etmp.afficher();

    QTextDocument doc;

    QString content = "<h1 style='font-family: Arial; font-size: 100pt;'>Liste des émissions</h1>";
    content += "<table border='0'><tr><th>ID</th><th>Nom</th><th>Date de diffusion</th><th>Durée</th><th>Type</th><th>Description</th></tr>";
    for (int row = 0; row < model->rowCount(); ++row) {
        content += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            content += "<td>" + model->data(model->index(row, col)).toString() + "</td>";
        }
        content += "</tr>";
    }
    content += "</table>";

    doc.setHtml(content);

    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer PDF", "", "PDF files (*.pdf)");


    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    doc.print(&printer);

    QMessageBox::information(nullptr, QObject::tr("Succès"),
                          QObject::tr("Le fichier PDF a été enregistré avec succès !."), QMessageBox::Ok);
    ui->tableView1->setModel(etmp.afficher());
    emssion *emssionWindow = new emssion(this);
    emssionWindow->show();
    this->hide();
}

void emssion::on_modifier_5_clicked()
{
    ui->tableView1->setModel(etmp.afficher());
    emssion *emssionWindow = new emssion(this);
    emssionWindow->show();
    this->hide();
}

void emssion::on_modifier_3_clicked()
{
    ui->tableView1->setModel(etmp.afficher());
    emssion *emssionWindow = new emssion(this);
    emssionWindow->show();
    this->hide();
}

void emssion::on_statistique_clicked()
{
    ui->tabWidget->setCurrentIndex(3);

    QGraphicsScene *scene = new QGraphicsScene(this);

    QMap<QString, int> emissionCounts = {
        {"Documentaire", 0},
        {"Divertissement", 0},
        {"TeleAchat", 0},
        {"Cuisine", 0},
        {"Sport", 0},
        {"Télé-réalité", 0},
        {"Talk-show", 0}
    };

    QSqlQuery query("SELECT type, COUNT(*) FROM emission GROUP BY type");

    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        emissionCounts[type] = count;
    }

    int totalEmissions = 0;
    for (int count : emissionCounts.values()) {
        totalEmissions += count;
    }

    QMap<QString, double> emissionPercentages;
    for (const QString &type : emissionCounts.keys()) {
        int count = emissionCounts.value(type);
        double percentage = (static_cast<double>(count) / totalEmissions) * 100.0;
        emissionPercentages.insert(type, percentage);
    }

    QBarSet *set = new QBarSet("Pourcentage");
    for (const QString &type : emissionPercentages.keys()) {
        *set << emissionPercentages.value(type);
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des types d'émission");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (const QString &type : emissionCounts.keys()) {
        categories << type;
    }
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setMinimumSize(900, 400);
    QGraphicsView *graphicsView = ui->graphicsView;
    graphicsView->setScene(scene);
    scene->addWidget(chartView);
}

