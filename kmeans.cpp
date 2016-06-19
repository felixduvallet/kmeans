//
// Created by felixd on 6/18/16.
//

#include <map>
#include <iostream>
#include "kmeans.h"


using namespace std;

KMeans::KMeans(int k)
        : k_(k) {

}

int KMeans::findNearestCluster(const Point &point) {
    double min_dist = 1e12;
    int min_cluster = -1;

    for (int idx = 0; idx < k_; ++idx) {
        const double dist = Point::distance(point, means_[idx]);
        if (dist < min_dist) {
            min_dist = dist;
            min_cluster = idx;
        }
    }

    return min_cluster;
}

bool KMeans::assign() {
    bool changed = false;
    // Assign each point to the nearest cluster.
    int new_cluster;
    for (auto &point : points_) {
        new_cluster = findNearestCluster(point);
        // set changed to true if the cluster was updated. Note that we cannot inline
        // (changed = changed || update) since the compiler will 'optimize out' the update step.
        bool ret = point.update(new_cluster);
        changed = changed || ret;

        cout << "Assigned point " << point << " to cluster: " << new_cluster << endl;
    }
    return changed;
}

bool KMeans::update_means() {
    cout <<"---- update means ----" << endl;
    // Compute each mean as the mean of the points in that cluster.
    std::multimap<int, const Point *> point_cluster_map;

    for (const auto &point : points_) {
        cout << "map[" << point.cluster_ << "]: Point:  " << point << endl;
        point_cluster_map.insert(std::pair<int, const Point *>(point.cluster_, &point));
    }

    // Iterate over each cluster, computing the mean.
    for (int cluster_idx = 0; cluster_idx < k_; ++cluster_idx) {
        computeClusterMean(point_cluster_map, cluster_idx, &means_[cluster_idx]);
    }
    return true;
}

void KMeans::computeClusterMean(const std::multimap<int, const Point *> &multimap, int k, Point *mean) {
    for (int dim = 0; dim < mean->dimensions_; ++dim)
        mean->data_[dim] = 0.0;

    // Find all the points in the given cluster, this returns an iterator pair (begin and end).
    auto points_in_cluster = multimap.equal_range(k);
    int num_points = 0;
    cout << "[compute] have range " << " for cluster " << k << endl;

    for (auto itr = points_in_cluster.first; itr != points_in_cluster.second; ++itr) {
        mean->add(*(itr->second));

        num_points += 1;
        cout << "  -- adding point: " << *(itr->second) << " .. " << *mean << endl;
    }
    cout << " number of points:  " << num_points << endl;

    // Divide by number of points in cluster.
    for (unsigned int idx = 0; idx < mean->dimensions_; ++idx) {
        mean->data_[idx] /= float(num_points);
    }
    cout << "Have new mean:  " << *mean << endl;
}

bool KMeans::init(const std::vector<Point> &points) {
    points_.clear();

    for (const auto &p : points) {
        points_.push_back(p);
    }

    for (int idx = 0; idx < k_; ++idx) {
        Point mean(points[idx]);
        means_.push_back(mean);
    }

    return true;
}

