#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    queryModel = new QSqlQueryModel(this);

    if(isDatabaseEmpty()){
        createTables();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::isDatabaseEmpty
 * Public MainWindow class method which return if the database contains tables or not
 * @return bool true if empty
 */
bool MainWindow::isDatabaseEmpty()
{
    qDebug()<<"bool MainWindow::isDatabaseEmpty()";
    return QSqlDatabase::database().tables().size() == 0;
}

/**
 * @brief MainWindow::createTables
 * Public MainWindow class method which create tables in the database
 */
void MainWindow::createTables()
{
    qDebug()<<"void MainWindow::createTables()";

    //creation of Project table
    QString project = "CREATE TABLE `Project`(`projectId` INTEGER NOT NULL,`projectStartDate` DATE,"
                      "`projectEndDate` DATE,`projectTitle` VARCHAR(75),`projectDescription` VARCHAR(300),"
                      "primary key(`projectId`));";
    qDebug()<<project;
    QSqlQuery createTableProject(project);

    //creation of Task table
    QString task = "CREATE TABLE `Task`(`taskId` INTEGER NOT NULL,`taskDescription` VARCHAR(300),"
                   "`taskDurationInHours` INTEGER,`taskOrder` INTEGER,`taskDaySpent` INTEGER DEFAULT 0,"
                   "`taskTimeSpent` TIME,`taskIsFinished` BOOL DEFAULT 0,`taskFinishNote` VARCHAR(100),"
                   "`projectId` INTEGER NOT NULL, foreign key (`projectId`) references Project(`projectId`),"
                   "primary key(`taskId`));";
    qDebug()<<task;
    QSqlQuery createTableTask(task);
}

