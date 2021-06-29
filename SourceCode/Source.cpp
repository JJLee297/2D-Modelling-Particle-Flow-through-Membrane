#include <iostream>
#include "RandomWalk.h"
#include <fstream>
#include <stdlib.h>  
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

/*
closureTest() - given an initial point, closureTest traces all possible 'bridges' over the pore openning. 
If a fully connected bridge exists, closureTest() returns true. Else, it returns false.
Fully connected bridge: A bridge is considered fully connected if it completely (without any gaps) connects both sides 
of the membrane surface. Diagonal connections are allowed. 
*/

bool closureTest(int arr[100][200], int x, int y) {
	vector<int> check;
	vector<int> check2;
	check.push_back(y);
	for (int i = x + 1; i < 100; ++i) {
		for (int k = 0; k < check.size(); ++k) {
			if (arr[i][check[k] - 1] == 0)
				if (find(check2.begin(), check2.end(), check[k] - 1) == check2.end())
					check2.push_back(check[k] - 1);
			if (arr[i][check[k]] == 0)
				if (find(check2.begin(), check2.end(), check[k]) == check2.end())
					check2.push_back(check[k]);
			if (arr[i][check[k] + 1] == 0)
				if (find(check2.begin(), check2.end(), check[k] + 1) == check2.end())
					check2.push_back(check[k] + 1);
		}
		if (check2.size() != 0) {
			check = check2;
			check2.clear();
		}
		else {
			return false; 
		}

		// the check vector is always sorted, due to the design of the if statements. The following if checks if the lowest element is 
		// directly on top of or to the left of the membrane wall. 
		if ((i > 70 && arr[i][check[0] - 1] == 2) || (i == 70 && arr[71][check[0]] == 2)) {
			return true;
		}
	}
	return false;
}

/*  There can be multiple definitions of clogged. We will only consider a pore 'clogged' if there exists a connected
	path from one side of the membrane over the pore to the other side of the membrane.
	Closure Check Algorithm:
		1. Mark each particle that is stuck directly on top of the membrane on the left side (y = 50, x < 29)
			* Also mark any particle that is stuck on the left side of the pore (x = 29, y < 50)
		2. For each of those particles, run closureTest()
		3. If any closureTest() runs return true, then return true
		4. else, return false
*/
bool checkForClosure(int arr[100][200]) {
	vector<int> init;
	int yvals = 0;
	for (int y = 0; y < 50; ++y) {
		if (arr[29][y] == 0) {
			init.push_back(y);
			++yvals;
		}
	}
	for (int x = 28; x >= 0; --x) {
		if (arr[x][50] == 0) {
			init.push_back(x);
		}
	}
	for (int i = 0; i < yvals; ++i) {
		if (closureTest(arr, 29, init[i])) {
			return true;
		}
	}
	for (int i = yvals; i < init.size(); ++i) {
		if (closureTest(arr, init[i], 50)) {
			return true;
		}
	}
	return false;
}


// accesses txt file and records final array data, with A and B
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


// checks if a particles new position coincides with another stuck particle or membrane wall
bool checkIfStuck(int arr[100][200], Particle poo) {
	int x = arr[poo.getWidth()][poo.getHeight()];
	if (x == 2 || x == 0) {
		return true;
	}
	return false;
}

void show(int arr[100][200]) {
	for (int y = 75; y >= 0; --y) {
		for (int x = 27; x < 73; ++x) {
			cout << arr[x][y];
		}
		cout << endl;
	}
}

void showfull(int arr[100][200]) {
	for (int y = 199; y >= 0; --y) {
		for (int x = 0; x < 100; ++x) {
			cout << arr[x][y];
		}
		cout << endl;
	}
}

int main() {
	// initialize 2D lattice
	// 0 symbolizes stuck particle, 1 symbolizes free space, 2 symbolizes membrane layer
	int arr[100][200];
	for (int x = 0; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			if ((x < 29 || x > 70) && y < 50) {
				arr[x][y] = 2;
			}
			else {
				arr[x][y] = 1;
			}
		}
	}

	int A = 0;
	int B = 0;
	srand(time(NULL));
	long long counter = 0;
	// Sim loop
	while (1) {
		int xpos = rand() % 100;
		int ypos = 199;
		bool tester = false;
		Particle poo(xpos, ypos);
		Particle poo2 = poo;

		// Particle movement loop
		// breaks when particle leaves or gets stuck, poo2 updates if neither
		while (1) {
			poo.moveParticle();
			//cout << "poo coordinates: (" << poo.getWidth() << ", " << poo.getHeight() << ")\n";
			if (poo.getHeight() == 0) {
				B++;
				break;
			}
			else if (checkIfStuck(arr, poo) == true) {
				arr[poo2.getWidth()][poo2.getHeight()] = 0;
				A++;
				B++;
				tester = true;
				break;
			}
			else {
				poo2 = poo;
			}
		}
		// only checks for closure if a new particle is stuck
		// if closed, final particle structure is recorded into txt file
		if (tester == true) {
			counter++;
			// output function here
			if (counter % 50 == 0) {
				showfull(arr);
				system("pause");
				system("CLS");
			}
			if (checkForClosure(arr) == true) {
				//system("CLS");
				//showfull(arr);
				//system("pause");
				write(arr, A, B);
				break;
			}
			tester = false;
		}
	}
}
