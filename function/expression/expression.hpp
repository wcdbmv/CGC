#ifndef FUNCTION_EXPRESSION_EXPRESSION_HPP_
#define FUNCTION_EXPRESSION_EXPRESSION_HPP_

#include "function/exprtk/exprtk.hpp"

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

#endif  // FUNCTION_EXPRESSION_EXPRESSION_HPP_
