#include <iostream>
#include "RandomWalk.h"
#include <fstream>
#include <stdlib.h>  
#include <time.h>
#include <vector>

using namespace std;
using ll = long long;

bool checkForClosure(int arra[100][200]) {
	vector<int> porecheck;
	for (int y = 0; y < 200; y++) {
		if (arra[29][y] == 0) {
			porecheck.push_back(y); //record all of the heights of the stuck particles
		}
	}
	int length = porecheck.size();
	for (int x = 29; x < 71; x++) {
		for (int y = 0; y < length; y++) {
			if (arra[(x + 1)][porecheck.at(y)] == 0) {
				continue;
			}
			if (arra[x + 1][porecheck.at(y) + 1] == 0) {
				porecheck.erase(porecheck.begin() + y);
				porecheck.push_back(porecheck.at(y) + 1);
			}
			if (arra[x + 1][porecheck.at(y) - 1] == 0) {
				porecheck.erase(porecheck.begin() + y);
				porecheck.push_back(porecheck.at(y) - 1);
			}
			int length = porecheck.size();
			if (length == 0) {
				return false;
			}
		}
	}
	return true;
}

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

bool checkForClosure(int arr[100][200]) {
	return true;
}

bool checkIfStuck(int arr[100][200], Particle poo) {
	if (arr[poo.getWidth()][poo.getHeight()] == 0) {
		return true;
	}
	return false;
}

int main() {
	// initialize 2D lattice
	// 0 symbolizes stuck particle, 1 symbolizes free space
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
	// Sim start
	// Generate particle
	// Keep moving particle until it gets stuck or leaves pore
	// If stuck, update lattice with new stuck position (B++, A++) and (1) check for closure
	// If it leaves (2), leave lattice alone, (B++)
	// If (1) or (2), repeat
	// If (1*), exit and write lattice, B, and A to txt file
	bool Sim = true;
	int A = 0;
	int B = 0;
	srand(time(NULL));
	while (Sim) {
		// generate random starting x position [0 - 99], y position will be fixed at 199 initially
		int xpos = rand() % 100;
		int ypos = 199;
		Particle poo(xpos, ypos);
		Particle poo2 = poo;
		while (1) {
			poo.moveParticle();
			if (checkIfStuck(arr, poo) == false) {
				poo2 = poo;
				continue;
			}
			else if (poo.getHeight() == 0) {
				B++;
				break;
			}
			else {
				arr[poo2.getWidth()][poo2.getHeight()] == 0;
				A++;
				B++;
				break;
			}
		}
		if (checkForClosure(arr) == true) {
			write(arr, A, B);
			break;
		}
	}
}
