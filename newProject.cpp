#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::initNewProject
 * Public method of MainWindow class which initialize the 'New Project' page
 */
void MainWindow::initNewProject()
{
    qDebug()<<"void MainWindow::initNewProject()";
    clearNewProject();
    connect(ui->lineEditNewProjectTitle,SIGNAL(textChanged(QString)),this,SLOT(on_allInputs_textChanged()));
    connect(ui->dateEditNewProjectStartDate,SIGNAL(dateChanged(QDate)),this,SLOT(on_allInputs_textChanged()));
    connect(ui->dateEditNewProjectEndDate,SIGNAL(dateChanged(QDate)),this,SLOT(on_allInputs_textChanged()));
    connect(ui->plainTextEditNewProjectDescription,SIGNAL(textChanged()),this,SLOT(on_allInputs_textChanged()));
}

/**
 * @brief MainWindow::clearNewProject
 * Public method of MainWindow class which clear all inputs for the 'New Project' page
 */
void MainWindow::clearNewProject()
{
    //clear all inputs
    ui->lineEditNewProjectTitle->clear();
    ui->plainTextEditNewProjectDescription->clear();

    //by default we set the current day for the start date and +1 day for the end date
    QDate today = QDate::currentDate();
    ui->dateEditNewProjectStartDate->setDate(today);
    ui->dateEditNewProjectEndDate->setDate(today.addDays(1));

    //disable create project button
    ui->pushButtonNewProjectCreate->setEnabled(false);
}

/**
 * @brief MainWindow::on_pushButtonNewProjectCancel_clicked
 * Private slots method of MainWindow class which shows back the 'Home' window
 */
void MainWindow::on_pushButtonNewProjectCancel_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonNewProjectCancel_clicked()";
    ui->stackedWidgetApp->setCurrentIndex(0);
}

/**
 * @brief MainWindow::on_allInputs_textChanged
 * Private slots method of MainWindow class which allow us to enable or disable the 'Create Project' button
 */
void MainWindow::on_allInputs_textChanged()
{
    qDebug()<<"void MainWindow::on_allInputs_textChanged()";
    bool title = ui->lineEditNewProjectTitle->text().length() > 3 && ui->lineEditNewProjectTitle->text().length() <= 75;
    bool date = ui->dateEditNewProjectStartDate->date().daysTo(ui->dateEditNewProjectEndDate->date()) > -1;
    bool description = ui->plainTextEditNewProjectDescription->toPlainText().length() > 10;
    if (ui->plainTextEditNewProjectDescription->toPlainText().length() > 300) {
        ui->plainTextEditNewProjectDescription->textCursor().deletePreviousChar();
    }
    if(title && date && description){
        ui->pushButtonNewProjectCreate->setEnabled(true);
    } else {
        ui->pushButtonNewProjectCreate->setEnabled(false);
    }
}

/**
 * @brief MainWindow::on_pushButtonNewProjectCreate_clicked
 * Private slots method of MainWindow class which create a new project
 */
void MainWindow::on_pushButtonNewProjectCreate_clicked()
{
    qDebug()<<"void MainWindow::on_pushButtonNewProjectCreate_clicked()";
    //get all datas
    QString table = "Project";
    QString column = "projectId";
    QString projectId = setNextId(table,column);
    QString title = escapeString(ui->lineEditNewProjectTitle->text());
    QString startDate = ui->dateEditNewProjectStartDate->date().toString("yyyy-MM-dd");
    QString endDate = ui->dateEditNewProjectEndDate->date().toString("yyyy-MM-dd");
    QString description = escapeString(ui->plainTextEditNewProjectDescription->toPlainText());

    //insert request
    QString reqInsertProject = "INSERT INTO Project (projectId,projectStartDate,projectEndDate,projectTitle,projectDescription) "
                               "VALUES ("+projectId+",'"+startDate+"','"+endDate+"','"+title+"','"+description+"')";
    qDebug()<<reqInsertProject;
    QSqlQuery resultInsertProject(reqInsertProject);

    //if the request worked
    if(resultInsertProject.numRowsAffected() != -1){
        ui->comboBoxHomeProject->addItem(title,projectId);
        ui->stackedWidgetApp->setCurrentIndex(0);
    }
}
