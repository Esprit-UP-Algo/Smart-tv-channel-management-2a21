#include "acceuil.h"
#include "ui_acceuil.h"
#include "publicite.h"
#include "mainwindow.h"
#include "menuprincipal.h"

acceuil::acceuil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acceuil)
{
    ui->setupUi(this);
}

acceuil::~acceuil()
{
    delete ui;
}

void acceuil::on_pushButton_8_clicked()
{
    this->hide(); // Hide the acceuil window
        menuprincipal *mainwindow = new menuprincipal(); // Create an instance of MainWindow
        mainwindow->show(); // Show the MainWindow
}
