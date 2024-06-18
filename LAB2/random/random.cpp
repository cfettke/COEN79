#include "random.h"
#include <iostream>

using namespace std;

namespace coen79_lab2 {
	//gets numbers and save to class
	rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
		this->seed = seed;
		this->multiplier = multiplier;
		this->increment = increment;
		this->modulus = modulus;
	}
	//sets new seed
	void rand_gen::set_seed(int new_seed) {
		seed = new_seed;
	}
	//generates random number using formula
	int rand_gen::next() {
		seed = (multiplier * seed + increment) % modulus;
		return seed;
	}
	//prints output
	void rand_gen::print_info() {
		cout << "Seed: " << seed << endl;
		cout << "Multiplier: " << multiplier << endl;
		cout << "Increment: " << increment << endl;
		cout << "Modulus: " << modulus << endl;
	}
}
