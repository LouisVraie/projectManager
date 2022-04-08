#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * Constructor of MainWindow class which create our app window
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    queryModel = new QSqlQueryModel(this);

    //we first show the 'Home' page
    ui->stackedWidgetApp->setCurrentIndex(0);

    //dropTables();

    //if the database is empty
    if(isDatabaseEmpty()){
        //creation of database's tables
        createTables();
    }
    /* home.cpp */
    initHome();

    /* newProject.cpp */
    initNewProject();

    /* newTask.cpp */
}

/**
 * @brief MainWindow::~MainWindow
 * Destructor of MainWindow class
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::isDatabaseEmpty
 * Public method of MainWindow class which return if the database contains tables or not
 * @return bool true if empty
 */
bool MainWindow::isDatabaseEmpty()
{
    qDebug()<<"bool MainWindow::isDatabaseEmpty()";
    return QSqlDatabase::database().tables().size() == 0;
}

/**
 * @brief MainWindow::createTables
 * Public method of MainWindow class which create tables in the database
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
 * Public method of MainWindow class which drop tables in the database
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

/**
 * @brief MainWindow::escapeString
 * Public static method of MainWindow class which allow us to escape some characters
 * @param myQString: QString
 * @return QString
 */
QString MainWindow::escapeString(QString myQString)
{
    //replace ';' by an empty string
    myQString = myQString.replace(";","");
    //double simples quotes
    myQString = myQString.replace("'","''");
    return myQString;
}

/**
 * @brief MainWindow::setNextId
 * Public method of MainWindow class which set the next id for the current column in the current table
 * @param table: QString The table name
 * @param column: QString The column name | Default value : "id"
 * @param interation: int The iteration value | Default value : 1
 * @return QString The new next id
 */
QString MainWindow::setNextId(QString table, QString column = "id",int iteration)
{
    qDebug()<<"int MainWindow::setNextId(QString table, QString column,int iteration)";
    QString nextId = "";

    QString reqNextId = "SELECT IFNULL(MAX("+column+")+"+QString::number(iteration)+",1) FROM "+table;
    qDebug()<<reqNextId;
    QSqlQuery resultNextId(reqNextId);

    //if the request worked
    if(resultNextId.numRowsAffected() != -1){
        resultNextId.first();
        nextId = resultNextId.value(0).toString();
    }
    return nextId;
}







