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

	void moveParticleXY(int xpos, int ypos) {
		x = xpos;
		y = ypos;
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

	Particle moveParticle() {
		srand(time(NULL));
		int dir = rand() % 5 + 1;
		Particle newPart(x, y);
		// 1 is left, 2 is down-left, 3 is down, 4 is down-right, 5 is right
		switch (dir) {
		case 1:
			if (newPart.getWidth() > 0)
				newPart.moveParticleXY(x - 1, y);
			else
				newPart.moveParticleXY(99, y);
			break;
		
		case 2:
			if (newPart.getWidth() > 0)
				newPart.moveParticleXY(x - 1, y);
			else
				newPart.moveParticleXY(99, y);
			if (newPart.getHeight() > 0)
				newPart.moveParticleXY(x, y - 1);
			break;
		
		case 3:
			if (newPart.getHeight() > 0)
				newPart.moveParticleXY(x, y - 1);
			break;
		
		case 4:
			if (newPart.getWidth() < 99)
				newPart.moveParticleXY(x + 1, y);
			else
				newPart.moveParticleXY(0, y);
			if (newPart.getHeight() > 0)
				newPart.moveParticleXY(x, y - 1);
			break;
		
		case 5:
			if (newPart.getWidth() < 99)
				newPart.moveParticleXY(x + 1, y);
			else
				newPart.moveParticleXY(0, y);
			break;
		}

		return newPart;
	}

private:
	int x;
	int y;
	int dir;
	bool stuck;
};
