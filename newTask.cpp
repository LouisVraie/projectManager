#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initNewTask
 * Public method of MainWindow class which initialize the 'New Task' page
 */
void MainWindow::initNewTask()
{
    qDebug()<<"void MainWindow::initNewTask()";
}

/**
 * @brief MainWindow::pageNewTask
 * Public method of MainWindow class which set the stackedWidgetApp current index on the 'New Task' page
 */
void MainWindow::pageNewTask()
{
    qDebug()<<"void MainWindow::pageNewTask()";
    ui->stackedWidgetApp->setCurrentIndex(2);
}

