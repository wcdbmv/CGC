#ifndef MATH_RANGE_RANGE_HPP_
#define MATH_RANGE_RANGE_HPP_

#include <vector>

class Range {
public:
	Range(double left, double right, double delta);

	[[nodiscard]] std::vector<double> range() const;

	[[nodiscard]] double left() const;
	[[nodiscard]] double right() const;
	[[nodiscard]] double delta() const;

	void set_left(double left);
	void set_right(double right);
	void set_delta(double delta);

private:
	double left_;
	double right_;
	double delta_;

	[[nodiscard]] bool check_range(double left, double right) const;
	[[nodiscard]] bool check_delta(double delta) const;
};

#endif  // MATH_RANGE_RANGE_HPP_
