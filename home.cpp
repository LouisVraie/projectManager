#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initHome
 * Public method of MainWindow class which initialize the 'Home' page
 */
void MainWindow::initHome()
{
    qDebug()<<"void MainWindow::initHome()";

    clearHome();
    connect(ui->comboBoxHomeProject,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBoxHomeProject_checkContent()));
    connect(ui->tableViewHomeTasks,SIGNAL(clicked(QModelIndex)),this,SLOT(on_tableViewHomeTasks_rowSelected()));

    sessionTimer = new QTimer();
    connect(sessionTimer,SIGNAL(timeout()),this,SLOT(on_progressBarHomeTaskTimer_update()));
    sessionIsActive = false;

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
    //if the comboBox is valid
    if(ui->comboBoxHomeProject->currentData().isValid()){
        ui->pushButtonHomeNewTask->setDisabled(false);
        ui->checkBoxHomeProjectFinished->setDisabled(false);
    } else {
        ui->pushButtonHomeNewTask->setDisabled(true);
        ui->checkBoxHomeProjectFinished->setDisabled(true);
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
        tableModel->setSort(4,Qt::AscendingOrder);
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
 * Public method of MainWindow class which clear inputs in the 'Home' page
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

    //we disable buttons
    ui->pushButtonHomeDeleteTask->setDisabled(true);
    ui->pushButtonHomeSessionStartRestart->setDisabled(true);
    ui->pushButtonHomeOrderUp->setDisabled(true);
    ui->pushButtonHomeOrderDown->setDisabled(true);
    ui->checkBoxHomeTaskFinished->setDisabled(true);
}

/**
 * @brief MainWindow::on_comboBoxHomeProject_currentIndexChanged
 * Private slots method of MainWindow class that changes the data displayed when changing projects
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
    selectedTask = index;
    //we set the task description in the label
    ui->labelHomeTaskDescription->setText(index.siblingAtColumn(1).data().toString());
    QString durationInHours = index.siblingAtColumn(2).data().toString();
    durationInHours = (durationInHours.size() == 1)?"0"+durationInHours:durationInHours;
    QString durationInMinutes = index.siblingAtColumn(3).data().toString();
    durationInMinutes = (durationInMinutes.size() == 1)?"0"+durationInMinutes:durationInMinutes;
    //we set the task duration in the label
    ui->labelHomeTaskDuration->setText(durationInHours+"h"+durationInMinutes);
}

/**
 * @brief MainWindow::on_tableViewHomeTasks_rowSelected
 * Private slots method of MainWindow class which toggle buttons on the 'Home' page
 */
void MainWindow::on_tableViewHomeTasks_rowSelected()
{
    qDebug()<<"void MainWindow::on_tableViewHomeTasks_rowSelected()";
    //if a row is selected in the tableViewHomeTasks
    if(ui->tableViewHomeTasks->selectionModel()->hasSelection()){
        //we enable buttons
        ui->pushButtonHomeDeleteTask->setDisabled(false);
        ui->pushButtonHomeSessionStartRestart->setDisabled(false);
        ui->pushButtonHomeOrderUp->setDisabled(false);
        ui->pushButtonHomeOrderDown->setDisabled(false);
        ui->checkBoxHomeTaskFinished->setDisabled(false);
    } else {
        //we disable buttons
        ui->pushButtonHomeDeleteTask->setDisabled(true);
        ui->pushButtonHomeSessionStartRestart->setDisabled(true);
        ui->pushButtonHomeOrderUp->setDisabled(true);
        ui->pushButtonHomeOrderDown->setDisabled(true);
        ui->checkBoxHomeTaskFinished->setDisabled(true);
    }
}

/**
 * @brief MainWindow::on_pushButtonHomeDeleteTask_clicked
 * Private slots method of MainWindow class which delete the selected task from the current project
 */
void MainWindow::on_pushButtonHomeDeleteTask_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonHomeDeleteTask_clicked()";
    //if a row is selected in the tableViewHomeTasks
    if(ui->tableViewHomeTasks->selectionModel()->hasSelection()){
        QString task = selectedTask.siblingAtColumn(1).data().toString();
        task = (task.size() > 15 )? task.sliced(0,15)+"...":task;
        if(QMessageBox::warning(this,this->windowTitle()+" - Delete Task","Do you really want to delete '"+task+"' task ?",
                                QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
        {
            //we remove the task
            tableModel->removeRow(ui->tableViewHomeTasks->currentIndex().row());
            tableModel->select();
            clearHome();
            updateTableViewHomeTasks();
        }
    }
}

/**
 * @brief MainWindow::on_pushButtonHomeOrderUp_clicked
 * Private slots method of MainWindow class which put the selected task higher in the Project task order
 */
void MainWindow::on_pushButtonHomeOrderUp_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonHomeOrderUp_clicked()";
    //if the task isn't the top one
    if(selectedTask.row() != 0 && ui->tableViewHomeTasks->selectionModel()->hasSelection()){
        int selectedRow = selectedTask.row();
        QString upperTaskOrder = selectedTask.sibling(selectedRow-1,4).data().toString();;
        QString selectedTaskOrder = selectedTask.siblingAtColumn(4).data().toString();
        //we change the taskOrder
        QString reqUpdateSelectedTask = "UPDATE Task SET taskOrder="+upperTaskOrder+" WHERE taskId="+selectedTask.siblingAtColumn(0).data().toString();
        queryModel->setQuery(reqUpdateSelectedTask);
        QString reqUpdateUpperTask = "UPDATE Task SET taskOrder="+selectedTaskOrder+" WHERE taskId="+selectedTask.sibling(selectedRow-1,0).data().toString();
        queryModel->setQuery(reqUpdateUpperTask);
        //we update the tableView
        updateTableViewHomeTasks();
        on_tableViewHomeTasks_rowSelected();
    }
}

