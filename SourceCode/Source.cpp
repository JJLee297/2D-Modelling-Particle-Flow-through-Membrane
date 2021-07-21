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
#include <string>

using namespace std;
using ll = long long;

char arr[100][200];
int agg[100][200];
ll totalA;
ll totalB;
int maxA;
int minA;
int maxB;
int minB;


void write(int A, int B, string name) {
	ofstream textfile;
	textfile.open(name, ofstream::out | ofstream::trunc);
	if (textfile.is_open()) {
		for (int y = 199; y >= 0; --y) {
			for (int x = 0; x < 100; ++x) {
				textfile << agg[x][y] << " ";
			}
		}
		textfile << "\n\nTotal Stuck Particles: " << A << "\nTotal Tested Particles: " << B << endl;
	}
	textfile.close();
}

bool checkIfStuck(Particle part) {
	char x = arr[part.getWidth()][part.getHeight()];
	if (x == '*' || x == 'M' && part.getHeight() <= 185) {
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

void showAgg() {
	for (int y = 199; y >= 0; --y) {
		for (int x = 0; x < 100; ++x) {
			cout << agg[x][y];
		}
		cout << endl;
	}
}

void setAgg() {
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			agg[x][y] = 0;
		}
	}
}

void aggregate() {
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			if (arr[x][y] == '*') {
				agg[x][y]++;
			}
		}
	}
}

void createMembrane(int xx, int yy) {
	float yint, xint;
	xint = (float)xx;
	yint = (float)yy;
	float slope = -(yint / xint);
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 200; ++y) {
			if (y < (slope * x + yint)) {
				arr[x][y] = 'M';
			}
			else if (y < -slope * (x - (99 - xint))) {
				arr[x][y] = 'M';
			}
			else {
				arr[x][y] = ' ';
			}
		}
	}
}

void sim(int xinter, int yinter) {
	createMembrane(xinter, yinter);
	int A = 0;
	int B = 0;
	while (1) {
		int xpos = rand() % 100;
		int ypos = rand() % 15 + 185;
		Particle part(xpos, ypos);
		if (checkIfStuck(part))
			continue;
		Particle part2 = part;
		while (1) {
			part.moveParticle();
			if (part.getHeight() == 0) {
				B++;
				break;
			}
			else if (checkIfStuck(part)) {
				arr[part2.getWidth()][part2.getHeight()] = '*';
				A++;
				B++;
				break;
			}
			else {
				part2 = part;
			}
		}
		if (contourOutline(arr, 99 - xinter)) {
			totalA += A;
			totalB += B;
			break;
		}
	}
}

int main() {
	srand(time(NULL));
	double porosity = 2100;
	for (double x = 1; x < 50; ++x) {
		double y = (porosity / (100 - x));
		if (y == (int)y) {
			cout << "point: (" << x << ", " << y << ")\n";
			setAgg();
			totalA = 0;
			totalB = 0;
			for (int i = 0; i < 50; ++i) {
				sim(x, y);
				aggregate();
				cout << " " << i;
			}
			write(totalA, totalB, "X" + to_string((int)x) + "Y" + to_string((int)y) + ".txt");
			cout << "\nsim over, next sim start\n";
		}
	}
	system("pause");
}
