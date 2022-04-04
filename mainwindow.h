#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QInputDialog>

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

    bool isDatabaseEmpty();
    void createTables();
    void dropTables();

private slots:
    void on_pushButtonAddTask_clicked();

private:
    Ui::MainWindow *ui;

    QSqlQueryModel *queryModel;

};
#endif // MAINWINDOW_H
