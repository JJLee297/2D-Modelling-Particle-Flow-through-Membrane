/*
works with two points, an anchor point and a tracing point. Anchor point will always be on a stuck particle/membrane point, 
and tracing point will always be adjacent to the anchor point.
Anchor point is initialized as first stuck particle/membrane point  on leftmost column, from the top. Tracing point is on top of anchor point. 
Tracing point will swing clockwise around the anchor point until it either hits another stuck particle/membrane point, or hits the wall. 
If it hits a wall, anchor point/tracing point is re-initialized under the first spot. If it hits another stuck particle/membrane point,
that becomes the new anchor point, and the tracing point continues to swing clockwise. 
If tracing point reaches bottom of pore, the pore is open. If tracing point reaches across pore to the other wall, the membrane is closed.
runs pretty fast, but is not used in dynamicDomain.cpp or constantDomain.cpp. 
*/

#include <iostream>

using namespace std;

class point {
private:
	int x;
	int y;
public:
	int returnX() {
		return x;
	}
	int returnY() {
		return y;
	}
	void setX(int xx) {
		x = xx;
	}
	void setY(int yy) {
		y = yy;
	}
};

point OutlineSquare;
point ASP;

void show(char arr[100][200]) {
	for (int y = 199; y >= 0; --y) {
		for (int x = 0; x < 100; ++x) {
			if (x != OutlineSquare.returnX() || y != OutlineSquare.returnY()) {
				if (x != ASP.returnX() || y != ASP.returnY()) {
					cout << arr[x][y];
				}
				else {
					cout << "A";
				}
			}
			else {
				cout << "O";
			}
		}
		cout << endl;
	}
}

bool move(char arr[100][200]) {
	if (OutlineSquare.returnX() > ASP.returnX()) {
		if (OutlineSquare.returnY() > ASP.returnY()) {
			if (arr[OutlineSquare.returnX()][OutlineSquare.returnY() - 1] == ' ') {
				OutlineSquare.setY(OutlineSquare.returnY() - 1);
				return true;
			}
			else {
				ASP.setX(ASP.returnX() + 1);
				return true;
			}
		}
		else if (OutlineSquare.returnY() == ASP.returnY()) {
			if (arr[OutlineSquare.returnX()][OutlineSquare.returnY() - 1] == ' ') {
				OutlineSquare.setY(OutlineSquare.returnY() - 1);
				return true;
			}
			else {
				ASP.setX(ASP.returnX() + 1);
				ASP.setY(ASP.returnY() - 1);
				return true; 
			}
		}
		else {
			if (arr[OutlineSquare.returnX() - 1][OutlineSquare.returnY()] == ' ') {
				OutlineSquare.setX(OutlineSquare.returnX() - 1);
				return true;
			}
			else {
				ASP.setY(ASP.returnY() - 1);
				return true; 
			}
		}
	}
	else if (OutlineSquare.returnX() == ASP.returnX()) {
		if (OutlineSquare.returnY() > ASP.returnY()) {
			if (arr[OutlineSquare.returnX() + 1][OutlineSquare.returnY()] == ' ') {
				OutlineSquare.setX(OutlineSquare.returnX() + 1);
				return true; 
			}
			else {
				ASP.setX(ASP.returnX() + 1);
				ASP.setY(ASP.returnY() + 1);
				return true; 
			}
		}
		else {
			if (OutlineSquare.returnX() == 0) {
				while (1) {
					if (arr[OutlineSquare.returnX()][OutlineSquare.returnY() - 1] != ' ') {
						ASP.setX(0);
						ASP.setY(OutlineSquare.returnY() - 1);
						return true;
					}
					else {
						OutlineSquare.setY(OutlineSquare.returnY() - 1);
					}
				}
			}
			if (arr[OutlineSquare.returnX() - 1][OutlineSquare.returnY()] == ' ') {
				OutlineSquare.setX(OutlineSquare.returnX() - 1);
				return true;
			}
			else {
				ASP.setX(ASP.returnX() - 1);
				ASP.setY(ASP.returnY() - 1);
				return true; 
			}
		}
	}
	else {
		if (OutlineSquare.returnY() > ASP.returnY()) {
			if (arr[OutlineSquare.returnX() + 1][OutlineSquare.returnY()] == ' ') {
				OutlineSquare.setX(OutlineSquare.returnX() + 1);
				return true;
			}
			else {
				ASP.setY(ASP.returnY() + 1);
				return true; 
			}
		}
		else if (OutlineSquare.returnY() == ASP.returnY()) {
			if (arr[OutlineSquare.returnX()][OutlineSquare.returnY() + 1] == ' ') {
				OutlineSquare.setY(OutlineSquare.returnY() + 1);
				return true;
			}
			else {
				ASP.setX(ASP.returnX() - 1);
				ASP.setY(ASP.returnY() + 1);
				return true; 
			}
		}
		else {
			if (arr[OutlineSquare.returnX()][OutlineSquare.returnY() + 1] == ' ') {
				OutlineSquare.setY(OutlineSquare.returnY() + 1);
				return true;
			}
			else {
				ASP.setX(ASP.returnX() - 1);
				return true; 
			}
		}
	}
}

bool contourOutline(char arr[100][200], int rightM) {
	for (int y = 199; y >= 0; y--) {
		if (arr[0][y] == '*') {
			OutlineSquare.setX(0);
			ASP.setX(0);
			OutlineSquare.setY(y + 1);
			ASP.setY(y);
			break;
		}
	}
	bool endCheck = false;
	while (!endCheck) {
		endCheck = (ASP.returnX() >= rightM) 
			&&(ASP.returnX() == 99 
			|| arr[ASP.returnX()][ASP.returnY() - 1] == 'M'
			|| arr[ASP.returnX() + 1][ASP.returnY()] == 'M'
			|| arr[ASP.returnX() + 1][ASP.returnY() - 1] == 'M');
		move(arr);
		if (OutlineSquare.returnY() == 0) {
			return false;
		}
	}
	return true; 
}
