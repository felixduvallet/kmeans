#include <iostream>
#include <vector>
#include "point.h"
#include "kmeans.h"


using namespace std;

int main() {


    Point p1(std::vector<double>{-2.0});
    cout << p1.data_[0] << endl;
    Point p2(std::vector<double>{-1.0});

    Point p3(std::vector<double>{5.0});
    Point p4(std::vector<double>{6.0});


    std::vector<Point> points{p1, p2, p3, p4};

    KMeans kmeans(2);
    kmeans.init(points);

    for (const auto &mean : kmeans.means_) {
        cout << "Mean: " << mean << endl;
    }

    for (int idx = 0; idx < 10; ++idx) {
        cout << "== KMeans iteration " << idx << " == " << endl;
        kmeans.assign();
        kmeans.update();
    }

    cout << "Hello, World!" << endl;
    return 0;
}