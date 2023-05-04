#include <bits/stdc++.h>
using namespace std;

struct Data {
 private:
  vector<int> type2c;
  vector<vector<int>> day_type2s;
 public:
  int c(int type) {
    return type2c.at(type-1);
  }
  int s(int day, int type) {
    return day_type2s.at(day-1).at(type-1);
  }
  void pushC(int tmp) {
    type2c.push_back(tmp);
  }
  void pushS(vector<int> tmp) {
    day_type2s.push_back(tmp);
  }
};

struct Scoring {
  Data data;
  int today, score;
  unordered_map<int, int> lastHeld;
  Scoring (Data dataInit) {
    data = dataInit;
    today = 1;
    score = 0;
    for(int i=1;i<=26;i++) {
      lastHeld[i] = 0;
    }
  }
  void solve(int days) {
    for (int i=0;i<days;i++) {
      int type;
      cin >> type;
      hold(type);
      cout << score << endl;
    }
  }
  void hold(int type) {
    score += data.s(today, type);
    lastHeld[type] = today;
    for (int i=1;i<=26;i++) {
      score -= data.c(i) * (today - lastHeld[i]);
    }
    today++;
  }
};

int main() {
  Data data;
  int D;
  cin >> D;
  for (int i=0;i<26;i++) {
    int tmp;
    cin >> tmp;
    data.pushC(tmp);
  }
  for(int i=0;i<D;i++) {
    vector<int> tmp(26);
    for (int j=0;j<26;j++) {
      cin >> tmp.at(j);
    }
    data.pushS(tmp);
  }
  
  Scoring scoring(data);
  scoring.solve(D);
}

