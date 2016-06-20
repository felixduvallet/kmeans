// Author: Felix Duvallet

#include "kmeans.h"

using namespace std;

KMeans::KMeans(int k, int max_iterations)
        : num_clusters_(k),
          max_iterations_(max_iterations) {

}

bool KMeans::init(const std::vector<Point> &points) {
    points_.clear();

    for (const auto &p : points) {
        points_.push_back(p);
    }

    for (int idx = 0; idx < num_clusters_; ++idx) {
        Point mean(points[idx]);
        means_.push_back(mean);
    }

    return true;
}

bool KMeans::run() {
    for (int iteration = 1; iteration <= max_iterations_; ++iteration) {
        cout << "== KMeans iteration " << iteration << " == " << endl;
        bool changed = assign();
        update_means();

        if(!changed) {
            cout << "KMeans has converted after " << iteration
            << " iterations." << endl;
            return true;
        }
    }
    return false;
}

int KMeans::findNearestCluster(const Point &point) {
    double min_dist = 1e12;
    int min_cluster = -1;

    for (int idx = 0; idx < num_clusters_; ++idx) {
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
    // Assign each point to the nearest cluster: iterate over all points, find
    // the nearest cluster, and assign.
    for (auto &point : points_) {
        const int new_cluster = findNearestCluster(point);

        // set changed to true if the cluster was updated. Note that we cannot
        // inline (changed = changed || update) since the compiler will
        // 'optimize out' the update step.
        bool ret = point.update(new_cluster);
        changed = changed || ret;

        cout << "Assigned point " << point << " to cluster: "
             << new_cluster << endl;
    }
    return changed;
}

bool KMeans::update_means() {
    // Compute each mean as the mean of the points in that cluster.

    // First, compute a map of the cluster assignments. This prevents us from
    // iterating over the data k times.
    std::multimap<int, const Point *> point_cluster_map;
    for (const auto &point : points_) {
        // Map is cluster_index -> Point*
        auto pair = std::pair<int, const Point *>(point.cluster_, &point);
        point_cluster_map.insert(pair);
    }

    // Iterate over each cluster, computing the mean.
    for (int cluster_idx = 0; cluster_idx < num_clusters_; ++cluster_idx) {
        computeClusterMean(point_cluster_map, cluster_idx,
                           &means_[cluster_idx]);
    }
    return true;
}

void KMeans::computeClusterMean(
        const std::multimap<int, const Point *> &multimap,
        int cluster,
        Point *mean) {

    // Zero-out the mean.
    for (int dim = 0; dim < mean->dimensions_; ++dim)
        mean->data_[dim] = 0.0;

    // Find all the points in the given cluster, this returns an iterator pair
    // (begin and end).
    auto in_cluster = multimap.equal_range(cluster);
    int num_points = 0;

    // Compute the mean: sum over all points, then divide by the number.
    for (auto itr = in_cluster.first; itr != in_cluster.second; ++itr) {
        mean->add(*(itr->second));

        num_points += 1;
    }

    for (unsigned int idx = 0; idx < mean->dimensions_; ++idx) {
        mean->data_[idx] /= float(num_points);
    }
}

void KMeans::printMeans() {
    for (const auto &mean : means_) {
        cout << "Mean: " << mean << endl;
    }
}


