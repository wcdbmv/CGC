#ifndef MATH_EXPRESSION_EXPRESSION_HPP_
#define MATH_EXPRESSION_EXPRESSION_HPP_

#include "../exprtk/exprtk.hpp"

class Expression {
public:
	Expression();

	double& x();
	[[nodiscard]] double x() const;
	double& y();
	[[nodiscard]] double y() const;

	[[nodiscard]] double value() const;

	friend class FunctionParser;

private:
	exprtk::symbol_table<double> symbol_table_;
	exprtk::expression<double> expression_;
};

#endif  // MATH_EXPRESSION_EXPRESSION_HPP_