/**
 * @brief MainWindow::on_pushButtonHomeOrderDown_clicked
 * Private slots method of MainWindow class which put the selected task lower in the Project task order
 */
void MainWindow::on_pushButtonHomeOrderDown_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonHomeOrderDown_clicked()";
    //if the task isn't the bottom one
    if(selectedTask.row() != ui->tableViewHomeTasks->model()->rowCount() && ui->tableViewHomeTasks->selectionModel()->hasSelection()){
        int selectedRow = selectedTask.row();
        QString lowerTaskOrder = selectedTask.sibling(selectedRow+1,4).data().toString();;
        QString selectedTaskOrder = selectedTask.siblingAtColumn(4).data().toString();
        //we change the taskOrder
        QString reqUpdateSelectedTask = "UPDATE Task SET taskOrder="+lowerTaskOrder+" WHERE taskId="+selectedTask.siblingAtColumn(0).data().toString();
        queryModel->setQuery(reqUpdateSelectedTask);
        QString reqUpdateLowerUpperTask = "UPDATE Task SET taskOrder="+selectedTaskOrder+" WHERE taskId="+selectedTask.sibling(selectedRow+1,0).data().toString();
        queryModel->setQuery(reqUpdateLowerUpperTask);
        //we update the tableView
        updateTableViewHomeTasks();
        on_tableViewHomeTasks_rowSelected();
    }
}

/**
 * @brief MainWindow::on_comboBoxHomeProject_checkContent
 * Private slots method of MainWindow class which toggle some inputs link to the current project
 */
void MainWindow::on_comboBoxHomeProject_checkContent()
{
    qDebug()<<"void MainWindow::on_comboBoxHomeProject_checkContent()";
    if(ui->comboBoxHomeProject->currentData().isValid()){
        ui->pushButtonHomeNewTask->setDisabled(false);
        ui->checkBoxHomeProjectFinished->setDisabled(false);
    } else {
        ui->pushButtonHomeNewTask->setDisabled(true);
        ui->checkBoxHomeProjectFinished->setDisabled(true);
    }
}

/**
 * @brief MainWindow::on_progressBarHomeTaskTimer_update
 * Private slots method of MainWindow class which update the progressBarHomeTaskTimer value
 */
void MainWindow::on_progressBarHomeTaskTimer_update()
{
    qDebug()<<"void MainWindow::on_progressBarHomeTaskTimer_update()";
    int value = ui->progressBarHomeTaskTimer->value();
    if(value != 100){
        ui->progressBarHomeTaskTimer->setValue(value+1);
    } else {
        ui->progressBarHomeTaskTimer->setStyleSheet("color: red;");
    }
}

/**
 * @brief MainWindow::on_pushButtonHomeSessionStartRestart_clicked
 * Private slots method of MainWindow class which start or restart the timer for the selected task
 */
void MainWindow::on_pushButtonHomeSessionStartRestart_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonHomeSessionStartRestart_clicked()";
    if(!sessionIsActive){
        sessionTimer->start(100);
        ui->pushButtonHomeSessionStartRestart->setText("Stop");
        toggleHomeInputsWhenStartRestart(true);
    } else {
        sessionTimer->stop();
        ui->pushButtonHomeSessionStartRestart->setText("Start / Restart");
        toggleHomeInputsWhenStartRestart(false);
    }
    sessionIsActive = !sessionIsActive;
}

/**
 * @brief MainWindow::toggleHomeInputsWhenStartRestart
 * Private slots method of MainWindow class which toggle all inputs of the 'Home' except pushButtonHomeSessionStartRestart
 * @param isDisable: bool
 */
void MainWindow::toggleHomeInputsWhenStartRestart(bool isDisable)
{
    qDebug()<<"void MainWindow::toggleHomeInputsWhenStartRestart(bool isDisable)";
    ui->comboBoxHomeProject->setDisabled(isDisable);
    ui->pushButtonHomeNewProject->setDisabled(isDisable);
    ui->tableViewHomeTasks->setDisabled(isDisable);
    ui->pushButtonHomeNewTask->setDisabled(isDisable);
    ui->pushButtonHomeDeleteTask->setDisabled(isDisable);
    ui->pushButtonHomeOrderUp->setDisabled(isDisable);
    ui->pushButtonHomeOrderDown->setDisabled(isDisable);
    ui->checkBoxHomeTaskFinished->setDisabled(isDisable);
    ui->checkBoxHomeProjectFinished->setDisabled(isDisable);
}
