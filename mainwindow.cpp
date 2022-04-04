#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    queryModel = new QSqlQueryModel(this);

    dropTables();

    //if the database is empty
    if(isDatabaseEmpty()){
        //creation of database's tables
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
    QString project = "CREATE TABLE `Project`(`projectId` INTEGER NOT NULL,`projectStartDate` DATE,`projectEndDate` DATE,"
                      "`projectTitle` VARCHAR(75),`projectDescription` VARCHAR(300),`projectRealEndDate` DATE,"
                      "`projectIsFinished` BOOL DEFAULT 0,primary key(`projectId`));";
    qDebug()<<project;
    QSqlQuery createTableProject(project);

    //creation of Task table
    QString task = "CREATE TABLE `Task`(`taskId` INTEGER NOT NULL,`taskDescription` VARCHAR(300),"
                   "`taskDurationInHours` INTEGER DEFAULT 0,`taskDurationInMinutes` INTEGER DEFAULT 0,"
                   "`taskOrder` INTEGER DEFAULT 0,`taskIsFinished` BOOL DEFAULT 0,`taskFinishNote` VARCHAR(100),"
                   "`projectId` INTEGER NOT NULL, foreign key (`projectId`) references Project(`projectId`),primary key(`taskId`));";
    qDebug()<<task;
    QSqlQuery createTableTask(task);

    //creation of Session table
    QString session = "CREATE TABLE `Session`(`sessionId` INTEGER NOT NULL,`sessionStartDate` DATETIME,`sessionEndDate` DATETIME,"
                      "`sessionDescription` VARCHAR(300),`taskId` INTEGER NOT NULL, "
                      "foreign key (`taskId`) references Task(`taskId`),primary key(`sessionId`));";
    qDebug()<<session;
    QSqlQuery createTableSession(session);
}

/**
 * @brief MainWindow::dropTables
 * Public MainWindow class method which drop tables in the database
 */
void MainWindow::dropTables()
{
    qDebug()<<"void MainWindow::dropTables()";

    //drop of the Session table
    QString session = "DROP TABLE `Session`;";
    qDebug()<<session;
    QSqlQuery dropTableSession(session);

    //drop of the Task table
    QString task = "DROP TABLE `Task`;";
    qDebug()<<task;
    QSqlQuery dropTableTask(task);

    //drop of the Project table
    QString project = "DROP TABLE `Project`;";
    qDebug()<<project;
    QSqlQuery dropTableProject(project);
}

void MainWindow::on_pushButtonAddTask_clicked()
{
    QString text = QInputDialog::getText(this, tr("Add a task"),
                                             tr("User name:"), QLineEdit::Normal,"");
}

