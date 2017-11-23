#include "jmc_driver.h"

jmc_driver::jmc_driver(QSerialPort *serial_port): serial_port(serial_port)
{
    int ret;
    ret = this->read_reg(0x80);
    if (ret != 0x12)
        throw(ret);

}
jmc_driver::~jmc_driver()
{

}

int jmc_driver::read_reg(uint reg)
{
    QByteArray buffer;

    buffer.resize(JMC_OUT_FRM_SIZE);
    buffer[0] = 0x01;
    buffer[1] = 0x03;
    buffer[2] = static_cast<char>((reg & 0xFF00) >> 8);
    buffer[3] = static_cast<char>(reg & 0xFF);
    buffer[4] = 0x00;
    buffer[5] = 0x01;
    buffer = this->xcv_packet(buffer, JMC_OUT_FRM_SIZE, JMC_IN_RD_FRM_SIZE);
    if (buffer.size() == 0)
        return -1;
    return static_cast<unsigned char>(buffer[4]) + (static_cast<unsigned char>(buffer[3]) << 8);
}

int jmc_driver::write_reg(uint reg, uint value)
{
    QByteArray buffer;

    buffer.resize(JMC_OUT_FRM_SIZE);
    buffer[0] = 0x01;
    buffer[1] = 0x06;
    buffer[2] = static_cast<char>((reg & 0xFF00) >> 8);
    buffer[3] = static_cast<char>(reg & 0xFF);
    buffer[4] = static_cast<char>((value & 0xFF00) >> 8);
    buffer[5] = static_cast<char>(value & 0xFF);
    buffer = this->xcv_packet(buffer, JMC_OUT_FRM_SIZE, JMC_IN_WR_FRM_SIZE);
    if (buffer.size() == 0)
        return -1;
    return static_cast<unsigned char>(buffer[5]) + (static_cast<unsigned char>(buffer[4]) << 8);
}

uint jmc_driver::crc16_modbus(QByteArray buf, uint len)
{
    uint crc = 0xFFFF;

    for (uint pos = 0; pos < len; pos++)
    {
      crc ^= static_cast<unsigned char>(buf[pos]);          // XOR byte into least sig. byte of crc

      for (int i = 8; i != 0; i--) {    // Loop over each bit
        if ((crc & 0x0001) != 0) {      // If the LSB is set
          crc >>= 1;                    // Shift right and XOR 0xA001
          crc ^= 0xA001;
        }
        else                            // Else LSB is not set
          crc >>= 1;                    // Just shift right
      }
    }
    // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
    return crc;
}

QByteArray jmc_driver::xcv_packet(QByteArray buf, uint len, uint ret_packet)
{
    uint crc, rcv_crc;
    QTime timeout;

    crc = this->crc16_modbus(buf, len);
    buf.resize(JMC_OUT_FRM_SIZE + 2);
    buf[7] = static_cast<char>((crc & 0xFF00) >> 8);
    buf[6] = static_cast<char>(crc & 0xFF);
    this->serial_port->write(buf, buf.length());
    if (this->serial_port->waitForBytesWritten(10))
    {
        buf.clear();
        this->serial_port->waitForReadyRead(20);
        timeout.start();
        while((this->serial_port->bytesAvailable() < (ret_packet + 2)) && (timeout.elapsed() < 20));
        if (this->serial_port->bytesAvailable() < (ret_packet + 2))
            return NULL;
        buf = serial_port->readAll();

        crc = this->crc16_modbus(buf, ret_packet);
        rcv_crc = static_cast<uint>(static_cast<unsigned char>(buf[ret_packet]) + (static_cast<unsigned char>(buf[ret_packet + 1]) << 8u));
        if (crc != rcv_crc)
            return NULL;
        buf.resize(buf.length() - 2);
        return buf;

    }
    return NULL;
}
