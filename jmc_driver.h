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

/* Position registers */
#define JMC_REG_PP      0x40
#define JMC_REG_PD      0x41
#define JMC_REG_PF      0x42
#define JMC_REG_POSFIL  0x45
#define JMC_REG_PMXERR  0x48
#define JMC_REG_POSCMD  0x85
#define JMC_REG_POSRL   0x86
#define JMC_REG_POSERR  0x87

/* Velocity registers */
#define JMC_REG_VP      0x50
#define JMC_REG_VI      0x51
#define JMC_REG_VD      0x52
#define JMC_REG_AF      0x53
#define JMC_REG_VELFIL  0x54
#define JMC_REG_CONVEL  0x55
#define JMC_REG_VELLIM  0x56
#define JMC_REG_ACC     0x57
#define JMC_REG_DEC     0x58

/* Current registers */
#define JMC_REG_CP      0x60
#define JMC_REG_CI      0x61
#define JMC_REG_CONCUR  0x62
#define JMC_REG_LIMCUR  0x63

/* Threshold registers */
#define JMC_REG_TMPLIM  0x3a
#define JMC_REG_OVRVOL  0x3b
#define JMC_REG_UNDVOL  0x3c
#define JMC_REG_I2TLIM  0x3d



#endif // JMC_DRIVER_H
