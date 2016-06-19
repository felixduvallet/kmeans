//
// Created by felixd on 6/18/16.
//

#ifndef __KMEANS_POINT_H__
#define __KMEANS_POINT_H__

#include <vector>
#include <iostream>

class Point {
public:
    Point();
    Point(int num_dimensions, bool init_zeros=true);

    Point(double x, double y, double z);
    Point(const std::vector<double> &data);
    ~Point() {};

    static double distance(const Point &p1, const Point &p2);

    void update(int k) { cluster_ = k;}

    std::vector<double> data_;
    int dimensions_;
    int cluster_;

    friend std::ostream &operator<<(std::ostream &target, const Point &point);

};


#endif  // __KMEANS_POINT_H_
