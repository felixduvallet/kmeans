// Basic storage class for an n-dimensional point with a cluster assignment.
//
// Author: Felix Duvallet

#ifndef __KMEANS_POINT_H__
#define __KMEANS_POINT_H__

#include <vector>
#include <iostream>

class Point {
 public:
  Point() { }

  // Initialize the number of dimensions, optionally set all values to zero.
  Point(int num_dimensions, bool init_zeros = true);

  Point(double x, double y, double z);

  // Initialize from a vector.
  Point(const std::vector<double> &vector);

  ~Point() { }

  // Compute distance between two points.
  static double distance(const Point &p1, const Point &p2);

  // Adds a point to the current point.
  void add(const Point &point);

  // Update the cluster assignment. Returns true if cluster assignment
  // changed, false if it stayed the same.
  bool update(int k);

  // Members: the data, the number of dimensions, and the cluster ID.
  std::vector<double> data_;
  int dimensions_;
  int cluster_;

  friend std::ostream &operator<<(std::ostream &target, const Point &point);
};

#endif  // __KMEANS_POINT_H_
