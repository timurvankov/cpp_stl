#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

template <typename T>
class Polynomial {
private:
    map<size_t, T> coef;

public:
    Polynomial<T>() = default;
    Polynomial<T>(const vector<T>& n) {
        for (size_t i = 0; i != n.size(); ++i) {
            if (n[i] != 0) {
                coef[i] = n[i];
            }
        }
    }
    explicit Polynomial<T>(const T& n) {
        if (n != 0) {
            coef[0] = n;
        } else {
            coef = {};
        }
    }
    template <typename Iterator>
    Polynomial<T>(Iterator first, Iterator end) {
        size_t i = 0;
        while (first != end) {
            if (*first != 0) {
                coef[i] = *first;
            }
            ++first;
            ++i;
        }
    }
    int Degree() const {
        int ans = -1;
        for (auto it = coef.begin(); it != coef.end(); ++it) {
            ans = max(static_cast<int>((*it).first), ans);
        }
        return ans;
    }
    const T operator[](size_t i) const {
        if (coef.count(i))
            return (*coef.find(i)).second;
        return T(0);
    }
    T operator[](size_t i) {
        if (coef.count(i))
            return (*coef.find(i)).second;
        return T(0);
    }

    T operator()(const T& n) const {
        vector<T> help(static_cast<size_t>(Degree() + 1));
        for (auto it = begin(); it != end(); ++it) {
            help[(*it).first] = (*it).second;
        }
        T ans = T(0);
        T now = T(1);
        for (T c : help) {
            ans += c * now;
            now *= n;
        }
        return ans;
    }

    typename map<size_t, T>::const_iterator begin() const {
        return coef.begin();
    }
    typename map<size_t, T>::const_iterator end() const {
        return coef.end();
    }
    typename map<size_t, T>::iterator begin() {
        return coef.begin();
    }
    typename map<size_t, T>::iterator end() {
        return coef.end();
    }
};

template <typename T>
class vecPolynomial {
private:
    vector<T> coef;

public:
    vecPolynomial<T>() = default;
    vecPolynomial<T>(const vector<T>& n) {
        coef = n;
        size_t i = coef.size();
        while (i != 0 && coef[i - 1] == T(0)) {
            --i;
        }
        coef.resize(i);
    }
    explicit vecPolynomial<T>(const T& n) {
        if (n != T(0)) {
            coef = {n};
        }
        size_t i = coef.size();
        while (i != 0 && coef[i - 1] == T(0)) {
            --i;
        }
        coef.resize(i);
    }
    vecPolynomial<T>(const Polynomial<T>& n) {
        if (n.Degree() == -1) {
            coef = vector<T>();
        } else {
            auto first = n.begin();
            auto end = n.end();
            coef.resize(static_cast<size_t>(n.Degree() + 1));
            while (first != end) {
                if ((*first).second != 0)
                    coef[(*first).first] = (*first).second;
                ++first;
            }
        }
    }
    template <typename T1>
    friend Polynomial<T1> to_p(const vecPolynomial<T1>& n);
    template <typename Iterator>
    vecPolynomial<T>(Iterator first, Iterator end) {
        while (first != end) {
            coef.push_back(*first++);
        }
        size_t i = coef.size();
        while (i != 0 && coef[i - 1] == T(0)) {
            --i;
        }
        coef.resize(i);
    }
    int Degree() const {
        if (coef.empty()) {
            return -1;
        }
        return static_cast<int>(coef.size() - 1);
    }
    size_t size() const {
        return coef.size();
    }
    T operator[](size_t i) const {
        if (i > static_cast<size_t>((*this).Degree())) {
            return static_cast<T>(0);
        }
        return coef[i];
    }


    typename vector<T>::const_iterator begin() const {
        return coef.begin();
    }
    typename vector<T>::const_iterator end() const {
        return coef.end();
    }
    typename vector<T>::iterator begin() {
        return coef.begin();
    }
    typename vector<T>::iterator end() {
        return coef.end();
    }

    T operator()(const T& n) const {
        T ans = T(0);
        T now = T(1);
        for (T c : coef) {
            ans += c * now;
            now *= n;
        }
        return ans;
    }

