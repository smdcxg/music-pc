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
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>

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
    void receiveCmd(const QString &cmdText);

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *event);
    virtual void labelMousePressEvent(QMouseEvent *event);
    virtual void labelMouseMoveEvent(QMouseEvent *event);
    virtual void labelMouseReleaseEvent(QMouseEvent *event);

signals:
    void sendText(const QString &text);

private slots:
    void on_close_clicked();
    void on_maximized_clicked();
    void on_minimized_clicked();

private:
    void initialization();
    void titleDragStart();
    Ui::Widget *ui;
    QWebEngineView *view;
    bool mMoveing;
    QPoint mMovePosition;
    QLabel *label;
    QVBoxLayout *cmdLayout;

};

#endif // WIDGET_H
