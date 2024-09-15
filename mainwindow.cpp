#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Заполнение комбобоксов доступными последовательными портами
  for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
    ui->portSelector1->addItem(info.portName());
    ui->portSelector2->addItem(info.portName());
  }

  connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendButtonClicked);
  connect(ui->portSelector1, &QComboBox::currentTextChanged, [this]() {
    emit portsSelected(ui->portSelector1->currentText(), ui->portSelector2->currentText());
  });

  connect(ui->portSelector2, &QComboBox::currentTextChanged, [this]() {
    emit portsSelected(ui->portSelector1->currentText(), ui->portSelector2->currentText());
  });
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::onSendButtonClicked() {
  QByteArray data = ui->inputField->text().toUtf8();
  emit sendButtonClicked(data);
}

void MainWindow::updateOutputField(const QByteArray& data) {
  ui->outputField->setText(QString::fromUtf8(data));
}
