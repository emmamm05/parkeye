#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "constants.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fileBttnParking_clicked();
    void on_fileBttnReference_clicked();

    void on_bttnStep_clicked();

    void on_bttnRestart_clicked();

private:
    Ui::MainWindow *ui;
    void showErrorMessage();
};

#endif // MAINWINDOW_H
