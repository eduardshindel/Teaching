#include <iostream>
#include <graphics.h>
#include <ctime>
#include <cmath>

#define WIDTH 700
#define HEIGHT 500

using namespace std;
  

class tfigure { 
      protected: 
       int dx, dy, scrw, scrh;
       int color;
      public: 
       tfigure();
       virtual void move() {};
       virtual void move(int) {};
};
class tpoint: public tfigure {
      protected:
       int x, y;    
      public:
       tpoint();
       void move();
       void move(int);
};
class tline: public tpoint {
      protected:
       int x1, y1;
	   float time, length, spd; 
	  public:
       tline();
       void move();
       void move(int);
};
class tcircle: public tpoint {
      protected:
       int r1; 
      public:
       tcircle();
       void move();
       void move(int);
};
class trectangle: public tline {
      protected:
       int x2, y2; 
       float angle;
      public:
       trectangle();
       void move();
       void move(int);
};
class tromb: public tline {
      protected:
       int x2, y2; 
       float angle; 
      public:
       tromb();
       void move();
       void move(int);
};
class ttriangle: public tline {
    protected:
    	int x2, y2; 
    	float angle; 
    public:
    	ttriangle();
        void move();
        void move(int);
};
class tellipse: public tline {
    protected:
       int x2, y2; 
       float angle, t, length2;
    public:
    	tellipse();
    	void move(); 
    	void move(int);
};

tfigure::tfigure() {
    do {
		dy = rand() % 3 - 1;
		dx = rand() % 3 - 1;
	} while ((dx == 0) | (dy == 0));
    color = COLOR(rand() % 256, rand() % 256, rand() % 256);
}

tpoint::tpoint():tfigure() {
	scrw = WIDTH - (WIDTH / 5);
	scrh = HEIGHT - (HEIGHT / 4);
    x = 100 + rand() % scrw;
    y = 100 + rand() % scrh;
}

tline::tline():tpoint() { 
     spd = 0.05;              //spd=0.02
     x1 = rand() % 100 - 50;
     y1 = rand() % 100 - 50; 
     while (y1 == 0) y1 = rand() % 100 - 50;
     if (x + abs(x1) > scrw+5) x = scrw - x1; //границы поправил
     if (x - abs(x1) < 0+5) x = x1;        
     if (y + abs(y1) > scrh+5) y = scrh - y1;        
     if (y - abs(y1) < 0+5) y = y1;       
     length = sqrt(x1 * x1 + y1 * y1);
     time = rand() % 360;            
}
tcircle::tcircle():tpoint() {
     r1 = rand() % 40 + 10;
     if (x + r1 > scrw) x = scrw - r1;        
     if (x - r1 < 0) x = r1;        
     if (y + r1 > scrh) y = scrh - r1;        
     if (y - r1 < 0) y = r1;                       
}

trectangle::trectangle():tline() {
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > scrw) x = scrw - x1;        
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > scrh) y = scrh - y1;        
     if (y - abs(y1) < 0) y = y1;   
     angle= 2 * atan(abs(x1 / y1));
}

tromb::tromb():tline() {
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > scrw) x = scrw - x1;        
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > scrh) y = scrh - y1;        
     if (y - abs(y1) < 0) y = y1; 
     angle = 2 * atan(abs(x1 / y1));
}

ttriangle::ttriangle():tline() {  
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > scrw) x = scrw - x1;        
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > scrh) y = scrh - y1;        
     if (y - abs(y1) < 0) y = y1;   
     angle = 2 * atan(abs(x1 / y1));                   
}

tellipse::tellipse():tline() {
     x2 = -x1;
     y2 = y1;
     t = 0;
     if (x + length * cos(t) - y + length2 * sin(t) > scrw) x = scrw - length * cos(t) - length2 * sin(t);        
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > scrh) y = scrh - y1;        
     if (y - abs(y1) < 0) y = y1; 
     length = x1;
     length2 = y1;
     angle = 2 * atan(abs(x1 / y1));
}

void tpoint::move() {
     setcolor(0);
     circle(x, y, 2);
     if (x + dx + 2 > WIDTH) dx = -dx;
     if (x + dx - 2 < 0) dx = -dx;
     if (y + dy + 2 > HEIGHT) dy = -dy;
     if (y + dy - 2 < 0) dy = -dy;
     x += dx;
     y += dy;
     setcolor(color);
     circle(x, y, 2);
}

