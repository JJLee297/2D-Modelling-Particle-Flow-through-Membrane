/*
Use for constant domain + wrap-around effect
flow pattern can be modified here
for dynamicDomain, add int argument to moveParticle(): as follows
	void moveParticle(int dom) {...}
	replace all '99' with 'dom - 1'
for no wrap-around effect (particle cannot teleport after reaching wall), remove all '=' operations in moveParticle
*/
#include <cstdlib>
#include <iostream>
#include <stdlib.h>  
#include <time.h>

using namespace std;

class Particle {
public:
	Particle(int xpos, int ypos) {
		x = xpos;
		y = ypos;
		stuck = false;
	}

	bool getState() {
		return stuck;
	}

	int getHeight() {
		return y;
	}

	int getWidth() {
		return x;
	}
	void moveParticle() {
		int dir = rand() % 5 + 1;
		// 1 is left, 2 is down-left, 3 is down, 4 is down-right, 5 is right
		switch (dir) {
		case 1:
			if (x > 0)
				x--;
			else
				x = 99;
			break;
		
		case 2:
			if (x > 0)
				x--;
			else
				x = 99;
			if (y > 0)
				y--;
			break;
		
		case 3:
			if (y > 0)
				y--;
			break;
		
		case 4:
			if (x < 99)
				x++;
			else
				x = 0;
			if (y > 0)
				y--;
			break;
		
		case 5:
			if (x < 99)
				x++;
			else
				x = 0;
			break;
		}
	}

private:
	int x;
	int y;
	bool stuck;
};
