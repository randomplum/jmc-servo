#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QSerialPort>
#include "jmc_driver.h"

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
    void on_connect_button_clicked();

    void on_readall_button_clicked();

    void on_live_button_clicked();

private:
    Ui::MainWindow *ui;
    jmc_driver *servo = NULL;
    QTextStream out;
    QSerialPort *serial_port = NULL;
};

#endif // MAINWINDOW_H
