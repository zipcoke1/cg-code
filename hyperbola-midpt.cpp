#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<dos.h>
#include<stdlib.h>

void main()
{
  int gd=DETECT, gm;
  initgraph(&gd,&gm,”c:\\tc\\bgi”);
  float x,y, xc,yc, d,fx,fy,b,a;
  d=b*b*(a+0.5)*(a+0.5)-a*a-a*a*b*b;
  printf(“enter centre (xc,yc)\n”);
  scanf(“%f %f”,&xc,&yc);
  printf(“enter a & b”);
  scanf(“%f %f”,&a,&b);
  x=a;
  y=0;
  fx=2*b*b*a;
  fy=0;
  setcolor(MAGENTA);
  line(0,240,640,240);
  line(320,0,320,480);
  while(abs(fy)<=fx)
    {
    if(d>=0) d=d-a*a*(2*y+3);
    else
    {
      d=d-a*a*(2*y+3)+b*b*(2*x+2);
      x++;
      fx=fx+2*b*b;
    }
    y++;
    fy=fy+2*a*a;
    putpixel(x+320+xc,240-y-yc,GREEN);
    putpixel(x+320+xc,240+y-yc,GREEN);
    putpixel(-x+320+xc,240-y-yc,GREEN);
    delay(20);
    putpixel(-x+320+xc,240+y-yc,GREEN);
    delay(20);
  }
  x=p/2;
  y=p;
  d=-p;
  while(y<3*p)
  {
    x++;
    if(d>=0) d=d-2*p;
    else
    {
      d=d+2*y+2-2*p;
      y++;
    }
    putpixel(x+320+xc,240-y-yc,RED);
    delay(20);
    putpixel(x+320+xc,240+y-yc,RED);
    delay(20);
  }
  getch();
}
