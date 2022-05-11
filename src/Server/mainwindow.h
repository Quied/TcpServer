#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTcpServer>
#include <QVector>


class Server : public  QTcpServer{

    Q_OBJECT

public:

    Server();
    QTcpSocket *socket;


private:

    QVector<QTcpSocket*> Sockets;
    QByteArray Data;

    void SendToClient(QString str);

public slots:

    void IncomingConnection(qintptr SocketDescriptor);
    void SlotReadyRead();


};

#endif // MAINWINDOW_H
