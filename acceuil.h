#ifndef ACCEUIL_H
#define ACCEUIL_H
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class acceuil;
}

class acceuil : public QDialog
{
    Q_OBJECT

public:
    explicit acceuil(QWidget *parent = nullptr);
    ~acceuil();

private slots:
    void on_pushButton_8_clicked();

private:
    Ui::acceuil *ui;
};

#endif // ACCEUIL_H
