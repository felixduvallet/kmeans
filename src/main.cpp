#include <iostream>
#include <vector>
#include "point.h"
#include "kmeans.h"


using namespace std;

int main() {
    Point p1(std::vector<double>{-2.0, 1.0});
    Point p2(std::vector<double>{-1.0, 3.0});
    Point p3(std::vector<double>{5.0, 2.0});
    Point p4(std::vector<double>{6.0, 4.0});
    Point p5(std::vector<double>{7.0, 2.0});

    std::vector<Point> points{p1, p2, p3, p4, p5};

    KMeans kmeans(2);
    kmeans.init(points);

    kmeans.run();
    kmeans.printMeans();

    cout << "Finished." << endl;
    return 0;
}
