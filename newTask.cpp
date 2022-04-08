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

/**
 * @brief MainWindow::on_pushButtonNewTaskCancel_clicked
 * Private slots method of MainWindow class which shows back the 'Home' window
 */
void MainWindow::on_pushButtonNewTaskCancel_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonNewTaskCancel_clicked()";
    pageHome();
}
