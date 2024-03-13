#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <QDialog>

namespace Ui {
class menuprincipal;
}

class menuprincipal : public QDialog
{
    Q_OBJECT

public:
    explicit menuprincipal(QWidget *parent = nullptr);
    ~menuprincipal();

private slots:
    void on_gestion_publicite_clicked();

private:
    Ui::menuprincipal *ui;
};

#endif // MENUPRINCIPAL_H
