#ifndef FCSOPERATIONS_H
#define FCSOPERATIONS_H

#include <vector>
#include <unordered_map>
#include <string>
#include <QByteArray>

using std::vector;
using std::unordered_map;
using std::string;
extern const vector<bool> polynomial;

void distortRandomBit(QByteArray& data);
QByteArray convertBitArrayToByteArray(const vector<bool>& dataInBits, size_t bitLength);
vector<bool> convertByteArrayToBitArray(const QByteArray& dataInBytes, size_t bitLength);
vector<bool> dividePolynomials(const vector<bool>& dividend, const vector<bool>& divisor);
void shiftLeft(vector<bool>& bitArray, size_t degree);
void addRemainder(vector<bool>& shiftedBitArray, const vector<bool>& remainder);
QByteArray generateFCS(const QByteArray& data, const vector<bool>& polynomial);
unordered_map<string, size_t> generateSyndromeTable(size_t totalBits, const vector<bool>& polynomial);
bool decodeAndCorrect(QByteArray& data, QByteArray& receivedFCS, const vector<bool>& polynomial, const unordered_map<string, size_t>& syndromeTable);

#endif // FCSOPERATIONS_H






























// #include <random>
// #include "frame.h"
// #include <QVector>
// #include <QByteArray>

// extern QVector<bool> polynomial;

// QByteArray calculateFCS(const QByteArray& data, const QVector<bool>& polynomial);
// QVector<bool> byteArrayToBits(const QByteArray &byteArray);
// QVector<bool> byteArrayToBits(const QByteArray &byteArray, qsizetype numberOfBitsNeeded);
// qsizetype calculatePolynomialDegree(qsizetype bitArraySize);
// QVector<bool> shiftBits(const QVector<bool>& bitArray, qsizetype polynomialDegree);
// QVector<bool> divideByPolynomial(const QVector<bool>& bitArray, const QVector<bool>& polynomial);
// QByteArray BitsToByteArray(const QVector<bool>& bitArray);
// QVector<bool> addRemainderToData(const QVector<bool>& dataBits, const QVector<bool>& remainderBits);
// void corruptRandomBit(QByteArray& data);
// qsizetype countOnes(const QVector<bool>& bits);
// void applyRemainderToData(QVector<bool>& combinedData, const QVector<bool>& remainder);


//bool checkAndCorrectFCS(QByteArray& receivedData, const QByteArray& receivedFCS, const QVector<bool>& polynomial);
