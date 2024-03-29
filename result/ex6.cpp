#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;

class Point {
public:
  int x;
  int y;

  Point() {this->x = 0; this->y = 0;};
  Point(int x, int y) {this->x = x; this->y = y;}
};

/**
 * @param n_rows The height of the image.
 * @param n_cols The width of the image.
 * @param image Pixels of the image, given row by row from top to bottom. All pixel colors are alphanumeric.
 * @return The total length of wire needed to deploy the network.
 */
int getCableLength(int n_rows, int n_cols, vector<string> image) {
  map<char, vector<Point>> byColors;
  for (int x = 0; x < n_cols; x++) {
    for (int y = 0; y < n_rows; y++) {
      char c = image[y][x];
      if (!byColors.contains(c))
        byColors[c] = vector<Point>();
      byColors[c].push_back(Point(x, y));
    }
  }

  int res = 0;
  for (pair<char, vector<Point>> elem : byColors) {
    vector<Point> pts = elem.second;
    vector<int> rows;
    vector<int> cols;
    for (Point p : pts) {
      rows.push_back(p.y);
      cols.push_back(p.x);
    }
    std::sort(rows.begin(), rows.end());
    std::sort(cols.begin(), cols.end());
    for (int i = 1; i < cols.size(); i++) {
      res += (i * (cols.size() - i) * (cols[i] - cols[i - 1])) * 2;
      if (res >= 1000000007)
        res %= 1000000007;
    }
    for (int i = 1; i < rows.size(); i++) {
      res += (i * (rows.size() - i) * (rows[i] - rows[i - 1])) * 2;
      if (res >= 1000000007)
        res %= 1000000007;
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

