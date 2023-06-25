#include <sstream>

using std::cout, std::endl, std::string, std::stringstream;

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


    /*
     * ========================
     *       CONSTRUCTORS
     * ========================
    */
    Fraction(int numerator, int denominator) {

        if (denominator == 0) {
            throw ZERO_DENOMINATOR();
        }

        this->numerator = numerator;
        this->denominator = denominator;

        reduce();
    }

    Fraction(int numerator) : Fraction(numerator, 1) {}

    Fraction() : Fraction(0, 1) {}


    /*
     * ========================
     *        OPERATORS
     * ========================
    */

    // Overloaded extraction operator
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        if (f.isWhole()) {
            os << f.numerator;
        } else {
            os << f.numerator << "/" << f.denominator;
        }
        return os;
    }

    // Overloaded division operator
    friend Fraction operator/(const Fraction& f1, const Fraction& f2) {
        return Fraction(f1.numerator * f2.denominator, f1.denominator * f2.numerator);
    }

    // Overloaded multiplication operator
    friend Fraction operator*(const Fraction& f1, const Fraction& f2) {
        return Fraction(f1.numerator * f2.numerator, f1.denominator * f2.denominator);
    }

    // Overloaded addition operator
    friend Fraction operator+(const Fraction& f1, const Fraction& f2) {
        return Fraction(f1.numerator * f2.denominator + f2.numerator * f1.denominator, 
        f1.denominator * f2.denominator);
    }

    friend Fraction operator+(const Fraction& f1, int i) {
        return f1 + Fraction(i);
    }

    friend Fraction operator+=(Fraction& f1, const Fraction& f2) {
        f1 = f1 + f2;
        return f1;
    }

    friend Fraction operator+=(Fraction& f1, int i) {
        f1 = f1 + i;
        return f1;
    }

    // Overloaded subtraction operator
    friend Fraction operator-(const Fraction& f1, const Fraction& f2) {
        return Fraction(f1.numerator * f2.denominator - f2.numerator * f1.denominator, 
        f1.denominator * f2.denominator);
    }

    // Overloaded equals operator
    friend bool operator==(const Fraction& f1, const Fraction& f2) {
        return f1.numerator == f2.numerator && f1.denominator == f2.denominator;
    }

    friend bool operator==(const Fraction& f1, int i) {
        return f1 == Fraction(i);
    }

    // Overloaded not equals operator
    friend bool operator!=(const Fraction& f1, const Fraction& f2) {
        return !(f1 == f2);
    }

    friend bool operator!=(const Fraction& f1, int i) {
        return !(f1 == i);
    }

    // Overloaded less than operator
    friend bool operator<(const Fraction& f1, const Fraction& f2) {
        return f1.numerator * f2.denominator < f2.numerator * f1.denominator;
    }

    friend bool operator>= (const Fraction& f1, const Fraction& f2) {
        return !(f1 < f2);
    }

    
    /*
     * ========================
     *     FRACTION HELPERS
     * ======================== 
    */

    // Reduces fraction to lowest terms
    void reduce() {
        int gcd = getGCD(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }

    // Returns greatest common divisor of two numbers
    int getGCD(int a, int b) {
        int gcd = 1;
        for (int i = 1; i <= numerator && i <= denominator; i++) {
            if (numerator % i == 0 && denominator % i == 0) {
                gcd = i;
            }
        }

        return gcd;
    }

    // Returns true if fraction is a whole number
    bool isWhole() const {
        return denominator == 1;
    }
};