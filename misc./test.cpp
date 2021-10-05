/*
#include <iostream>
#include <fstream>
#include <stdlib.h>  
#include <time.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <string>
#include <random>
#include <chrono>


using namespace std;
using ll = long long;

// 0 is empty space, 1 is left, 2 is right
int arr[100][200];
int agg[100][200];
ll totalA;
ll totalB;
ll totalC;
vector<ll> totalAs;
vector<ll> totalBs;
vector<ll> totalCs;
int x1, x2, x3;
int two, three, four, total;

class Particle {
public:
	Particle(int xpos, int ypos) {
		x = xpos;
		y = ypos;
	}

	int getHeight() {
		return y;
	}

	int getWidth() {
		return x;
	}

	void moveParticle(int dom, int dir) {
		if (dir < x1) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
		}
		// left down
		else if (dir < two) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
			y--;
		}
		// down
		else if (dir < three) {
			y--;
		}
		// right down
		else if (dir < four) {
			if (x < dom - 1)
				x++;
			else
				x = 0;
			y--;
		}
		// right
		else {
			if (x < dom - 1)
				x++;
			else
				x = 0;
		}
	}

	void moveParticle2(int dom, double dir) {
		if (dir < -75) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
		}
		// left down
		else if (dir <= -25) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
			y--;
		}
		// down
		else if (dir < 25) {
			y--;
		}
		// right down
		else if (dir <= 75) {
			if (x < dom - 1)
				x++;
			else
				x = 0;
			y--;
		}
		// right
		else {
			if (x < dom - 1)
				x++;
			else
				x = 0;
		}
	}
private:
	int x;
	int y;
};

class Generator {
    default_random_engine generator;
    normal_distribution<double> distribution;
    int min;
    int max;
public:
	Generator(double mean, int stddev, int min, int max) :
		distribution(mean, stddev), min(min), max(max)
    {}

    double operator ()() {
		while (true) {
			double number = this->distribution(generator);
			if (number >= this->min && number <= this->max)
				return number;
		}
    }
};

// mean, standard deviation
Generator gen(0, 60, -125, 125);

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

void write(ll A, ll B, ll C, string name) {
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
		textfile << "\n\nTotal Stuck Particles: " << A << "\nTotal Tested Particles: " << B << "\nTotal Particle Moves: " << C << endl;
	}
	textfile.close();
}

void writeTots(string name) {
	ofstream textfile;
	textfile.open(name, ofstream::out | ofstream::trunc);
	if (textfile.is_open()) {
		for (int i = 0; i < totalAs.size(); ++i) {
			textfile << totalBs[i] << " " << totalAs[i] << " " << totalCs[i] << endl;
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

bool checkIfStuck2(Particle part) {
	int x = arr[part.getWidth()][part.getHeight()];
	if (x == 2 && part.getHeight() < 185) {
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
	cout << "A:" << totalA << "\nB:" << totalB;
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

void aggregate2(int dom) {
	for (int x = 0; x < dom; ++x) {
		for (int y = 0; y < 200; ++y) {
			if ((arr[x][y] != 0)) {
				agg[x][y] = 1;
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
	for (int x = dom; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			arr[x][y] = 0;
		}
	}
}

void sim(int xinter, int yinter, int dom) {
	createMembrane(xinter, yinter, dom);
	int A = 0;
	int B = 0;
	int C = 0;
	while (1) {
		int xpos = rand() % dom;
		int ypos = rand() % 15 + 185;
		Particle part(xpos, ypos);
		Particle part2 = part;
		while (1) {
			part.moveParticle(dom, rand() % total);
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
					totalC += C;
					return;
				}
				break;
			}
			else {
				part2 = part;
				C++;
			}
		}
	}
}

void sim2(int xinter, int yinter, int dom) {
	createMembrane(xinter, yinter, dom);
	int A = 0;
	int B = 0;
	while (1) {
		int xpos = rand() % dom;
		int ypos = rand() % 15 + 185;
		Particle part(xpos, ypos);
		Particle part2 = part;
		while (1) {
			part.moveParticle(dom, rand() % total);
			if (part.getHeight() == 0) {
				B++;
				return;
			}
			else if (checkIfStuck2(part)) {
				return;
			}
			else {
				arr[part2.getWidth()][part2.getHeight()] = 1;
				part2 = part;
			}
		}
	}
}

void setProb() {
	int ar2[5] = { 0 };
	for (int i = 0; i < 100000; ++i) {
		int b = gen();
		if (b < -75)
			ar2[0]++;
		else if (b <= -25)
			ar2[1]++;
		else if (b < 25)
			ar2[2]++;
		else if (b <= 75)
			ar2[3]++;
		else
			ar2[4]++;
	}
	x1 = (ar2[0] + ar2[4]) / 230;
	x2 = (ar2[1] + ar2[3]) / 230;
	x3 = ar2[2] / 115;
	for (int i = 0; i < 5; ++i) {
		cout << i << ": " << ar2[i] << endl;
	}
	two = x1 + x2;
	three = two + x3;
	four = three + x2;
	total = four + x1;
	cout << "\n" << x1 << " " << two << " " << three << " " << four << " " << total << endl;
}

void testingsetProb() {
	setProb();
	int ar2[5] = { 0 };
	for (int i = 0; i < 10000000; ++i) {
		int b = gen();
		if (b < -75)
			ar2[0]++;
		else if (b <= -25)
			ar2[1]++;
		else if (b < 25)
			ar2[2]++;
		else if (b <= 75)
			ar2[3]++;
		else
			ar2[4]++;
		if (i % 1000000 == 0) {
			cout << "1";
		}
	}
	cout << endl;
	for (int i = 0; i < 5; ++i) {
		cout << i << ": " << ar2[i] << endl;
	}
}


int main() {
	srand(time(NULL));
	setProb();
	setAgg();
	totalA = 0;
	totalB = 0;
	totalC = 0;
	for (int k = 0; k < 1000; ++k) {
		sim(30, 50, 100);
		aggregate(100);
		if (k % 100 == 0) {
			cout << k << " ";
		}
	}
	write(totalA, totalB, totalC, "temp.txt");
	system("pause");

	int y = 50; 
	int x_init = 30;
	int area = y * (100 - x_init); 
	cout << "Area: " << area << endl;
	for (int i = 0; i < x_init; ++i) {
		cout << x_init - i << endl;
		setAgg();
		totalA = 0;
		totalB = 0;
		totalC = 0;
		for (int k = 0; k < 500; ++k) {
			sim(x_init - i, y, 100 - i);
			aggregate(100 - i);
			if (k % 50 == 0) {
				cout << k << " ";
			}
		}
		totalAs.push_back(totalA);
		totalBs.push_back(totalB);
		totalCs.push_back(totalC);
		write(totalA, totalB, totalC, "X" + to_string(x_init - i) + "Y" + to_string(y) + "por" + to_string(area) + ".txt");
		cout << "\nsim over, next sim start\n";
	}
	writeTots("stddev300-FOREXCEL.txt");
	system("pause");
}
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>  
#include <time.h>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <string>
#include <random>
#include <chrono>


using namespace std;
using ll = long long;

// 0 is empty space, 1 is left, 2 is right
int arr[100][200];
int agg[100][200];
ll totalA;
ll totalB;
ll totalC;
vector<ll> totalAs;
vector<ll> totalBs;
vector<ll> totalCs;
int x1, x2, x3;
int two, three, four, total;

class Particle {
public:
	Particle(int xpos, int ypos) {
		x = xpos;
		y = ypos;
	}

	int getHeight() {
		return y;
	}

	int getWidth() {
		return x;
	}

	void moveParticle(int dom, int dir) {
		if (dir < x1) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
		}
		// left down
		else if (dir < two) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
			y--;
		}
		// down
		else if (dir < three) {
			y--;
		}
		// right down
		else if (dir < four) {
			if (x < dom - 1)
				x++;
			else
				x = 0;
			y--;
		}
		// right
		else {
			if (x < dom - 1)
				x++;
			else
				x = 0;
		}
	}

	void moveParticle2(int dom, double dir) {
		if (dir < -75) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
		}
		// left down
		else if (dir <= -25) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
			y--;
		}
		// down
		else if (dir < 25) {
			y--;
		}
		// right down
		else if (dir <= 75) {
			if (x < dom - 1)
				x++;
			else
				x = 0;
			y--;
		}
		// right
		else {
			if (x < dom - 1)
				x++;
			else
				x = 0;
		}
	}
private:
	int x;
	int y;
};

class Generator {
	default_random_engine generator;
	normal_distribution<double> distribution;
	int min;
	int max;
public:
	Generator(double mean, int stddev, int min, int max) :
		distribution(mean, stddev), min(min), max(max)
	{}

	double operator ()() {
		while (true) {
			double number = this->distribution(generator);
			if (number >= this->min && number <= this->max)
				return number;
		}
	}
};

// mean, standard deviation
Generator gen(0, 300, -125, 125);

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

void write(ll A, ll B, ll C, string name) {
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
		textfile << "\n\nTotal Stuck Particles: " << A << "\nTotal Tested Particles: " << B << "\nTotal Particle Moves: " << C << endl;
	}
	textfile.close();
}

void writeTots(string name) {
	ofstream textfile;
	textfile.open(name, ofstream::out | ofstream::trunc);
	if (textfile.is_open()) {
		for (int i = 0; i < totalAs.size(); ++i) {
			textfile << totalBs[i] << " " << totalAs[i] << " " << totalCs[i] << endl;
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
	cout << "A:" << totalA << "\nB:" << totalB;
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

void createMembrane2(int xx, int yy, int dom) {
	float yint, xint;
	xint = (float)xx;
	yint = (float)yy;
	float slope = -(yint / xint);
	for (int x = 0; x < dom; x++) {
		for (int y = 0; y < 200; ++y) {
			if (y < (slope * x + yint)) {
				arr[x][y] = 1;
				agg[x][y] = 1;
			}
			else if (y < -slope * (x - (dom - 1 - xint))) {
				arr[x][y] = 2;
				agg[x][y] = 1;
			}
			else {
				arr[x][y] = 0;
			}
		}
	}
	for (int x = dom; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			arr[x][y] = 0;
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
	for (int x = dom; x < 100; ++x) {
		for (int y = 0; y < 200; ++y) {
			arr[x][y] = 0;
		}
	}
}

void sim(int xinter, int yinter, int dom) {
	createMembrane(xinter, yinter, dom);
	int A = 0;
	int B = 0;
	int C = 0;
	while (1) {
		int xpos = rand() % dom;
		int ypos = rand() % 15 + 185;
		Particle part(xpos, ypos);
		Particle part2 = part;
		while (1) {
			part.moveParticle(dom, rand() % total);
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
					totalC += C;
					return;
				}
				break;
			}
			else {
				part2 = part;
				C++;
			}
		}
	}
}

void sim2(int xinter, int yinter, int dom) {
	createMembrane(xinter, yinter, dom);
	int A = 0;
	int B = 0;
	while (1) {
		int xpos = rand() % dom;
		int ypos = rand() % 15 + 185;
		Particle part(xpos, ypos);
		Particle part2 = part;
		while (1) {
			part.moveParticle(dom, rand() % total);
			if (part.getHeight() == 0) {
				B++;
				return;
			}
			else if (checkIfStuck(part)) {
				return;
			}
			else {
				arr[part2.getWidth()][part2.getHeight()] = 1;
				part2 = part;
			}
		}
	}
}

void setProb() {
	int ar2[5] = { 0 };
	for (int i = 0; i < 100000; ++i) {
		int b = gen();
		if (b < -75)
			ar2[0]++;
		else if (b <= -25)
			ar2[1]++;
		else if (b < 25)
			ar2[2]++;
		else if (b <= 75)
			ar2[3]++;
		else
			ar2[4]++;
	}
	x1 = (ar2[0] + ar2[4]) / 230;
	x2 = (ar2[1] + ar2[3]) / 230;
	x3 = ar2[2] / 115;
	for (int i = 0; i < 5; ++i) {
		cout << i << ": " << ar2[i] << endl;
	}
	two = x1 + x2;
	three = two + x3;
	four = three + x2;
	total = four + x1;
	cout << "\n" << x1 << " " << two << " " << three << " " << four << " " << total << endl;
}

void testingsetProb() {
	setProb();
	int ar2[5] = { 0 };
	for (int i = 0; i < 10000000; ++i) {
		int b = gen();
		if (b < -75)
			ar2[0]++;
		else if (b <= -25)
			ar2[1]++;
		else if (b < 25)
			ar2[2]++;
		else if (b <= 75)
			ar2[3]++;
		else
			ar2[4]++;
		if (i % 1000000 == 0) {
			cout << "1";
		}
	}
	cout << endl;
	for (int i = 0; i < 5; ++i) {
		cout << i << ": " << ar2[i] << endl;
	}
}


int main() {
	srand(time(NULL));
	setProb();
	int y = 50;
	int x_init = 30;
	int area = y * (100 - x_init);
	cout << "Area: " << area << endl;
	for (int i = 0; i < x_init; ++i) {
		cout << x_init - i << endl;
		setAgg();
		totalA = 0;
		totalB = 0;
		totalC = 0;
		for (int k = 0; k < 500; ++k) {
			sim(x_init - i, y, 100 - i);
			aggregate(100 - i);
			if (k % 50 == 0) {
				cout << k << " ";
			}
		}
		totalAs.push_back(totalA);
		totalBs.push_back(totalB);
		totalCs.push_back(totalC);
		write(totalA, totalB, totalC, "X" + to_string(x_init - i) + "Y" + to_string(y) + "por" + to_string(area) + ".txt");
		cout << "\nsim over, next sim start\n";
	}
	writeTots("stddev300-FOREXCEL.txt");
	system("pause");
}
