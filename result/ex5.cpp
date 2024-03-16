#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
#include <map>
using namespace std;



/**
 * @param n The size of the image
 * @param target_image The rows of the desired image, from top to bottom
 */
vector<string> solve(int n, vector<string> target_image) {
  vector<string> cmds;

  set<string> typeOfRowsSet;
  map<string, vector<int>> typeOfRowsMap;
  for (int i = 0; i < n; i++) {
    string row = target_image[i];
    if (typeOfRowsSet.find(row) == typeOfRowsSet.end()) {
      typeOfRowsSet.insert(row);
      typeOfRowsMap[row] = vector<int>();
    }
    typeOfRowsMap[row].push_back(i);
  }

  vector<string> typeOfRows = vector(typeOfRowsSet.begin(), typeOfRowsSet.end());
  std::sort(typeOfRows.begin(), typeOfRows.end());

  for (int i = 0; i < typeOfRows.size(); i++) {
    string row = typeOfRows[i];
    if (row.find('#') == string::npos)
      continue;

    string nextRow = string(n, '.');
    if (i < typeOfRows.size() - 1)
      nextRow = typeOfRows[i+1];

    for (int j = 0; j < row.size(); j++) {
      if (row[j] == '#' && nextRow[j] == '.') {
        cmds.push_back("C " + to_string(j));
      }
    }

    if (i < typeOfRows.size() - 1) {
      vector<int> nextRowsMap = typeOfRowsMap[nextRow];
      for (int nextRowIdx : nextRowsMap) {
        cmds.push_back("R " + to_string(nextRowIdx));
      }
    }
  }

  return cmds;
}

/* Ignore and do not change the code below */

void trySolution(vector<string> commands) {
  Json::Value output_json;

  output_json = Json::Value(Json::arrayValue);
  Json::Value current_value;
  for (int i = 0 ; i < commands.size() ; i++) {
    current_value = Json::Value(commands[i]);
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
  vector<string> target_image = array;

  vector<string> output = solve(n, target_image);
  trySolution(output);
}
/* Ignore and do not change the code above */