    vecPolynomial<T>& operator+=(const vecPolynomial<T>& n) {
        if ((*this).Degree() < n.Degree()) {
            coef.resize(n.Degree() + 1);
        }
        for (size_t i = 0; i != static_cast<size_t>(n.Degree() + 1); ++i) {
            coef[i] += n[i];
        }
        size_t i = coef.size();
        while (i != 0 && coef[i - 1] == T(0)) {
            --i;
        }
        coef.resize(i);
        return *this;
    }
    vecPolynomial<T> operator+(const vecPolynomial<T>& n) const {
        vecPolynomial<T> ans = *this;
        return ans += n;
    }
    vecPolynomial<T>& operator-=(const vecPolynomial<T>& n) {
        if ((*this).Degree() < n.Degree()) {
            coef.resize(n.Degree() + 1);
        }
        for (size_t i = 0; i != static_cast<size_t>(n.Degree() + 1); ++i) {
            coef[i] -= n[i];
        }
        size_t i = coef.size();
        while (i != 0 && coef[i - 1] == T(0)) {
            --i;
        }
        coef.resize(i);
        return *this;
    }
    vecPolynomial<T> operator-(const vecPolynomial<T>& n) const {
        vecPolynomial<T> ans = *this;
        return ans -= n;
    }
    vecPolynomial<T>& operator*=(const vecPolynomial<T>& n) {
        vecPolynomial<T> help = *this;
        if (n.Degree() == -1 || (*this).Degree() == -1) {
            *this = vecPolynomial<T>();
            return *this;
        } else {
            coef = vector<T>((*this).Degree() + n.Degree() + 1);
        }
        for (size_t i = 0; i != static_cast<size_t>(n.Degree() + 1); ++i) {
            for (size_t j = 0; j != static_cast<size_t>(help.Degree() + 1); ++j) {
                coef[i + j] += n[i] * help[j];
            }
        }
        return *this;
    }
    vecPolynomial<T> operator*(const vecPolynomial<T>& n) const {
        vecPolynomial<T> ans = *this;
        return ans *= n;
    }
    vecPolynomial<T>& operator/=(const vecPolynomial<T>& n) {
        if (size() == 0 || n.Degree() == -1) {
            return *this;
        } else if (n.size() > size()) {
            *this = vecPolynomial<T>(T(0));
            return *this;
        }
        vector<T> help(size() - n.size() + 1);
        while (Degree() >= n.Degree() && size() > 0) {
            T now = (*this)[size() - 1] / n[n.size() - 1];
            help[size() - n.size()] = now;
            vector<T> new_vecPolynomial(size() - n.size() + 1);
            new_vecPolynomial.back() = now;
            *this -= n * new_vecPolynomial;
        }
        *this = vecPolynomial<T>(help);
        size_t i = coef.size();
        while (i != 0 && coef[i - 1] == T(0)) {
            --i;
        }
        coef.resize(i);
        return *this;
    }
    vecPolynomial operator/(const vecPolynomial<T>& n) const {
        vecPolynomial<T> ans = *this;
        return ans /= n;
    }
    vecPolynomial& operator%=(const vecPolynomial<T>& n) {
        *this = *this - (*this / n) * n;
        return *this;
    }
    vecPolynomial operator%(const vecPolynomial<T>& n) const {
        vecPolynomial<T> ans = *this;
        return ans %= n;
    }
    template <typename T1>
    friend vecPolynomial<T1> gcd(vecPolynomial<T1> a, vecPolynomial<T1> b);
    vecPolynomial<T> operator,(const vecPolynomial<T>& n) const {
        vecPolynomial<T> ans = gcd(*this, n);
        return ans;
    }
    vecPolynomial<T> operator&(const vecPolynomial& n) const {
        if (size() == 0) {
            return vecPolynomial<T>(T(0));
        }
        vecPolynomial<T> ans = vecPolynomial<T>((*this)[0]);
        vecPolynomial<T> now = n;
        for (size_t i = 1; i != size(); ++i) {
            ans += now * (*this)[i];
            now *= n;
        }
        return ans;
    }

    bool operator==(const vecPolynomial<T>& m) const {
        return coef == m.coef;
    }
};

template <typename T>
Polynomial<T> to_p(const vecPolynomial<T>& a) {
    return Polynomial<T>(a.coef);
}

