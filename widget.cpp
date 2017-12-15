#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground, true);    //设置窗体透明

    view = new QWebEngineView(this);
    //view->setUrl(QUrl("http://47.104.14.238/webmusic1/server.php"));
    view->setUrl(QUrl("http://127.0.0.1/webmusic/server.php"));
    view->show();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *)
{
    view->setGeometry(this->rect().x() + 25, this->rect().y() + 25, this->size().width() - 50, this->size().height() - 50);
    //view->resize(this->size().width() - 30, this->size().height() - 30);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(25, 25, this->width()-50, this->height()-50);
    QPainter painter(this);
    //painter.setCompositionMode( QPainter::CompositionMode_Clear );
    //painter.fillRect( 10, 10, 300, 300, Qt::SolidPattern );
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);
    for(int i=0; i<25; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(25-i, 25-i, this->width()-(25-i)*2, this->height()-(25-i)*2);
        color.setAlpha(140 - qSqrt(i)*40);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

//重写鼠标按下事件
void Widget::mousePressEvent(QMouseEvent *event)
{
    return QWidget::mousePressEvent(event);
}

//重写鼠标移动事件
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << 1;

    return QWidget::mouseMoveEvent(event);
}

void Widget::sendText(const QString &text)
{
    qDebug() << "sw:" << text;
}

void Widget::receiveSize(const qint8 offsetX, const qint8 offsetY){
    qDebug() << offsetX << "," << offsetY;
    qDebug() << this->rect().x();
    /*QRect rect = this->rect();
    rect.setX(this->pos().x() + offsetX);
    rect.setY(this->pos().y() + offsetY);*/

    this->setGeometry(this->pos().x() + offsetX, this->pos().y() + offsetY, this->width(), this->height());
}

void Widget::receiveText(const QString &text)
{
    qDebug() << "rw:" << text;
    if(text == "@close"){
        this->close();
        qDebug() << "bye";
    }else if(text == "@minimized"){
        this->showMinimized();
    }else if(text == "@maximized"){
        this->showMaximized();
    }else if(text == "@normal"){
        this->showNormal();
    }
}
