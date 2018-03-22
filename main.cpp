#include <QCoreApplication>
#include "myserver.h"
#include "mythread.h"

std::thread::id main_thread_id;

// To properly end server, press ctrl+c in server window or enter "quit" client-side
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyServer server;
    server.startServer();

    return a.exec();
}
