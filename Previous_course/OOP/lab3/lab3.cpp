#include <iostream>
#include <graphics.h>
#include <ctime>

#define POINTS 100
#define WIDTH 700
#define HEIGHT 500
#define RADIUS 1

using namespace std;

class tpoint {
	private:
		int x, y, dx, dy, color;
	public:
		tpoint();
		void move();
};

tpoint::tpoint() {
	x = rand() % WIDTH;
	y = rand() % HEIGHT;
	do {
		dx = rand() % 3 - 1;
		dy = rand() % 3 - 1;
	} while((dx == 0) && (dy == 0));
	color = COLOR(rand() % 256, rand() % 256, rand() % 256);
}

void tpoint::move() {
	setcolor(BLACK);
	circle(x, y, RADIUS);
	if (x + dx > WIDTH - 2) dx = -dx;
	if (x + dx < 2) dx = -dx;
	if (y + dy > HEIGHT - 2) dy = -dy;
	if (y + dy < 2) dy = -dy;
	x += dx;
	y += dy;
	setcolor(color);
	circle(x, y, RADIUS);
}

int main()
{
	srand(time(NULL));
	int i;
	
	initwindow(WIDTH, HEIGHT, "Space");
	tpoint *p[POINTS];
	for (i = 0; i < POINTS; i++) p[i] = new tpoint();
	while (1) {
		for (i = 0; i < POINTS; i++) p[i]->move();
	}

	return 0;
}
