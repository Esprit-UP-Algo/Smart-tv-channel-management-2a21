#include "menuprincipal.h"
#include "ui_menuprincipal.h"
#include "mainwindow.h"

menuprincipal::menuprincipal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menuprincipal)
{
    ui->setupUi(this);
}

menuprincipal::~menuprincipal()
{
    delete ui;
}

void menuprincipal::on_gestion_publicite_clicked()
{
    this->hide(); // Hide the acceuil window
        MainWindow *mainwindow = new MainWindow(); // Create an instance of MainWindow
        mainwindow->show(); // Show the MainWindow
}
