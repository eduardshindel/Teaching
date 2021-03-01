#include <iostream>
#include <graphics.h>
#include <ctime>
#include <cmath>

#define WIDTH 700
#define HEIGHT 500

class tfigure { // ????? ????? ??? ?????
      protected: // ???? ??? ?????? ?????? ? ????????
       int dx, dy;
       int color;
       int width, height;
      public: // ???? ??? ????
       tfigure(int, int);
       virtual void move() {};
};
class tpoint: public tfigure {
      protected:
       int x, y;     // ??????????
      public:
       tpoint(int, int);
       virtual void move();
};
class tline: public tpoint {
      protected:
       int x1, y1; // ?????? ?????????? ??????? ??????????? ?? ?????, ?????? ??????????? ???
       int typemove;
	   float time, length; 
	  public:
       tline(int, int);
       virtual void move();
};
class tcircle: public tpoint {
      protected:
       int r1; // ??????
      public:
       tcircle(int, int);
       virtual void move();
};
class trectangle: public tline {
      protected:
       int x2, y2; // ?????? ?????????? ???????, ????????? ???????????
       float angle; // ????
      public:
       trectangle(int, int);
       virtual void move();
};
class tromb: public tline {
      protected:
       int x2, y2; // ?????? ??????????, ????????? ????? ???????????
       float angle; // ????
      public:
       tromb(int, int);
       virtual void move();
};
class ttriangle: public tline {
      protected:
       int x2, y2; // ?????? ??????????
       float angle; // ????
      public:
       ttriangle(int, int);
       virtual void move();
};
class tellipse: public tcircle {
      protected:
       int r2; // ?????? ??????
      public:
       tellipse(int, int);
       virtual void move(); 
};
//????????????
tfigure::tfigure(int w, int h) { // ??????????? ?????, ??? ??????
     width = w; // ??????
     height = h; // ??????  
     dx = rand() % 3 - 1;
     dy = rand() % 3 - 1;
    while ((dx == 0) & (dy == 0)) {
	 	if ((rand() % 2) == 1){
			dy = rand() % 3 - 1;
		} else {
			dx = rand() % 3 - 1;
		}
	 }
     color = COLOR(rand() % 256, rand() % 256, rand() % 256); // ????
}
tpoint::tpoint(int w, int h):tfigure(w, h) { // ??????????? ?????, ??????? ?????????? ??????????? ??????
     x = rand() % w; // ???????? ??????????
     y = rand() % h;
}
tline::tline(int w, int h):tpoint(w, h) { // ?????
     typemove = rand() % 2;
     x1 = rand() % 100 - 50; // ?????? ?????????? (???????? ???????????? ?????? ????? ?? -50 ?? 50)
     y1 = rand() % 100 - 50;
     while (y1 == 0) y1 = rand() % 100 - 50; // ???? ????? = 0 ?????????? ??????, ????? ?? ?????????? ????? ?????? ??????
     if (x + abs(x1) > w) x = w - x1;
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > h) y = h - y1;        
     if (y - abs(y1) < 0) y = y1;       
     length = sqrt(x1 * x1 + y1 * y1); // ??????? ?????
     time = rand() % 360;   // ????? - ????. ???????? (????? ?????? ???? ????????)              
}
tcircle::tcircle(int w, int h):tpoint(w, h) { // ??????????
     r1 = rand() % 40 + 10;
     if (x + r1 > w) x = w - r1;        
     if (x - r1 < 0) x = r1;        
     if (y + r1 > h) y = h - r1;        
     if (y - r1 < 0) y = r1;                       
}
trectangle::trectangle(int w, int h):tline(w, h) {
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > w) x = w - x1;        
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > h) y = h - y1;        
     if (y - abs(y1) < 0) y = y1;   
     angle= 2 * atan(abs(x1 / y1)); // ????????? ???? ???????? ??????????????, ???? ?????????? ?????
}
tromb::tromb(int w, int h):tline(w, h) {
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > w) x = w - x1;        
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > h) y = h - y1;        
     if (y - abs(y1) < 0) y = y1; 
     angle = 2 * atan(abs(x1 / y1));
}
ttriangle::ttriangle(int w, int h):tline(w, h) {  
     x2 = -x1;
     y2 = y1;
     if (x + abs(x1) > w) x = w - x1;        
     if (x - abs(x1) < 0) x = x1;        
     if (y + abs(y1) > h) y = h - y1;        
     if (y - abs(y1) < 0) y = y1;   
     angle = 2 * atan(abs(x1 / y1));                   
}
tellipse::tellipse(int w, int h):tcircle(w, h) {
     r2 = rand() % 40 + 10;     
     if (x + r2 > w) x = w - r2;        
     if (x - r2 < 0) x = r2;        
     if (y + r2 > h) y = h - r2;        
     if (y - r2 < 0) y = r2;
}
//????????
void tpoint::move() { // ???????? ?????
     setcolor(0);
     rectangle(x, y, x + 1, y + 1);
     if (x + dx > width) dx = -dx;
     if (x + dx < 0) dx = -dx;
     if (y + dy > height) dy = -dy;
     if (y + dy < 0) dy = -dy;
     x += dx;
     y += dy;
     setcolor(color);
     rectangle(x, y, x + 1, y + 1);     
}
void tline::move() { // ???????? ?????
     setcolor(0);
     line(x - x1, y - y1, x + x1, y + y1);    
     	time += 0.05; 
     	x1 = int(sin(time) * length); 
    	y1 = int(cos(time) * length);        

         if ((x + x1 + dx > width) | (x - x1 + dx > width)) dx = -dx; 
         if ((x + x1 + dx < 0) | (x - x1 + dx < 0)) dx = -dx;
         if ((y + y1 + dy > height) | (y - y1 + dy > height)) dy = -dy;
         if ((y + y1 + dy < 0) | (y - y1 + dy < 0)) dy = -dy; 
         x += dx;
         y += dy; 
     
     setcolor(color);
     line(x - x1, y - y1, x + x1, y + y1);     
}
void tcircle::move() { // ??????????
     setcolor(0);
     circle(x, y, r1);   
     if (x + dx + r1 > width) dx = -dx;
     if (x + dx - r1 < 0) dx = -dx;
     if (y + dy + r1 > height) dy = -dy;
     if (y + dy - r1 < 0) dy = -dy; 
     x += dx;
     y += dy;    
     setcolor(color);
     circle(x, y, r1);     
}
void trectangle::move() { // ?????????????
     setcolor(0);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x + x2, y + y2);
     line(x + x2, y + y2, x - x1, y - y1);  
