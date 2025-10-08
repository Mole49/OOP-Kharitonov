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
};

int main() {
    Money m1, m2;
    cout << "Enter first amount:" << endl;
    m1.Read();
    cout << "Enter second amount:" << endl;
    m2.Read();

    cout << "First: "; m1.Display();
    cout << "Second: "; m2.Display();

    Money sum = m1 + m2;
    cout << "Sum: " << sum.toString() << endl;

    Money diff = m1 - m2;
    cout << "Difference: " << diff.toString() << endl;

    Money mult = sum * 1.5;
    cout << "Sum * 1.5: " << mult.toString() << endl;

    Money div = sum / 1.5;
    cout << "Sum / 1.5: " << div.toString() << endl;

    return 0;
}