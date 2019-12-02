#ifndef MATH_FUNCTION_FUNCTION_HPP_
#define MATH_FUNCTION_FUNCTION_HPP_

#include "../function_parser/function_parser.hpp"

class Function {
public:
	Function() = default;
	explicit Function(const std::string& expression_string);
	bool set_expression(const std::string& expression_string);

	double operator()(double x, double y);

private:
	Expression expression_;
};

#endif  // MATH_FUNCTION_FUNCTION_HPP_
