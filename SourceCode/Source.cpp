#include <iostream>
#include "RandomWalk.h"
#include <fstream>
#include <vector>

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
	vector<int> porecheck(200,1);
	/*
	for(int y = 0;y<200;y++){
		if(arr[29][y] == 0){
			vector.y = 0; //initialize all of the stuck particles on the leftmost side of the membrane
		}
	}
	for(int x = 29; x<71;x++){
		for(int y = 0;y<199;y++){
			if(arr[x+1][y] == 0 || arr[x+1][y+1] == 0 || arr[x][y+1]){
				vector.y = 0; // 0 means that the 'line' in that y index is preserved
			}
			else{
				vector.y = 1; // 1 means that the 'line' in the y index has not been preserved
			}
		}
	}
	for(int x = 0; x<100; x++){
		bool check = false;
		if (vector.x == 0){
			check = true; // check refers to pore being open or closed
		}
	}
	*/
	
}
