#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <climits>
#include "poly.h"

using namespace std;
using namespace coen79_lab4;

namespace coen79_lab4 {

	polynomial::polynomial (double c, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		clear();
		coef[exponent] = c;
		current_degree = exponent;
	}

	void polynomial::assign_coef (double c, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		coef[exponent] = c;
		update_current_degree();
	}
	
	void polynomial::add_to_coef (double amount, unsigned int exponent) {
		assert(exponent <= MAXIMUM_DEGREE);
		coef[exponent] += amount;
		update_current_degree();
	}

	void polynomial::clear () {
		int i;
		for(i=0; i<MAXIMUM_DEGREE + 1; i++) {
			coef[i] = 0;
		}
		current_degree = 0;
	}

	void polynomial::update_current_degree() {
		int count = 0;
		int i;
		for(i=0; i<=MAXIMUM_DEGREE; i++) {
			if(coef[i] != 0) {
				count = i;
			}
		}
		current_degree = count;
	}

	//const member functions
	polynomial polynomial::antiderivative() const {
		polynomial anti;
		for(int i = 0; i<MAXIMUM_DEGREE-1; i++) {
			anti.coef[i+1] = coef[i] / (i+1);
		}
		anti.coef[0] = 0;
		anti.update_current_degree();
		return anti;
		/*
		assert(degree() < MAXIMUM_DEGREE);
		polynomial tempPolynomial(0,0);
		int i;
		for(i=current_degree + 1; i>0; i--) {
			tempPolynomial.coef[i] = tempPolynomial.coef[i-1]/(i);
		}
		//tempPolynomial.coef[0] = 0;
		tempPolynomial.update_current_degree();
		return tempPolynomial;*/
	}

	double polynomial::coefficient(unsigned int exponent) const {
		if(exponent > MAXIMUM_DEGREE) {
			return 0;
		} else {
			return coef[exponent];
		}
	}

	double polynomial::definite_integral (double x0, double x1) const {
		if(x0 == x1) {
			return 0;
		}	
		polynomial anti = antiderivative();
		return (anti.eval(x1) - anti.eval(x0));
	}

	unsigned int polynomial::degree() const{
		return current_degree;
	}

	polynomial polynomial::derivative () const {
		polynomial der;
		int i;
		for(i=0; i<MAXIMUM_DEGREE-1; i++) {
			der.coef[i] = coef[i+1] * (i+1);
		}
		der.update_current_degree();
		return der;
	}

	double polynomial::eval(double x) const {
		int i;
		double value = 0;
		for(i=0; i<MAXIMUM_DEGREE; i++) {
			value += coef[i] * pow(x, i);
		}
		return value;
	}

	bool polynomial::is_zero() const {
		int i;
		for(i=0; i<MAXIMUM_DEGREE; i++) {
			if(coef[i] != 0) {
				return false;
			}
		}
		return true;
	}

	unsigned int polynomial::next_term (unsigned int e) const {
		int i;
		for(i=e+1; i<MAXIMUM_DEGREE; i++) {
			if(coef[i] != 0) {
				return i;
			}
		}
		return 0;
	}

	unsigned int polynomial::previous_term (unsigned int e) const {
		int i;
		for(i=e-1; i<MAXIMUM_DEGREE; i--) {
			if(coef[i] != 0) {
				return i;
			}
		}

		return 0;
	}

	polynomial operator +(const polynomial& p1, const polynomial&p2) {
		polynomial temp;
		int i;
		for(i=0; i<polynomial::MAXIMUM_DEGREE; i++) {
			temp.assign_coef (p1.coefficient(i)+p2.coefficient(i), i);
		}
		return temp;
	}

        polynomial operator -(const polynomial& p1, const polynomial& p2) {
                polynomial temp;
                int i;
                for(i=0; i<polynomial::MAXIMUM_DEGREE; i++) {
                        temp.assign_coef (p1.coefficient(i)-p2.coefficient(i), i);
                }
                return temp;
        }

	polynomial operator *(const polynomial& p1, const polynomial &p2) {
		assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
		polynomial temp;
		int i, j;
		for(i=0; i<=p1.degree(); i++) {
			for(j=0; j<=p2.degree(); j++) {
				temp.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j);
			}
		}
		return temp;
	}
	
	std::ostream &operator<<(ostream &out, const polynomial &p) {
        int i;
        unsigned int d = p.degree();
        bool zero = true;
        for(i = d; i >= 0; i--){
            if(p.coefficient(i) != 0) {

                if (p.coefficient(i) >= 0 && i != d) {
                    out << "+ ";
                }
                if (p.coefficient(i) < 0) {
                    out << "- ";
                }

                out << abs (p.coefficient(i));

                if (i != 0 && i != 1) {
                    out << "x^" << i << " ";
                } else if (i == 1) {
                    out << "x ";
                }
            }

        }

        if(zero) out << 0;

        return out;

    }

}
