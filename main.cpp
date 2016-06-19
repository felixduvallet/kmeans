#include <iostream>
#include <vector>
#include "point.h"
#include "kmeans.h"


using namespace std;

int main() {


    Point p1(std::vector<double>{-2.0, 1.0});
    cout << p1.data_[0] << endl;
    Point p2(std::vector<double>{-1.0, 3.0});

    Point p3(std::vector<double>{5.0, 2.0});
    Point p4(std::vector<double>{6.0, 4.0});
    Point p5(std::vector<double>{7.0, 2.0});


    std::vector<Point> points{p1, p2, p3, p4, p5};

    KMeans kmeans(2);
    kmeans.init(points);

    for (const auto &mean : kmeans.means_) {
        cout << "Mean: " << mean << endl;
    }

    bool changed = false;
    for (int iteration = 1; iteration <= 10; ++iteration) {
        cout << "== KMeans iteration " << iteration << " == " << endl;
        changed = kmeans.assign();
        kmeans.update_means();

        if(!changed) {
            cout << "KMneans has converted after " << iteration << " iterations." << endl;
            break;
        }
    }

    cout << "Hello, World!" << endl;
    return 0;
}