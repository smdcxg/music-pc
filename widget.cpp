#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initialization();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *)
{
    view->setGeometry(this->rect().x() + 25, this->rect().y() + 25, this->size().width() - 50, this->size().height() - 25 - 25);
}

void Widget::paintEvent(QPaintEvent *event)
{
    /*QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(25, 25, this->width()-50, this->height()-50);
    QPainter painter(this);
    //painter.setCompositionMode( QPainter::CompositionMode_Clear );
    //painter.fillRect( 10, 10, 300, 300, Qt::SolidPattern );
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(200, 200, 200, 0);
    for(int i=0; i<25; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(25-i, 25-i, this->width()-(25-i)*2, this->height()-(25-i)*2);
        color.setAlpha(150 - qSqrt(i)*40);
        painter.setPen(color);
        painter.drawPath(path);
    }*/
}

void Widget::labelMousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
    return QWidget::mouseMoveEvent(event);
}

//重写鼠标移动事件
void Widget::labelMouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //鼠标移动事件需要移动窗口，窗口移动到哪里呢？就是要获取鼠标移动中，窗口在整个屏幕的坐标，然后move到这个坐标，怎么获取坐标？
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    qDebug() << event->globalPos();
    if (mMoveing && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}
void Widget::labelMouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << 0;
    mMoveing = false;
}

void Widget::initialization(){
    //应用样式 apply the qss style
    QFile file(":/qss/skin/black.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);
    file.close();
    setMouseTracking(true);
    mMoveing = false;
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    //setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint |Qt::WindowStaysOnTopHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);    //设置窗体透明

    view = new QWebEngineView(this);
    view->page()->profile()->clearHttpCache(); // 清理缓存
    view->page()->profile()->clearAllVisitedLinks(); // 清理浏览记录
    view->page()->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);       // 支持MP3播放
    QWebEngineCookieStore* pCookie = view->page()->profile()->cookieStore();
    pCookie->deleteAllCookies(); // 清理cookie
    pCookie->deleteSessionCookies(); // 清理会话cookie
    //view->setUrl(QUrl("http://47.104.14.238/webmusic/server.php"));
    view->setUrl(QUrl("http://127.0.0.1/webmusic/server.php"));
    //view->setUrl(QUrl("http://music.163.com/outchain/player?type=2&id=516392300&auto=1&height=66&bg=e8e8e8"));
    //view->setUrl(QUrl("http://html5test.com/"));
    view->show();
}

void Widget::receiveText(const QString &text)
{
    qDebug() << "rw:" << text;
}
void Widget::receiveCmd(const QString &cmdText)
{
    qDebug() << "cmd:" << cmdText;
    if(cmdText == "dragStart"){
        titleDragStart();
        //emit label->mousePressEvent();
        //mMoveing = true;
        //记录下鼠标相对于窗口的位置
        //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
        //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
        //mMovePosition = pos();
    }
}

void Widget::on_close_clicked()
{
    this->close();
}
void Widget::on_maximized_clicked()
{
    //emit sendText("123");
    //this->showMaximized();rr
}
void Widget::on_minimized_clicked()
{
    this->showMinimized();
}

void Widget::titleDragStart()
{
    label = new QLabel();
    label->setMouseTracking(true);
    connect(label, SIGNAL(mousePressEvent), this, SLOT(labelMousePressEvent));
    connect(label, SIGNAL(mouseMoveEvent), this, SLOT(labelMouseMoveEvent));

    label->setMinimumHeight(50);
    label->setMaximumHeight(50);
    label->setStyleSheet("background-color:#000");
    cmdLayout = new QVBoxLayout;
    cmdLayout->setContentsMargins(25, 25, 25, 0);
    cmdLayout->addWidget(label);
    cmdLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(cmdLayout);
}
