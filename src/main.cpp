#include <iostream>
#include <vector>
#include "point.h"
#include "kmeans.h"


using namespace std;

void usage() {
  cout << "Usage: ./kmeans <filename> <k>" << endl;
  cout << "   file should be space-separated points, one point per line."
  << endl;
  cout << "   k is the number of desired clusters."
  << endl;
  return;
}

int main(int argc, char *argv[]) {

  if (argc < 3) {
    usage();
    return -1;
  }
  const std::string fpath = argv[1];
  const int num_clusters = atoi(argv[2]);

  std::vector<Point> points;

  KMeans::loadPoints(fpath, &points);
  for (const auto &p : points) {
    cout << p << endl;
  }

  KMeans kmeans(num_clusters);
  kmeans.init(points);

  kmeans.run();
  kmeans.printMeans();

  kmeans.writeMeans("means.txt");

  cout << "Finished." << endl;
  return 0;
}
