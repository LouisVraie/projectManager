#include "mainwindow.h"
#include "ui_mainwindow.h"



void MainWindow::on_pushButtonNewTaskAddTask_clicked()
{
    QString text = QInputDialog::getText(this, tr("Add a task"),
                                             tr("User name:"), QLineEdit::Normal,"");
}
