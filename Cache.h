// code to help make the speed of doing another monte carlo simulation more
// efficient.
#ifndef CACHE_H
#define CACHE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "cards.h"

using namespace std;

class Cache {
 private:
  unordered_map<string, float> cache;
  unordered_map<string, float> weights;

 public:
  bool cardAcending(cards a, cards b) {  // comparitor for the sorting function
    int aNum = a.getRankAsInt();
    int bNum = b.getRankAsInt();
    return aNum < bNum;  // returns the cards in acending order
  }
  string makeKey(
      vector<cards>& hand,
      vector<cards>& board) {  // functions returns a key for a given hand and
                               // board that is sorted so "A,K" == "K,A"
    // combining the hand and board
    vector<cards> totalCards = board;
    totalCards.push_back(hand[0]);
    totalCards.push_back(hand[1]);

    // sorting the hand and board
    sort(totalCards.begin(), totalCards.end(), cardAcending);

    // adding the rank and then suit for the hand and board
    //
    string key;
    for (int i = 0; i < totalCards.size(); i++) {
      string suit = totalCards[i].suitToString();
      key.push_back(totalCards[i].getRankAsInt());
      key.push_back(suit[0]);
    }

    return key;
  }
  void addToRCache(vector<cards>& hand, vector<cards>& board,
                   double probability) {  // function to add to the cache
    string key = makeKey(hand, board);

    //  find the value to be placed in the cache and add it
    double value =
        (cache[key] * weights[key] + probability * 1) / (weights[key] + 1);
    weights[key]++;
    cache[key] = value;
  }

  // function to read in the .dat file so that the information can be stored in
  // the cache.
  void loadCacheFromFile(string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
      cerr << "Error: Could not open file for reading." << endl;
      return;
    }

    cache.clear();
    weights.clear();

    while (inFile.peek() != EOF) {  // Read until the end of the file
      // read key size to make the key
      size_t keySize;
      inFile.read(reinterpret_cast<char*>(&keySize), sizeof(keySize));

      string key(keySize, '\0');
      inFile.read(&key[0], keySize);

      // Read probability
      float probability;
      inFile.read(reinterpret_cast<char*>(&probability), sizeof(probability));

      // Read weight
      float weight;
      inFile.read(reinterpret_cast<char*>(&weight), sizeof(weight));

      // Store in maps
      cache[key] = probability;
      weights[key] = weight;
    }

    inFile.close();
  }

  // function to write the data in the cache to the binary file
  void saveCacheToFile(const string& filename) {
    // to open the binary file for writing
    ofstream outFile;
    outFile.open(filename, ios::binary);

    if (!outFile) {
      cerr << "Error opening file for writing!" << endl;
      return;
    }
    for (auto& c : cache) {
      string key = c.first;

      // writing it in order
      size_t keysize = key.size();
      outFile.write(reinterpret_cast<char*>(&keysize), sizeof(keysize));
      outFile.write(&key[0], key.size());
      float* prob = &c.second;
      outFile.write(reinterpret_cast<char*>(prob), sizeof(float));
      float* weight = &weights[key];
      outFile.write(reinterpret_cast<char*>(weight), sizeof(float));
    }
    outFile.close();
  }

  void outputCache() {  // outputs the cache and the values inside for testing
                        // purposes
    for (auto& c : cache) {
      cout << "the key is: " << c.first << endl;
      cout << "the probability is: " << c.second << endl;
      cout << "the weight is: " << weights[c.first] << endl;
    }
  }
};

#endif
