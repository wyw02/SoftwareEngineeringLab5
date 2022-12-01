#include "subwidget.h"
#include "ui_subwidget.h"
#include "mainwindow.h"

SubWidget::SubWidget(QString s1, QString s2, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWidget)
{
    ui->setupUi(this);
    ui->path1->setText(s1);
    ui->path2->setText(s2);

    QFile file_1(s1);
    QFile file_2(s2);
    if (!file_1.open(QIODevice::ReadOnly) || !file_2.open(QIODevice::ReadOnly))
    {
        qDebug() << "fail to open" << endl;
        return;
    }
    ui->oj1->setPlainText(file_1.readAll());
    ui->oj2->setPlainText(file_2.readAll());
}

SubWidget::~SubWidget()
{
    delete ui;
}


void SubWidget::on_btn6_clicked()
{
    this->close();
}

void SubWidget::on_btn4_clicked() // equal
{
    QString name1 = ui->path1->text();
    name1 = name1.mid(21, name1.size()-21);
    QString name2 = ui->path2->text();
    name2 = name2.mid(21, name2.size()-21);
    QString path = name1 + "," + name2; // current oj pair
    QString path_0 = name2 + "," + name1;
    QFile equalfile("/home/njucs/Eqminer1/output/equal.csv");
    int flag = 0;
    if (equalfile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString line;
        QTextStream in(&equalfile);
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())//字符串有内容
        {
            if (QString::compare(path, line) == 0 || QString::compare(path_0, line) == 0){
                qDebug() << "already exist in equal.csv" << endl;
                flag = 1;
                break;
            }
            line=in.readLine();//循环读取下行
        }
    }else{
        qDebug() << "fail to open result file" << endl;
    }
    equalfile.close();
    if (flag == 0){ //add to equal.csv and delete from inequal
       if( equalfile.open(QIODevice::Append)){
           QTextStream txtOutput(&equalfile);
           txtOutput << path << endl;
           qDebug() << "successfully modify the result" << endl;
       }
       QString inequalpath = "/home/njucs/Eqminer1/output/inequal.csv";
       Deleteojpairs(inequalpath, path, path_0);
    }
}

void SubWidget::on_btn7_clicked()
{

    QFile result("/home/njucs/Eqminer1/output/equal.csv");
    if (!result.open(QIODevice::ReadOnly))
    {
        return;
    }
    ui->result->setPlainText(result.readAll());
}

void SubWidget::Deleteojpairs(QString path, QString pairs1, QString pairs2)
{
    QFile temp(path);
    QString content[100];
    int i = 0;
    if (temp.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString line;
        QTextStream in(&temp);
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())
        {
            if (QString::compare(pairs1, line) == 0 || QString::compare(pairs2, line) == 0){
                qDebug() << "delete this wrong record in csv" << endl;
            }
            else{
                content[i++] = line;
            }
            line=in.readLine();
            //qDebug() << line;
        }
    }
    temp.close();
    if(temp.open(QIODevice::WriteOnly | QFile::Truncate)){
        for (int j = 0; j < i; j++)
        {
            QTextStream out(&temp);
            out << content[j] << "\n";
        }
        temp.close();
    }
    temp.close();
}

void SubWidget::on_btn5_clicked() //inequal
{
    QString name1 = ui->path1->text();
    name1 = name1.mid(21, name1.size()-21);
    QString name2 = ui->path2->text();
    name2 = name2.mid(21, name2.size()-21);
    QString path = name1 + "," + name2; // current oj pair
    QString path_0 = name2 + "," + name1;
    QFile inequalfile("/home/njucs/Eqminer1/output/inequal.csv");
    int flag = 0;
    if (inequalfile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString line;
        QTextStream in(&inequalfile);
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())//字符串有内容
        {
            if (QString::compare(path, line) == 0 || QString::compare(path_0, line) == 0){
                qDebug() << "already exist in inequal.csv" << endl;
                flag = 1;
                break;
            }
            line=in.readLine();//循环读取下行
        }
    }
    else{
        qDebug() << "fail to open result file" << endl;
    }
    inequalfile.close();
    if (flag == 0){ //add to equal.csv and delete from inequal
       if( inequalfile.open(QIODevice::Append)){
           QTextStream txtOutput(&inequalfile);
           txtOutput << path << endl;
           qDebug() << "successfully modify the result" << endl;
       }
       QString inequalpath = "/home/njucs/Eqminer1/output/equal.csv";
       Deleteojpairs(inequalpath, path, path_0);
    }
}
