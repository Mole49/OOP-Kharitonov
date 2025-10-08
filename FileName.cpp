#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class Money {
private:
    long hryvnia;
    unsigned char kopiyky;

    void normalize() {
        if (kopiyky >= 100) {
            hryvnia += kopiyky / 100;
            kopiyky %= 100;
        }
        if (hryvnia > 0 && kopiyky < 0) {
            hryvnia -= 1;
            kopiyky += 100;
        }
    }

public:
    Money() : hryvnia(0), kopiyky(0) {}
    Money(long grn, unsigned char kop) : hryvnia(grn), kopiyky(kop) { normalize(); }

    void Init(long grn, unsigned char kop) {
        hryvnia = grn;
        kopiyky = kop;
        normalize();
    }

    void Read() {
        cout << "Enter hryvnias: ";
        cin >> hryvnia;
        int k;
        cout << "Enter kopecks (0-99): ";
        cin >> k;
        kopiyky = (unsigned char)(k % 100);
        normalize();
    }

    void Display() const {
        cout << hryvnia << "," << setw(2) << setfill('0') << (int)kopiyky << " UAH" << endl;
    }

    string toString() const {
        stringstream ss;
        ss << hryvnia << "," << setw(2) << setfill('0') << (int)kopiyky << " UAH";
        return ss.str();
    }

    long long toKopecks() const {
        return (long long)hryvnia * 100 + kopiyky;
    }

    Money operator+(const Money& other) const {
        long long total = toKopecks() + other.toKopecks();
        return Money(total / 100, total % 100);
    }

    Money operator-(const Money& other) const {
        long long a = toKopecks();
        long long b = other.toKopecks();
        if (a < b) swap(a, b);
        long long total = a - b;
        return Money(total / 100, total % 100);
    }

    Money operator*(double num) const {
        long long total = (long long)(toKopecks() * num);
        return Money(total / 100, total % 100);
    }

    Money operator/(double num) const {
        long long total = (long long)(toKopecks() / num);
        return Money(total / 100, total % 100);
    }

    bool operator==(const Money& other) const { return toKopecks() == other.toKopecks(); }
    bool operator!=(const Money& other) const { return !(*this == other); }
    bool operator<(const Money& other)  const { return toKopecks() < other.toKopecks(); }
    bool operator>(const Money& other)  const { return toKopecks() > other.toKopecks(); }
    bool operator<=(const Money& other) const { return !(*this > other); }
    bool operator>=(const Money& other) const { return !(*this < other); }
};

int main() {
    Money m1, m2;
    cout << "Enter first amount:" << endl;
    m1.Read();
    cout << "Enter second amount:" << endl;
    m2.Read();

    cout << "First amount: "; m1.Display();
    cout << "Second amount: "; m2.Display();

    Money sum = m1 + m2;
    cout << "Sum: " << sum.toString() << endl;

    Money diff = m1 - m2;
    cout << "Difference: " << diff.toString() << endl;

    double factor = 1.5;

    Money multSum = sum * factor;
    cout << "Sum * " << factor << ": " << multSum.toString() << endl;

    Money divSum = sum / factor;
    cout << "Sum / " << factor << ": " << divSum.toString() << endl;

    if (m1 > m2) cout << "First amount is greater than second." << endl;
    else cout << "First amount is not greater than second." << endl;

    return 0;
}