#include "range.hpp"
#include <cmath>
#include <cstdlib>
#include <limits>
#include <stdexcept>

Range::Range(double left, double right, double delta) : left_(left), right_(right), delta_(delta) {
	if (!check_range(left, right)) {
		throw std::invalid_argument("Range::Range (right < left)");
	}

	if (!check_delta(delta)) {
		throw std::invalid_argument("Range::Range (delta < 0)");
	}
}

std::vector<double> Range::range() const {
	std::vector<double> nodes(static_cast<size_t>(std::ceil((right_ - left_) / delta_)) + 1);

	double cur = left_;
	for (auto&& node: nodes) {
		node = cur;
		cur += delta_;
	}
	nodes.back() = right_;

	return nodes;
}

double Range::left() const {
	return left_;
}

double Range::right() const {
	return right_;
}

double Range::delta() const {
	return delta_;
}

bool Range::check_range(double left, double right) const {
	return left <= right;
}

bool Range::check_delta(double delta) const {
	return delta > std::numeric_limits<double>::epsilon();
}

void Range::set_left(double left) {
	if (!check_range(left, right_)) {
		throw std::invalid_argument("Range::set_left (right < left)");
	}

	left_ = left;
}

void Range::set_right(double right) {
	if (!check_range(left_, right)) {
		throw std::invalid_argument("Range::set_right (right < left)");
	}

	right_ = right;
}

void Range::set_delta(double delta) {
	if (!check_delta(delta)) {
		throw std::invalid_argument("Range::set_delta (delta < 0)");
	}

	delta_ = delta;
}
