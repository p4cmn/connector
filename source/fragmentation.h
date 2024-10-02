#ifndef FRAGMENTATION_H
#define FRAGMENTATION_H

#include <QList>
#include <bitset>
#include <iostream>
#include "frame.h"
#include "FCSOperations.h"

using std::bitset;

QList<Frame> fragmentData(const QByteArray& data, const QString& sourcePort, int fragmentSize) {
  QList<Frame> frames;
  int dataSize = data.size();
  int totalFragments = (dataSize + fragmentSize - 1) / fragmentSize;

  for (int i = 0; i < totalFragments; ++i) {
    Frame frame;
    frame.flag[0] = '$';
    frame.flag[1] = 'a' + 9;
    frame.sourceAddress = sourcePort.at(3).digitValue();
    frame.destinationAddress = 0x00;

    int start = i * fragmentSize;
    int end = std::min(start + fragmentSize, dataSize);
    for (int j = start; j < end; ++j) {
      frame.data[j - start] = data[j];
    }
    for (int j = end - start; j < fragmentSize; ++j) {
      frame.data[j] = 0x00;
    }
    frame.FCS = generateFCS(frame.data, polynomial);
    frames.append(frame);
  }

  return frames;
}

QByteArray defragmentData(QList<Frame>& frames) {
  QByteArray completeData;

  for (Frame& frame : frames) {
    std::cout << "st" << std::endl;
    size_t dataBitLength = frame.data.size() * 8;
    size_t degree = polynomial.size() - 1;
    unordered_map<string, size_t> syndromeTable = generateSyndromeTable(dataBitLength + degree, polynomial);
    if(decodeAndCorrect(frame.data, frame.FCS, polynomial, syndromeTable)) {
      std::cout << "err" << std::endl;
    } else {
      std::cout << "clear" << std::endl;
    }

    QByteArray dataWithoutNulls(frame.data.data(), DATA_SIZE);
    dataWithoutNulls = dataWithoutNulls.replace('\0', "");
    completeData.append(dataWithoutNulls);
  }

  return completeData;
}



#endif // FRAGMENTATION_H
