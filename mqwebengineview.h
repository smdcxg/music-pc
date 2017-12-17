#ifndef MQWEBENGINEVIEW_H
#define MQWEBENGINEVIEW_H

#include <QWebEngineView>

class mQWebEngineView : public QWebEngineView
{
public:
    mQWebEngineView();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // MQWEBENGINEVIEW_H
