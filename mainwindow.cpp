#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::isDatabaseEmpty
 * Public MainWindow class method which return if the database contains tables or not
 * @return bool true if empty
 */
bool MainWindow::isDatabaseEmpty()
{
    qDebug()<<"bool MainWindow::isDatabaseEmpty()";
    return QSqlDatabase::database().tables().size() == 0;
}

/**
 * @brief MainWindow::createTables
 * Public MainWindow class method which create tables in the database
 */
void MainWindow::createTables()
{
    qDebug()<<"void MainWindow::createTables()";
}