void tpoint::move(int w) {
     cout << w;
}

void tline::move() {
     setcolor(0);
     line(x - x1, y - y1, x + x1, y + y1);      
		if ((x + int(sin(time) * length) + dx > WIDTH) | (x - int(sin(time) * length) + dx > WIDTH)) {
			dx = -dx;
			spd = -spd;
		}
        if ((x + int(sin(time) * length) + dx < 0) | (x - int(sin(time) * length) + dx < 0)) {
			dx = -dx;
			spd = -spd;
    	}
        if ((y + int(cos(time) * length) + dy > HEIGHT) | (y - int(cos(time) * length) + dy > HEIGHT)) {
			dy = -dy;
			spd = -spd;
		}
        if ((y + int(cos(time) * length) + dy < 0) | (y - int(cos(time) * length) + dy < 0)) {
			dy = -dy;
			spd = -spd;
		} 
        x += dx;
        y += dy;   
     	time += spd; 
     	x1 = int(sin(time) * length); 
    	y1 = int(cos(time) * length);   
     setcolor(color);
     line(x - x1, y - y1, x + x1, y + y1);     
}

void tline::move(int w) {
	cout << w;
}

void tcircle::move() {
     setcolor(0);
     circle(x, y, r1);   
     if (x + dx + r1 > WIDTH) dx = -dx;
     if (x + dx - r1 < 0) dx = -dx;
     if (y + dy + r1 > HEIGHT) dy = -dy;
     if (y + dy - r1 < 0) dy = -dy; 
     x += dx;
     y += dy;    
     setcolor(color);
     circle(x, y, r1);     
}

void tcircle::move(int w) {
	cout << w;
}

void trectangle::move() {
     setcolor(0);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x + x2, y + y2);
     line(x + x2, y + y2, x - x1, y - y1);  
		if (((x + int(sin(time) * length) + dx > WIDTH) | (x - int(sin(time) * length) + dx > WIDTH)) | ((x + int(sin(time + angle) * length) + dx > WIDTH) | (x - int(sin(time + angle) * length) + dx > WIDTH))) {
			dx = -dx;
			spd = -spd;
		}
       if (((x + int(sin(time) * length) + dx < 0) | (x - int(sin(time) * length) + dx < 0)) | ((x + int(sin(time + angle) * length) + dx < 0) | (x - int(sin(time + angle) * length) + dx < 0))) {
			dx = -dx;
			spd = -spd;
    	}
        if (((y + int(cos(time) * length) + dy > HEIGHT) | (y - int(cos(time) * length) + dy > HEIGHT)) | ((y + int(cos(time + angle) * length) + dy > HEIGHT) | (y - int(cos(time + angle) * length) + dy > HEIGHT))) {
			dy = -dy;
			spd = -spd;
		}
        if (((y + int(cos(time) * length) + dy < 0) | (y - int(cos(time) * length) + dy < 0)) | ((y + int(cos(time + angle) * length) + dy < 0) | (y - int(cos(time + angle) * length) + dy < 0))) {
			dy = -dy;
			spd = -spd;
		} 
		time += spd;
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length); 
        x += dx;
        y += dy; 
     setcolor(color);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x + x2, y + y2);
     line(x + x2, y + y2, x - x1, y - y1);    
}

void trectangle::move(int w) {
	cout << w;
}

