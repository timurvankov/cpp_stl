#include <cmath>
#include <iostream>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex() : real(0), imag(0) {}

    Complex(double x, double y) : real(x), imag(y) {}

    explicit Complex(double x) : real(x), imag(0) {}

    double Re() const {
        return real;
    }

    double Im() const {
        return imag;
    }

    friend double abs(const Complex &n);

    Complex operator+() const {
        return Complex(real, imag);
    }

    Complex operator-() const {
        return Complex(-real, -imag);
    }

    Complex operator+(const Complex &n) const {
        return Complex(n.Re() + real, n.Im() + imag);
    }

    Complex operator-(const Complex &n) const {
        return Complex(real - n.Re(), imag - n.Im());
    }

    Complex operator*(const Complex &n) const {
        return Complex(real * n.Re() - imag * n.Im(), real * n.Im() + imag * n.Re());
    }

    Complex operator/(const Complex &n) const {
        return Complex((real * n.Re() + imag * n.Im()) / (abs(n) * abs(n)),
                       (n.Re() * imag - n.Im() * real) / (abs(n) * abs(n)));
    }

    bool operator==(const Complex &n) const {
        return real == n.Re() && imag == n.Im();
    }

    bool operator!=(const Complex &n) const {
        return real != n.Re() || imag != n.Im();
    }
};

double abs(const Complex &n) {
    return sqrt(n.Re() * n.Re() + n.Im() * n.Im());
}


Complex operator+(const double &n, const Complex &m) {
    return Complex(n + m.Re(), m.Im());
}

Complex operator+(const Complex &n, const double &m) {
    return Complex(n.Re() + m, n.Im());
}

Complex operator-(const double &n, const Complex &m) {
    return Complex(n - m.Re(), -m.Im());
}

Complex operator-(const Complex &n, const double &m) {
    return Complex(n.Re() - m, n.Im());
}

Complex operator*(const double &n, const Complex &m) {
    return Complex(m.Re() * n, m.Im() * n);
}

Complex operator*(const Complex &n, const double &m) {
    return Complex(n.Re() * m, n.Im() * m);
}

Complex operator/(const Complex &n, const double &m) {
    return Complex(n.Re() / m, n.Im() / m);
}

Complex operator/(const double &n, const Complex &m) {
    return Complex(m.Re() * n / (abs(m) * abs(m)), -m.Im() * n / (abs(m) * abs(m)));
}

bool operator==(const Complex &n, const double &m) {
    return m == n.Re() && 0 == n.Im();
}

bool operator==(const double &n, const Complex &m) {
    return n == m.Re() && 0 == m.Im();
}

bool operator!=(const Complex &n, const double &m) {
    return m != n.Re() || 0 != n.Im();
}

bool operator!=(const double &n, const Complex &m) {
    return n != m.Re() || 0 != m.Im();
}
