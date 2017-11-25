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

    void on_pp_spin_editingFinished();

    void on_live_box_clicked();

    void on_pd_spin_editingFinished();

    void on_pf_spin_editingFinished();

    void on_posfil_spin_editingFinished();

    void on_poserr_spin_editingFinished();

    void on_vp_spin_editingFinished();

    void on_vi_spin_editingFinished();

    void on_vd_spin_editingFinished();

    void on_af_spin_editingFinished();

    void on_velfil_spin_editingFinished();

    void on_convel_spin_editingFinished();

    void on_vellim_spin_editingFinished();

    void on_acc_spin_editingFinished();

    void on_dec_spin_editingFinished();

    void on_cp_spin_editingFinished();

    void on_ci_spin_editingFinished();

    void on_concur_spin_editingFinished();

    void on_limcur_spin_editingFinished();

    void on_tmplim_spin_editingFinished();

    void on_ovrvol_spin_editingFinished();

    void on_undvol_spin_editingFinished();

    void on_i2tlim_spin_editingFinished();

private:
    Ui::MainWindow *ui;
    jmc_driver *servo = NULL;
    QTextStream out;
    QSerialPort *serial_port = NULL;
};

#endif // MAINWINDOW_H
