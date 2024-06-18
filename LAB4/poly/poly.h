#ifndef COEN79_POLY_H
#define COEN79_POLY_H
#include <iostream> 
namespace coen79_lab4
{
class polynomial
    {
    public:

        static const unsigned int MAXIMUM_DEGREE = 29;

        polynomial(double c = 0.0, unsigned int exponent = 0);

        void assign_coef(double coefficient, unsigned int exponent);
        void add_to_coef(double amount, unsigned int exponent);
        void clear( );

        polynomial antiderivative( ) const;
        double coefficient(unsigned int exponent) const;
        double definite_integral(double x0, double x1) const;
        unsigned int degree( ) const;
        polynomial derivative( ) const;
        double eval(double x) const;
        bool is_zero( ) const;
        unsigned int next_term(unsigned int e) const;
        unsigned int previous_term(unsigned int e) const;
	void update_current_degree(); 
        double operator( ) (double x) const { return eval(x); }
    private:
        double coef[MAXIMUM_DEGREE+1];
        unsigned int current_degree;
    };
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    polynomial operator -(const polynomial& p1, const polynomial& p2);
    polynomial operator *(const polynomial& p1, const polynomial& p2);
    
    std::ostream& operator << (std::ostream& out, const polynomial& p);
}
#endif
