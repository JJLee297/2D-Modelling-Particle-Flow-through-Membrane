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
			if(arra[(x+1][porecheck.at(y)] == 0 || arra[x+1][porecheck.at(y)+1] == 0 || arra[x+1][porecheck.at(y)-1]){
				porecheck.replace = 0; // 0 means that the 'line' in that y index is preserved
			}
			else{
				porecheck.y = 1; // 1 means that the 'line' in the y index has not been preserved
			}
			int length = porecheck.size()
		}
	}
	for(int x = 0; x<100; x++){
		bool check = false;
		if (porecheck.x == 0){
			check = true; // check refers to pore being open or closed
		}
	}
	*/
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
