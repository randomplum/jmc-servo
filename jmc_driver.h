#ifndef JMC_DRIVER_H
#define JMC_DRIVER_H

#include <QByteArray>
#include <QTime>
#include <QtSerialPort/QSerialPort>

#define JMC_OUT_FRM_SIZE 6u
#define JMC_IN_RD_FRM_SIZE 5u
#define JMC_IN_WR_FRM_SIZE 6u

class jmc_driver
{
public:
    explicit jmc_driver(QSerialPort *serial_port);
    ~jmc_driver();

    int read_reg(uint reg);
    int write_reg(uint reg, uint value);
private:
    uint crc16_modbus(QByteArray buf, uint len);
    QByteArray xcv_packet(QByteArray buf, uint len, uint ret_packet);
    QSerialPort *serial_port;
};

#endif // JMC_DRIVER_H
