#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initNewTask
 * Public method of MainWindow class which initialize the 'New Task' page
 */
void MainWindow::initNewTask()
{
    qDebug()<<"void MainWindow::initNewTask()";
    clearNewTask();
    connect(ui->plainTextEditNewTaskDescription,SIGNAL(textChanged()),this,SLOT(on_allInputsNewTask_textChanged()));
    connect(ui->spinBoxNewTaskDurationInHours,SIGNAL(valueChanged(int)),this,SLOT(on_allInputsNewTask_textChanged()));
    connect(ui->spinBoxNewTaskDurationInMinutes,SIGNAL(valueChanged(int)),this,SLOT(on_allInputsNewTask_textChanged()));
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
 * @brief MainWindow::clearNewTask
 * Public method of MainWindow class which clear all inputs for the 'New Task' page
 */
void MainWindow::clearNewTask()
{
    qDebug()<<"void MainWindow::clearNewTask()";
    //clear all inputs
    ui->plainTextEditNewTaskDescription->clear();
    ui->spinBoxNewTaskDurationInHours->setValue(0);
    ui->spinBoxNewTaskDurationInMinutes->setValue(0);

    //disable add task button
    ui->pushButtonNewTaskAddTask->setEnabled(false);
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

/**
 * @brief MainWindow::on_allInputsNewTask_textChanged
 * Private slots method of MainWindow class which allow us to enable or disable the 'Add Task' button
 */
void MainWindow::on_allInputsNewTask_textChanged()
{
    qDebug()<<"void MainWindow::on_allInputsNewTask_textChanged()";
    bool description = ui->plainTextEditNewTaskDescription->toPlainText().length() > 10;
    bool duration = ui->spinBoxNewTaskDurationInHours->value() + ui->spinBoxNewTaskDurationInMinutes->value() != 0;
    if (ui->plainTextEditNewTaskDescription->toPlainText().length() > 300) {
        ui->plainTextEditNewTaskDescription->textCursor().deletePreviousChar();
    }
    qDebug()<<description<<duration;
    if(description && duration){
        ui->pushButtonNewTaskAddTask->setEnabled(true);
    } else {
        ui->pushButtonNewTaskAddTask->setEnabled(false);
    }
}
