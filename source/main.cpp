#include "mainwindow.h"

#include <QApplication>
#include "mainwindow.h"
#include "serialportmodel.h"
#include "serialportscanner.h"
#include "serialportcontroller.h"

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
}
