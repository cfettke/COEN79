//pre condition: takes in set of numbers, checks that it is exactly 10 and all are ints
//post condition: outposts reversed number order, returns 0

#include <iostream>
#include <cassert>
#include <string.h>
using namespace std;

int main() {
 	string chars;
	cout << "Input Numbers" << endl;
	cin >> chars;
	int len = chars.length();
	assert(len == 10);
	int i, j, k;
	int num;
	for(i=0; i<10; i++) {
		num = int(chars[i]);
		assert(num > 47 && num < 58);
	}
	k = 0;
	for(j=0; j<5; j++) {			//for loop that runs 5 times 
		for(i=0; i<j; i++) {		//for loop responsible for first spaces
			cout << " ";
		}
		i = 0;
		while(i < 10) {			//while loop that prints numbers in order
			cout << chars[i];
			i++;
		}
		cout << "    ";			//pruints space in middle
		for(i=0; i<j; i++) {		//for loop that prints another space that incriments with each j
			cout << " ";
		}
		i = 0;
		while(i < 10) {			//prints numbers in reverse order by starting at end of string
			cout << chars[9 - i];
			i++;
		}	
		cout << endl;
	}
	return 0;
} 
