#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QObject>
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebSocketServer>
#include <QRect>

#include <QPainterPath>
#include <QPainter>
#include <QtMath>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void receiveText(const QString &text);
    void receiveSize(const qint8 offsetX, const qint8 offsetY);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

signals:


public slots:
    void sendText(const QString &text);

private:
    Ui::Widget *ui;
    QWebEngineView *view;

};

#endif // WIDGET_H
