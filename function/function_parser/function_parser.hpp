#ifndef FUNCTION_FUNCTION_PARSER_FUNCTION_PARSER_HPP_
#define FUNCTION_FUNCTION_PARSER_FUNCTION_PARSER_HPP_

#include "function/expression/expression.hpp"

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

#endif  // FUNCTION_FUNCTION_PARSER_FUNCTION_PARSER_HPP_
