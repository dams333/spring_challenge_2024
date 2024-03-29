#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param n The number of buildings
 * @param building_map Representation of the n buildings
 * @return The height of each building.
 */
vector<int> buildingHeights(int n, vector<string> building_map) {
  vector<int> res;
  for (string s : building_map) {
    int r = 0;
    for (char c : s) {
      if (c == '*')
        r++;
    }
    res.push_back(r);
  }

  return res;
}

/* Ignore and do not change the code below */

void trySolution(vector<int> output) {
  Json::Value output_json;

  output_json = Json::Value(Json::arrayValue);
  Json::Value current_value;
  for (int i = 0 ; i < output.size() ; i++) {
    current_value = Json::Value(output[i]);
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
  int n = parsed_json.asInt();
  std::getline(std::cin, line, '\n');
  reader.parse(line, parsed_json);

  vector<string> array;
  for (int i = 0 ; i < parsed_json.size() ; i++) {
    array.push_back(parsed_json[i].asString());
  }
  vector<string> building_map = array;

  vector<int> output = buildingHeights(n, building_map);
  trySolution(output);
}
/* Ignore and do not change the code above */

