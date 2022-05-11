#include "mainwindow.h"
#include <QDebug>


Server::Server(){

    if(this->listen(QHostAddress::Any, 2323)){ qDebug() << "Server is starting"; }
    else { qDebug() << "Erorr"; }

}


void Server::IncomingConnection(qintptr SocketDescriptor){

    socket = new QTcpSocket;
    socket->setSocketDescriptor(SocketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::SlotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug() << "Connect " << SocketDescriptor;
}

void Server::SlotReadyRead(){

    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);

    // Take text
    if(in.status() == QDataStream::Ok){
        QString text;
        in >> text;
        SendToClient(text);
    }

}

void Server::SendToClient(QString str){

    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_15);
    out << str;

   // socket->write(Data);
    for(int i = 0; i < Sockets.size(); i++){
       Sockets[i]->write(Data);
    }

}


