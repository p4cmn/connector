#ifndef FRAGMENTATION_H
#define FRAGMENTATION_H

#include <QList>
#include "frame.h"

QList<Frame> fragmentData(const QByteArray& data, const QString& sourcePort, int fragmentSize) {
  QList<Frame> frames;
  int dataSize = data.size();
  int totalFragments = (dataSize + fragmentSize - 1) / fragmentSize;

  for (int i = 0; i < totalFragments; ++i) {
    Frame frame;
    frame.flag[0] = '$';
    frame.flag[1] = 'a' + 9;  // Установка флага
    frame.sourceAddress = sourcePort.toUInt();
    frame.destinationAddress = 0x00;

    int start = i * fragmentSize;
    int end = std::min(start + fragmentSize, dataSize);
    for (int j = start; j < end; ++j) {
      frame.data[j - start] = static_cast<uint8_t>(data[j]);
    }

    for (int j = end - start; j < fragmentSize; ++j) {
      frame.data[j] = 0x00;
    }

    frames.append(frame);
  }

  return frames;
}

QByteArray defragmentData(const QList<Frame>& frames) {
  QByteArray completeData;

  for (const Frame& frame : frames) {
    // Извлекаем данные каждого кадра, удаляя нули
    QByteArray dataWithoutNulls(reinterpret_cast<const char*>(frame.data.data()), DATA_SIZE);
    dataWithoutNulls = dataWithoutNulls.replace('\0', "");
    completeData.append(dataWithoutNulls);
  }

  return completeData;
}

#endif // FRAGMENTATION_H
