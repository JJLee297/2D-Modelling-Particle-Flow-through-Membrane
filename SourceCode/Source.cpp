#include <iostream>
#include "RandomWalk.h"
#include <fstream>

using namespace std;
using ll = long long;

void write(int arr[100][200], int A, int B) {
	ofstream textfile;
	textfile.open("LatticeData.txt", ofstream::out | ofstream::trunc);
	if (textfile.is_open()) {
		for (int y = 199; y >= 0; --y) {
			for (int x = 0; x < 100; ++x) {
				textfile << arr[x][y] << " ";
			}
			textfile << endl;
		}
		textfile << "\n\nTotal Stuck Particles: " << A << "\nTotal Tested Particles: " << B << endl;
	}
	textfile.close();
}

int main() {
	// initialize 2D lattice
	// 0 symbolizes stuck particle, 1 symbolizes free space, 2 symbolizes free particle
	int arr[100][200];
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			if ((x < 29 || x > 70) && y < 50) {
				arr[x][y] = 0;
			}
			else {
				arr[x][y] = 1;
			}
		}
	}
	
	system("pause");
}
