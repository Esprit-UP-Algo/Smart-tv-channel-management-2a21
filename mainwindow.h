#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "serie.h"

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

    void on_Ajouter_Button_clicked();

    void on_supprimer_button_clicked();

    void on_Modifier_button_clicked();

    void on_ShowButton_clicked();

private:
    Ui::MainWindow *ui;
    serie etmp;
};
#endif // MAINWINDOW_H
