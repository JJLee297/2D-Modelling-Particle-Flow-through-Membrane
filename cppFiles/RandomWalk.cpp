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
	}

	int getHeight() {
		return y;
	}

	int getWidth() {
		return x;
	}

	void moveParticle(int dom,  int dir) {
		if (dir < 55) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
		}
		// left down
		else if (dir < 2018) {
			if (x > 0)
				x--;
			else
				x = dom - 1;
			y--;
		}
		// down
		else if (dir < 7982) {
			y--;
		}
		// right down
		else if (dir < 9945) {
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
	
	void moveParticle2(int dom,  double dir) {
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
