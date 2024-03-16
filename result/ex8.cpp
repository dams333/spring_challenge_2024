#include <iostream>
#include <jsoncpp/json/json.h>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;

class Matrix2;
ostream& operator<<(ostream& os, const Matrix2& m);

class Matrix2 {
public:
  int w;
  int h;
  vector<vector<int>> content;

  Matrix2(int w, int h): Matrix2(w, h, 0) {}

  Matrix2(int w, int h, int val) {
    this->w = w;
    this->h = h;
    for (int i = 0; i < h; i++) {
      content.push_back(vector<int>());
      for (int j = 0; j < w; j++) {
        content[i].push_back(val);
      }
    }
  }

  Matrix2 &operator=(const Matrix2 &rhs) {
    if (this != &rhs) {
      this->w = rhs.w;
      this->h = rhs.h;
      this->content = rhs.content;
    }
    return *this;
  }

  vector<int> &getLine(int y) {
    return content[y];
  }

  //WARNING: Specific to the exercice (modulo 2)
  vector<int> addRows(int r1, int r2) {
    vector<int> res;
    for (int x = 0; x < w; x++) {
      res.push_back(content[r1][x] + content[r2][x]);
      res[x] = res[x] % 2;
    }
    return res;
  }

  //WARNING: Specific to the exercice (modulo 2)
  void invert() {
    if (w != h)
      throw invalid_argument("Matrix is not squared (" + to_string(w) + " " + to_string(h) + ")");
    Matrix2 identity = Matrix2::toIdentity(w);
    for (int x = 0; x < w; x++) {
      if (content[x][x] == 0) {
        //find pivot
        bool found = false;
        for (int y = x + 1; y < h; y++) {
          if (content[y][x] != 0) {
            this->content[x] = this->addRows(y, x);
            identity.content[x] = identity.addRows(y, x);
            found = true;
            break;
          }
        }
        if (!found) {
          throw invalid_argument("Matrix is not invertible");
        }
      }
      for (int y = x + 1; y < h; y++) {
        if (content[y][x] != 0) {
          this->content[y] = this->addRows(x, y);
          identity.content[y] = identity.addRows(x, y);
        }
      }
    }
    for (int x = 0; x < w; x++) {
      for (int y = 0; y < x; y++) {
        if (content[y][x] != 0) {
          this->content[y] = this->addRows(x, y);
          identity.content[y] = identity.addRows(x, y);
        }
      }
    }
    *this = identity;
  }

  //WARNING: rhs need to be width = 1
  Matrix2 operator*(const Matrix2 &rhs) {
    if (this->w != rhs.h) {
      throw invalid_argument("Matrixes doesn't have a similar side tu be multiplied");
    }
    Matrix2 res = Matrix2(rhs.w, this->h);
    for (int y = 0; y < h; y++) {
      int val = 0;
      for (int rhsY = 0; rhsY < h; rhsY++) {
        val ^= this->content[y][rhsY] * rhs.content[rhsY][0];
      }
      res.content[y][0] = val;
    }
    return res;
  }

  static Matrix2 toIdentity(int size) {
    Matrix2 matrix = Matrix2(size, size);
    for (int i = 0; i < size; i++) {
      matrix.content[i][i] = 1;
    }
    return matrix;
  }
};

ostream& operator<<(ostream& os, const Matrix2& m) {
  for (int i = 0; i < m.h; i++) {
    for (int j = 0; j < m.w; j++) {
      if (j != 0)
        os << " ";
      os << m.content[i][j];
    }
    os << endl;
  }
  return os;
}

int computeKey(int x, int y, int n_rows, int n_cols) {
  return x + y*n_cols;
}

Matrix2 getInfluenceMatrix(int n_rows, int n_cols) {
  Matrix2 influenceMatrix = Matrix2(n_cols*n_rows, n_cols*n_rows);

  for (int y = 0; y < n_rows; y++) {
    for (int x = 0; x < n_cols; x++) {
      vector<int> &line = influenceMatrix.getLine(computeKey(x, y, n_rows, n_cols));
      line[computeKey(x, y, n_rows, n_cols)] = 1;

      //top
      if (y > 0)
        line[computeKey(x, y-1, n_rows, n_cols)] = 1;
      //bottom
      if (y < n_rows - 1)
        line[computeKey(x, y+1, n_rows, n_cols)] = 1;
      //left
      if (x > 0)
        line[computeKey(x-1, y, n_rows, n_cols)] = 1;
      //right
      if (x < n_cols - 1)
        line[computeKey(x+1, y, n_rows, n_cols)] = 1;
    }
  }

  return influenceMatrix;
}

Matrix2 getTargetMatrix(int n_rows, int n_cols, vector<string> target_pattern) {
  Matrix2 targetMatrix = Matrix2(1, n_rows*n_cols);
  int i = 0;
  for (string s : target_pattern) {
    for (char c : s) {
      targetMatrix.content[i++][0] = (c == '#' ? 1 : 0);
    }
  }
  return targetMatrix;
}

// #define DEBUG

/**
 * @param n_rows The number of rows in the target pattern.
 * @param n_cols The number of columns in the target pattern.
 * @param target_pattern The target pattern, row by row from left to right.
 * @return The shortest possible list of pixel coordinates to activate in order to reproduce the target pattern.
 */
vector<vector<int>> createPattern(int n_rows, int n_cols, vector<string> target_pattern) {
  Matrix2 influenceMatrix = getInfluenceMatrix(n_rows, n_cols);
  #ifdef DEBUG
    cerr << "===== INFLUENCE =====" << endl;
    cerr << influenceMatrix;
  #endif

  influenceMatrix.invert();
  #ifdef DEBUG
    cerr << "===== INVERTED =====" << endl;
    cerr << influenceMatrix;
  #endif

  Matrix2 targetMatrix = getTargetMatrix(n_rows, n_cols, target_pattern);
  #ifdef DEBUG
    cerr << "===== TARGET =====" << endl;
    cerr << targetMatrix;
  #endif

  Matrix2 res = influenceMatrix * targetMatrix;
  #ifdef DEBUG
    cerr << "===== RESULT =====" << endl;
    cerr << res;
  #endif

  vector<vector<int>> pattern;
  for (int y = 0; y < n_rows; y++) {
    for (int x = 0; x < n_cols; x++) {
      if (res.content[computeKey(x, y, n_rows, n_cols)][0] == 1) {
        pattern.push_back({y, x});
      }
    }
  }
  return pattern;
}

/* Ignore and do not change the code below */

void trySolution(vector<vector<int>> output) {
  Json::Value output_json;

  output_json = Json::Value(Json::arrayValue);
  Json::Value current_value;
  for (int i = 0 ; i < output.size() ; i++) {
  
    current_value = Json::Value(Json::arrayValue);
    Json::Value current_value2;
    for (int j = 0 ; j < output[i].size() ; j++) {
      current_value2 = Json::Value(output[i][j]);
      current_value.append(current_value2);
    }
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
  vector<string> target_pattern = array;

  vector<vector<int>> output = createPattern(n_rows, n_cols, target_pattern);
  trySolution(output);
}
/* Ignore and do not change the code above */

