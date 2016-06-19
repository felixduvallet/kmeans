//
// Created by felixd on 6/18/16.
//

#ifndef __KMEANS_KMEANS_H__
#define __KMEANS_KMEANS_H__


#include "point.h"
#include <map>

class KMeans {

public:

    KMeans(int k);

    bool init(const std::vector<Point> &points);

    // Assign each point to the nearest cluster.
    bool assign();

    // Compute each mean to the mean of the points in that cluster.
    bool update();

    std::vector<Point> means_;
    int k_;
    std::vector<Point> points_;


    int findNearestCluster(const Point &point);

    void computeClusterMean(std::multimap<int, const Point *> multimap, int k, Point *mean);
};


#endif  // __KMEANS_KMEANS_H__
