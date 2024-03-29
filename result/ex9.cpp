#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
#include <map>
using namespace std;

vector<string> treated;
vector<pair<int, string>> toTreat;

void addToTreat(int idx, string s) {
  if (find(treated.begin(), treated.end(), s) == treated.end())
  {
    treated.push_back(s);
    toTreat.push_back(make_pair(idx, s));
  }
}

// #define DEBUG

/**
 * @param codes The list of binary codes in the table
 * @return The shortest and smallest possible ambiguous sequence. If no such sequence exists, return "X"
 */
string crashDecode(vector<string> codes) {

  map<int, string> sequences;

  for (int i = 0; i < codes.size(); i++) {
    for (int j = 0; j < codes.size(); j++) {
      if (i == j)
        continue;
      if (codes[i].starts_with(codes[j])) {
        string rest = codes[i].substr(codes[j].size(), string::npos);
        int idx = sequences.size();
        treated.push_back(rest);
        toTreat.push_back(make_pair(idx, rest));
        sequences[idx] = codes[j];
      }
    }
  }

  vector<string> validAmbigousSequences;

  while (!toTreat.empty()) {

    #ifdef DEBUG
      cerr << "==========" << endl;
      for (pair<int, string> t : toTreat) {
        cerr << sequences[t.first] << "|" << t.second << endl;
      }
      cerr << "==========" << endl;
    #endif

    string current = toTreat[0].second;
    int currentIdx = toTreat[0].first;
    toTreat.erase(toTreat.begin());

    for (string code : codes) {
      if (code == current) {
        validAmbigousSequences.push_back(sequences[currentIdx] + current);
      } else if (code.starts_with(current)) {
        string rest = code.substr(current.size(), string::npos);
        int newIdx = sequences.size();
        addToTreat(newIdx, rest);
        sequences[newIdx] = sequences[currentIdx] + current;
      } else if (current.starts_with(code)) {
        string rest = current.substr(code.size(), string::npos);
        int newIdx = sequences.size();
        addToTreat(newIdx, rest);
        sequences[newIdx] = sequences[currentIdx] + code;
      }
    }
  }

  if (validAmbigousSequences.empty()) {
    return "X";
  } else {
    string smallest = validAmbigousSequences[0];
    for (string s : validAmbigousSequences) {
      if (s.size() < smallest.size()) {
        smallest = s;
      }
      if (s.size() == smallest.size() && s < smallest) {
        smallest = s;
      }
    }
    return smallest;
  }
}

/* Ignore and do not change the code below */

void trySolution(string ambiguous_sequence) {
  Json::Value output_json;
  output_json = Json::Value(ambiguous_sequence);

  Json::FastWriter fastWriter;
  std::string output_str = fastWriter.write(output_json);
  cout << "" << output_str.c_str();
}

int main () {
  setlocale(LC_ALL, "en_US.UTF-8");
  Json::Reader reader;
  string line;
  Json::Value parsed_json;
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);

  vector<string> array;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array.push_back(parsed_json[i].asString());
  }
  vector<string> codes = array;

  string output = crashDecode(codes);
  trySolution(output);
}
/* Ignore and do not change the code above */
