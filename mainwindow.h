#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QInputDialog>
#include <QPlainTextEdit>
#include <QString>
#include <QMessageBox>
#include <QTimer>

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
    void updateTableViewHomeTasks();
    void clearHome();

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
    void on_comboBoxHomeProject_currentIndexChanged(int index);
    void on_tableViewHomeTasks_clicked(const QModelIndex &index);
    void on_tableViewHomeTasks_rowSelected();
    void on_pushButtonHomeDeleteTask_clicked();
    void on_pushButtonHomeOrderUp_clicked();
    void on_pushButtonHomeOrderDown_clicked();
    void on_comboBoxHomeProject_checkContent();
    void on_progressBarHomeTaskTimer_update();
    void on_pushButtonHomeSessionStartRestart_clicked();
    void toggleHomeInputsWhenStartRestart(bool isDisable);

    /* newProject.cpp */
    void on_pushButtonNewProjectCancel_clicked();
    void on_allInputsNewProject_textChanged();
    void on_pushButtonNewProjectCreate_clicked();

    /* newTask.cpp */
    void on_pushButtonNewTaskCancel_clicked();
    void on_allInputsNewTask_textChanged();
    void on_pushButtonNewTaskAddTask_clicked();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *queryModel;
    QSqlTableModel *tableModel;
    QModelIndex selectedTask;
    QTimer *sessionTimer;
    bool sessionIsActive;
};
#endif // MAINWINDOW_H
