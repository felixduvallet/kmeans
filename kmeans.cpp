//
// Created by felixd on 6/18/16.
//

#include <map>
#include <assert.h>
#include <iostream>
#include "kmeans.h"


using namespace std;
KMeans::KMeans(int k)
: k_(k){

}

int KMeans::findNearestCluster(const Point &point) {
    double min_dist = 1e12;
    int min_cluster = -1;

    for(int idx = 0; idx < k_; ++idx) {
        const double dist = Point::distance(point, means_[idx]);
        if (dist < min_dist) {
            min_dist = dist;
            min_cluster = idx;
        }
    }

    return min_cluster;
}

bool KMeans::assign() {

    // Assign each point to the nearest cluster.
    int cluster;
    for(auto &point : points_) {
        cluster = findNearestCluster(point);
        point.update(cluster);
        cout << "Assigned point " << point << " to cluster: " << cluster << endl;
    }
    return true;
}

bool KMeans::update() {
    // Compute each mean as the mean of the points in that cluster.
    std::multimap<int, const Point *> point_cluster_map;

    for (const auto & point : points_) {
        point_cluster_map.insert(std::pair<int, const Point*>(point.cluster_, &point));
    }

    // Iterate over each cluster, computing the mean.
    for (int cluster_idx = 0; cluster_idx < k_; ++cluster_idx) {
        computeClusterMean(point_cluster_map, cluster_idx, &means_[cluster_idx]);
    }
    return true;
}

void addPoints(const Point &p1, const Point &p2, Point *result) {
    assert(p1.dimensions_ == p2.dimensions_ == result->dimensions_);
    for (unsigned int idx = 0; idx < p1.dimensions_; ++idx) {
        result->data_[idx] = p1.data_[idx] + p2.data_[idx];
    }
}

void KMeans::computeClusterMean(std::multimap<int, const Point *> multimap, int k, Point *mean) {
    for (int dim = 0; dim < mean->dimensions_; ++dim)
        mean->data_[dim] = 0.0;

    // Find all the points in the given cluster, this returns an iterator pair (begin and end).
    auto points_in_cluster = multimap.equal_range(k);
    int num_points = 0;
    cout << "[compute] have range " << " for cluster " << k << endl;

    for(auto itr = points_in_cluster.first; itr != points_in_cluster.second; ++itr) {
        addPoints(*mean, *(itr->second), mean);
        num_points += 1;
        cout << "  -- adding point: " << *(itr->second)  << " .. " << *mean << endl;
    }

    // Divide by number of points in cluster.
    for (unsigned int idx = 0; idx < mean->dimensions_; ++idx) {
        mean->data_[idx] /= float(num_points);
    }
    cout << "Have new mean:  " << *mean << endl;
}

bool KMeans::init(const std::vector<Point> &points) {
    points_.clear();

    int num_dimensions = points[0].dimensions_;
    for(const auto &p : points) {
        points_.push_back(p);
    }

    for (int idx = 0; idx < k_; ++idx) {
        Point mean(points[idx]);
        means_.push_back(mean);
    }

    return true;
}



