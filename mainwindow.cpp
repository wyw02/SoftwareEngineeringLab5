#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "subwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn1_clicked()
{
    ui->inputoj1->setText("");
    ui->inputoj2->setText("");
}

void MainWindow::on_btn0_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "choose file1", "/home/njucs/Eqminer1/");
    file1.setFileName(filename);
    if(!file1.open(QIODevice::ReadOnly))
    {
        qDebug() <<"failed to open the file"<<endl;
        return;
    }
    ui->inputoj1->setPlainText(file1.readAll());
}

void MainWindow::on_btn3_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "choose file2", "/home/njucs/Eqminer1/");
    file2.setFileName(filename);
    if(!file2.open(QIODevice::ReadOnly))
    {
        qDebug() <<"failed to open the file"<<endl;
        return;
    }
    QString exactname = file2.fileName();
    ui->inputoj2->setPlainText(file2.readAll());

}

void MainWindow::on_btn2_clicked()
{
    qDebug() <<file1.fileName()<<endl;
    qDebug() <<file2.fileName()<<endl;
    SubWidget *a = new SubWidget(file1.fileName(), file2.fileName());
    a->show();
}
