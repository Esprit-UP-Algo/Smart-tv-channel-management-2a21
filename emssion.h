#ifndef EMSSION_H
#define EMSSION_H
#include "emission.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class emssion; }
QT_END_NAMESPACE

class emssion : public QMainWindow
{
    Q_OBJECT

public:
    emssion(QWidget *parent = nullptr);
     void on_modifier_clicked();
    ~emssion();

private slots:
    void on_pushButton_3_clicked();

    void on_modifier_2_clicked();

    void on_sup_clicked();
   void onModifierClicked();

   void on_modifier_4_clicked();

private:
    Ui::emssion *ui;
     emission etmp;
};
#endif // EMSSION_H
