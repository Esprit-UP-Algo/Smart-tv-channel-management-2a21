#ifndef EMSSION_H
#define EMSSION_H
#include "emission.h"
#include <QMainWindow>
#include <QSortFilterProxyModel>
QT_BEGIN_NAMESPACE
namespace Ui { class emssion; }
QT_END_NAMESPACE

class emssion : public QMainWindow
{
    Q_OBJECT

public:
    emssion(QWidget *parent = nullptr);

    ~emssion();

private slots:
    void on_pushButton_3_clicked();
    void on_modifier_2_clicked();
    void on_sup_clicked();
    void onModifierClicked();
    void on_modifier_4_clicked();
    void on_comboBox_activated(int index);

    void on_pushButton_5_clicked();

    void on_generer_pdf_clicked();

    void on_modifier_5_clicked();

    void on_modifier_3_clicked();

    void on_statistique_clicked();

private:
    Ui::emssion *ui;
     emission etmp;
     QSortFilterProxyModel *proxyModel;
};
#endif // EMSSION_H