template <typename T>
vecPolynomial<T> gcd(vecPolynomial<T> a, vecPolynomial<T> b) {
    if (b.Degree() == -1) {
        if (a.size() != 0 && a[a.size() - 1] != T(1)) {
            for (size_t i = 0; i != a.size(); ++i) {
                a.coef[i] /= a.coef[a.size() - 1];
            }
        }
        return a;
    }
    return gcd(b, a % b);
}

template <typename T>
vecPolynomial<T>& operator+=(vecPolynomial<T>& n, const T& m) {
    n += vecPolynomial<T>(m);
    return n;
}
template <typename T>
vecPolynomial<T> operator+(const vecPolynomial<T>& n, const T& m) {
    vecPolynomial<T> ans = n;
    return ans += m;
}
template <typename T>
vecPolynomial<T> operator+(const T& m, const vecPolynomial<T>& n) {
    vecPolynomial<T> ans = vecPolynomial<T>(m);
    return ans += n;
}
template <typename T>
vecPolynomial<T>& operator-=(vecPolynomial<T>& n, const T& m) {
    n -= vecPolynomial<T>(m);
    return n;
}
template <typename T>
vecPolynomial<T> operator-(const vecPolynomial<T>& n, const T& m) {
    vecPolynomial<T> ans = n;
    return ans -= m;
}
template <typename T>
vecPolynomial<T> operator-(const T& m, const vecPolynomial<T>& n) {
    vecPolynomial<T> ans = vecPolynomial<T>(m);
    return ans -= n;
}
template <typename T>
vecPolynomial<T>& operator*=(vecPolynomial<T>& n, const T& m) {
    n *= vecPolynomial<T>(m);
    return n;
}
template <typename T>
vecPolynomial<T> operator*(const vecPolynomial<T>& n, const T& m) {
    vecPolynomial<T> ans = n;
    return ans *= m;
}
template <typename T>
vecPolynomial<T> operator*(const T& m, const vecPolynomial<T>& n) {
    vecPolynomial<T> ans = vecPolynomial<T>(m);
    return ans *= n;
}
template <typename T>
bool operator==(const vecPolynomial<T>& n, const T& m) {
    return n == vecPolynomial<T>(m);
}
template <typename T>
bool operator==(const T& n, const vecPolynomial<T>& m) {
    return m == n;
}
template <typename T>
bool operator!=(const vecPolynomial<T>& n, const vecPolynomial<T>& m) {
    return !(n == m);
}
template <typename T>
bool operator!=(const vecPolynomial<T>& n, const T& m) {
    return !(n == m);
}
template <typename T>
bool operator!=(const T& n, const vecPolynomial<T>& m) {
    return !(n == m);
}

template <typename T>
ostream& operator<<(ostream& out, const vecPolynomial<T>& n) {
    if (n.size() == 0) {
        out << 0;
        return out;
    }
    for (size_t i = n.size() - 1; i != 0; --i) {
        if (n[i] != T(0)) {
            if (i == n.size() - 1) {
                if (n[i] == T(-1)) {
                    out << "-";
                } else if (n[i] != T(1)) {
                    out << n[i] << "*";
                }
                out << "x";
                if (i != 1) {
                    out << "^" << i;
                }
            } else {
                if (n[i] == T(-1)) {
                    out << "-";
                } else if (n[i] != T(1)) {
                    if (n[i] > T(0)) {
                        out << "+";
                    }
                    out << n[i] << "*";
                } else {
                    out << "+";
                }
                out << "x";
                if (i != 1) {
                    out << "^" << i;
                }
            }
        }
    }
    if (n[0] > T(0) && n.size() != 1) {
        out << "+";
    }
    if (n[0] != T(0)) {
        out << n[0];
    }
    return out;
}
template <typename T>
ostream& operator<<(ostream& out, const Polynomial<T>& n) {
    out << vecPolynomial<T>(n);
    return out;
}

