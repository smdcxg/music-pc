#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    view = new QWebEngineView(this);
    view->setUrl(QUrl("http://47.104.14.238/webmusic1/server.php"));
    view->show();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *)
{
    view->resize(this->size());
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
