#ifndef GESTION_EMPLOYES_H
#define GESTION_EMPLOYES_H
#include "employes.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class gestion_employes; }
QT_END_NAMESPACE

class gestion_employes : public QMainWindow
{
    Q_OBJECT

public:
    gestion_employes(QWidget *parent = nullptr);
    QString getSelectedGender();

    ~gestion_employes();

private slots:
    void on_ajouter_clicked();

    void on_modifier1_clicked();

    void on_sup_clicked();

    void on_recherche_clicked();

    void on_TriDateEmbauche_clicked();
    void on_TriSalaire_clicked();
    void on_TriDateNaissance_clicked();



    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::gestion_employes *ui;
    employes emp;


};
#endif // GESTION_EMPLOYES_H
