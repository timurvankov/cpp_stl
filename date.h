#include <stdexcept>
#include <iostream>
#include <vector>
using namespace std;

vector<int> days = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool is29(int y) {
    if (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0)) {
        return true;
    }
    return false;
}

class Date {
private:
    int d;
    int m;
    int y;

public:
    Date(int d1, int m1, int y1) {
        if (1970 <= y1 && y1 <= 2099 && ((1 <= m1 && m1 <= 12 && 1 <= d1 && d1 <= days[m1]) ||
                                         (m1 == 2 && d1 == 29 && is29(y1)))) {
            d = d1;
            m = m1;
            y = y1;
        } else {
            throw invalid_argument("incorrect data");
        }
    }

    int GetDay() const {
        return d;
    }
    int GetMonth() const {
        return m;
    }
    int GetYear() const {
        return y;
    }

    friend bool operator<(const Date& n, const Date& m);
    friend bool operator!=(const Date& n, const Date& m);

    Date& operator++() {
        d++;
        if (d > days[m] && !(d == 29 && m == 2 && is29(y))) {
            d = 1;
            m++;
        }
        if (m > 12) {
            m = 1;
            y++;
        }
        return *this;
    }
    Date& operator--() {
        d--;
        if (d < 1) {
            --m;
            if (m < 1) {
                m = 12;
                d = 31;
                --y;
            } else {
                if (is29(y) && m == 2) {
                    d = 29;
                } else {
                    d = days[m];
                }
            }
        }
        return *this;
    }
    Date operator+(const int& n) {
        Date ans = *this;
        for (int i = 0; i != n; ++i) {
            ++ans;
        }
        return ans;
    }
    Date operator-(const int& n) {
        Date ans = *this;
        for (int i = 0; i != n; ++i) {
            --ans;
        }
        return ans;
    }
    int operator-(const Date& n) const {
        int counter = 0;
        if (*this < n) {
            Date help = *this;
            while (help != n) {
                ++help;
                --counter;
            }
        } else {
            Date help = n;
            while (help != *this) {
                ++help;
                ++counter;
            }
        }
        return counter;
    }
};

bool operator<(const Date& n, const Date& m) {
    pair<pair<int, int>, int> first = {{n.GetYear(), n.GetMonth()}, n.GetDay()};
    pair<pair<int, int>, int> second = {{m.GetYear(), m.GetMonth()}, m.GetDay()};
    return first < second;
}

bool operator!=(const Date& n, const Date& m) {
    pair<pair<int, int>, int> first = {{n.GetYear(), n.GetMonth()}, n.GetDay()};
    pair<pair<int, int>, int> second = {{m.GetYear(), m.GetMonth()}, m.GetDay()};
    return first != second;
}