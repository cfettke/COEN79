//pre condition: gets time and srand to genrate random array
//post condition: goes until yes or all numbers have been guessed, returns 0

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main() {
	int i;
	int array[21];
	int count[21];
	for(i=0; i < 21; i++) {
		array[i] = i;
	}
	int random1;
	int random2;
	int temp;
	srand(time(NULL));
	for(i=0; i<110; i++) {
		random1 = rand() % 21;
		random2 = rand() % 21;
		temp = array[random1];
		array[random1] = array[random2];
		array[random2] = temp;
	}

	int interations = 0;
	string input;
	string y = "y";
	string n = "n";
	string Y = "Y";
	string N = "N";
	string yes = "yes";
	string no = "no";
	string Yes = "Yes";
	string No = "No";
	int inputFlag = 0;
	int k;
	for(i=0; i<21; i++) {
		cout << "Is your number " << array[i] << "?\n";
		while(inputFlag == 0) {			//while loop that goes until a correct input is given, either some from of yes or no, that breaks when there is a correct input
			cin >> input;
			if(0 == input.compare(y) || 0 == input.compare(Y) || 0 == input.compare(yes) || 0 == input.compare(Yes)) {
				inputFlag = 1;
			} else if (0 == input.compare(n) || 0 == input.compare(N) || 0 == input.compare(no) || 0 == input.compare(No)) {
                                inputFlag = 2;
                        } else {
				cout << "Put in a better answer\n";
			}
		}
		if(inputFlag == 1) {			//if the input was yes, then the input flag will be set to one which breaks the for loop and says that the correct number has been guessed
			cout << "I have guessed your number in " << i + 1 << "guesses";
			i = 200;
		}
		inputFlag = 0;
	}
	if(i == 21) {
		cout << "You are a lying person";
	}
	return 0;
}
