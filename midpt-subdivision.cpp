#include<iostream.h> 
#include<graphics.h> 
#include<conio.h> 
#include<math.h>

class LineCoordinates
{
  public:
    float x_1, y_1, x_2, y_2;
    LineCoordinates(const float x1,const float y1,const float x2,const float y2)
    {
      x_1=x1; 
      y_1=y1; 
      x_2=x2; 
      y_2=y2;
    }
};

class WindowCoordinates
{
  public:
    float x_min,y_min,x_max,y_max;
    WindowCoordinates(const float x1,const float y1,const float x2,const float y2)
    {
      x_min=x1;
      y_min=y1;
      x_max=x2;
      y_max=y2;
    }
};

class RegionCode
{
  public:
    int bit_1, bit_2, bit_3, bit_4;
    RegionCode( )
    {
      bit_1=0; bit_2=0; bit_3=0; bit_4=0;
    }
    const int equal_zero( )
    {
      if(bit_1==0 && bit_2==0 && bit_3==0 && bit_4==0) return 1;
      return 0;
    }
    void get_logical_AND(RegionCode rc1,RegionCode rc2)
    {
      if(rc1.bit_1==1 && rc2.bit_1==1) bit_1=1;
      if(rc1.bit_2==1 && rc2.bit_2==1) bit_2=1;
      if(rc1.bit_3==1 && rc2.bit_3==1) bit_3=1;
      if(rc1.bit_4==1 && rc2.bit_4==1) bit_4=1;
    }
    void get_region_code(const WindowCoordinates wc,const int x,const int y)
    {
      if((wc.x_min-x)>0) bit_1=1;
      if((x-wc.x_max)>0) bit_2=1;
      if((wc.y_min-y)>0) bit_3=1;
      if((y-wc.y_max)>0) bit_4=1;
    }
};

const int clip_line(const WindowCoordinates,LineCoordinates&);
void calculate_intersecting_points(const WindowCoordinates,LineCoordinates&); void Rectangle(const int,const int,const int,const int);
void Line(const int,const int,const int,const int);

