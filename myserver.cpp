#include "myserver.h"
#include <QApplication>

MyServer::MyServer(QObject *parent) : QTcpServer(parent)
{

}

void MyServer::startServer() {

    // If connection to host address is successful or not
    if (!this->listen(QHostAddress::Any, 1124)) {
        qDebug() << "Could not start server";
    } else {
        qDebug() << "Listening...";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor) {
    qDebug() << socketDescriptor << "Connecting...";

    // Creates a new thread for the incoming connection
    MyThread *thread = new MyThread(socketDescriptor, this);

    // Thread responds to signal that its tasks are finished, then deletes itself
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    // Thread responds to application signal to quit by ending the thread
    connect(QApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));
    thread->start();
}

MyServer::~MyServer() {
    this->close();
}
