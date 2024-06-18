//pre condition: akes in txt file and opens so it is readable
//post condition: outposts words longer than 10 letter in uppercase with only letters, returns 0

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
	string chars;
	int i = 0;
	int j = 0;
	int length;
	int temp = 0;
	string tempString = "                           ";
	if (argc > 1) {
		cout << "argv[1] = " << argv[1] << endl; 
	} else {
		cout << "No file name entered. Exiting...";
		return -1;
	}
	ifstream infile(argv[1]); //open the file
    
	if (infile.is_open() && infile.good()) {		//opens file if possible
		cout << "File opened successfully:\nList of adjusted words:\n\n";
		string line = "";				//gets a specific line in file
		while (getline(infile, line)){
			i = 0;
			while(line[i] != '\0') {		//loop removes non wanted characters by checking ascii values
				temp = int(line[i]);
				if (temp < 65 && temp != 32 || temp > 90 &&  temp < 97 || temp > 122) {
					line.erase(line.begin() + i);
				} else {
					i++;
				}	
			}
			i = 0;
			while (line[i] != '\0') {		//while loop that changes all lower case letter to upper case using ascii values and subtracting 32 to get the upper case character
				temp = int(line[i]);
				if (temp > 96 && temp < 123 && temp != 32) {
					temp = temp - 32;
					line[i] = char(temp);
				}
				i++;
			}
			i = 0;
			temp = 0;
			j = 0;
			while(line[i] != '\0') {		//j used as length counter
				temp = int(line[i]);
				if(temp != 32) {		//if statement that incriments counter if there is not a space
					tempString[j] = char(temp);
					j++;
				} else {			//if there is a space, chekc if the word is over 9 letter and if so, then print
					if(j > 9) {
						cout << tempString << '\n';
					}
					tempString = "                           "; 
					j = 0;			//reset string and counter
				}
				i++;
			}
			if (j > 9) {		//if you dont end on a space, this will print out the final word
				cout << tempString << endl;
			}			
			tempString = "                           ";	
		length = line.size();
		}
	} else {
		cout << "File cannot be opened";
	}

	return 0;
} 
