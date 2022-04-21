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

    ui->tableViewHomeTasks->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    updateTableViewHomeTasks();
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
 * @brief MainWindow::updateTableViewHomeTasks
 * Public method of MainWindow class which update the table view in the 'Home' page
 */
void MainWindow::updateTableViewHomeTasks()
{
    qDebug()<<"void MainWindow::updateTableViewHomeTasks()";
    //if a project is selected
    if (ui->comboBoxHomeProject->currentData().isValid()){
        tableModel->setTable("Task");
        tableModel->setFilter("projectId ="+ui->comboBoxHomeProject->currentData().toString());
        tableModel->setSort(4,Qt::DescendingOrder);
    } else {
        clearHome();
    }
    tableModel->select();

    //define the tableView model we want to show
    ui->tableViewHomeTasks->setModel(tableModel);
    ui->tableViewHomeTasks->show();
    //if there are columns
    if(tableModel->columnCount()>0){
        //we hide all column by default
        for(int columnIndex = 0;columnIndex<tableModel->columnCount();columnIndex++){
            ui->tableViewHomeTasks->hideColumn(columnIndex);
        }
        //we show the only one we want
        ui->tableViewHomeTasks->showColumn(1);
    }
}

/**
 * @brief MainWindow::clearHome
 */
void MainWindow::clearHome()
{
    qDebug()<<"void MainWindow::clearHome()";
    //we clear tableModel
    tableModel->clear();

    //we clear all label fields
    ui->labelHomeTaskDescription->clear();
    ui->labelHomeTaskDuration->setText("00h00");

    //we clear the tableViewHomeTasks selection
    ui->tableViewHomeTasks->clearSelection();
}

/**
 * @brief MainWindow::on_comboBoxHomeProject_currentIndexChanged
 * @param index: int Current index
 */
void MainWindow::on_comboBoxHomeProject_currentIndexChanged(int index)
{
    qDebug()<<"void MainWindow::on_comboBoxHomeProject_currentIndexChanged(int index)"<<index;
    clearHome();
    updateTableViewHomeTasks();
}

/**
 * @brief MainWindow::on_tableViewHomeTasks_clicked
 * Private slots method of MainWindow class which update the ui when a row is clicked
 * @param index: QModelIndex&
 */
void MainWindow::on_tableViewHomeTasks_clicked(const QModelIndex &index)
{
    qDebug()<<"void MainWindow::on_tableViewHomeTasks_clicked(const QModelIndex &index)";
    //we set the task description in the label
    ui->labelHomeTaskDescription->setText(index.siblingAtColumn(1).data().toString());
    QString durationInHours = index.siblingAtColumn(2).data().toString();
    durationInHours = (durationInHours == "0")?"00":durationInHours;
    QString durationInMinutes = index.siblingAtColumn(3).data().toString();
    durationInMinutes = (durationInMinutes == "0")?"00":durationInMinutes;
    //we set the task duration in the label
    ui->labelHomeTaskDuration->setText(durationInHours+"h"+durationInMinutes);
}

