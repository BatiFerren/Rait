#include "myrait.h"
#include "ui_myrait.h"

MyRait::MyRait(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyRait)
{
    ui->setupUi(this);

    univdb = QSqlDatabase::addDatabase("QSQLITE");
    univdb.setDatabaseName("E:/QtProjects/Raiting_of_univ/Raitings/university.db");

    if (!univdb.open()){
        ui->label_status->setText("Failed to connection...");
        ui->label_status->setStyleSheet("color: red;");
    }
    else{
        ui->label_status->setText("Connected");
        ui->label_status->setStyleSheet("color: green;");
    }
}

MyRait::~MyRait()
{
    delete ui;
}

void MyRait::on_pushButton_show_clicked()
{
    QSqlQueryModel * qmodel = new QSqlQueryModel();
    QSqlQuery * qr = new QSqlQuery(univdb);
    qr->prepare("SELECT * FROM raiting");
    qr->exec();
    qmodel->setQuery(*qr);
    ui->tableView->setModel(qmodel);
    ui->tableView->setSortingEnabled(true);
}

void MyRait::on_pushButton_add_clicked()
{
    QString name, city, country, rait;
    name = ui->lineEdit_name->text();
    city = ui->lineEdit_city->text();
    country = ui->lineEdit_country->text();
    rait = ui->lineEdit_raiting->text();
    QSqlQuery q;
    q.prepare("INSERT INTO raiting(name, city, country, rait) VALUES ('"+name+"', '"+city+"', '"+country+"', '"+rait+"')");
    if(!q.exec()){
        ui->label_status->setText("Failed to save");
        ui->label_status->setStyleSheet("color: red;");
    }
    else{
        ui->label_status->setText("Data saved");
        ui->label_status->setStyleSheet("color: green;");
    }
}

void MyRait::on_pushButton_delete_clicked()
{
    QItemSelectionModel * sel = ui->tableView->selectionModel();
    if(sel->hasSelection()){
        QModelIndexList selrow = ui->tableView->selectionModel()->selectedIndexes();
        int rownumb = selrow.at(0).row();
        QModelIndex v = ui->tableView->model()->index(rownumb, 0);
        QVariant vdat = ui->tableView->model()->data(v);
        QString delid = vdat.toString();
        QSqlQuery q;
        q.prepare("DELETE FROM raiting WHERE id='"+delid+"'");
        if(!q.exec()){
            ui->label_status->setText("Failed to delete");
            ui->label_status->setStyleSheet("color: red;");
        }
        else{
            ui->label_status->setText("Row deleted");
            ui->label_status->setStyleSheet("color: green;");
        }
            qDebug() << selrow.at(0).data().toString() << "\n";
            qDebug() << vdat.toString();
        ui->label_status->setText("Row has been selected");
        ui->label_status->setStyleSheet("color: green;");
    }
    else {
        ui->label_status->setText("No selected row");
        ui->label_status->setStyleSheet("color: red;");
    }
}
