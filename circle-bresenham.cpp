#include <stdio.h> 
#include<conio.h> 
#include <dos.h> 
#include <graphics.h>

void drawCircle(int xc, int yc, int x, int y)
{
  putpixel(xc+x, yc+y, RED); 
  putpixel(xc-x, yc+y, RED); 
  putpixel(xc+x, yc-y, RED); 
  putpixel(xc-x, yc-y, RED); 
  putpixel(xc+y, yc+x, RED); 
  putpixel(xc-y, yc+x, RED);
  putpixel(xc+y, yc-x, RED); 
  putpixel(xc-y, yc-x, RED);
}

void circleBres(int xc, int yc, int r)
{
  int x = 0, y = r; 
  int d = 3 - 2 * r;
  drawCircle(xc, yc, x, y); 
  while (y >= x)
  {
    x++;
    if(d > 0){
      y--;
      d = d + 4*(x-y) + 10;
    }
    else d = d + 4*x + 6; 
    drawCircle(xc, yc, x, y); 
    delay(100);
  }
}

void main()
{
  int xc, yc , r2;
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TC\\BGI"); 
  printf("Enter the values of xc and yc : "); scanf("%d%d",&xc,&yc);
  printf("Enter the value of radius : "); scanf("%d",&r2);
  circleBres(xc, yc, r2);	
}




