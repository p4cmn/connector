#include <QApplication>
#include "mainwindow.h"
#include "serialportmodel.h"
#include "serialportscanner.h"
#include "serialportcontroller.h"

// #include "FCSOperations.h"
// #include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(":/icons/comIcon.ico"));

  SerialPortScanner portScanner;
  QList<QPair<QString, QString>> validPortPairs = portScanner.getValidPortPairs();

  SerialPortModel model;
  MainWindow view;
  Logger logger;

  SerialPortController controller(&model, &view, &logger, validPortPairs);

  view.show();

  return a.exec();
  // QVector<bool> dataBits = {1, 1, 0, 1};  // Данные 1101000
  // QVector<bool> pol = {1, 0, 1, 1};
  // QVector<bool> shift = shiftBits(dataBits, 3);
  // QVector<bool> rem = divideByPolynomial(shift, pol);
  // QVector<bool> resultBits = addRemainderToData(shift, rem);

  // // Выводим результат
  // qDebug() << "Результат:";
  // for (bool bit : resultBits) {
  //   qDebug() << bit;
  // }
}

