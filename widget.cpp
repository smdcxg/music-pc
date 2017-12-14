#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::sendText(const QString &text)
{
    qDebug() << "sw:" << text;
}

void Widget::receiveText(const QString &text)
{
    qDebug() << "rw:" << text;
    if(text == "close"){
        this->close();
        qDebug() << "bye";
    }
}
