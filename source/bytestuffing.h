#ifndef BYTESTUFFING_H
#define BYTESTUFFING_H

#include <QByteArray>

const char FLAG1 = '$';
const char FLAG2 = 'a' + 9;
const char ESCAPE_BYTE = 0x1B;
const char XOR_MASK = 0x20;

QByteArray applyByteStuffing(const QByteArray& data) {
  QByteArray stuffedData;

  for (int i = 0; i < data.size(); ++i) {
    char byte = data[i];

    if (byte == FLAG1 && i + 1 < data.size() && data[i + 1] == FLAG2) {
      stuffedData.append(ESCAPE_BYTE);
      stuffedData.append(FLAG1 ^ XOR_MASK);
      stuffedData.append(FLAG2 ^ XOR_MASK);
      ++i;
    }
    else if (byte == ESCAPE_BYTE) {
      stuffedData.append(ESCAPE_BYTE);
      stuffedData.append(ESCAPE_BYTE ^ XOR_MASK);
    }
    else {
      stuffedData.append(byte);
    }
  }

  return stuffedData;
}

QByteArray removeByteStuffing(const QByteArray& data) {
  QByteArray originalData;
  bool escapeNext = false;
  for (int i = 0; i < data.size(); ++i) {
    char byte = data[i];
    if (escapeNext) {
      if (byte == (FLAG1 ^ XOR_MASK) && i + 1 < data.size() && data[i + 1] == (FLAG2 ^ XOR_MASK)) {
        originalData.append(FLAG1);
        originalData.append(FLAG2);
        ++i;
      } else if (byte == (ESCAPE_BYTE ^ XOR_MASK)) {
        originalData.append(ESCAPE_BYTE);
      } else {
        originalData.append(byte);
      }
      escapeNext = false;
    }
    else if (byte == ESCAPE_BYTE) {
      escapeNext = true;
    }
    else {
      originalData.append(byte);
    }
  }

  return originalData;
}

#endif // BYTESTUFFING_H
