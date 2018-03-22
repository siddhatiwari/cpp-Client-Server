#include <QCoreApplication>
#include "myserver.h"
#include "mythread.h"

std::thread::id main_thread_id;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer server;
    server.startServer();

    return a.exec();
}
