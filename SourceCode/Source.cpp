#include <iostream>
#include "RandomWalk.cpp"
#include "contourOutline.cpp"
#include <fstream>
#include <stdlib.h>  
#include <time.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;

char arr[100][200];

void write(int A, int B) {
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

bool checkIfStuck(Particle part) {
	int x = arr[part.getWidth()][part.getHeight()];
	if (x == '*' || x == 'M') {
		return true;
	}
	return false;
}

void showfull() {
	for (int y = 199; y >= 0; --y) {
		for (int x = 0; x < 100; ++x) {
			cout << arr[x][y];
		}
		cout << endl;
	}
}

void createMembrane(int xx, int yy) {
	float yint, xint;
	xint = (float)xx;
	yint = (float)yy;
	float slope = -(yint / xint);
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 200; ++y) {
			if (y < (slope * x + yint) || y < -slope * (x - (99 - xint)))
				arr[x][y] = 'M';
			else
				arr[x][y] = ' ';
		}
	}
}

int main() {
	createMembrane(40, 50);
	showfull();
	system("pause");
	// sim

	int A = 0;
	int B = 0;
	srand(time(NULL));
	while (1) {
		int xpos = rand() % 100;
		int ypos = 199;
		Particle part(xpos, ypos);
		Particle part2 = part;

		while (1) {
			part.moveParticle();
			if (part.getHeight() == 0) {
				B++;
				break;
			}
			else if (checkIfStuck(part) == true) {
				arr[part2.getWidth()][part2.getHeight()] = '*';
				A++;
				B++;
				break;
			}
			else {
				part2 = part;
			}
		}
		if (contourOutline(arr, 75)) {
			system("CLS");
			showfull();
			cout << "Total Particles Tested: " << B << "\nTotal Particles Stuck: " << A << endl;
			system("pause");
		}
	}
}
