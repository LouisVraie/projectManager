#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initHome
 * Public method of MainWindow class which initialize the 'Home' page
 */
void MainWindow::initHome()
{
    qDebug()<<"void MainWindow::initHome()";
    //we fill the comboBox with all unfinished projects
    fillComboBoxHomeProject();
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
    ui->stackedWidgetApp->setCurrentIndex(1);
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
