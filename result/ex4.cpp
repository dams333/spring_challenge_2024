nclude <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
#include <map>
#include <cmath>
using namespace std;


bool stringMadeOfUniqueChar(string s) {
  char c = s[0];
  for (char ch : s) {
    if (ch != c)
      return false;
  }
  return true;
}

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
  int bigRadius = 0;
  int bigX = 0;
  int bigY = 0;
  
  //For a radius X, list all offsets (x, y) from the center that are on the circle
  int biggestDiameter = max(n_rows, n_cols);
  map<int, vector<Point>> circleShapes;
  for (int i = 0; i <= biggestDiameter/2; i++)
    circleShapes[i] = vector<Point>();
  for (int y = -biggestDiameter/2; y <= biggestDiameter/2; y++) {
    for (int x = -biggestDiameter/2; x <= biggestDiameter/2; x++) {
      int radius = (int)sqrtf(powf(x - 0, 2) + powf(y - 0, 2));
      if (radius <= biggestDiameter/2) {
        circleShapes[radius].push_back(Point(x, y));
      }
    }
  }

  for (int y = 0; y < n_rows; y++) {
    int maxTopRadius = y;
    int maxBottomRadius = n_rows - y - 1;
    for (int x = 0; x < n_cols; x++) {
      int maxLeftRadius = x;
      int maxRightRadius = n_cols - x -1;
      int maxRadius = min({maxTopRadius, maxBottomRadius, maxLeftRadius, maxRightRadius});

      for(int r = maxRadius; r > bigRadius; r--) {
        string circle = "";
        bool valid = true;
        for (Point p : circleShapes.at(r)) {
          circle += image[y + p.y][x + p.x];
          if (!stringMadeOfUniqueChar(circle)) {
            valid = false;
            break;
          }
        }
        if (valid) {
          bigRadius = r;
          bigX = x;
          bigY = y;
          break;
        }
      }
    }
  }

  cerr << bigY << " | " << bigX << " | " << bigRadius << endl;
  return {bigY, bigX, bigRadius};
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

