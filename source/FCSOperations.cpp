#include "FCSOperations.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

constexpr ssize_t BITS_PER_BYTE = 8;
const vector<bool> polynomial = {1,0,0,0,0,0,1,1};

void distortRandomBit(QByteArray& data) {
  if (data.isEmpty()) {
    return;
  }
  size_t probability = rand() % 100;
  if (probability < 70) {
    size_t byteIndex = rand() % data.size();
    size_t bitIndex = rand() % 8;
    data[byteIndex] ^= (1 << bitIndex);
  }
}

vector<bool> convertByteArrayToBitArray(const QByteArray& dataInBytes, size_t bitLength) {
  vector<bool> bitArray;
  bitArray.reserve(bitLength);

  size_t bitIndex = 0;
  for (qsizetype i = 0; i < dataInBytes.size(); ++i) {
    for (int j = 7; j >= 0 && bitIndex < bitLength; --j) {
      bool bit = (dataInBytes[i] >> j) & 1;
      bitArray.push_back(bit);
      bitIndex++;
    }
  }
  return bitArray;
}

QByteArray convertBitArrayToByteArray(const vector<bool>& dataInBits, size_t bitLength) {
  QByteArray byteArray;
  size_t bytesLength = (bitLength + 7) / 8;
  byteArray.resize(bytesLength);
  byteArray.fill(0);
  for (size_t i = 0; i < bitLength; ++i) {
    size_t byteIndex = i / 8;
    size_t bitIndex = 7 - (i % 8);
    if (dataInBits[i]) {
      byteArray[byteIndex] |= (1 << bitIndex);
    }
  }
  return byteArray;
}

void shiftLeft(vector<bool>& bitArray, size_t degree) {
  bitArray.resize(bitArray.size() + degree, 0);
}

vector<bool> dividePolynomials(const vector<bool>& dividend, const vector<bool>& divisor) {
  vector<bool> remainder = dividend;
  size_t divisorLength = divisor.size();
  for (size_t i = 0; i <= remainder.size() - divisorLength; ++i) {
    if (remainder[i]) {
      for (size_t j = 0; j < divisorLength; ++j) {
        remainder[i + j] = remainder[i + j] ^ divisor[j];
      }
    }
  }
  vector<bool> result(remainder.end() - (divisorLength - 1), remainder.end());
  return result;
}

void addRemainder(vector<bool> &shiftedBitArray, const vector<bool> &remainder) {
  for(size_t i = 0; i < remainder.size(); ++i) {
    size_t bitIndex = shiftedBitArray.size() - remainder.size();
    shiftedBitArray[bitIndex + i] = remainder[i];
  }
}

QByteArray generateFCS(const QByteArray& data, const vector<bool>& polynomial) {
  size_t dataBitLength = data.size() * 8;
  vector<bool> bitArray = convertByteArrayToBitArray(data, dataBitLength);
  size_t degree = polynomial.size() - 1;
  shiftLeft(bitArray, degree);
  vector<bool> remainder = dividePolynomials(bitArray, polynomial);
  QByteArray fcs = convertBitArrayToByteArray(remainder, degree);
  if (fcs.size() < 1) {
    fcs.prepend('\0');
  }
  return fcs;
}

string bitArrayToString(const vector<bool>& bitArray) {
  string result;
  for (bool bit : bitArray) {
    result += bit ? '1' : '0';
  }
  return result;
}

unordered_map<string, size_t> generateSyndromeTable(size_t totalBits, const vector<bool>& polynomial) {
  unordered_map<string, size_t> syndromeTable;
  for (size_t i = 0; i < totalBits; ++i) {
    vector<bool> errorVector(totalBits, false);
    errorVector[i] = true;
    vector<bool> syndrome = dividePolynomials(errorVector, polynomial);
    string syndromeKey = bitArrayToString(syndrome);
    syndromeTable[syndromeKey] = i;
  }
  return syndromeTable;
}

