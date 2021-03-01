#include <iostream>
#include <graphics.h>
#include <ctime>
#include <cmath>

#define WIDTH 700
#define HEIGHT 500

using namespace std;
  
class tfigure { 
      protected: 
       int dx, dy, color; 
      public: 
       tfigure();
};

class tpoint: public tfigure {
      protected:
      	int x, y; 
    public:
    	tpoint();
    	void move(); 
};

class tline: public tpoint {
    protected:
       int x1, y1;
       float time,length;
    public:
       tline();
       void move();
};

class tcircle: public tpoint {
    protected:
       int radius;
    public:
       tcircle();
    	void move();
};

class trectangle: public tline {
    protected:
       int x2, y2; 
       float angle; 
    public:
       trectangle();
       void move();
};

class trhomb: public tline {
    protected:
       int x2, y2;
       float angle; 
    public:
       trhomb();
       void move();
};

class ttriangle: public tline {
    protected:
       int x2, y2;
       float angle;
    public:
       ttriangle();
       void move();
};

class tellipse: public tcircle { 
    protected:
       int radius2; 
     public:
       tellipse();
       void move(); 
};


tfigure::tfigure() { 
     do {
	 	dx = rand() % 3 - 1; 
     	dy = rand() % 3 - 1;
     } while ((dx == 0) && (dy == 0));
     color = COLOR(rand() % 256, rand() % 256, rand() % 256);
}

tpoint::tpoint():tfigure() { 
     x = rand() % WIDTH;
     y = rand() % HEIGHT;
}

tline::tline():tpoint() {            
    do {
		x1 = rand() % 100 - 50;
     	y1 = rand() % 100 - 50;
	} while ((x1 == 0) && (y1 == 0));
     if (x + x1 > WIDTH) x1 = -x1;
     if (x - x1 < 0) x1 = -x1;        
     if (y + y1 > HEIGHT) y1 = -y1;        
     if (y - y1 < 0) y1 = -y1;       
     length = sqrt(x1 * x1 + y1 * y1);
     time = rand() % 360;             
}

tcircle::tcircle():tpoint() {
     radius = rand() % 40 + 10;
     if (x + radius > WIDTH - 2) x = WIDTH - radius;        
     if (x - radius < 2) x = radius;        
     if (y + radius > HEIGHT - 2) y = HEIGHT - radius;        
     if (y - radius < 2) y = radius;                       
}

trectangle::trectangle():tline() {
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > WIDTH - 2) x = WIDTH - x1;        
     if (x - abs(x1) < 2) x = x1;        
     if (y + abs(y1) > HEIGHT - 2) y = HEIGHT - y1;        
     if (y - abs(y1) < 2) y = y1;   
     angle = 2 * atan(abs(x1 / y1));
}

trhomb::trhomb():tline() {
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > WIDTH - 2) x = WIDTH - x1;        
     if (x - abs(x1) < 2) x = x1;        
     if (y + abs(y1) > HEIGHT - 2) y = HEIGHT - y1;        
     if (y - abs(y1) < 2) y = y1; 
     angle = 2 * atan(abs(x1 / y1));
}

ttriangle::ttriangle():tline() {  
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > WIDTH - 2) x = WIDTH - x1;        
     if (x - abs(x1) < 2) x = x1;        
     if (y + abs(y1) > HEIGHT - 2) y = HEIGHT - y1;        
     if (y - abs(y1) < 2) y = y1;   
     angle = 2 * atan(abs(x1 / y1));                   
}

tellipse::tellipse():tcircle() {
     radius2 = rand() % 40 + 10;     
     if (x + radius2 > WIDTH - 2) x = WIDTH - radius2;        
     if (x - radius2 < 2) x = radius2;        
     if (y + radius2 > HEIGHT - 2) y = HEIGHT - radius2;        
     if (y - radius2 < 2) y = radius2;
}

void tpoint::move() {
     setcolor(0);
     circle(x, y, 2);
     if (x + dx > WIDTH - 2) dx = -dx;
     if (x + dx < 2) dx = -dx;
     if (y + dy > HEIGHT - 2) dy = -dy;
     if (y + dy < 2) dy = -dy;
     x += dx;
     y += dy;
     setcolor(color);
     circle(x, y, 2);     
}

void tline::move() {
     setcolor(0);
     line(x - x1, y - y1, x + x1, y + y1);
        time += 0.05; 
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length);        
         if ((x + x1 + dx > WIDTH) || (x - x1 + dx > WIDTH)) dx = -dx;
         if ((x + x1 + dx < 0) || (x - x1 + dx < 0)) dx = -dx;
         if ((y + y1 + dy > HEIGHT) || (y - y1 + dy > HEIGHT)) dy = -dy;
         if ((y + y1 + dy < 0) || (y - y1 + dy < 0)) dy = -dy; 
         x += dx;
         y += dy; 
     setcolor(color);
     line(x - x1, y - y1, x + x1, y + y1);     
}

