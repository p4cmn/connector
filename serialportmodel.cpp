#include "serialportmodel.h"

SerialPortModel::SerialPortModel(QObject *parent)
    : QObject(parent),
    firstPort(new QSerialPort(this)),
    secondPort(new QSerialPort(this)) {}

SerialPortModel::~SerialPortModel() {
  if (firstPort->isOpen()) firstPort->close();
  if (secondPort->isOpen()) secondPort->close();
}

void SerialPortModel::setPorts(const QString& firstPortName, const QString& secondPortName) {
  firstPort->setPortName(firstPortName);
  secondPort->setPortName(secondPortName);

  if (firstPort->open(QIODevice::ReadWrite)
      && secondPort->open(QIODevice::ReadWrite)) {
    connect(secondPort, &QSerialPort::readyRead, this, &SerialPortModel::readData);
  }
}

void SerialPortModel::sendData(const QByteArray& data) {
  if (firstPort->isOpen()) {
    firstPort->write(data);
  }
}

void SerialPortModel::readData() {
  QByteArray data = secondPort->readAll();
  emit dataReceived(data);
}
