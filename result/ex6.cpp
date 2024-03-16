#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param n_rows The height of the image.
 * @param n_cols The width of the image.
 * @param image Pixels of the image, given row by row from top to bottom. All pixel colors are alphanumeric.
 * @return The total length of wire needed to deploy the network.
 */
int getCableLength(int n_rows, int n_cols, vector<string> image) {
  int res = 0;
  for (int i = 0; i < n_rows*n_cols; i++) {
    for (int j = i + 1; j < n_rows*n_cols; j++) {
      int y1 = i / n_cols;
      int x1 = i % n_cols;
      int y2 = j / n_cols;
      int x2 = j % n_cols;
      if (image[y1][x1] == image[y2][x2]) {
        res += (abs(x1-x2)+abs(y1-y2)) * 2;
      }
    }
  }

  return res;
}

/* Ignore and do not change the code below */

void trySolution(int cable_length) {
  Json::Value output_json;
  output_json = Json::Value(cable_length);

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
  int n_rows = parsed_json.asInt();
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);
  int n_cols = parsed_json.asInt();
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);

  vector<string> array;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array.push_back(parsed_json[i].asString());
  }
  vector<string> image = array;

  int output = getCableLength(n_rows, n_cols, image);
  trySolution(output);
}
/* Ignore and do not change the code above */

