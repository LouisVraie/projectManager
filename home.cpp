#include "mainwindow.h"
#include "ui_mainwindow.h"


/**
 * @brief MainWindow::on_pushButtonHomeNewProject_clicked
 * Private slots method of the MainWindow class which shows the 'New Project' page
 */
void MainWindow::on_pushButtonHomeNewProject_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonNewProject_clicked()";
    //initialize the 'New Project' page
    initNewProject();
    //show the 'New Project' page
    ui->stackedWidgetApp->setCurrentIndex(1);
}
