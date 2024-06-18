#ifndef COEN79_SEQUENCE_H
#define COEN79_SEQUENCE_H

#include <iostream>

namespace coen79_lab3 {
    
	class sequence {
	public:
		//typedefs
		typedef double value_type;
		typedef std::size_t size_type;
		static const size_type CAPACITY = 30;

		sequence();
		//members
		void start();
		void end();
		void last();
		void advance();
		void retreat();
		void insert(const value_type& entry);
		void attach(const value_type& entry);
		void remove_current();
		void insert_front(const value_type& entry);
		void attach_back(const value_type& entry);
		void remove_front();
		void operator +=(const sequence& rhs);

		//const member funcs
		size_type size() const;
		bool is_item( ) const;
		value_type current() const;
		value_type operator[](int index) const;
		double mean() const;
		double standardDeviation() const;
	private:
		value_type data[CAPACITY];
		size_type used;
		size_type current_index;		
	};
	//non member functions
	sequence operator +(const sequence& lhs, const sequence& rhs);
	sequence::value_type summation(const sequence &s);
}
#endif
