/*
Constant domain simulation, array size 100x200
Simulation with dynamic y and x lengths, satisfying (constant(+=0.5%) = y(100-x))
keep in mind the txt file naming procedure (can be modified), which does not account for different flow patterns.
Other cpp files have been changed accordinly - take care to use the appropriate files for dynamicdomain vs constantdomain
*/
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

// 0 is empty space, 1 is left, 2 is right
int arr[100][200];
int agg[100][200];
ll totalA;
ll totalB;


bool closureCheck(int x, int y) {
	int state;
	if (arr[x][y] == 1)
		state = 2;
	else
		state = 1;
	if (x != 99 && y != 199 && x != 0) {
		if (arr[x + 1][y] == state || arr[x + 1][y + 1] == state || arr[x + 1][y - 1] == state
			|| arr[x][y + 1] == state || arr[x][y - 1] == state
			|| arr[x - 1][y] == state || arr[x - 1][y + 1] == state || arr[x - 1][y - 1] == state)
			return true;
	}
	else if (x == 99 && y != 199) {
		if (arr[x][y + 1] == state || arr[x][y - 1] == state
			|| arr[x - 1][y] == state || arr[x - 1][y + 1] == state || arr[x - 1][y - 1] == state)
			return true;
	}
	else if (x == 0 && y != 199) {
		if (arr[x + 1][y] == state || arr[x + 1][y + 1] == state || arr[x + 1][y - 1] == state
			|| arr[x][y + 1] == state || arr[x][y - 1] == state)
			return true;
	}
	else if (x == 99 && y == 199) {
		if (arr[x - 1][y] == state || arr[x - 1][y - 1] == state || arr[x][y - 1] == state)
			return true;
	}
	else if (x == 0 && y == 199) {
		if (arr[x + 1][y] == state || arr[x + 1][y - 1] == state || arr[x][y - 1] == state)
			return true;
	}
	return false;
}

void write(int A, int B, string name) {
	ofstream textfile;
	textfile.open(name, ofstream::out | ofstream::trunc);
	if (textfile.is_open()) {
		for (int y = 199; y >= 0; --y) {
			for (int x = 0; x < 100; ++x) {
				if (agg[x][y] != -1)
					textfile << agg[x][y] << " ";
				else
					textfile << 0 << " ";
			}
		}
		textfile << "\n\nTotal Stuck Particles: " << A << "\nTotal Tested Particles: " << B << endl;
	}
	textfile.close();
}

bool checkIfStuck(Particle part) {
	int x = arr[part.getWidth()][part.getHeight()];
	if ((x == 1 || x == 2) && part.getHeight() <= 185) {
		return true;
	}
	return false;
}

void showfull2() {
	for (int y = 199; y >= 0; --y) {
		for (int x = 0; x < 100; ++x) {
			if (arr[x][y] != 0)
				cout << arr[x][y];
			else
				cout << ' ';
		}
		cout << endl;
	}
}

void showfull() {
	for (int y = 199; y >= 0; --y) {
		for (int x = 0; x < 100; ++x) {
			int b = arr[x][y];
			if (b == 1 || b == 2) 
				cout << '*';
			else
				cout << ' ';
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
			if ((arr[x][y] == 1 || arr[x][y] == 2) && agg[x][y] != -1) {
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
				arr[x][y] = 1;
				agg[x][y] = -1;
			}
			else if (y < -slope * (x - (99 - xint))) {
				arr[x][y] = 2;
				agg[x][y] = -1;
			}
			else {
				arr[x][y] = 0;
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
				if (part2.getWidth() != 0 && part2.getWidth() != 99)
					arr[part2.getWidth()][part2.getHeight()] = arr[part.getWidth()][part.getHeight()];
				else if (part2.getWidth() == 99)
					arr[part2.getWidth()][part2.getHeight()] = 2;
				else 
					arr[part2.getWidth()][part2.getHeight()] = 1;
				A++;
				B++;
				if (closureCheck(part2.getWidth(), part2.getHeight())) {
					totalA += A;
					totalB += B;
					return;
				}
				break;
			}
			else {
				part2 = part;
			}
		}
	}
}

int main() {
	//650: 6, 900: 8, 1175: 10, 1425: 13, 1800: 14
	srand(time(NULL));
	double porosity = 900;
	for (int x = 1; x < 50; ++x) {
		double y = (0.995 * porosity) / (100 - x);
		if (y != (int)y)
			y = (int)y + 1;
		double lim = (1.005 * porosity) / (100 - x);
		for (y; y < lim; ++y) {
			cout << "(" << x << ", " << y << ")\n";
			setAgg();
			totalA = 0;
			totalB = 0;
			for (int i = 0; i < 250; ++i) {
				sim(x, y);
				aggregate();
				if (i % 50 == 0) {
					cout << i << " ";
				}
			}
			write(totalA, totalB, "X" + to_string(x) + "Y" + to_string((int)y) + "por" + to_string((int)porosity) + ".txt");
			cout << "\nsim over, next sim start\n";
		}
	}
	system("pause");
}
