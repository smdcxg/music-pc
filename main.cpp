#include "widget.h"
#include "core.h"
#include "./shared/websocketclientwrapper.h"
#include "./shared/websockettransport.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    // setup the QWebSocketServer
    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"), QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    Core core(&w);
    channel.registerObject(QStringLiteral("core"), &core);

    /*QWebEngineView *view = new QWebEngineView(this);
    //QWebEngineView view(&w);
    view.setUrl(QUrl("http://47.104.14.238/webmusic1/server.php"));
    //view.setUrl(QUrl("http://127.0.0.1/music/server.php"));
    view.show();*/

    return a.exec();
}
