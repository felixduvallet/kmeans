// Author: Felix Duvallet

#include <cassert>
#include <cmath>
#include "point.h"

Point::Point(int num_dimensions, bool init_zeros)
  : cluster_(-1),
    dimensions_(num_dimensions) {
  if (init_zeros) {  // default is true.
    for (int idx = 0; idx < dimensions_; ++idx) {
      data_.push_back(0.0);
    }
  }
}

Point::Point(double x, double y, double z)
  : Point(3, false) {
  data_.clear();
  data_.push_back(x);
  data_.push_back(y);
  data_.push_back(z);
}

Point::Point(const std::vector<double> &vector)
  : cluster_(-1) {
  dimensions_ = (int) vector.size();
  data_.clear();
  data_.insert(data_.begin(), vector.begin(), vector.end());
}

bool Point::update(int k) {
  const bool ret = cluster_ != k;
  cluster_ = k;
  return ret;
}

// static
double Point::distance(const Point &p1, const Point &p2) {
  assert(p1.dimensions_ == p2.dimensions_);
  double dist = 0.0;

  for (int idx = 0; idx < p1.dimensions_; ++idx) {
    const double tmp = p1.data_[idx] - p2.data_[idx];
    dist += tmp * tmp;
  }
  return sqrt(dist);
}

void Point::add(const Point &point) {
  assert(dimensions_ == point.dimensions_);
  for (int idx = 0; idx < dimensions_; ++idx) {
    data_[idx] += point.data_[idx];
  }
}

std::ostream &operator<<(std::ostream &target, const Point &point) {
  target << "[";
  for (const double &d : point.data_) {
    target << d << ", ";
  }
  target << "]";
  return target;
}
