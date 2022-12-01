#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QFile>

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
    void on_btn1_clicked();

    void on_btn0_clicked(); //choose file1

    void on_btn3_clicked(); //choose file2

    void on_btn2_clicked();

private:
    Ui::MainWindow *ui;
    QFile file1;
    QFile file2;
};

#endif // MAINWINDOW_H
