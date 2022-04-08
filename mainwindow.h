#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QInputDialog>
#include <QPlainTextEdit>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /* mainwindow.cpp */
    bool isDatabaseEmpty();
    void createTables();
    void dropTables();
    QString escapeString(QString myQString);
    QString setNextId(QString table, QString column,int iteration = 1);

    /* home.cpp */
    void initHome();
    void pageHome();
    void fillComboBoxHomeProject();

    /* newProject.cpp */
    void initNewProject();
    void pageNewProject();
    void clearNewProject();

    /* newTask.cpp */
    void initNewTask();
    void pageNewTask();
    void clearNewTask();

private slots:

    /* home.cpp */
    void on_pushButtonHomeNewProject_clicked();
    void on_pushButtonHomeNewTask_clicked();

    /* newProject.cpp */
    void on_pushButtonNewProjectCancel_clicked();
    void on_allInputsNewProject_textChanged();
    void on_pushButtonNewProjectCreate_clicked();

    /* newTask.cpp */
    void on_pushButtonNewTaskCancel_clicked();
    void on_allInputsNewTask_textChanged();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *queryModel;

};
#endif // MAINWINDOW_H
