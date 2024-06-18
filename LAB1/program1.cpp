//pre conditon: creates string that gets in[ut
//post condition: outputs number of alpha numeric and non alpha numeric characers, returns 0

#include <iostream>
#include <string.h>
using namespace std;

int main() {
	string chars;
	cout << "Input character" << endl;
	//cin >> chars;
	getline(cin, chars);
	int len = chars.length();
	int total = 0;
	int i = 0;
	int num;
	while (/*chars[i] != '\0'*/ i < len) {
		num = int(chars[i]);
		if (num > 47 && num < 58 || num > 64 && num < 91 || num > 96 && num < 123) { //if statement to increment count if character is an alphabet character or number using ascii values
			total++;
		}
		i++;
	}
	
	cout << "anum = " << total;
	cout << ", non anum = " << len - total;
	return 0;
}
