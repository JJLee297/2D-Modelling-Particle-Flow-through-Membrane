/*
Dynamic Domain, satisfying (constant area = (y_constant)(domain_length - x)) 
Keep in mind txt file naming procedure, doesn't take into account the flow pattern (modifiable). 
Other cpp files have been changed accordinly - take care to use the appropriate files for dynamicdomain vs constantdomain
*/
#include <iostream>
#include "RandomWalk.cpp"
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
vector<ll> totalAs;
vector<ll> totalBs;

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

void writeTots() {
	ofstream textfile;
	textfile.open("TotCounts.txt", ofstream::out | ofstream::trunc);
	if (textfile.is_open()) {
		for (int i = 0; i < totalAs.size(); ++i) {
			textfile << totalAs[i] << " " << totalBs[i] << endl;
		}
	}
	textfile.close();
}

bool checkIfStuck(Particle part) {
	int x = arr[part.getWidth()][part.getHeight()];
	if ((x == 1 || x == 2) && part.getHeight() < 185) {
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
			if (agg[x][y] != -1)
				cout << agg[x][y];
			else
				cout << 0;
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

void aggregate(int dom) {
	for (int x = 0; x < dom; ++x) {
		for (int y = 0; y < 200; ++y) {
			if ((arr[x][y] == 1 || arr[x][y] == 2) && agg[x][y] != -1) {
				agg[x][y]++;
			}
		}
	}
}

void createMembrane(int xx, int yy, int dom) {
	float yint, xint;
	xint = (float)xx;
	yint = (float)yy;
	float slope = -(yint / xint);
	for (int x = 0; x < dom; x++) {
		for (int y = 0; y < 200; ++y) {
			if (y < (slope * x + yint)) {
				arr[x][y] = 1;
				agg[x][y] = -1;
			}
			else if (y < -slope * (x - (dom - 1 - xint))) {
				arr[x][y] = 2;
				agg[x][y] = -1;
			}
			else {
				arr[x][y] = 0;
			}
		}
	}
}

void sim(int xinter, int yinter, int dom) {
	createMembrane(xinter, yinter, dom);
	int A = 0;
	int B = 0;
	while (1) {
		int xpos = rand() % dom;
		int ypos = rand() % 15 + 185;
		Particle part(xpos, ypos);
		Particle part2 = part;
		while (1) {
			part.moveParticle(dom);
			if (part.getHeight() == 0) {
				B++;
				break;
			}
			else if (checkIfStuck(part)) {
				if (part2.getWidth() != 0 && part2.getWidth() != dom - 1)
					arr[part2.getWidth()][part2.getHeight()] = arr[part.getWidth()][part.getHeight()];
				else if (part2.getWidth() == dom - 1) 
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
	srand(time(NULL));
	int y = 50; 
	int x_init = 30;
	int area = y * (100 - x_init);
	cout << "Area: " << area << endl;
	for (int i = 0; i < x_init; ++i) {
		cout << x_init - i << endl;
		setAgg();
		totalA = 0;
		totalB = 0;
		for (int k = 0; k < 250; ++k) {
			sim(x_init - i, y, 100 - i);
			aggregate(100 - i);
		}
		totalAs.push_back(totalA);
		totalBs.push_back(totalB);
		write(totalA, totalB, "X" + to_string(x_init - i) + "Y" + to_string(y) + "por" + to_string(area) + ".txt");
		cout << "\nsim over, next sim start\n";
	}
	writeTots();
	system("pause");
}

