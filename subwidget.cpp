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
    QString nextline;
    int flag = 0, extra = 0;
    int i = 0;
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
            }
            line=in.readLine();//循环读取下行
            i++;
            if (flag == 1){
                if (!line.isNull())
                    nextline = line;
                else
                    extra = 1; //no more next lines
                break;
            }
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
    else{
        recommendnext(nextline, extra);
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
    int i = 0, flag = 0;
    QString nextline;
    if (temp.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString line;
        QTextStream in(&temp);
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())
        {
            if (QString::compare(pairs1, line) == 0 || QString::compare(pairs2, line) == 0){
                qDebug() << "delete this wrong record in csv" << endl;
                flag = i;
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
    if (i == flag)//dose not have any lines
        recommendnext("nextline", 1);
    else{
        nextline = content[flag+1];
        recommendnext(nextline, 0);
    }
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
    QString nextline;
    int flag = 0, extra = 0;
    int i = 0;
    if (inequalfile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString line;
        QTextStream in(&inequalfile);
        line = in.readLine();//读取一行放到字符串里
        while(!line.isNull())//字符串有内容
        {
            if (QString::compare(path, line) == 0 || QString::compare(path_0, line) == 0){
                qDebug() << "already exist in equal.csv" << endl;
                flag = 1;
            }
            line=in.readLine();//循环读取下行
            i++;
            if (flag == 1){
                if (!line.isNull())
                    nextline = line;
                else
                    extra = 1; //no more next lines
                break;
            }
        }
    }else{
        qDebug() << "fail to open result file" << endl;
    }
    inequalfile.close();
    if (flag == 0){ //add to equal.csv and delete from inequal
       if( inequalfile.open(QIODevice::Append)){
           QTextStream txtOutput(&inequalfile);
           txtOutput << path << endl;
           qDebug() << "successfully modify the result" << endl;
       }
       QString equalpath = "/home/njucs/Eqminer1/output/equal.csv";
       Deleteojpairs(equalpath, path, path_0);
    }
    else{
        recommendnext(nextline, extra);
    }
}

void SubWidget::recommendnext(QString path, int flag){
    if (flag == 1){
        QString contents = "no more oj pairs need to be judged, please go back and add new ones if you require";
        ui->path1->setText("");
        ui->path2->setText("");
        ui->oj1->setPlainText(contents);
        ui->oj2->setPlainText(contents);
        return;
    }
    QString title = "/home/njucs/Eqminer1/";
    QStringList list = path.split(",");
    QString name1 = title + list[0];
    QString name2 = title + list[1];
    qDebug() << name1 << endl;
    qDebug() << name2 << endl;

    QFile file1(name1);
    QFile file2(name2);

    if (!file1.open(QIODevice::ReadOnly) || !file2.open(QIODevice::ReadOnly))
    {
        qDebug() <<"failed to open the file"<<endl;
        return;
    }
    ui->oj1->setPlainText(file1.readAll());
    ui->oj2->setPlainText(file2.readAll());
    ui->path1->setText(name1);
    ui->path2->setText(name2);
    file1.close();
    file2.close();

}
