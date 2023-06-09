#include <bits/stdc++.h>
using namespace std;

struct Data {
 private:
  vector<int> type2c;
  vector<vector<int>> day_type2s;
 public:
  int D;
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
 private:
  Data data;
  int today, score;
  vector<int> schedule;
  unordered_map<int, int> lastHeld;
 public:
  Scoring() {}
  Scoring (Data dataInit, vector<int> scheduleInit) {
    data = dataInit;
    schedule = scheduleInit;
    today = 1;
    score = 0;
    for(int i=1;i<=26;i++) {
      lastHeld[i] = 0;
    }
    solve();
  }
  int getScore() {
    return score;
  }
  void print() {
    for (int i=0;i<schedule.size();i++) {
      cout << schedule.at(i) << endl;
    }
  }
  vector<int> getSchedule() {
    return schedule;
  }
 private:
  void solve() {
    for (int i=0;i<schedule.size();i++) {
      hold(schedule.at(i));
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

struct Solver {
 private:
  Data data;
  Scoring bestScore;
  int limit, steps;
 public:
  Solver (Data dataInit) {
    data = dataInit;
    limit = 1000;
    steps = 0;
    vector<int> schedule = findInitial();
    for (int i=0;i<limit;i++)
      neighbor(schedule);
    bestScore.print();
  }
  vector<int> findInitial() {
    vector<int> schedule(data.D);
    for (int i=0;i<data.D;i++)
      schedule.at(i) = i%26 +1;
    bestScore = Scoring(data, schedule);
    return schedule;
  }
  void neighbor (vector<int> &schedule) {
    int i = rand()%data.D;
    int j = rand()%data.D;
    int iVal = schedule.at(i);
    schedule.at(i) = schedule.at(j);
    schedule.at(j) = iVal;
    Scoring scoring(data, schedule);
    if (scoring.getScore()>bestScore.getScore()) {
      bestScore = scoring;
    }
    if (temperature()<((double)rand()/RAND_MAX)) {
      schedule = bestScore.getSchedule();
    }
    steps++;
  }
  double temperature() {
    if (steps<100) return 0.1;
    if (steps<500) return 0.01;
    return 0.001;
  }
};

int main() {
  srand(0);
  Data data;
  cin >> data.D;
  for (int i=0;i<26;i++) {
    int tmp;
    cin >> tmp;
    data.pushC(tmp);
  }
  for(int i=0;i<data.D;i++) {
    vector<int> tmp(26);
    for (int j=0;j<26;j++) {
      cin >> tmp.at(j);
    }
    data.pushS(tmp);
  }
  Solver solver(data);
}

