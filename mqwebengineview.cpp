#include "mqwebengineview.h"

mQWebEngineView::mQWebEngineView()
{

}
//重写鼠标移动事件
void mQWebEngineView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << 1;

    return QWidget::mouseMoveEvent(event);
}
