#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    out(stdout)
{
    ui->setupUi(this);
    out << QObject::tr("Started") << QString::number(0x50, 16) << endl;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
            ui->port_combo->addItem(info.portName());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete servo;
    delete serial_port;
}

void MainWindow::on_connect_button_clicked()
{
    int failed = 0;
    if (serial_port == NULL)
    {
        serial_port = new QSerialPort;
        serial_port->setBaudRate(QSerialPort::Baud57600);
        serial_port->setPortName(ui->port_combo->currentText());
        if (serial_port->open(QIODevice::ReadWrite))
        {
            try {
                servo = new jmc_driver(serial_port);
            } catch (int ret) {
                out << QObject::tr("Error comunicating with the servo driver ") << ret << endl;
                failed = 1;
            }
            if (failed == 0)
            {
                this->ui->connect_button->setText("Disconnect");
                return;
            }
        }
    }
    if (serial_port)
    {
        if (servo)
        {
            delete servo;
            servo = NULL;
        }
        delete serial_port;
        serial_port = NULL;
        this->ui->connect_button->setText("Connect");
    }
}

void MainWindow::on_readall_button_clicked()
{
    int read_value;
    if (servo)
    {
        for (uint i = 0u; i < 0xA5u; i++)
        {
            read_value = servo->read_reg(i);
            ui->para_table->setItem(static_cast<int>(i) , 0, new QTableWidgetItem("0x"+ QString::number(i, 16)));
            ui->para_table->setItem(static_cast<int>(i) , 1, new QTableWidgetItem(QString::number(read_value, 10)
                                                                                  + " (0x" + QString::number(read_value, 16) + " )"));
            switch (i)
            {
            case 0x40:ui->pp_spin->setValue(read_value);
                break;
            case 0x41:ui->pd_spin->setValue(read_value);
                break;
            case 0x42:ui->pf_spin->setValue(read_value);
                break;
            case 0x45:ui->posfil_spin->setValue(read_value);
                break;
            case 0x48:ui->poserr_spin->setValue(read_value);
                break;
            case 0x50:ui->vp_spin->setValue(read_value);
                break;
            case 0x51:ui->vi_spin->setValue(read_value);
                break;
            case 0x52:ui->vd_spin->setValue(read_value);
                break;
            case 0x53:ui->af_spin->setValue(read_value);
                break;
            case 0x54:ui->velfil_spin->setValue(read_value);
                break;
            case 0x55:ui->convel_spin->setValue(read_value);
                break;
            case 0x56:ui->vellim_spin->setValue(read_value);
                break;
            case 0x57:ui->acc_spin->setValue(read_value);
                break;
            case 0x58:ui->dec_spin->setValue(read_value);
                break;
            case 0x60:ui->cp_spin->setValue(read_value);
                break;
            case 0x61:ui->ci_spin->setValue(read_value);
                break;
            case 0x62:ui->concur_spin->setValue(read_value);
                break;
            case 0x63:ui->limcur_spin->setValue(read_value);
                break;
            case 0x3a:ui->tmplim_spin->setValue(read_value);
                break;
            case 0x3b:ui->ovrvol_spin->setValue(read_value);
                break;
            case 0x3c:ui->undvol_spin->setValue(read_value);
                break;
            case 0x3d:ui->i2tlim_spin->setValue(read_value);
                break;
            }
        }
    }
}

void MainWindow::on_live_button_clicked()
{

}


