// move closure algo here
// ALGO DOES NOT WORK !!!
// DO NOT USE !!
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


/*
closureTest() - given an initial point, closureTest traces all possible 'bridges' over the pore openning.
If a fully connected bridge exists, closureTest() returns true. Else, it returns false.
Fully connected bridge: A bridge is considered fully connected if it completely (without any gaps) connects both sides
of the membrane surface. Diagonal connections are allowed.
*/

bool closureTest(char arr[100][200], int x, int y) {
	vector<int> check;
	vector<int> check2;
	check.push_back(y);
	for (int i = x + 1; i < 100; ++i) {
		for (int k = 0; k < check.size(); ++k) {
			if (arr[i][check[k] - 1] == '*')
				if (find(check2.begin(), check2.end(), check[k] - 1) == check2.end())
					check2.push_back(check[k] - 1);
			if (arr[i][check[k]] == '*')
				if (find(check2.begin(), check2.end(), check[k]) == check2.end())
					check2.push_back(check[k]);
			if (arr[i][check[k] + 1] == '*')
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
		if ((i > 70 && arr[i][check[0] - 1] == 'M') || (i == 70 && arr[71][check[0]] == 'M')) {
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
bool checkForClosure(char arr[100][200]) {
	vector<int> init;
	int yvals = 0;
	for (int y = 0; y < 50; ++y) {
		if (arr[29][y] == '*') {
			init.push_back(y);
			++yvals;
		}
	}
	for (int x = 28; x >= 0; --x) {
		if (arr[x][50] == '*') {
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
	yvals = 0;
	init.clear();
	return false;
}
