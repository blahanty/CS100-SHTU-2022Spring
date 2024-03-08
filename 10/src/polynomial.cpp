#include "polynomial.hpp"
#include <fstream>
#include <cmath>

Polynomial::Polynomial() { m_coeffs = {}; }

Polynomial::Polynomial(const std::vector<double> &coeffs) { m_coeffs = coeffs; }

Polynomial::Polynomial(std::vector<double> &&coeffs) { m_coeffs = std::move(coeffs); }

Polynomial::Polynomial(std::initializer_list<double> coeffs) {
    m_coeffs = {};
    for (auto coeff: coeffs)
        m_coeffs.push_back(coeff);
}

Polynomial::Polynomial(const std::string &path) {
    m_coeffs = {};
    double c;
    std::ifstream input(path);
    while (input >> c)
        m_coeffs.push_back(c);
}

Polynomial::Polynomial(const Polynomial &p) { m_coeffs = p.m_coeffs; }

Polynomial::Polynomial(Polynomial &&p) noexcept: m_coeffs(std::move(p).m_coeffs) {}

Polynomial &Polynomial::operator=(const Polynomial &p) = default;

Polynomial &Polynomial::operator=(Polynomial &&p) noexcept {
    m_coeffs = std::move(p).m_coeffs;
    return *this;
}

Polynomial::~Polynomial() { m_coeffs.clear(); }

double &Polynomial::operator[](int index) { return m_coeffs[index]; }

const double &Polynomial::operator[](int index) const { return m_coeffs[index]; }

int Polynomial::size() const { return (int) m_coeffs.size(); }

Polynomial Polynomial::operator+(const Polynomial &p) const {
    Polynomial res = *this, other = p;
    if (res.size() < other.size())
        for (int i = 0; i < p.size() - size(); ++i)
            res.m_coeffs.push_back(0);
    else if (res.size() > other.size())
        for (int i = 0; i < size() - p.size(); ++i)
            other.m_coeffs.push_back(0);
    for (int i = 0; i < res.size(); ++i)
        res.m_coeffs[i] += other.m_coeffs[i];
    return res;
}

Polynomial &Polynomial::operator+=(const Polynomial &p) {
    *this = *this + p;
    return *this;
}

Polynomial Polynomial::operator-(const Polynomial &p) const {
    Polynomial res = *this, other = p;
    if (res.size() < other.size())
        for (int i = 0; i < p.size() - size(); ++i)
            res.m_coeffs.push_back(0);
    else if (res.size() > other.size())
        for (int i = 0; i < size() - p.size(); ++i)
            other.m_coeffs.push_back(0);
    for (int i = 0; i < res.size(); ++i)
        res.m_coeffs[i] -= other.m_coeffs[i];
    return res;
}

Polynomial &Polynomial::operator-=(const Polynomial &p) {
    *this = *this - p;
    return *this;
}

Polynomial Polynomial::operator*(const Polynomial &p) const {
    Polynomial res;
    for (int i = 0; i < size() + p.size() - 1; ++i)
        res.m_coeffs.push_back(0);
    for (int i = 0; i < size(); ++i)
        for (int j = 0; j < p.size(); ++j)
            res.m_coeffs[i + j] += m_coeffs[i] * p.m_coeffs[j];
    return res;
}

Polynomial Polynomial::operator*(double factor) const {
    Polynomial res = *this;
    for (int i = 0; i < res.size(); ++i)
        res.m_coeffs[i] *= factor;
    return res;
}

Polynomial &Polynomial::operator*=(const Polynomial &p) {
    *this = *this * p;
    return *this;
}

double Polynomial::operator()(double x) const {
    double res = 0;
    for (int i = 0; i < size(); ++i)
        res += m_coeffs[i] * pow(x, i);
    return res;
}

