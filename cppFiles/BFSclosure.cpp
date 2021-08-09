#include <iostream>
#include <vector>
#include <unordered_set>
// BFS Search for Path in *'s
// BFS is fine, but it is very inefficient for this project. Is not included in source code, but may be interesting to look at
// for a different problem/scenario

class ArElement {
public:
	ArElement(int xx, int yy) {
		x = xx;
		y = yy;
	}
	int retX() {
		return x;
	}
	int retY() {
		return y;
	}
	bool operator==(const ArElement& lhs) {
		return ((this->x == lhs.x) && (this->y == lhs.y));
	}
private:
	int x;
	int y;
};


bool validStart(char arr[100][200], int x, int y) {
	return ((arr[x - 1][y] == 'M' || arr[x][y - 1] == 'M' || arr[x - 1][y - 1] == 'M'));
}

bool validEnd(char arr[100][200], int x, int y) {
	return ((arr[x + 1][y] == 'M' || arr[x][y - 1] == 'M' || arr[x + 1][y - 1] == 'M'));
}

vector<ArElement> findAdjacents(char arr[100][200], int xx, int yy) {
	vector<ArElement> ret;
	if (arr[xx + 1][yy] == '*') {
		ArElement b(xx + 1, yy);
		ret.push_back(b);
	}
	if (arr[xx + 1][yy + 1] == '*') {
		ArElement b(xx + 1, yy + 1);
		ret.push_back(b);
	}
	if (arr[xx][yy + 1] == '*') {
		ArElement b(xx, yy + 1);
		ret.push_back(b);
	}
	if (arr[xx - 1][yy + 1] == '*') {
		ArElement b(xx - 1, yy + 1);
		ret.push_back(b);
	}
	if (arr[xx - 1][yy] == '*') {
		ArElement b(xx - 1, yy);
		ret.push_back(b);
	}
	if (arr[xx - 1][yy - 1] == '*') {
		ArElement b(xx - 1, yy - 1);
		ret.push_back(b);
	}
	if (arr[xx][yy - 1] == '*') {
		ArElement b(xx, yy - 1);
		ret.push_back(b);
	}
	if (arr[xx + 1][yy - 1] == '*') {
		ArElement b(xx + 1, yy - 1);
		ret.push_back(b);
	}
	return ret;
}

vector<ArElement> closureInit(char arr[100][200]) {
	vector<ArElement> ret;
	for (int x = 0; x < 30; x++) {
		for (int y = 0; y < 51; ++y) {
			//cout << arr[x][y] << " ";
			if (arr[x][y] == '*' && validStart(arr, x, y)) {
				ArElement pp(x, y);
				ret.push_back(pp);
			}
		}
	}
	return ret;
}

bool closureDet(char arr[100][200]) {
	vector<ArElement> bootup = closureInit(arr); 
	vector<ArElement> seen;
	for (int i = 0; i < bootup.size(); ++i) {
		vector<ArElement> queue;
		queue.push_back(bootup[i]);
		while (queue.size() != 0) {
			ArElement x = queue[0];
			queue.erase(queue.begin());
			if (find(seen.begin(), seen.end(), x) == seen.end()) {
				seen.push_back(x);
				if (x.retX() > 70 && (validEnd(arr, x.retX(), x.retY()))) {
					return true;
				}
			}
			vector<ArElement> check = findAdjacents(arr, x.retX(), x.retY());
			for (int k = 0; k < check.size(); ++k) {
				if (find(seen.begin(), seen.end(), check[k]) == seen.end()) {
					queue.push_back(check[k]);
				}
			}
		}
	}
	return false;
}
