#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QObject>
#include <QWebChannel>
#include <QWebEngineView>
#include <QWebSocketServer>

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

signals:


public slots:
    void sendText(const QString &text);

private:
    Ui::Widget *ui;
    QWebEngineView *view;

};

#endif // WIDGET_H
