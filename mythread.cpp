#include "mythread.h"
#include <QApplication>

MyThread::MyThread(int ID, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
}

void MyThread::run() {

    // Prints out socket ID
    qDebug() << socketDescriptor << "Starting thread";

    // Checks for error while setting socket
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    // Data has arrived, and slot is executed immediately after b/c DirectConnection
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);

    // Socket has disconnected
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    qDebug() << socketDescriptor << "Client thread";

    exec();
}

void MyThread::readyRead() {
    QByteArray Data = socket->readAll();

    qDebug() << socketDescriptor << "Data in: " << Data;

    // If Data is "quit\r\n", application quits
    if (Data == "quit\r\n") {
        QApplication::quit();
    }

    socket->write(Data);
}

void MyThread::disconnected() {

    // Socket connection ended
    qDebug() << socketDescriptor << "Disconnected";

    // Close socket if thread disconnected
    socket->close();
    exit(0);
}
