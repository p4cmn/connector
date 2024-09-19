#ifndef SERIALPORTTESTER_H
#define SERIALPORTTESTER_H

#include <QSerialPort>
#include <QSerialPortInfo>

class SerialPortTester {
public:
  bool testPortPair(const QString& port1, const QString& port2) {
    QSerialPort serial1, serial2;
    serial1.setPortName(port1);
    serial2.setPortName(port2);

    // Открываем первый порт на запись
    if (!serial1.open(QIODevice::WriteOnly)) {
      return false;
    }

    // Открываем второй порт на чтение
    if (!serial2.open(QIODevice::ReadOnly)) {
      serial1.close();
      return false;
    }

    // Пробуем отправить и принять данные
    QByteArray testData = "TEST";
    serial1.write(testData);
    if (!serial1.waitForBytesWritten(1000)) {
      serial1.close();
      serial2.close();
      return false;
    }

    if (!serial2.waitForReadyRead(1000)) {
      serial1.close();
      serial2.close();
      return false;
    }

    QByteArray receivedData = serial2.readAll();
    serial1.close();
    serial2.close();

    return receivedData == testData;
  }
};

#endif // SERIALPORTTESTER_H
