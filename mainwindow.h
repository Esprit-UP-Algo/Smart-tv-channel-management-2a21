#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "publicite.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();

    void on_sup_clicked();

    void on_modifier_clicked();

    void on_btnpdf_clicked();

    void on_tri_currentIndexChanged(int index);

    void on_searchButton_clicked();

    void on_confirmer_clicked();

private:
    Ui::MainWindow *ui;

    publicite Pubmp;
};
#endif // MAINWINDOW_H