int main( )
{
  int driver=VGA; 
  int mode=VGAHI;
  initgraph(&driver,&mode,"C:\\TC\\bgi"); 
  WindowCoordinates WC(180,140,470,340); 
  setcolor(15); 
  Rectangle(WC.x_min,WC.y_min,WC.x_max,WC.y_max); 
  LineCoordinates LC_1(150,160,120,320); 
  LineCoordinates LC_2(250,150,200,200);
  LineCoordinates LC_3(160,200,490,260); 
  LineCoordinates LC_4(300,300,400,380); 
  LineCoordinates LC_5(550,300,450,400); 
  LineCoordinates LC_6(440,110,400,370);
  setcolor(7); 
  Line(LC_1.x_1,LC_1.y_1,LC_1.x_2,LC_1.y_2); 
  Line(LC_2.x_1,LC_2.y_1,LC_2.x_2,LC_2.y_2); 
  Line(LC_3.x_1,LC_3.y_1,LC_3.x_2,LC_3.y_2);
  Line(LC_4.x_1,LC_4.y_1,LC_4.x_2,LC_4.y_2);
  Line(LC_5.x_1,LC_5.y_1,LC_5.x_2,LC_5.y_2); 
  Line(LC_6.x_1,LC_6.y_1,LC_6.x_2,LC_6.y_2); 
  char Key=NULL;
  
  do
  {
    Key=getch( );
  }while(Key!='C' && Key!='c'); 
  settextstyle(0,0,1); 
  setcolor(0);
  outtextxy(163,450,"Press 'C' to see the Clipped Lines. ");

  setcolor(15); outtextxy(163,450,"—— ——-"); setcolor(12);
outtextxy(213,450,"Press any Key to exit. "); setcolor(10);
if(clip_line(WC,LC_1)) Line(LC_1.x_1,LC_1.y_1,LC_1.x_2,LC_1.y_2);
if(clip_line(WC,LC_2)) Line(LC_2.x_1,LC_2.y_1,LC_2.x_2,LC_2.y_2);
if(clip_line(WC,LC_3)) Line(LC_3.x_1,LC_3.y_1,LC_3.x_2,LC_3.y_2);
if(clip_line(WC,LC_4)) Line(LC_4.x_1,LC_4.y_1,LC_4.x_2,LC_4.y_2);
if(clip_line(WC,LC_5)) Line(LC_5.x_1,LC_5.y_1,LC_5.x_2,LC_5.y_2);
if(clip_line(WC,LC_6)) Line(LC_6.x_1,LC_6.y_1,LC_6.x_2,LC_6.y_2);
getch( ); return 0;
}
const int clip_line(const WindowCoordinates wc,LineCoordinates &lc)
{
RegionCode rc1,rc2,rc; rc1.get_region_code(wc,lc.x_1,lc.y_1); rc2.get_region_code(wc,lc.x_2,lc.y_2); rc.get_logical_AND(rc1,rc2); if(rc1.equal_zero( ) && rc2.equal_zero( ))
return 1;
else if(!rc.equal_zero( )) return 0;
else
{
calculate_intersecting_points(wc,lc); lc.x_1=(int)(lc.x_1+0.5);
lc.y_1=(int)(lc.y_1+0.5);
lc.x_2=(int)(lc.x_2+0.5);
lc.y_2=(int)(lc.y_2+0.5); if(lc.x_1==lc.x_2 && lc.y_1==lc.y_2)
return 0;
}
 
return 1;
}
void calculate_intersecting_points(const WindowCoordinates wc,LineCoordinates &lc)
{
LineCoordinates lc1(lc.x_1,lc.y_1,lc.x_2,lc.y_2); LineCoordinates lc2(lc.x_2,lc.y_2,lc.x_1,lc.y_1); float x_mid;
float y_mid; if(lc1.y_1>wc.y_max)
{
while(lc1.y_1!=wc.y_max)
{
x_mid=((lc1.x_1+lc1.x_2)/2); y_mid=((lc1.y_1+lc1.y_2)/2); if(y_mid>=wc.y_max)
{
lc1.x_1=x_mid; lc1.y_1=y_mid;
}
else
{
lc1.x_2=x_mid; lc1.y_2=y_mid;
}
if((int)(lc1.x_1+0.5)==(int)(lc1.x_2+0.5) &&
(int)(lc1.y_1+0.5)==(int)(lc1.y_2+0.5)) break;
}
}
else if(lc1.y_1<wc.y_min)
{
while(lc1.y_1!=wc.y_min)
{
x_mid=((lc1.x_1+lc1.x_2)/2); y_mid=((lc1.y_1+lc1.y_2)/2); if(y_mid<=wc.y_min)
{
lc1.x_1=x_mid; lc1.y_1=y_mid;
 
}
else
{
lc1.x_2=x_mid; lc1.y_2=y_mid;
}
if((int)(lc1.x_1+0.5)==(int)(lc1.x_2+0.5) &&
(int)(lc1.y_1+0.5)==(int)(lc1.y_2+0.5)) break;
}
}
if(lc1.x_1>wc.x_max)
{
while(lc1.x_1!=wc.x_max)
{
x_mid=((lc1.x_1+lc1.x_2)/2); y_mid=((lc1.y_1+lc1.y_2)/2); if(x_mid>=wc.x_max)
{
lc1.x_1=x_mid; lc1.y_1=y_mid;
}
else
{
lc1.x_2=x_mid; lc1.y_2=y_mid;
}
if((int)(lc1.x_1+0.5)==(int)(lc1.x_2+0.5) &&
(int)(lc1.y_1+0.5)==(int)(lc1.y_2+0.5)) break;
}
}
else if(lc1.x_1<wc.x_min)
{
while(lc1.x_1!=wc.x_min)
{
x_mid=((lc1.x_1+lc1.x_2)/2); y_mid=((lc1.y_1+lc1.y_2)/2); if(x_mid<=wc.x_min)
{
 
lc1.x_1=x_mid; lc1.y_1=y_mid;
}
else
{
lc1.x_2=x_mid; lc1.y_2=y_mid;
}
if((int)(lc1.x_1+0.5)==(int)(lc1.x_2+0.5) &&
(int)(lc1.y_1+0.5)==(int)(lc1.y_2+0.5)) break;
}
}
lc2.x_2=lc1.x_1; lc2.y_2=lc1.y_1; if(lc2.y_1>wc.y_max)
{
while(lc2.y_1!=wc.y_max)
{
x_mid=((lc2.x_1+lc2.x_2)/2); y_mid=((lc2.y_1+lc2.y_2)/2); if(y_mid>=wc.y_max)
{
lc2.x_1=x_mid; lc2.y_1=y_mid;
}
else
{
lc2.x_2=x_mid; lc2.y_2=y_mid;
}
if((int)(lc2.x_1+0.5)==(int)(lc2.x_2+0.5) &&
(int)(lc2.y_1+0.5)==(int)(lc2.y_2+0.5)) break;
}
}
else if(lc2.y_1<wc.y_min)
{
while(lc2.y_1!=wc.y_min)
{
 
x_mid=((lc2.x_1+lc2.x_2)/2); y_mid=((lc2.y_1+lc2.y_2)/2); if(y_mid<=wc.y_min)
{
lc2.x_1=x_mid; lc2.y_1=y_mid;
}
else
{
lc2.x_2=x_mid; lc2.y_2=y_mid;
}
if((int)(lc2.x_1+0.5)==(int)(lc2.x_2+0.5) &&
(int)(lc2.y_1+0.5)==(int)(lc2.y_2+0.5)) break;
}
}
if(lc2.x_1>wc.x_max)
{
while(lc2.x_1!=wc.x_max)
{
x_mid=((lc2.x_1+lc2.x_2)/2); y_mid=((lc2.y_1+lc2.y_2)/2); if(x_mid>=wc.x_max)
{
lc2.x_1=x_mid; lc2.y_1=y_mid;
}
else
{
lc2.x_2=x_mid; lc2.y_2=y_mid;
}
if((int)(lc2.x_1+0.5)==(int)(lc2.x_2+0.5) &&
(int)(lc2.y_1+0.5)==(int)(lc2.y_2+0.5)) break;
}
}
else if(lc2.x_1<wc.x_min)
{
 
while(lc2.x_1!=wc.x_min)
{
x_mid=((lc2.x_1+lc2.x_2)/2); y_mid=((lc2.y_1+lc2.y_2)/2); if(x_mid<=wc.x_min)
{
lc2.x_1=x_mid; lc2.y_1=y_mid;
}
else
{
lc2.x_2=x_mid; lc2.y_2=y_mid;
}
if((int)(lc2.x_1+0.5)==(int)(lc2.x_2+0.5) &&
(int)(lc2.y_1+0.5)==(int)(lc2.y_2+0.5)) break;
}
}
lc.x_1=lc1.x_1; lc.y_1=lc1.y_1; lc.x_2=lc2.x_1; lc.y_2=lc2.y_1;
}
//————————— Rectangle( ) —————————-//
void Rectangle(const int x_1,const int y_1,const int x_2,const int y_2)
{
Line(x_1,y_1,x_2,y_1); Line(x_2,y_1,x_2,y_2); Line(x_2,y_2,x_1,y_2); Line(x_1,y_2,x_1,y_1);
}
//————————– Line( ) ————————//
void Line(const int x_1,const int y_1,const int x_2,const int y_2)
{
int color=getcolor( ); int x1=x_1;
int y1=y_1; int x2=x_2; int y2=y_2;
 
if(x_1>x_2)
{
x1=x_2; y1=y_2; x2=x_1; y2=y_1;
}
int dx=abs(x2-x1); int dy=abs(y2-y1);
int inc_dec=((y2>=y1)?1:-1); if(dx>dy)
{
int two_dy=(2*dy);
int two_dy_dx=(2*(dy-dx)); int p=((2*dy)-dx);
int x=x1; int y=y1;
putpixel(x,y,color); while(x<x2)
{
x++;
if(p<0)
p+=two_dy; else
{
y+=inc_dec; p+=two_dy_dx;
}
putpixel(x,y,color);
}
}
else
{
int two_dx=(2*dx);
int two_dx_dy=(2*(dx-dy)); int p=((2*dx)-dy);
int x=x1; int y=y1;
putpixel(x,y,color); while(y!=y2)
 
{
y+=inc_dec; if(p<0)
p+=two_dx; else
{
x++;
p+=two_dx_dy;
}
putpixel(x,y,color);
}
}
}






