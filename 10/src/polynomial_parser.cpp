#include "polynomial_parser.hpp"
#include <stack>
#include <sstream>

Polynomial
PolynomialParser::compute_polynomial(const std::string &expression, std::map<std::string, Polynomial> &polys) {
    std::istringstream exp(expression);
    std::string element;
    std::stack<Polynomial> calc;
    while (exp >> element) {
        if (element != "+" && element != "-" && element != "*") {
            calc.push(polys[element]);
        } else {
            Polynomial b = calc.top();
            calc.pop();
            Polynomial a = calc.top();
            calc.pop();
            if (element == "+")
                calc.push(a + b);
            else if (element == "-")
                calc.push(a - b);
            else if (element == "*")
                calc.push(a * b);
        }
    }
    return calc.top();
}

PolynomialParser::scalarFct
PolynomialParser::compute_lambda(const std::string &expression, std::map<std::string, Polynomial> &polys) {
    return [p = compute_polynomial(expression, polys)](double x) { return p(x); };
}