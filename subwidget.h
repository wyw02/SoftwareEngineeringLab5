#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
namespace Ui {
class SubWidget;
}

class SubWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubWidget(QString s1, QString s2, QWidget *parent = nullptr);
    ~SubWidget();
    void Deleteojpairs(QString path, QString pairs1, QString pairs2);

private slots:
    void on_btn6_clicked();

    void on_btn4_clicked();

    void on_btn7_clicked();

    void on_btn5_clicked();

private:
    Ui::SubWidget *ui;
    QFile equal;
    QFile inequal;
};

#endif // SUBWIDGET_H