bool decodeAndCorrect(QByteArray& data, QByteArray& receivedFCS, const vector<bool>& polynomial, const unordered_map<string, size_t>& syndromeTable) {
  std::cout << "rec" << std::endl;
  size_t dataBitLength = data.size() * 8;
  size_t degree = polynomial.size() - 1;
  vector<bool> bitArray = convertByteArrayToBitArray(data, dataBitLength);
  vector<bool> remainder = convertByteArrayToBitArray(receivedFCS, degree);
  shiftLeft(bitArray, degree);
  addRemainder(bitArray, remainder);
  vector<bool> syndrome = dividePolynomials(bitArray, polynomial);
  bool errorDetected = false;
  for (bool bit : syndrome) {
    if (bit) {
      errorDetected = true;
      break;
    }
  }
  if (!errorDetected) {
    return false;
  }
  string syndromeKey = bitArrayToString(syndrome);
  auto it = syndromeTable.find(syndromeKey);
  if (it != syndromeTable.end()) {
    size_t errorPosition = it->second;
    if (errorPosition < dataBitLength + degree) {
      qsizetype byteIndex = errorPosition / 8;
      size_t bitIndex = 7 - (errorPosition % 8);
      std::cout << byteIndex << ' ' << bitIndex << std::endl;
      if (byteIndex < data.size()) {
        data[byteIndex] ^= (1 << bitIndex);
      } else {
        size_t fcsBitPosition = errorPosition - dataBitLength;
        qsizetype fcsByteIndex = fcsBitPosition / 8;
        size_t fcsBitIndex = 7 - (fcsBitPosition % 8);
        if (fcsByteIndex < receivedFCS.size()) {
          receivedFCS[fcsByteIndex] ^= (1 << fcsBitIndex);
        }
      }
    }
    return true;
  } else {
    return false;
  }
}


























// #include <ctime>
// #include <cmath>
// #include <cstdlib>
// #include "FCSOperations.h"
// #include <iostream>

// QVector<bool> polynomial = {1, 0, 0, 0, 0, 0, 1, 1};

// QVector<bool> byteArrayToBits(const QByteArray &byteArray) {
//   QVector<bool> bitArray;
//   bool significantBitFound = false;

//   for (qsizetype i = 0; i < byteArray.size(); ++i) {
//     uint8_t byte = static_cast<uint8_t>(byteArray[i]);
//     for (qsizetype bitPos = BITS_PER_BYTE - 1; bitPos >= 0; --bitPos) {
//       bool bit = (byte >> bitPos) & 1;
//       if (bit || significantBitFound) {
//         significantBitFound = true;
//         bitArray.append(bit);
//       }
//     }
//   }

//   return bitArray;
// }

// QVector<bool> byteArrayToBits(const QByteArray &byteArray, qsizetype numberOfBitsNeeded) {
//   QVector<bool> bitArray;
//   qsizetype totalBits = byteArray.size() * BITS_PER_BYTE;
//   qsizetype bitsToSkip = totalBits - numberOfBitsNeeded;

//   for (qsizetype i = 0; i < byteArray.size(); ++i) {
//     uint8_t byte = static_cast<uint8_t>(byteArray[i]);

//     for (qsizetype bitPos = BITS_PER_BYTE - 1; bitPos >= 0; --bitPos) {
//       if (bitsToSkip > 0) {
//         --bitsToSkip;
//       } else {
//         bool bit = (byte >> bitPos) & 1;
//         bitArray.append(bit);
//         if (bitArray.size() == numberOfBitsNeeded) {
//           return bitArray;
//         }
//       }
//     }
//   }
//   return bitArray;
// }

// qsizetype calculatePolynomialDegree(qsizetype bitArraySize) {
//   return std::ceil(log2( (bitArraySize + 1) + std::ceil(log2(bitArraySize + 1)) ));
// }

// QVector<bool> shiftBits(const QVector<bool>& bitArray, qsizetype polynomialDegree) {
//   QVector<bool> shiftedBitArray = bitArray;

//   for (qsizetype i = 0; i < polynomialDegree; ++i) {
//     shiftedBitArray.append(0);
//   }

//   return shiftedBitArray;
// }

// QVector<bool> divideByPolynomial(const QVector<bool>& bitArray, const QVector<bool>& polynomial) {
//   QVector<bool> remainder = bitArray;
//   qsizetype polynomialDegree = polynomial.size() - 1;

//   for (qsizetype i = 0; i <= remainder.size() - polynomial.size(); ++i) {
//     if (remainder[i]) {
//       for (qsizetype j = 0; j < polynomial.size(); ++j) {
//         remainder[i + j] = remainder[i + j] ^ polynomial[j];
//       }
//     }
//   }
//   return remainder.mid(remainder.size() - polynomialDegree);
// }

// QByteArray BitsToByteArray(const QVector<bool>& bits) {
//   qsizetype byteCount = (bits.size() + BITS_PER_BYTE - 1) / BITS_PER_BYTE;
//   QByteArray byteArray(byteCount, 0);
//   for(qsizetype i = 0; i < bits.size(); ++i) {
//     qsizetype bitPosition = (bits.size() - 1 - i) % BITS_PER_BYTE;
//     qsizetype bytePosition = byteCount - 1 - (bits.size() - 1 - i) / BITS_PER_BYTE;
//     byteArray[bytePosition] |= (bits[i] << bitPosition);
//   }
//   return byteArray;
// }

