#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{

    socket->connectToHost("127.0.0.1", 2323);

}

void MainWindow::SendToServer(QString str)
{

    Data.clear();
    QDataStream out (&Data, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_5_15);
    out >> str;
    socket->write(Data);
    ui->lineEdit->setText("");

}



void MainWindow::slotReadyRead()
{

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    if(in.status() == QDataStream::Ok){
        QString text;
        in >> text;
        ui->textBrowser->append(text);
    }
    else{ ui->textBrowser->append("Error data"); }

}


void MainWindow::on_pushButton_clicked()
{
    SendToServer(ui->lineEdit->text());
}


void MainWindow::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}

