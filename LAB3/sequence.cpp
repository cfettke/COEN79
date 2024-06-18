#include "sequence.h"
#include <iostream>
#include <cassert>
#include <cmath>


using namespace std;
using namespace coen79_lab3;

namespace coen79_lab3 {

	//constructor
	sequence::sequence() {
		int i;
		used = 0;
		current_index = 0;
		for(i=0; i<CAPACITY; i++) {
			data[i] = 0;
		}
	}

	void sequence::start() {
		current_index = 0;
	}

	void sequence::end() {
		current_index = used-1;
	}

	void sequence::last() {
		current_index = CAPACITY-1;
	}

	void sequence::advance() {
		//assert(is_item());
		if(current_index < used) {
			current_index++;
		}
	}

	void sequence::retreat() {
		//assert(current_index != 0);
		if(current_index > 0) {
			current_index--;	
		}
	}

	void sequence::insert(const value_type& entry) {
		assert(size() < CAPACITY);
		int i;
		if (used == 0) {
			data[0] = entry;
			current_index = 0;
		} else {
			for(i=used; i>current_index; i--) {
				data[i] = data[i-1];
			}
			data[current_index] = entry;
		}
		used++;
	}

	void sequence::attach(const value_type& entry) {
		assert(size() < CAPACITY);
		int i;
		if(used==0) {
			data[0] = entry;
			current_index = 0;
		} else { 
			for(i=used; i>current_index+1; i--) {
				data[i] = data[i-1];
			}
			data[current_index++] = entry;
		}
		used++;
	}

	void sequence::remove_current() {
		assert(is_item());
		int i;
		for(i=current_index; i<used-1; i++) {
			data[i] = data[i+1];
		}
		used--;
	}
		
	void sequence::insert_front(const value_type& entry) {
		assert(size()<CAPACITY);
		start();
		insert(entry);
	}

	void sequence::attach_back(const value_type& entry) {
		assert(size()<CAPACITY);
		current_index = used;
		attach(entry);
	}

	void sequence::remove_front() {
		assert(is_item());
		current_index = 0;
		remove_current();
	}

	void sequence::operator +=(const sequence& rhs) {
		int rhs_pos = 0;
		int i;
		for(i=used; i<used+rhs.used; i++) {
			data[i] = rhs.data[rhs_pos++];
		}
		used += rhs.used;
	}
	
	sequence::size_type sequence::size() const {
		return used;
	}

	bool sequence::is_item() const {
		if(current_index < used) {
			return true;
		} else {
			return false;
		}

	}

	sequence::value_type sequence::current() const {
		assert(is_item());
		return data[current_index];
	}

	sequence::value_type sequence::operator[](int index) const {
		assert(index < used);
		return data[index];
	}

	double sequence::mean() const {
		int i;
		sequence::value_type total = 0;
		for(i=0; i<used; i++) {
			total += data[i];
		}
		total = total/used;
		return total;
	}

	double sequence::standardDeviation() const {
		int i;
		sequence::value_type total = 0;
		for(i=0; i<used; i++) {
			total += (data[i] - mean())*(data[i]-mean());
		}
		total = sqrt(total/used);
		return total;
	}

	sequence operator +(const sequence& lhs, const sequence& rhs) {
		assert(lhs.size() + rhs.size() <= sequence::CAPACITY);
		sequence newSequence;
		//newSequence = lhs + rhs;
		newSequence += lhs;
		newSequence += rhs;
		return newSequence;
	}

	sequence::value_type summation(const sequence &tempSequence) {
		int i;
		sequence::value_type sum;
		sum = 0;
		for(i=0; i<tempSequence.size(); i++) {
			sum += tempSequence[i];
		}
		return sum;
	}
}
			