// QByteArray calculateFCS(const QByteArray& data, const QVector<bool>& polynomial) {
//   QVector<bool> bitArray = byteArrayToBits(data);
//   for (bool bit : bitArray) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;
//   qsizetype polynomialDegree = polynomial.size() - 1;
//   QVector<bool> shiftedBitArray = shiftBits(bitArray, polynomialDegree);
//   for (bool bit : shiftedBitArray) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;
//   QVector<bool> remainder = divideByPolynomial(shiftedBitArray, polynomial);

//   QByteArray t = BitsToByteArray(remainder);
//   QVector<bool> tr = byteArrayToBits(t, polynomialDegree);
//   for (bool bit : tr) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;
//   QVector<bool> combinedData = addRemainderToData(shiftedBitArray, tr);
//   //
//   for (bool bit : combinedData) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;

//   QVector<bool> test = divideByPolynomial(combinedData, polynomial);
//   //
//   for (bool bit : test) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;
//   std::cout << std::endl << "TR" << std::endl;

//   return BitsToByteArray(remainder);
// }

// QVector<bool> addRemainderToData(const QVector<bool>& dataBits, const QVector<bool>& remainderBits) {
//   QVector<bool> result = dataBits;
//   qsizetype dataSize = dataBits.size();
//   qsizetype remainderSize = remainderBits.size();

//   for (int i = 0; i < remainderSize; ++i) {
//     result[dataSize - remainderSize + i] = remainderBits[i];
//   }

//   return result;
// }

// void corruptRandomBit(QByteArray &data) {
//   std::srand(static_cast<unsigned>(std::time(0)));
//   int probability = std::rand() % 100;
//   if (probability < 70) {
//     int byteIndex = std::rand() % data.size();
//     int bitIndex = std::rand() % 8;
//     data[byteIndex] ^= (1 << bitIndex);
//   }
// }

// qsizetype countOnes(const QVector<bool> &bits) {
//   return std::count(bits.begin(), bits.end(), true);
// }





// bool checkAndCorrectFCS(QByteArray &receivedData, const QByteArray &receivedFCS, const QVector<bool> &polynomial) {
//   QVector<bool> dataBits = byteArrayToBits(receivedData);
//   qsizetype polynomialDegree = polynomial.size() - 1;
//   std::cout << "Data:" <<std::endl;
//   for (bool bit : dataBits) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;
//   QVector<bool> fcsBits = byteArrayToBits(receivedFCS, polynomialDegree);
//   QVector<bool> shiftedBitArray = shiftBits(dataBits, polynomialDegree);
//   std::cout << "Shifted data:" <<std::endl;
//   for (bool bit : shiftedBitArray) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;

//   QVector<bool> combinedData = addRemainderToData(shiftedBitArray, fcsBits);
//   std::cout << "Shifted data + remainder:" <<std::endl;
//   for (bool bit : combinedData) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;
//   QVector<bool> remainder = divideByPolynomial(combinedData, polynomial);
//   std::cout << "Remainder:" <<std::endl;
//   for (bool bit : remainder) {
//     std::cout << (bit ? '1' : '0');
//   }
//   std::cout << std::endl;

//   if (countOnes(remainder) == 0) {
//     return true;
//   }

//   int shiftCount = 0;
//   while (shiftCount < combinedData.size()) {
//     qsizetype weight = countOnes(remainder);

//     if (weight == 1) {
//       applyRemainderToData(combinedData, remainder);
//       std::cout << "Apply:" <<std::endl;
//       for (bool bit : combinedData) {
// 	std::cout << (bit ? '1' : '0');
//       }
//       std::cout << std::endl;
//       std::cout << "Shifted data + remainder: ->" <<std::endl;
//       std::rotate(combinedData.rbegin(), combinedData.rbegin() + shiftCount, combinedData.rend());
//       for (bool bit : combinedData) {
// 	std::cout << (bit ? '1' : '0');
//       }
//       std::cout << std::endl;


//       receivedData = BitsToByteArray(combinedData.mid(0, receivedData.size()));
//       return true;
//     }

//     std::rotate(combinedData.begin(), combinedData.begin() + 1, combinedData.end());
//     std::cout << "Shifted data + remainder: <- " <<std::endl;
//     for (bool bit : combinedData) {
//       std::cout << (bit ? '1' : '0');
//     }
//     std::cout << std::endl;
//     remainder = divideByPolynomial(combinedData, polynomial);
//     std::cout << "Remainder:" <<std::endl;
//     for (bool bit : remainder) {
//       std::cout << (bit ? '1' : '0');
//     }
//     std::cout << std::endl;
//     shiftCount++;
//   }

//   return false;

// }





