#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./projectManager.sqlite");
        bool ok = db.open();
    if(ok){
        qDebug()<<"Database Connected";
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        qDebug()<<"Error Database isn't connected";
        return 0;
    }
}
