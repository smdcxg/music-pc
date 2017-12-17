#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QObject>
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebSocketServer>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QRect>

#include <QPainterPath>
#include <QPainter>
#include <QtMath>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QPoint>
#include <QMouseEvent>
#include <QLibrary>

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

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

signals:
    void sendText(const QString &text);

private slots:
    void on_close_clicked();
    void on_maximized_clicked();
    void on_minimized_clicked();
    void changeSearch(const QString &text);

private:
    void initialization();
    Ui::Widget *ui;
    QWebEngineView *view;
    bool mMoveing;
    QPoint mMovePosition;

};

#endif // WIDGET_H
