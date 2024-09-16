#include "mainwindow.h"

#include <QApplication>
#include "mainwindow.h"
#include "serialportmodel.h"
#include "serialportcontroller.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QList<QPair<QString, QString>> validPortPairs = {
    {"COM1", "COM2"}, {"COM2", "COM1"},
    {"COM3", "COM4"}, {"COM4", "COM3"},
  };

  SerialPortModel model;
  MainWindow view;
  Logger logger;

  SerialPortController controller(&model, &view, &logger, validPortPairs);

  view.setWindowIcon(QIcon(":/icons/comIcon.ico"));
  view.show();

  return a.exec();
}
