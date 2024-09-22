#ifndef SERIALPORTSCANNER_H
#define SERIALPORTSCANNER_H

#include "serialporttester.h"
#include <QSerialPortInfo>

class SerialPortScanner {
public:
  QList<QPair<QString, QString>> getValidPortPairs() const {
    SerialPortTester tester;
    QList<QPair<QString, QString>> validPortPairs;
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int i = 0; i < ports.size(); ++i) {
      for (int j = i + 1; j < ports.size(); ++j) {
        QString port1 = ports[i].portName();
        QString port2 = ports[j].portName();

	if (tester.testPortPair(port1, port2)) {
	  validPortPairs.append(qMakePair(port1, port2));
	  validPortPairs.append(qMakePair(port2, port1));
	}
      }
    }
    return validPortPairs;
  }
};

#endif // SERIALPORTSCANNER_H
