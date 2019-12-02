#ifndef MATH_FUNCTION_PARSER_FUNCTION_PARSER_HPP_
#define MATH_FUNCTION_PARSER_FUNCTION_PARSER_HPP_

#include "../expression/expression.hpp"

class FunctionParser {
public:
	FunctionParser(const FunctionParser&) = delete;
	FunctionParser& operator=(const FunctionParser&) = delete;

	static Expression compile(const std::string& expression_string);
	static bool compile(const std::string& expression_string, Expression& expression);
private:
	FunctionParser() = default;
	~FunctionParser() = default;

	static exprtk::parser<double>& parser();
};

#endif  // MATH_FUNCTION_PARSER_FUNCTION_PARSER_HPP_
