#include <iostream>
#include <vector>
#include "point.h"
#include "kmeans.h"


using namespace std;

void usage() {
    cout << "Usage: ./kmeans <filename>" << endl;
    cout << "   file should be space-separated points, one point per line."
    << endl;
    return;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        usage();
        return -1;
    }
    std::string fpath = argv[1];

    std::vector<Point> points;

    KMeans::loadPoints(fpath, &points);
    for (const auto &p : points) {
        cout << p << endl;
    }

    KMeans kmeans(2);
    kmeans.init(points);

    kmeans.run();
    kmeans.printMeans();

    cout << "Finished." << endl;
    return 0;
}
