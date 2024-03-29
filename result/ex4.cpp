#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
#include <map>
#include <cmath>
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
 * @param image Pixels of the image, given row by row from top to bottom.
 * @return The parameters of the largest circle [centerRow, centerCol, radius].
 */
vector<int> findLargestCircle(int n_rows, int n_cols, vector<string> image) {
  // Write your code here

  int biggestDiameter = max(n_rows, n_cols);
  map<int, vector<Point>> circleShapes;
  for (int i = 0; i <= biggestDiameter/2; i++) {
    circleShapes[i] = vector<Point>();
  }
  for (int y = -biggestDiameter/2; y <= biggestDiameter/2; y++) {
    for (int x = -biggestDiameter/2; x <= biggestDiameter/2; x++) {
      int radius = (int)sqrtf(powf(x, 2) + powf(y, 2));
      if (radius <= biggestDiameter/2)
        circleShapes[radius].push_back(Point(x, y));
    }
  }

  int biggestRadius = 0;
  Point biggestCenter = Point(0, 0);
  for (int y = 0; y < n_rows; y++) {
    for (int x = 0; x < n_cols; x++) {
      int maxRadius = min({y, n_rows - y -1, x, n_cols - x -1});
      for (int r = maxRadius; r  > biggestRadius; r--) {
        char circle = '\0';
        bool valid = true;
        for (Point p : circleShapes.at(r)) {
          char current = image[y + p.y][x + p.x];
          if (circle == '\0' || circle == current) {
            circle = current;
            continue;
          }
          valid = false;
          break;
        }
        if (valid) {
          biggestRadius = r;
          biggestCenter.x = x;
          biggestCenter.y = y;
        }
      }
    }
  }

  return {biggestCenter.y, biggestCenter.x, biggestRadius};
}

/* Ignore and do not change the code below */

void trySolution(vector<int> largest_circle) {
  Json::Value output_json;

  output_json = Json::Value(Json::arrayValue);
  Json::Value current_value;
  for (int i = 0 ; i < largest_circle.size() ; i++) {
    current_value = Json::Value(largest_circle[i]);
    output_json.append(current_value);
  }

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

  vector<int> output = findLargestCircle(n_rows, n_cols, image);
  trySolution(output);
}
/* Ignore and do not change the code above */

