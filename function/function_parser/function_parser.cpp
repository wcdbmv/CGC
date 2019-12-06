#include "function_parser.hpp"

exprtk::parser<double>& FunctionParser::parser() {
	static exprtk::parser<double> parser;
	return parser;
}

Expression FunctionParser::compile(const std::string& expression_string) {
	Expression expression;

	if (!parser().compile(expression_string, expression.expression_)) {
		throw std::invalid_argument("invalid expression string");
	}

	return expression;
}

bool FunctionParser::compile(const std::string& expression_string, Expression& expression) {
	return parser().compile(expression_string, expression.expression_);
}
