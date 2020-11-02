#ifndef MYRAIT_H
#define MYRAIT_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QModelIndex>

namespace Ui {
class MyRait;
}

class MyRait : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyRait(QWidget *parent = 0);
    ~MyRait();

private slots:
    void on_pushButton_show_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

private:
    Ui::MyRait *ui;
    QSqlDatabase univdb;
};

#endif // MYRAIT_H
