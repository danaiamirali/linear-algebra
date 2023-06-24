#include <sstream>

class ZERO_DENOMINATOR {
    public:
        ZERO_DENOMINATOR() {
            cout << "Error: Denominator cannot be 0" << endl;
        }
};

class Fraction {

    int numerator;
    int denominator;

    public:

    Fraction(int numerator, int denominator) {

        if (denominator == 0) {
            throw ZERO_DENOMINATOR();
        }

        // Reduce fraction
        int gcd = 1;
        for (int i = 1; i <= numerator && i <= denominator; i++) {
            if (numerator % i == 0 && denominator % i == 0) {
                gcd = i;
            }
        }

        numerator /= gcd;
        denominator /= gcd;

        this->numerator = numerator;
        this->denominator = denominator;
    }

    bool isWhole() const {
        return denominator == 1;
    }

    // Overloaded extraction operator
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        if (f.isWhole()) {
            os << f.numerator;
        } else {
            os << f.numerator << "/" << f.denominator;
        }
        return os;
    }
};