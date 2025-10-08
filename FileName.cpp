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
    }

public:
    Money() : hryvnia(0), kopiyky(0) {}
    Money(long grn, unsigned char kop) : hryvnia(grn), kopiyky(kop) { normalize(); }
    Money(long long totalKopecks) {
        hryvnia = totalKopecks / 100;
        kopiyky = totalKopecks % 100;
        normalize();
    }
    Money(const Money& other) {
        hryvnia = other.hryvnia;
        kopiyky = other.kopiyky;
    }

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
    Money m1;
    Money m2(10, 50);
    Money m3(12345);
    Money m4(m2);

    cout << "m1: " << m1.toString() << endl;
    cout << "m2: " << m2.toString() << endl;
    cout << "m3: " << m3.toString() << endl;
    cout << "m4: " << m4.toString() << endl;

    Money sum = m2 + m3;
    cout << "Sum: " << sum.toString() << endl;

    Money diff = m2 - m3;
    cout << "Difference: " << diff.toString() << endl;

    Money multSum = sum * 1.5;
    cout << "Sum * 1.5: " << multSum.toString() << endl;

    Money divSum = sum / 1.5;
    cout << "Sum / 1.5: " << divSum.toString() << endl;

    if (m2 > m3) cout << "m2 > m3" << endl;
    else cout << "m2 < m3" << endl;

    return 0;
}
