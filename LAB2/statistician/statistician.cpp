#include <iostream>
#include <stdio.h>
#include "statistician.h"
#include <cassert>
#include <algorithm>

using namespace std;
using namespace coen79_lab2;

namespace coen79_lab2
{	
	//creates statistician class
	statistician::statistician() {
		size = 0.0;
		total = 0.0;
	}
	//gets next number and adjusts values
	void statistician::next(double r) {
		total = total + r;
		size++;
		if (length() == 1 || (r < min)) {
			min = r;
		}
		if (length() == 1 || (r > max)) {
			max = r;
		}
		avg = total/size;
	}
	//resets values
	void statistician::reset() {
		size = 0;
		total = 0.0;
		//min = 0.0;
		//max = 0.0;
		//avg = 0.0;	
	}
	//gets avg
	double statistician::mean() const {
		assert (size > 0);
		return avg;
	}
	//gets min
	double statistician::minimum() const {
		assert (size > 0);
		return min;
	}
	//gets max
	double statistician::maximum() const {
		assert (size > 0);
		return max;
		
	}
	//adds two classes together
	statistician operator +(const statistician& s1, const statistician& s2) {
		statistician temp;
		temp.size = s1.length() + s2.length();
		temp.total = s1.sum() + s2.sum();
		if(s1.minimum() < s2.minimum()) {
			temp.min = s1.minimum();
		} else {
			temp.min = s2.minimum();
		}
		if(s1.maximum() > s2.maximum()) {
			temp.max = s1.maximum();
		} else {
			temp.max = s2.maximum();
		}
		temp.avg = (s1.mean() + s2.mean())/2;
		return temp;
	}
	//checks if two classes are equal
	bool operator ==(const statistician& s1, const statistician& s2) {
		if (s1.length() == 0 && s2.length() == 0) {
			return true;
		}
		if (s1.length() == s2.length() && s1.sum() == s2.sum() && s1.mean() == s2.mean() && s1.maximum() == s2.maximum() && s1.minimum() == s2.minimum()) {
			return true;
		}
		return false;
	}
	//scales class acording to input factor
	statistician operator *(double scale, const statistician& s) {
		statistician scaleStat;
		scaleStat.total = scale * s.sum();
		scaleStat.size = s.length();
		if(scale > 0) {
			scaleStat.min = scale * s.minimum();
			scaleStat.max = scale * s.maximum();
		} else {
			scaleStat.min = scale * s.maximum();
			scaleStat.max = scale * s.minimum();
		}
		scaleStat.avg = scale * s.mean();
		return scaleStat;
	}				
}
