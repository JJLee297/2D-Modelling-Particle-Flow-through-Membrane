#include <iostream>
#include "RandomWalk.h"
#include <fstream>
#include <vector>

using namespace std;
using ll = long long;

bool checkForClosure (int arra){
	for(int y = 0;y<200;y++){
		if(arra[29][y] == 0){
			porecheck.pushback(y); //record all of the heights of the stuck particles
		}
	}
	int length = porecheck.size()
	for(int x = 29; x<71;x++){
		for(int y = 0;y<length;y++){
			if(arra[(x+1][porecheck.at(y)] == 0){
				continue;
			} 
			if(arra[x+1][porecheck.at(y)+1] == 0){
				vector.erase(porecheck.begin()+y);
				vector.pushback(porecheck.at(y)+1);
			}
			if(arra[x+1][porecheck.at(y)-1] == 0){
				vector.erase(porecheck.begin()+y);
				vector.pushback(porecheck.at(y)-1);
			}
			int length = porecheck.size()
			if(length == 0){
				return false;
			}
		}
	}
}

bool checkIfStuck(int arr[100][200], Particle poo) {
	if (arr[poo.getWidth()][poo.getHeight()] == 0) {
		return true;
	}
	return false;
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
	vector<int> porecheck(200,1);
	/*

	
}