void tcircle::move() { 
     setcolor(0); 
     circle(x, y, radius);
     if (x + dx + radius > WIDTH - 2) dx = -dx;
     if (x + dx - radius < 2) dx = -dx;
     if (y + dy + radius > HEIGHT - 2) dy = -dy;
     if (y + dy - radius < 2) dy = -dy; 
     x += dx;
     y += dy;       
     setcolor(color);
     circle(x, y, radius);     
}

void trectangle::move() {
     setcolor(0);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x + x2, y + y2);
     line(x + x2, y + y2, x - x1, y - y1);
        time+=0.05; 
        x1 = int(sin(time) * length); 
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);        
         if ((x + x1 + dx > WIDTH - 4) || (x - x1 + dx > WIDTH - 4)) dx = -dx;
         if ((x + x1 + dx < 4) || (x - x1 + dx < 4)) dx = -dx;
         if ((y + y1 + dy > HEIGHT - 4) || (y - y1 + dy > HEIGHT - 4)) dy = -dy;
         if ((y + y1 + dy < 4) || (y - y1 + dy < 4)) dy = -dy; 
         x += dx;
         y += dy; 
     setcolor(color);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x + x2, y + y2);
     line(x + x2, y + y2, x - x1, y - y1);    
}

void trhomb::move() { 
     setcolor(0); 
     line(((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2, ((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2);
     line(((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2, ((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2);
     line(((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2, ((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2);
     line(((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2, ((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2);
     
        time += 0.05;
        x1 = int(sin(time) * length); 
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);        

         if (( x + x1 + dx > WIDTH - 4) || (x - x1 + dx > WIDTH - 4)) dx = -dx;
         if ((x + x1 + dx < 4) || (x - x1 + dx < 4)) dx = -dx;
         if ((y + y1 + dy > HEIGHT - 4) || (y - y1 + dy > HEIGHT - 4)) dy = -dy;
         if ((y + y1 + dy < 4) || (y - y1 + dy < 4)) dy = -dy; 
         x += dx;
         y += dy; 
        
     setcolor(color);
     line(((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2, ((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2);
     line(((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2, ((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2);
     line(((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2, ((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2);
     line(((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2, ((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2);    
}

void ttriangle::move() { 
     setcolor(0);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x - x1, y - y1);

        time += 0.05;
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);        

         if ((x + x1 + dx > WIDTH - 2) || (x - x1 + dx > WIDTH - 2)) dx = -dx;
         if ((x + x1 + dx < 2) || (x - x1 + dx < 2)) dx = -dx;
         if ((y + y1 + dy > HEIGHT - 2) || (y - y1 + dy > HEIGHT - 2)) dy = -dy;
         if ((y + y1 + dy < 2) || (y - y1 + dy < 2)) dy = -dy; 
         x += dx;
         y += dy; 
     
     setcolor(color);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x - x1, y - y1);         
}

void tellipse::move() {
     setcolor(0);
     ellipse(x, y, 0, 360, radius, radius2);                  
     if (x + dx + radius > WIDTH - 4) dx = -dx;
     if (x + dx - radius < 4) dx = -dx;
     if (y + dy + radius2 > HEIGHT - 4) dy = -dy;
     if (y + dy - radius2 < 0) dy = -dy; 
     x += dx;
     y += dy;     
     setcolor(color);
     ellipse(x, y, 0, 360, radius, radius2);       
}

int main()
{
	srand(time(NULL));
	int i;
	
	initwindow(WIDTH, HEIGHT, "Figure");	
	tpoint *p[20];
	tline *l[5];
	tcircle *c[5];
	trectangle *r[5];
	ttriangle *t[5];
	tellipse *e[5];
	trhomb *rh[5];
	
	for (i = 0; i < 20; i++) p[i] = new tpoint();
	for (i = 0; i < 5; i++) {
		l[i] = new tline();
		c[i] = new tcircle();
		r[i] = new trectangle();
		t[i] = new ttriangle();
		e[i] = new tellipse();
		rh[i] = new trhomb();
	}
	
	while (1) {
		for (i = 0; i < 20; i++) p[i]->move();
		for (i = 0; i < 5; i++) {
			l[i]->move();
			c[i]->move();
			r[i]->move();
			t[i]->move();
			e[i]->move();
			rh[i]->move();
		}
	}
	
	return 0;
}
