#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initHome
 * Public method of MainWindow class which initialize the 'Home' page
 */
void MainWindow::initHome()
{
    qDebug()<<"void MainWindow::initHome()";

    updateListWidgetHomeTasks();
    //we fill the comboBox with all unfinished projects
    fillComboBoxHomeProject();
}

/**
 * @brief MainWindow::pageHome
 * Public method of MainWindow class which set the stackedWidgetApp current index on the 'Home' page
 */
void MainWindow::pageHome()
{
    qDebug()<<"void MainWindow::pageHome()";
    ui->stackedWidgetApp->setCurrentIndex(0);
}

/**
 * @brief MainWindow::on_pushButtonHomeNewProject_clicked
 * Private slots method of MainWindow class which shows the 'New Project' page
 */
void MainWindow::on_pushButtonHomeNewProject_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonNewProject_clicked()";
    //initialize the 'New Project' page
    initNewProject();
    //show the 'New Project' page
    pageNewProject();
}

/**
 * @brief MainWindow::fillComboBoxHomeProject
 * Public method of MainWindow class which list all unfinished projects
 */
void MainWindow::fillComboBoxHomeProject()
{
    qDebug()<<"void MainWindow::fillComboBoxHomeProject()";
    //clear old datas
    ui->comboBoxHomeProject->clear();

    QString reqSelectProject = "SELECT projectId, projectTitle FROM Project WHERE projectIsFinished = FALSE";
    qDebug()<<reqSelectProject;
    QSqlQuery resultSelectProject(reqSelectProject);

    //add all unfinished projects to the comboBox
    while(resultSelectProject.next()){
        QString projectTitle = resultSelectProject.value("projectTitle").toString();
        QString projectId = resultSelectProject.value("projectId").toString();
        ui->comboBoxHomeProject->addItem(projectTitle,projectId);
    }
}

/**
 * @brief MainWindow::on_pushButtonHomeNewTask_clicked
 * Private slots method of MainWindow class which shows the 'New Task' page
 */
void MainWindow::on_pushButtonHomeNewTask_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonHomeNewTask_clicked()";
    clearNewTask();
    pageNewTask();
}

/**
 * @brief MainWindow::updateListWidgetHomeTasks
 * Public method of MainWindow class which update the list widget in the 'Home' page
 */
void MainWindow::updateListWidgetHomeTasks()
{
    qDebug()<<"void MainWindow::updateListViewHomeTasks()";
    ui->listWidgetHomeTasks->clear();
    QString reqTaskList = "SELECT taskDescription FROM Task ORDER BY taskOrder DESC";
    qDebug()<<reqTaskList;
    QSqlQuery resultTaskList(reqTaskList);

    //while there are tasks we list them in the list widget
    while(resultTaskList.next()){
        ui->listWidgetHomeTasks->addItem(resultTaskList.value("taskDescription").toString());
    }

}
