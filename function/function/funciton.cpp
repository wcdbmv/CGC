#include "function.hpp"

Function::Function(const std::string& expression_string) : expression_(FunctionParser::compile(expression_string)) {}

bool Function::set_expression(const std::string& expression_string) {
	return FunctionParser::compile(expression_string, expression_);
}

double Function::operator()(double x, double y) {
	expression_.x() = x;
	expression_.y() = y;
	return expression_.value();
}
