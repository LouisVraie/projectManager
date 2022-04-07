#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initNewProject
 * Public method of the MainWindow class which initialize the 'New Project' page
 */
void MainWindow::initNewProject()
{
    qDebug()<<"void MainWindow::initNewProject()";

    //clear all inputs
    ui->lineEditNewProjectTitle->clear();
    ui->plainTextEditNewProjectDescription->clear();

    //by default we set the current day for the start date and +1 day for the end date
    QDate today = QDate::currentDate();
    ui->dateEditNewProjectStartDate->setDate(today);
    ui->dateEditNewProjectEndDate->setDate(today.addDays(1));
}

/**
 * @brief MainWindow::on_pushButtonNewProjectCancel_clicked
 * Private slots method of the MainWindow class which shows back the 'Home' window
 */
void MainWindow::on_pushButtonNewProjectCancel_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonNewProjectCancel_clicked()";
    ui->stackedWidgetApp->setCurrentIndex(0);
}
