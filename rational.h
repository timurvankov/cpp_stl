using namespace std;

int gcd(int a, int b) {
    return b ? gcd (b, a % b) : a;
}

class Rational {
public:
    int ch;
    int zn;

public:
    Rational() {
        ch = 0;
        zn = 1;
    }
    Rational(int ch1, int zn1) {
        ch = ch1 / gcd(ch1, zn1);
        zn = zn1 / gcd(ch1, zn1);
        if (zn < 0) {
            zn *= -1;
            ch *= -1;
        }
    }

    Rational operator+() const {
        return *this;
    }
    Rational operator-() const {
        return Rational(-ch, zn);
    }

    int numerator() const {
        return ch;
    }
    int denominator() const {
        return zn;
    }

    Rational operator+(const Rational& n) const {
        int new_ch = ch * n.zn + n.ch * zn;
        int new_zn = zn * n.zn;
        return Rational(new_ch / gcd(new_ch, new_zn), new_zn / gcd(new_ch, new_zn));
    }
    Rational operator-(const Rational& n) const {
        int new_ch = ch * n.zn - n.ch * zn;
        int new_zn = zn * n.zn;
        return Rational(new_ch / gcd(new_ch, new_zn), new_zn / gcd(new_ch, new_zn));
    }
    Rational operator*(const Rational& n) const {
        int new_ch = ch * n.ch;
        int new_zn = zn * n.zn;
        return Rational(new_ch / gcd(new_ch, new_zn), new_zn / gcd(new_ch, new_zn));
    }
    Rational operator/(const Rational& n) const {
        int new_ch = ch * n.zn;
        int new_zn = zn * n.ch;
        return Rational(new_ch / gcd(new_ch, new_zn), new_zn / gcd(new_ch, new_zn));
    }
};

Rational operator+(const Rational& n, const int& m) {
    Rational help = Rational(m, 1);
    return n + help;
}
Rational operator-(const Rational& n, const int& m) {
    Rational help = Rational(m, 1);
    return n - help;
}
Rational operator*(const Rational& n, const int& m) {
    Rational help = Rational(m, 1);
    return n * help;
}
Rational operator/(const Rational& n, const int& m) {
    Rational help = Rational(m, 1);
    return n / help;
}
Rational operator+(const int& n, const Rational& m) {
    return m + n;
}
Rational operator-(const int& n, const Rational& m) {
    return -m + n;
}
Rational operator*(const int& n, const Rational& m) {
    return m * n;
}
Rational operator/(const int& n, const Rational& m) {
    Rational one = Rational(1, 1);
    return n * (one / m);
}

template <typename T>
Rational operator+=(Rational& n, const T& m) {
    n = n + m;
    return n;
}
template <typename T>
Rational operator*=(Rational& n, const T& m) {
    n = n * m;
    return n;
}
template <typename T>
Rational operator-=(Rational& n, const T& m) {
    n = n - m;
    return n;
}
template <typename T>
Rational operator/=(Rational& n, const T& m) {
    n = n / m;
    return n;
}

bool operator==(const Rational& n, const Rational& m) {
    return n.ch == m.ch && n.zn == m.zn;
}
bool operator!=(const Rational& n, const Rational& m) {
    return !(n == m);
}

Rational& operator++(Rational& n) {
    n += 1;
    return n;
}
Rational& operator--(Rational& n) {
    n -= 1;
    return n;
}
Rational operator++(Rational& n, int) {
    auto m = n;
    n += 1;
    return m;
}
Rational operator--(Rational& n, int) {
    auto m = n;
    n -= 1;
    return m;
}