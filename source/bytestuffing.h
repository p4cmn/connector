#ifndef BYTESTUFFING_H
#define BYTESTUFFING_H

#include <QByteArray>

QByteArray applyByteStuffing(const QByteArray& data) {
  QByteArray stuffedData;
  for (char byte : data) {
    if (byte == '$') {
      stuffedData.append(0x1B);
      stuffedData.append('$');
    } else {
      stuffedData.append(byte);
    }
  }
  return stuffedData;
}

QByteArray removeByteStuffing(const QByteArray& data) {
  QByteArray originalData;
  bool escapeNext = false;
  for (char byte : data) {
    if (escapeNext) {
      originalData.append(byte);
      escapeNext = false;
    } else if (byte == 0x1B) {
      escapeNext = true;
    } else {
      originalData.append(byte);
    }
  }
  return originalData;
}

#endif // BYTESTUFFING_H
