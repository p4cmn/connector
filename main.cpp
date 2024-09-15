#include "mainwindow.h"

#include <QApplication>
#include "mainwindow.h"
#include "serialportmodel.h"
#include "serialportcontroller.h"


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  SerialPortModel model;
  MainWindow view;
  SerialPortController controller(&model, &view);

  view.show();

  return a.exec();
}
