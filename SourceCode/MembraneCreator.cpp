#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void main()

{
	float yinput, xinput;
	char arr[200][100];
	for (int x = 0; x < 200; x++) {
		for (int y = 0; y < 100; y++) {
			arr[x][y] = ' ';
		}
	}
	cout << "Enter the x intercept: ";
	cin >> xinput;
	cout << "Enter the y intercept: ";
	cin >> yinput;
	float slope;
	int numberofcolumns;
	slope = yinput*(-1) / (xinput);
	for (int y = 0; y < (xinput + 1); y++) {
		int temp;
		temp = 200 - floor(y*slope + yinput);
		arr[temp][y] = 'M';
		arr[temp][99 - y] = 'M';
	}

	for (int x = 0; x < 200; x++) {
		for (int y = 0; y < 100; y++) {
			cout << arr[x][y];
			if (y == 99) {
				cout << endl;
			}
			else {
				continue;
			}

		}
	}
}