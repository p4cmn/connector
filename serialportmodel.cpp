#include "serialportmodel.h"

SerialPortModel::SerialPortModel(QObject *parent)
    : QObject(parent),
    firstPort(new QSerialPort(this)),
    secondPort(new QSerialPort(this)),
    bytesTransferred(0)
{}

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

void SerialPortModel::setParity(const QString &parity) {
  if (parity == "None") {
    firstPort->setParity(QSerialPort::NoParity);
    secondPort->setParity(QSerialPort::NoParity);
  } else if (parity == "Even") {
    firstPort->setParity(QSerialPort::EvenParity);
    secondPort->setParity(QSerialPort::EvenParity);
  } else if (parity == "Odd") {
    firstPort->setParity(QSerialPort::OddParity);
    secondPort->setParity(QSerialPort::OddParity);
  }
}

void SerialPortModel::sendData(const QByteArray& data) {
  if (firstPort->isOpen()) {
    bytesTransferred = 0;
    firstPort->write(data);
    bytesTransferred = data.size();
    emit statusUpdated(firstPort->baudRate(), bytesTransferred);
  }
}

void SerialPortModel::readData() {
  QByteArray data = secondPort->readAll();
  emit dataReceived(data);
}