void tromb::move() {
     setcolor(0); 
     line(((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2, ((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2);
     line(((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2, ((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2);
     line(((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2, ((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2);
     line(((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2, ((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2);    
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);  
		if (((((x - x1) + (x - x2)) / 2 + dx > WIDTH) | (((x - x2) + (x + x1)) / 2 + dx > WIDTH)) | ((((x + x1) + (x + x2)) / 2 + dx > WIDTH) | (((x + x2) + (x - x1)) / 2 + dx > WIDTH))) {
			dx = -dx;
			spd = -spd;
		}
       if (((((x - x1) + (x - x2)) / 2 + dx < 0) | (((x - x2) + (x + x1)) / 2 + dx < 0)) | ((((x + x1) + (x + x2)) / 2 + dx < 0) | (((x + x2) + (x - x1)) / 2 + dx < 0))) {
			dx = -dx;
			spd = -spd;
    	}
        if (((((y - y1) + (y - y2)) / 2 + dy > HEIGHT) | (((y - y2) + (y + y1)) / 2 + dy > HEIGHT)) | ((((y + y1) + (y + y2)) / 2 + dy > HEIGHT) | (((y + y2) + (y - y1)) / 2 + dy > HEIGHT))) {
			dy = -dy;
			spd = -spd;
		}
        if (((((y - y1) + (y - y2)) / 2 + dy < 0) | (((y - y2) + (y + y1)) / 2 + dy < 0)) | ((((y + y1) + (y + y2)) / 2 + dy < 0) | (((y + y2) + (y - y1)) / 2 + dy < 0))) {
			dy = -dy;
			spd = -spd;
		} 
		time += spd;
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);      
         x += dx;
         y += dy; 
     setcolor(color);
     line(((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2, ((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2);
     line(((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2, ((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2);
     line(((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2, ((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2);
     line(((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2, ((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2);     
}

void tromb::move(int w) {
	cout << w;
}

void ttriangle::move() {
     setcolor(0);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x - x1, y - y1);
     x1 = int(sin(time) * length); 
     y1 = int(cos(time) * length);   
     x2 = int(sin(time + angle) * length);
     y2 = int(cos(time + angle) * length); 
	if ((x - x1 + dx > WIDTH) | (x - x2 + dx > WIDTH) | (x + x1 + dx > WIDTH)) {
			dx = -dx;
			spd = -spd;
		}
        if ((x - x1 + dx < 0) | (x - x2 + dx < 0) | (x + x1 + dx < 0)) {
			dx = -dx;
			spd = -spd;
    	}
        if ((y - y1 + dy > HEIGHT) | (y - y2 + dy > HEIGHT) | (y + y1 + dy > HEIGHT)) {
			dy = -dy;
			spd = -spd;
		}
        if ((y - y1 + dy < 0) | (y - y2 + dy < 0) | (y + y1 + dy < 0)) {
			dy = -dy;
			spd = -spd;
		} 
		 time += spd; 
	    x1 = int(sin(time) * length); 
    	y1 = int(cos(time) * length);   
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);        
        x += dx;
        y += dy;       
     setcolor(color);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x - x1, y - y1);         
}

void ttriangle::move(int w) {
	cout << w;
}

void tellipse::move() {
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length2); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length2); 
     while (t < 360) {
     	t += 1;   
		int xc = length * cos(t), yc = length2 * sin(t);  	
		putpixel(x + xc * cos(time) - yc * sin(time), y + yc * cos(time) + xc * sin(time), 0);
	 }
	 t = 0;
		
	
		time += spd;
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length2); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length2);      
         x += dx;
         y += dy; 
     setcolor(color);
     while (t < 360) {
     	t += 1;
		int xc = length * cos(t), yc = length2 * sin(t);
		if ((x + xc * cos(time) - yc * sin(time) + dx > WIDTH) || (x + xc * cos(time) - yc * sin(time) + dx < 0)) {
				dx = -dx;
				spd = -spd;
		}
		if ((y + yc * cos(time) + xc * sin(time) + dy > HEIGHT) || (y + yc * cos(time) + xc * sin(time) + dy < 0)) {
				dy = -dy;
				spd = -spd;
		}   	
		putpixel(x + xc * cos(time) - yc * sin(time), y + yc * cos(time) + xc * sin(time), color);
	 }
	 t = 0;
}


void tellipse::move(int w) {
	cout << w;
}
    

int main()
{
	srand(time(NULL));
	int i;
	
	initwindow(WIDTH, HEIGHT, "Figure");	
	
	tfigure *f[42];
	
	i = 0;
	while (i < 20) f[i] = new tpoint(), i++;
	while (i < 25)  f[i] = new tline(), i++;
	f[i] = new tcircle();
	i++;
	while (i < 31) f[i] = new trectangle(), i++;
	while (i < 36) f[i] = new ttriangle(), i++;
	f[i] = new tellipse();
	i++;
	while (i < 42) f[i] = new tromb(), i++;
	
	while (1) for (i = 0; i < 42; i++) f[i]->move();
	
	return 0;
}
