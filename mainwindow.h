#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

signals:
  void sendButtonClicked(const QByteArray& data);
  void portsSelected(const QString& firstPort, const QString& secondPort);

public slots:
  void updateOutputField(const QByteArray& data);

private slots:
  void onSendButtonClicked();

private:
  Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
