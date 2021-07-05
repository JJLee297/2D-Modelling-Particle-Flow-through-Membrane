#include <iostream>
#include "RandomWalk.h"
//#include "ClosureDetection.h"
#include <fstream>
#include <stdlib.h>  
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;


// accesses txt file and records final array data, with A and B
void write(char arr[100][200], int A, int B) {
	ofstream textfile;
	textfile.open("LatticeData.txt", ofstream::out | ofstream::trunc);
	if (textfile.is_open()) {
		for (int y = 199; y >= 0; --y) {
			for (int x = 0; x < 100; ++x) {
				if (x == 0) {
					textfile << setw(3) << setfill(' ') << y;
				}
				textfile << setw(3) << setfill(' ') << arr[x][y];
			}
			textfile << endl;
		}
		textfile << "   ";
		for (int i = 0; i < 100; ++i) {
			textfile << setw(3) << setfill(' ') << i;
		}
		textfile << endl;
		textfile << "\n\nTotal Stuck Particles: " << A << "\nTotal Tested Particles: " << B << endl;
	}
	textfile.close();
}



// checks if a particles new position coincides with another stuck particle or membrane wall
bool checkIfStuck(char arr[100][200], Particle part) {
	int x = arr[part.getWidth()][part.getHeight()];
	if (x == '*' || x == 'M') {
		return true;
	}
	return false;
}

void showfull(char arr[100][200]) {
	for (int y = 199; y >= 0; --y) {
		for (int x = 0; x < 100; ++x) {
			if (x == 0) {
				cout << setw(3) << setfill(' ') << y;
			}
			cout << setw(3) << setfill(' ') << arr[x][y];
		}
		cout << endl;
	}
	cout << "   ";
	for (int i = 0; i < 100; ++i) {
		cout << setw(3) << setfill(' ') << i;
	}
	cout << endl;
}

int main() {
	// initialize 2D lattice
	// '*' symbolizes stuck particle, ' ' symbolizes free space, 'M' symbolizes membrane layer
	char arr[100][200];
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			if ((x < 29 || x > 70) && y < 50) {
				arr[x][y] = 'M';
			}
			else {
				arr[x][y] = ' ';
			}
		}
	}

	int A = 0;
	int B = 0;
	srand(time(NULL));
	long long counter = 0;

	while (1) {
		int xpos = rand() % 100;
		int ypos = 199;
		bool tester = false;
		Particle part(xpos, ypos);
		Particle part2 = part;

		// Particle movement loop
		// breaks when particle leaves or gets stuck, part2 updates if neither
		while (1) {
			part.moveParticle();
			if (part.getHeight() == 0) {
				B++;
				break;
			}
			else if (checkIfStuck(arr, part) == true) {
				arr[part2.getWidth()][part2.getHeight()] = '*';
				A++;
				B++;
				tester = true;
				break;
			}
			else {
				part2 = part;
			}
		}
		counter++;
		if (tester == true) {

			if (counter % 500 == 0) {
				write(arr, A, B);
				showfull(arr);
				cout << "Total Particles Tested: " << B << "\nTotal Particles Stuck: " << A << endl;
				system("pause");
				system("CLS");
			}
			
			if (checkForClosure(arr) == true) {
				write(arr, A, B);
				break;
			}
			tester = false;
		}
	}
}