template <typename T>
Polynomial<T>& operator+=(Polynomial<T>& n, const Polynomial<T>& m) {
    n = to_p(vecPolynomial<T>(n) + vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T>& operator+=(Polynomial<T>& n, const T& m) {
    n = to_p(vecPolynomial<T>(n) + vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T> operator+(const Polynomial<T>& n, const Polynomial<T>& m) {
    return to_p(vecPolynomial<T>(n) + vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator+(const Polynomial<T>& n, const T& m) {
    return to_p(vecPolynomial<T>(n) + vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator+(const T& m, Polynomial<T>& n) {
    return to_p(vecPolynomial<T>(n) + vecPolynomial<T>(m));
}


template <typename T>
Polynomial<T>& operator-=(Polynomial<T>& n, const Polynomial<T>& m) {
    n = to_p(vecPolynomial<T>(n) - vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T>& operator-=(Polynomial<T>& n, const T& m) {
    n = to_p(vecPolynomial<T>(n) - vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T> operator-(const Polynomial<T>& n, const Polynomial<T>& m) {
    return to_p(vecPolynomial<T>(n) - vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator-(const Polynomial<T>& n, const T& m) {
    return to_p(vecPolynomial<T>(n) - vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator-(const T& m, Polynomial<T>& n) {
    return to_p(vecPolynomial<T>(n) - vecPolynomial<T>(m));
}

template <typename T>
Polynomial<T>& operator*=(Polynomial<T>& n, const Polynomial<T>& m) {
    n = to_p(vecPolynomial<T>(n) * vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T>& operator*=(Polynomial<T>& n, const T& m) {
    n = to_p(vecPolynomial<T>(n) * vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T> operator*(const Polynomial<T>& n, const Polynomial<T>& m) {
    return to_p(vecPolynomial<T>(n) * vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator*(const Polynomial<T>& n, const T& m) {
    return to_p(vecPolynomial<T>(n) * vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator*(const T& m, Polynomial<T>& n) {
    return to_p(vecPolynomial<T>(n) * vecPolynomial<T>(m));
}

template <typename T>
Polynomial<T>& operator/=(Polynomial<T>& n, const Polynomial<T>& m) {
    n = to_p(vecPolynomial<T>(n) / vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T>& operator/=(Polynomial<T>& n, const T& m) {
    n = to_p(vecPolynomial<T>(n) / vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T> operator/(const Polynomial<T>& n, const Polynomial<T>& m) {
    return to_p(vecPolynomial<T>(n) / vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator/(const Polynomial<T>& n, const T& m) {
    return to_p(vecPolynomial<T>(n) / vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T>& operator%=(Polynomial<T>& n, const Polynomial<T>& m) {
    n = to_p(vecPolynomial<T>(n) % vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T>& operator%=(Polynomial<T>& n, const T& m) {
    n = to_p(vecPolynomial<T>(n) % vecPolynomial<T>(m));
    return n;
}
template <typename T>
Polynomial<T> operator%(const Polynomial<T>& n, const Polynomial<T>& m) {
    return to_p(vecPolynomial<T>(n) % vecPolynomial<T>(m));
}
template <typename T>
Polynomial<T> operator%(const Polynomial<T>& n, const T& m) {
    return to_p(vecPolynomial<T>(n) % vecPolynomial<T>(m));
}

template <typename T>
bool operator==(const Polynomial<T>& n, const Polynomial<T>& m) {
    return vecPolynomial<T>(n) == vecPolynomial<T>(m);
}
template <typename T>
bool operator==(const Polynomial<T>& n, const T& m) {
    return n == Polynomial<T>(m);
}
template <typename T>
bool operator==(const T& n, const Polynomial<T>& m) {
    return m == n;
}
template <typename T>
bool operator!=(const Polynomial<T>& n, const Polynomial<T>& m) {
    return !(n == m);
}
template <typename T>
bool operator!=(const Polynomial<T>& n, const T& m) {
    return !(n == m);
}
template <typename T>
bool operator!=(const T& n, const Polynomial<T>& m) {
    return !(n == m);
}

template <typename T>
Polynomial<T> operator,(const Polynomial<T>& n, const Polynomial<T>& m) {
    return to_p(gcd(vecPolynomial<T>(n), vecPolynomial<T>(m)));
}
template <typename T>
Polynomial<T> operator&(const Polynomial<T>& n, const Polynomial<T>& m) {
    return to_p(vecPolynomial<T>(n) & vecPolynomial<T>(m));
}