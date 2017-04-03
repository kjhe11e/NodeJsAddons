#include <string>
#include <vector>

using namespace std;

class sample {
public:
  sample() {
    date = "";
    rainfall = 0;
  };
  sample(string d, double r) {
    date = d;
    rainfall = r;
  };
  string date;
  double rainfall;
};

class location {
public:
  double longitude;
  double latitude;
  vector<sample> samples;
};

class rainResult {
public:
  float median;
  float mean;
  float standardDeviation;
  int n;
};

bool operator<(const sample &s1, const sample &s2);
double avgRainfall(location& loc);
rainResult calculateRainStats(location& loc);
