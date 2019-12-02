#include "expression.hpp"

Expression::Expression() {
	symbol_table_.create_variable("x");
	symbol_table_.create_variable("y");
	symbol_table_.add_constants();

	expression_.register_symbol_table(symbol_table_);
}

double& Expression::x() {
	return symbol_table_.get_variable("x")->ref();
}

double Expression::x() const {
	return symbol_table_.get_variable("x")->ref();
}

double& Expression::y() {
	return symbol_table_.get_variable("y")->ref();
}

double Expression::y() const {
	return symbol_table_.get_variable("y")->ref();
}

double Expression::value() const {
	return expression_.value();
}