if (typemove == 1) { // ???? ????? ???????
        time += 0.05; // ?????? ?????
        x1 = int(sin(time) * length); // ????????? ?????????? ????? ????????
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);        
     } else { // ????? ?????? ???????
         if ((x + x1 + dx > width) | (x - x1 + dx > width)) dx = -dx; // ???????? ????? ?? ?????? ?? ???????
         if ((x + x1 + dx < 0) | (x - x1 + dx < 0)) dx = -dx;
         if ((y + y1 + dy > height) | (y - y1 + dy > height)) dy = -dy;
         if ((y + y1 + dy < 0) | (y - y1 + dy < 0)) dy = -dy; 
         x += dx; //???????
         y += dy; 
     }       
     setcolor(color);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x + x2, y + y2);
     line(x + x2, y + y2, x - x1, y - y1);    
}
void tromb::move() { // ???? - ??????? ????? - ???????? ?????? ?????????????
     setcolor(0); 
     line(((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2, ((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2);
     line(((x - x2) + (x + x1)) / 2, ((y - y2) + (y + y1)) / 2, ((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2);
     line(((x + x1) + (x + x2)) / 2, ((y + y1) + (y + y2)) / 2, ((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2);
     line(((x + x2) + (x - x1)) / 2, ((y + y2) + (y - y1)) / 2, ((x - x1) + (x - x2)) / 2, ((y - y1) + (y - y2)) / 2);     
	if (typemove == 1) { // ???? ????? ??????? ?????? ????? ???
        time += 0.05;
        x1 = int(sin(time) * length); // ????????? ??????????
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);        
     } else {
         if ((x + x1 + dx > width) | (x - x1 + dx > width)) dx = -dx;
         if ((x + x1 + dx < 0) | (x - x1 + dx < 0)) dx = -dx;
         if ((y + y1 + dy > height) | (y - y1 + dy > height)) dy = -dy;
         if ((y + y1 + dy < 0) | (y - y1 + dy < 0)) dy = -dy; 
         x += dx;
         y += dy; 
     }      
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
     if (typemove == 1) {
        time += 0.05;
        x1 = int(sin(time) * length);
        y1 = int(cos(time) * length); 
        x2 = int(sin(time + angle) * length);
        y2 = int(cos(time + angle) * length);        
     } else {
         if ((x + x1 + dx > width) | (x - x1 + dx > width)) dx = -dx;
         if ((x + x1 + dx < 0) | (x - x1 + dx < 0)) dx = -dx;
         if ((y + y1 + dy > height) | (y - y1 + dy > height)) dy = -dy;
         if ((y + y1 + dy < 0) | (y - y1 + dy < 0)) dy = -dy; 
         x += dx;
         y += dy; 
     }   
     setcolor(color);
     line(x - x1, y - y1, x - x2, y - y2);
     line(x - x2, y - y2, x + x1, y + y1);
     line(x + x1, y + y1, x - x1, y - y1);         
}
void tellipse::move() {
     setcolor(0);
     ellipse(x, y, 0, 0, r1, r2);   
	 if (x + dx + r1 > width) dx = -dx;
     if (x + dx - r1 < 0) dx = -dx;
     if (y + dy + r2 > height) dy = -dy;
     if (y + dy - r2 < 0) dy = -dy; 
     x += dx;
     y += dy;                     
     setcolor(color);
     ellipse(x, y, 0, 0, r1, r2);       
}
