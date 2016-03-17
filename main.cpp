#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif


#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#define BI 3.14
using namespace std;

//Circles
void Cartesian_Circle(COLORREF  color);
void MidPoint_Circle(COLORREF color);
void Polar_Circle(COLORREF color);//new
void Modified_Polar_Circle(COLORREF color);//new
void MidPoint_Circle1(COLORREF color);//new
void Modified_MidPoint_Circle1(COLORREF color);//new
void drawCircleShape(double xc, double yc, double R, COLORREF color);//task
void drawCircles();//task
void Draw8Points (double xc, double yc, double x, double y, COLORREF color);
//Ellipse
void Polar_Ellipse(COLORREF color);
void Cartesian_Ellipse(COLORREF color);
void Modified_Polar_Ellipse(COLORREF color);
void MidPoint_Ellipse(COLORREF color);
void Draw4Points (double xc, double yc, double x, double y, COLORREF color);
//Lines
void SDDA_Line(COLORREF  color);
void DDA_Line(COLORREF  color);
void Parametric_Line(COLORREF color);
void MidPoint_Line(COLORREF color);// dr ref3ay
void MidPoint_Line_2(COLORREF color);// dr reda
//==
//task draw triangle - cross Lines -Rectangle
void drawLineShape(double x1, double y1, double x2, double y2);
void  drawAllShape();
void  CrossLines();
void  Triangle();
void  Rectangle();
//==
//curves
void DrawHermiteCurve(Point P0, Point T0, Point P1, Point T1, COLORREF color);
void drawBezierCurve(Point P0, Point P1, Point P2, Point P3, COLORREF color);
void DrawCurve1(COLORREF color);//draw Hermite
void DrawCurve2(COLORREF color);//draw Bezier
//==
//Clipping
void LineClipping ();

int NumClicks=0,type = 2;
int NumLine = -1, R=0, CurrentColor = 0;//NumLine  = -1;
int choose;
vector<Line>lines;
queue<Point>points;
queue <Line>linesq;
Point p;
//task
Point p1, p2, p3, p4;
Line l;
HDC hdc;
//Curves
void DrawCurve1(COLORREF color)
{
    if (points.size() > 3)
    {
        p1 = points.front();
        points.pop();

        p2 = points.front();
        points.pop();

        p3 = points.front();
        points.pop();

        p4 = points.front();
        while (!points.empty())
            points.pop();
        DrawHermiteCurve(p1,p2,p3,p4,color);
    }
}
void DrawCurve2(COLORREF color)
{
    if (points.size() > 3)
    {
        p1 = points.front();
        points.pop();

        p2 = points.front();
        points.pop();

        p3 = points.front();
        points.pop();

        p4 = points.front();
        while (!points.empty())
            points.pop();
        drawBezierCurve(p1,p2,p3,p4,color);
    }
}
void DrawHermiteCurve(Point P0, Point T0, Point P1, Point T1, COLORREF color)
{
    double H[4][4] = {{2, 1, -2, 1}, {-3, -2, 3, -1}, {0, 1, 0, 0}, {1, 0, 0, 0}};

    double vx[4], vy[4];
    double xcoeff[4], ycoeff[4];

    vx[0] = P0.x, vx[1] = T0.x, vx[2] = P1.x, vx[3] = T1.x;
    vy[0] = P0.y, vy[1] = T0.y, vy[2] = P1.y, vy[3] = T1.y;

    for(int i = 0; i < 4; i++)
    {
        xcoeff[i]=0;
        for(int j = 0; j < 4; j++)
            xcoeff[i] += (vx[j] * H[j][i]);
    }
    for(int i = 0; i < 4; i++)
    {
        ycoeff[i]=0;
        for(int j = 0; j < 4; j++)
            ycoeff[i] += (vy[j] * H[j][i]);
    }
    for (double t = 0; t <= 1; t+= 0.001)
    {
        //double x = (t * t * t * xcoeff[0]) + (t * t * xcoeff[1]) + (t * xcoeff[2]) + (xcoeff[3]);
        //double y = (t * t * t * ycoeff[0]) + (t * t * ycoeff[1]) + (t * ycoeff[2]) + (ycoeff[3]);
        double x = (t * t * t * ( (2*P0.x) + (1*T0.x) + (-2*P1.x) + (1*T1.x) ))
        + (t * t *  ( (-3*P0.x)+(-2*T0.x)+(3*P1.x)+(-1*T1.x) )) + (t * (T0.x)) + (P0.x);

        double y = (t * t * t * ( (2*P0.y) + (1*T0.y) + (-2*P1.y) + (1*T1.y) ))
        + (t * t *  ( (-3*P0.y)+(-2*T0.y)+(3*P1.y)+(-1*T1.y) )) + (t * (T0.y)) + (P0.y);

        SetPixel(hdc, round(x), round(y), color);
    }
}
void drawBezierCurve(Point P0, Point T0, Point P1, Point T1, COLORREF color)
{
    /*
    Point T0;
    T0.x = 3 *(P1.x - P0.x), T0.y = 3 *(P1.y  - P0.y);
    Point T1;
    T1.x = 3 * (P3.x - P2.x), T1.y = 3 * (P3.x - P2.x);
    DrawHermiteCurve(P0, T0, P3, T1, color);
    */
    for (double t = 0; t <= 1; t+= 0.001)
    {
        double x = (t * t * t * ( (-1*P0.x) + (3*T0.x) + (-3*P1.x) + (1*T1.x) ))
                   + (t * t *  ( (3*P0.x)+(-6*T0.x)+(3*P1.x)+(0*T1.x) )) + (t * ((-3*P0.x) + (3*T0.x))) + (P0.x);

        double y = (t * t * t * ( (-1*P0.y) + (3*T0.y) + (-3*P1.y) + (1*T1.y) ))
                   + (t * t *  ( (3*P0.y)+(-6*T0.y)+(3*P1.y)+(0*T1.y) )) + (t * ((-3*P0.y) + (3*T0.y))) + (P0.y);
        SetPixel(hdc, round(x), round(y), color);
    }
    /*
    double HB[4][4] = {{-1, 3, -3, 1}, {3, -6, 3, 0}, {-3, 3, 0, 0}, {1, 0, 0, 0}};

    double vx[4], vy[4];
    double xcoeff[4], ycoeff[4];

    vx[0] = P0.x, vx[1] = P1.x, vx[2] = P2.x, vx[3] = P3.x;
    vy[0] = P0.y, vy[1] = P1.y, vy[2] = P2.y, vy[3] = P3.y;

    for(int i = 0; i < 4; i++)
    {
        xcoeff[i]=0;
        for(int j = 0; j < 4; j++)
            xcoeff[i] += (vx[j] * HB[j][i]);
    }
    for(int i = 0; i < 4; i++)
    {
        ycoeff[i]=0;
        for(int j = 0; j < 4; j++)
            ycoeff[i] += (vy[j] * HB[j][i]);
    }
    for (double t = 0; t <= 1; t+= 0.001)
    {
        double x = (t * t * t * xcoeff[0]) + (t * t * xcoeff[1]) + (t * xcoeff[2]) + (xcoeff[3]);
        double y = (t * t * t * ycoeff[0]) + (t * t * ycoeff[1]) + (t * ycoeff[2]) + (ycoeff[3]);

        /*
        double x = (t * t * t * ( (2*P0.x) + (1*T0.x) + (-2*P1.x) + (1*T1.x) ))
        + (t * t *  ( (-3*P0.x)+(-2*T0.x)+(3*P1.x)+(-1*T1.x) )) + (t * (T0.x)) + (P0.x);

        double y = (t * t * t * ( (2*P0.y) + (1*T0.y) + (-2*P1.y) + (1*T1.y) ))
        + (t * t *  ( (-3*P0.y)+(-2*T0.y)+(3*P1.y)+(-1*T1.y) )) + (t * (T0.y)) + (P0.y);
        //
        SetPixel(hdc, round(x), round(y), color);

    }*/
}
void flood_fill(double x,double y,COLORREF  color)
{
    if(GetPixel(hdc,x,y) == RGB(255,255,255))
    {
        SetPixel(hdc,x,y,color);
        flood_fill(x,y-1,color);
        flood_fill(x-1,y,color);
        flood_fill(x,y+1,color);
        flood_fill(x+1,y,color);
        //flood_fill(x+1,y-1);
        //flood_fill(x+1,y+1);
        //flood_fill(x-1,y-1);
        //flood_fill(x-1,y+1);
    }
}
//Function Draw Shapes
void Draw(COLORREF  color = RGB(0,0,255))
{
    l = lines[NumLine];
    //Circle Algorithms
    if(l.algorithm == 1)
        Cartesian_Circle(color);
    //Modified_Polar_Circle(color);
    else if(l.algorithm == 2)
        MidPoint_Circle(color);
    //Line Algorithms
    else if(l.algorithm == 3)
        SDDA_Line(color);
    else if(l.algorithm == 4)
        MidPoint_Line_2(color);
    else if (l.algorithm == 5)
        Parametric_Line(color);
    //drawAllShape();
    else if (l.algorithm == 6)
        DDA_Line(color);
    //Shapes
    else if (l.algorithm == 7)
        CrossLines();
    else if (l.algorithm == 8)
        Triangle();
    else if (l.algorithm == 9)
        Rectangle();
    else if (l.algorithm == 10)
        Polar_Circle(color);
    else if (l.algorithm == 11)
        drawCircles();
    //Modified_Polar_Circle(color);
    else if (l.algorithm == 12)
        MidPoint_Circle1(color);
    else if (l.algorithm == 13)
        Modified_MidPoint_Circle1(color);
    //Ellipse
    else if (l.algorithm == 14)
        Polar_Ellipse(color);
    else if (l.algorithm == 16)
        Cartesian_Ellipse(color);
    else if (l.algorithm == 17)
        Modified_Polar_Ellipse(color);
    else if (l.algorithm == 18)
        MidPoint_Ellipse(color);
    //Curves
    else if (l.algorithm == 15)
        DrawCurve1(color);//Hermite
    else if (l.algorithm == 20)
        DrawCurve2(color);//Bezier

    NumClicks = 0;
}
//<< Line >>
void drawLineShape(double x1, double y1, double x2, double y2)
{
    COLORREF color =RGB(0, 0, 255);
    double dx = x2 - x1 ;
    double dy = y2 - y1;
    double k = 1/max(dx,dy);
    k = 0.001;
    SetPixel(hdc,round(l.pFirst.x),round(l.pFirst.y),color);
    for (double q = 0; q <= 1; q += k)
    {
        double x = x1 + q*dx;
        double y = y1 + q*dy;
        SetPixel(hdc,round(x),round(y),color);
    }
}
//task - 2
void drawCircles()
{
    if (NumLine % 2 == 1)
    {
        Line l1 = lines[NumLine];
        Line l2 = lines[NumLine - 1];

        p1 = l1.pFirst, p2 = l1.pSecond;
        p3 = l2.pFirst, p4 = l2.pSecond;
        double R, R_large, R_small;

        R = std::sqrt(((p2.x - p1.x)*(p2.x - p1.x))+((p2.y - p1.y)*(p2.y - p1.y)));
        //first circle
        drawCircleShape(p1.x, p1.y, R,RGB(0,0,255));
        //second circle
        R = std::sqrt(((p3.x - p1.x)*(p3.x - p1.x))+((p3.y - p1.y)*(p3.y - p1.y)));
        drawCircleShape(p1.x, p1.y, R,RGB(0,0,255));
        //third circle
        R = std::sqrt(((p4.x - p1.x)*(p4.x - p1.x))+((p4.y - p1.y)*(p4.y - p1.y)));
        drawCircleShape(p1.x, p1.y, R,RGB(0,0,255));
        //fill in between circle 2&3
        R_large = std::sqrt(((p4.x - p1.x)*(p4.x - p1.x))+((p4.y - p1.y)*(p4.y - p1.y)));//R of cicle - 3
        R_small = std::sqrt(((p2.x - p1.x)*(p2.x - p1.x))+((p2.y - p1.y)*(p2.y - p1.y)));//R of cirlce - 2
        while (R_small < R_large)
        {
            R_small += 0.5;
            drawCircleShape(p1.x, p1.y, R_small ,RGB(0, 255, 0));
        }
        //filling in circle -1
        R_large = std::sqrt(((p2.x - p1.x)*(p2.x - p1.x))+((p2.y - p1.y)*(p2.y - p1.y)));//R of circle -1
        while (R_large >= 0)
        {
            R_large -= 0.5;
            drawCircleShape(p1.x, p1.y, R_large ,RGB(0, 0, 255));
        }
    }
}
//task
void  CrossLines()
{
    //instead of NumLine >= 1 -OR- NumLine > 1
    if (NumLine % 2 == 1)
    {
        Line l1 = lines[NumLine];
        Line l2 = lines[NumLine - 1];

        double x1,y1, x2,y2;
        p1 = l1.pFirst;
        p2 = l2.pSecond;
        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape (x1,y1,x2,y2);

        p1 = l1.pSecond;
        p2 = l2.pFirst;
        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);
    }
}
void Triangle()
{
//To Draw Triangle By Points
    if ((int)points.size() >= 3)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();
        double x1,y1, x2,y2;

        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p1.x, y1 = p1.y;
        x2 = p3.x, y2 = p3.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p2.x, y1 = p2.y;
        x2 = p3.x, y2 = p3.y;
        drawLineShape(x1,y1,x2,y2);

        while(!points.empty())
            points.pop();
    }
}
void Rectangle()
{
//Draw Rectangle
    if ((int)points.size() >= 4)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();
        p4 = points.front();
        points.pop();
        double x1,y1, x2,y2;

        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p2.x, y1 = p2.y;
        x2 = p4.x, y2 = p4.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p1.x, y1 = p1.y;
        x2 = p3.x, y2 = p3.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p3.x, y1 = p3.y;
        x2 = p4.x, y2 = p4.y;
        drawLineShape(x1,y1,x2,y2);

        while(!points.empty())
            points.pop();
    }
}
void drawAllShape()
{
    //instead of NumLine >= 1 -OR- NumLine > 1
    /*if (NumLine % 2 == 1)
    {
        Line l1 = lines[NumLine];
        Line l2 = lines[NumLine - 1];

        double x1,y1, x2,y2;
        p1 = l1.pFirst;
        p2 = l2.pSecond;
        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape (x1,y1,x2,y2);

        p1 = l1.pSecond;
        p2 = l2.pFirst;
        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);
    }*/
    // To Draw Triangle
    /*if (NumLine % 2 == 1)
    {
        Line l1 = lines[NumLine];
        Line l2 = lines[NumLine - 1];
        double x1,y1, x2,y2;

        p1 = l1.pFirst;
        p2 = l1.pSecond;
        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape (x1,y1,x2,y2);

        p1 = l1.pSecond;
        p2 = l2.pFirst;
        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);

        p1 = l1.pFirst;
        p2 = l2.pFirst;
        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);
    }*/
    //To Draw Triangle By Points
    /*if ((int)points.size() >= 3)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();
        double x1,y1, x2,y2;

        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p1.x, y1 = p1.y;
        x2 = p3.x, y2 = p3.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p2.x, y1 = p2.y;
        x2 = p3.x, y2 = p3.y;
        drawLineShape(x1,y1,x2,y2);

        while(!points.empty())
            points.pop();
    }*/
    //Draw Rectangle
    if ((int)points.size() >= 4)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();
        p4 = points.front();
        points.pop();
        double x1,y1, x2,y2;

        x1 = p1.x, y1 = p1.y;
        x2 = p2.x, y2 = p2.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p2.x, y1 = p2.y;
        x2 = p4.x, y2 = p4.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p1.x, y1 = p1.y;
        x2 = p3.x, y2 = p3.y;
        drawLineShape(x1,y1,x2,y2);

        x1 = p3.x, y1 = p3.y;
        x2 = p4.x, y2 = p4.y;
        drawLineShape(x1,y1,x2,y2);

        while(!points.empty())
            points.pop();
    }
}
void DDA_Line(COLORREF  color)
{
    //Incremental Digital Differential Analyzer (DDA)  Algorithm
    if(l.pFirst.x > l.pSecond.x )
    {
        std::swap(l.pFirst.x,l.pSecond.x);
        std::swap(l.pFirst.y,l.pSecond.y);
    }
    if(l.pFirst.x == l.pSecond.x)
    {
        for(int i=l.pFirst.y; i<=l.pSecond.y; i++)
            SetPixel(hdc,l.pFirst.x,i,color);
    }
    else if(l.pFirst.y == l.pSecond.y)
    {
        for(int i=l.pFirst.x; i<=l.pSecond.x; i++)
            SetPixel(hdc,i,l.pFirst.y,color);
    }
    else
    {
        double m = (double)(l.pSecond.y-l.pFirst.y)/(double)(l.pSecond.x-l.pFirst.x);
        //double c = l.pSecond.y - (m *l.pFirst.x);
        if(abs(m) <= 1)
        {
            double y = l.pFirst.y;
            for(int i=l.pFirst.x; i<=l.pSecond.x; i++)
            {
                SetPixel(hdc,i,round(y),color);
                y += m;

            }
        }
        else if(abs(m) > 1)
        {
            double x = l.pFirst.x;
            for(int i=l.pFirst.y; i<=l.pSecond.y; i++)
            {
                SetPixel(hdc,round(x),i,color);
                x +=(1/m);
            }
        }
    }
    NumClicks = 0;
}
void SDDA_Line(COLORREF  color)
{
    //Simple Digital Differential Analyzer(DDA) Algorithm
    if(l.pFirst.x > l.pSecond.x )
    {
        std::swap(l.pFirst.x,l.pSecond.x);
        std::swap(l.pFirst.y,l.pSecond.y);
    }
    if(l.pFirst.x == l.pSecond.x)
    {
        for(int i=l.pFirst.y; i<=l.pSecond.y; i++)
            SetPixel(hdc,l.pFirst.x,i,color);
    }
    else if(l.pFirst.y == l.pSecond.y)
    {
        for(int i=l.pFirst.x; i<=l.pSecond.x; i++)
            SetPixel(hdc,i,l.pFirst.y,color);
    }
    else
    {
        double m = (double)(l.pSecond.y-l.pFirst.y)/(double)(l.pSecond.x-l.pFirst.x);
        double c = l.pSecond.y - (m *l.pFirst.x);
        if(abs(m) <= 1)
        {
            double y = l.pFirst.y;
            for(int i=l.pFirst.x; i<=l.pSecond.x; i++)
            {
                y =(m*i)+c;
                SetPixel(hdc,i,y,color);
            }
        }
        else if(abs(m) > 1)
        {
            double x = l.pFirst.x;
            for(int i=l.pFirst.y; i<=l.pSecond.y; i++)
            {
                x =((i-c)/m);
                SetPixel(hdc,x,i,color);
            }
        }
    }
    NumClicks = 0;
}
void Parametric_Line(COLORREF color)
{
    //scan conversion line
    l = lines[NumLine];
    double dx = l.pSecond.x - l.pFirst.x ;
    double dy = l.pSecond.y - l.pFirst.y;
    if (l.pFirst.x > l.pSecond.x)
    {
        std::swap(l.pFirst.x,l.pSecond.x);
        std::swap(l.pFirst.y,l.pSecond.y);
    }
    double slope = dy/dx;
    for (int x = l.pFirst.x; x < l.pSecond.x; ++x)
    {
        double y = x - l.pFirst.x * slope + l.pFirst.y;
        SetPixel(hdc, x, round(y),color);
    }
    //parametric line equation
    /*l = lines[NumLine];
    double dx = l.pSecond.x - l.pFirst.x ;
    double dy = l.pSecond.y - l.pFirst.y;
    double k = 1/max(dx,dy);
    k = 0.001;
    SetPixel(hdc,round(l.pFirst.x),round(l.pFirst.y),color);
    for (double q = 0; q <= 1; q += k)
    {
        double x = l.pFirst.x + q*dx;
        double y = l.pFirst.y + q*dy;
        SetPixel(hdc,round(x),round(y),color);
    }*/
    NumClicks = 0;
}
// MidPoint Algorithm
void MidPoint_Line(COLORREF  color)
{
    //ref3y
    l = lines[NumLine];
    double dx = l.pSecond.x - l.pFirst.x ,dy = l.pSecond.y - l.pFirst.y;
    double f = (dy*2) - dx;
    double m = dy/dx;
    if( abs(m) > 1 ) // for vertical line.
    {
        std::swap(l.pFirst.x,l.pFirst.y);
        std::swap(l.pSecond.x,l.pSecond.y);
        std::swap(dy,dx);
    }
    if(l.pFirst.x > l.pSecond.x )
    {
        std::swap(l.pFirst.x,l.pSecond.x);
        std::swap(l.pFirst.y,l.pSecond.y);
        dx = abs(dx) ,dy = abs(dy);
    }
    if(m < 0  && (int)m >=-1)
        dx = abs(dx) ,dy = abs(dy);
    while(l.pFirst.x <= l.pSecond.x)
    {
        if(f <= 0)
            f += dy*2;  //E
        else
        {
            f += (dy - dx)*2; //NE
            if(m < 0  && (int)m >=-1)
                l.pFirst.y--;
            else
                l.pFirst.y++;
        }
        l.pFirst.x++;
        if(abs (m) > 1)
            SetPixel(hdc,l.pFirst.y,l.pFirst.x,color);
        else
            SetPixel(hdc,l.pFirst.x,l.pFirst.y,color);
    }
    NumClicks = 0;
}
void MidPoint_Line_2(COLORREF color)
{
    //Midpoint Line by Dr.Reda
    l = lines[NumLine];
    double dx = l.pSecond.x - l.pFirst.x ;
    double dy = l.pSecond.y - l.pFirst.y;
    // Case : 1
    if (abs(dy)<=abs(dx))  // slope < 1
    {
        if (dx < 0)
        {
            std::swap(l.pFirst.x,l.pSecond.x);
            std::swap(l.pFirst.y,l.pSecond.y);
            dx = -dx;
            dy = -dy;
        }
        double d = dx - (2*abs(dy));
        double change1 =  2 *(dx - abs(dy));
        double change2 = -2 * abs(dy);
        int incY = 0;
        if (dy > 0) incY = 1; // draw the above point
        else incY = -1;//draw the below point

        double x =  l.pFirst.x;
        double y =  l.pFirst.y;
        SetPixel(hdc,x , y, color);
        while (x < l.pSecond.x) // X < Xe
        {
            if (d < 0)
            {
                d += change2;
                y += incY;
            }
            else d += change1;
            ++x;
            SetPixel(hdc,x , y, color);
        }
    }
    else if (dy < 0)
    {
        std::swap(l.pFirst.x,l.pFirst.y);
        std::swap(l.pSecond.x,l.pSecond.y);
        dx = -dx;
        dy = -dy;

        double d = (2 * dx) - dy;
        double change1 = 2*(abs(dx) - dy);
        double change2 = 2*abs(dx);
        int incX = 0;
        if (dx >= 0) incX = 1;
        else incX = -1;

        double x =  l.pFirst.x;
        double y =  l.pFirst.y;
        SetPixel(hdc, x, y, color);
        while (y < l.pSecond.y) // Y < Ye
        {
            if (d > 0)
            {
                d += change1;
                x += incX;
            }
            else d += change2;
            ++y;
            SetPixel(hdc, x, y, color);
        }
    }
}
//<< Circle >>
// Cartesian
void Cartesian_Circle(COLORREF  color)
{
    R = std::sqrt(((l.pSecond.x-l.pFirst.x)*(l.pSecond.x-l.pFirst.x))+((l.pSecond.y-l.pFirst.y)*(l.pSecond.y-l.pFirst.y)));
    for (int x = (l.pFirst.x-R); x <= (l.pFirst.x+R); x++)
    {
        int y = std::sqrt((R*R)-((l.pFirst.x-x)*(l.pFirst.x-x))) ;
        SetPixel( hdc,x , l.pFirst.y+y,  color);
        drawLineShape (l.pFirst.x, l.pFirst.y, x, l.pFirst.y+y);
        SetPixel( hdc,x , l.pFirst.y-y, color);
        drawLineShape (l.pFirst.x, l.pFirst.y, x, l.pFirst.y-y);
    }
    //flood_fill(l.pFirst.x,l.pFirst.y);
}
//<<Circle>>
// MidPoint
void MidPoint_Circle(COLORREF  color)
{

    R = std::sqrt(((l.pSecond.x-l.pFirst.x)*(l.pSecond.x-l.pFirst.x))+((l.pSecond.y-l.pFirst.y)*(l.pSecond.y-l.pFirst.y)));
    int x = 0 ,y = R ,d= 1-R;
    int dE = 3,dSE = -2*R + 5;

    SetPixel(hdc,l.pFirst.x, l.pFirst.y + R,color);
    SetPixel(hdc,l.pFirst.x, l.pFirst.y - R,color);
    SetPixel(hdc,l.pFirst.x + R, l.pFirst.y,color);
    SetPixel(hdc,l.pFirst.x - R, l.pFirst.y,color);
    while( y > x)
    {
        if(d < 0)
            d+=dE,dE += 2,dSE +=2;
        else
        {
            d+=dSE;
            dE+=2;
            dSE+=4;
            y--;
        }
        x++;
        SetPixel(hdc,l.pFirst.x + x, l.pFirst.y + y,color);
        SetPixel(hdc,l.pFirst.x - x, l.pFirst.y + y,color);
        SetPixel(hdc,l.pFirst.x + x, l.pFirst.y - y,color);
        SetPixel(hdc,l.pFirst.x - x, l.pFirst.y - y,color);
        SetPixel(hdc,l.pFirst.x + y, l.pFirst.y + x,color);
        SetPixel(hdc,l.pFirst.x - y, l.pFirst.y + x,color);
        SetPixel(hdc,l.pFirst.x + y, l.pFirst.y - x,color);
        SetPixel(hdc,l.pFirst.x - y, l.pFirst.y - x,color);
    }
    //flood_fill(l.pFirst.x,l.pFirst.y,RGB(255,255,0));
}
// Utility function for circle
void Draw8Points (double xc, double yc, double x, double y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc + y, yc - x, color);
    SetPixel(hdc, xc - y, yc - x, color);
}
//Utility function for Ellipse
void Draw4Points (double xc, double yc, double x, double y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc - y, color);
}
//new
void Polar_Circle(COLORREF color)
{
    double R = std::sqrt(((l.pSecond.x-l.pFirst.x)*(l.pSecond.x-l.pFirst.x))+
                         ((l.pSecond.y-l.pFirst.y)*(l.pSecond.y-l.pFirst.y)));
    double xc = l.pFirst.x, yc = l.pSecond.y;
    double x = R;
    double dtheta =  1/R, theta = 0;
    double y = 0;
    Draw8Points(xc, yc, x, y, color);
    while (x > y)
    {
        theta += dtheta;
        double x = round(R*cos(theta));
        double y = round(R*sin(theta));
        Draw8Points(xc, yc, x, y, color);
    }
}
//new
void drawCircleShape(double xc, double yc, double R, COLORREF color)
{
    double x = R;
    double dtheta =  1/R, theta = 0;
    double cs_dtheta = cos(dtheta), sn_dtheta = sin(dtheta);
    double y = 0;
    Draw8Points(xc, yc, x, y, color);
    while (x > y)
    {
        theta += dtheta;
        double x1 = x * cs_dtheta - y * sn_dtheta;
        y = x * sn_dtheta + y * cs_dtheta;
        x = x1;
        Draw8Points(xc, yc, round(x), round(y), color);
    }
}
void Modified_Polar_Circle(COLORREF color)
{
    double R = std::sqrt(((l.pSecond.x-l.pFirst.x)*(l.pSecond.x-l.pFirst.x))+
                         ((l.pSecond.y-l.pFirst.y)*(l.pSecond.y-l.pFirst.y)));
    double xc = l.pFirst.x, yc = l.pSecond.y;
    double x = R;
    double dtheta =  1/R, theta = 0;
    double cs_dtheta = cos(dtheta), sn_dtheta = sin(dtheta);
    double y = 0;
    Draw8Points(xc, yc, x, y, color);
    while (x > y)
    {
        theta += dtheta;
        double x1 = x * cs_dtheta - y * sn_dtheta;
        y = x * sn_dtheta + y * cs_dtheta;
        x = x1;
        Draw8Points(xc, yc, round(x), round(y), color);
    }
}
//new
void MidPoint_Circle1(COLORREF color)
{
    double R = std::sqrt(((l.pSecond.x-l.pFirst.x)*(l.pSecond.x-l.pFirst.x))+
                         ((l.pSecond.y-l.pFirst.y)*(l.pSecond.y-l.pFirst.y)));
    double xc = l.pFirst.x, yc = l.pSecond.y;
    double x = 0;
    double y = R;
    double d = 1- R;// = (5/4 - R)
    Draw8Points(xc, yc, x, y, color);
    while (x < y)
    {
        if (d < 0)
            d += (2*x) + 3;
        else
            d += (2*(x-y))+5, --y;
        ++x;
        Draw8Points(xc, yc, x, y, color);
    }
}
//new
void Modified_MidPoint_Circle1(COLORREF color)
{
    double R;
    R = std::sqrt(((l.pSecond.x-l.pFirst.x)*(l.pSecond.x-l.pFirst.x))+((l.pSecond.y-l.pFirst.y)*(l.pSecond.y-l.pFirst.y)));
    double xc = l.pFirst.x, yc = l.pSecond.y;
    double x = 0;
    double y = R;
    double d = 1- R;// = (5/4 - R)
    double dch1 = 3;
    double dch2 = 5 - 2*R;
    Draw8Points(xc, yc, x, y, color);
    while (x < y)
    {
        if (d < 0)
            d += dch1, dch2 += 2;
        else
            d += dch2, dch2 += 4, --y;
        ++x;
        ++dch1;
        Draw8Points(xc, yc, x, y, color);
    }
}
//new
void Polar_Ellipse(COLORREF color)
{
    if ((int)points.size() >= 3)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();

        double xc ,yc, x, y, A, B, theta, dtheta;
        A = std::sqrt(((p2.x - p1.x)*(p2.x - p1.x))+((p2.y - p1.y)*(p2.y - p1.y)));
        B = std::sqrt(((p3.x - p1.x)*(p3.x - p1.x))+((p3.y - p1.y)*(p3.y - p1.y)));
        xc = p1.x, yc = p1.y;
        x = A;
        dtheta =  (1.0/max(A,B)), theta = 0;
        y = 0;
        Draw4Points(xc, yc, x, y, color);
        while (x > 0)
        {
            theta += dtheta;
            double x = A * cos(theta);
            double y = B * sin(theta);
            Draw4Points(xc, yc, x, y, color);
        }
        while(!points.empty())
            points.pop();
    }
}
//new
void Modified_Polar_Ellipse(COLORREF color)
{
    if ((int)points.size() >= 3)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();

        double xc, yc, x, y, A, B, theta, dtheta, cs_dtheta, sn_dtheta, st1, st2;
        A = std::sqrt(((p2.x - p1.x)*(p2.x - p1.x))+((p2.y - p1.y)*(p2.y - p1.y)));
        B = std::sqrt(((p3.x - p1.x)*(p3.x - p1.x))+((p3.y - p1.y)*(p3.y - p1.y)));
        xc = l.pFirst.x, yc = l.pSecond.y;
        x = A;
        dtheta =  (1.0/max(A,B)), theta = 0;
        cs_dtheta = cos(dtheta), sn_dtheta = sin(dtheta);
        st1 = (A / B) * sn_dtheta;
        st2 = (B / A) * sn_dtheta;
        y = 0;
        Draw4Points(xc, yc, x, y, color);
        while (x > 0)
        {
            theta += dtheta;
            double x1 = x * cs_dtheta - y * st1;

            y = x * st2 + y * cs_dtheta;
            x = x1;
            Draw4Points(xc, yc, round(x), round(y), color);
        }
        while(!points.empty())
            points.pop();
    }
}
//new
void Cartesian_Ellipse(COLORREF color)
{
    if ((int)points.size() >= 3)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();

        double A = std::sqrt(((p2.x - p1.x)*(p2.x - p1.x))+((p2.y - p1.y)*(p2.y - p1.y)));
        double B = std::sqrt(((p3.x - p1.x)*(p3.x - p1.x))+((p3.y - p1.y)*(p3.y - p1.y)));
        double x, y;
        double xc = p1.x, yc = p1.y;
        if ((B * B) / (A * A) <= 1)
        {
            x = 0, y = B;
            Draw4Points(xc, yc, x, y, color);
            while (x * (B * B) <= y * (A * A))
            {
                x = x + 1;
                y = B * sqrt(1 - ((x * x)/(A * A)));
                Draw4Points(xc, yc, x, round(y), color);
            }
        }
        else   // x*B*B > y*A*A
        {
            x = A, y = 0;
            Draw4Points(xc, yc, x, y, color);
            while ((y * A * A) < (x * B * B))
            {
                y = y + 1;
                x = A * sqrt(1- (y*y / B*B));
                Draw4Points(xc, yc, round(x), y, color);
            }
        }
        while(!points.empty())
            points.pop();
    }
}
void MidPoint_Ellipse(COLORREF color)
{
    if ((int)points.size() >= 3)
    {
        p1 = points.front();
        points.pop();
        p2 = points.front();
        points.pop();
        p3 = points.front();
        points.pop();

        double x, y, d, xc, yc, A, B;
        A = std::sqrt(((p2.x - p1.x)*(p2.x - p1.x))+((p2.y - p1.y)*(p2.y - p1.y)));
        B = std::sqrt(((p3.x - p1.x)*(p3.x - p1.x))+((p3.y - p1.y)*(p3.y - p1.y)));
        x = 0, y = B, d = (y*B*B) - (y*B*A*A) + (A*A);
        Draw4Points(xc, yc, x, y, color);
        while ((x* B * B) <= (y * A * A))
        {
            if (d < 0)
            {
                d = d + ((4 * B * B)*(2*x + 1));
            }
            else
            {
                d = d + ((4 * B * B)*(2*x + 1)) - ((8 * A * A)*(y - 1));
                y = y - 1;
            }
            Draw4Points(xc, yc, x, y, color);
        }
        x = A, y = 0, d = (4 * A * A) - (4 * B * B * A) + (B * B);
        Draw4Points(xc, yc, x, y, color);
        while((y * A * A) < (x * B * B))
        {
            y = y + 1;
            if (d < 0)
            {
                d = d + (4 * A * A) * (2 * y + 1);
            }
            else
            {
                d = d + ((4 * A * A)*(2*y + 1)) - ((8 * A * A)*(x - 1));
                x = x - 1;
            }
            Draw4Points(xc, yc, x, y, color);
        }
        while(!points.empty())
            points.pop();
    }
}
void Open()
{
    std::ifstream file("save.txt",std::ios::in);
    int i=0;
    while(!file.eof())
    {
        std::string s="";
        file>>s;
        if(i==0)
        {
            l.pFirst.x = atoi(s.c_str());
        }
        else if(i==1)
            l.pFirst.y = atoi(s.c_str());
        else if(i==2)
            l.pSecond.x = atoi(s.c_str());
        else if(i==3)
            l.pSecond.y = atoi(s.c_str());
        else
        {
            l.algorithm = atoi(s.c_str());
            lines.push_back(l);
            i=-1;
        }
        i++;
    }
    file.close();
}
void Save()
{
    std::ofstream file("save.txt",std::ios::out);
    for(int i=0; i<(int)lines.size(); i++)
    {
        l = lines[i];
        file<<abs(l.pFirst.x)<<" "<<abs(l.pFirst.y)<<" "<<abs(l.pSecond.x)<<" "<<abs(l.pSecond.y)<<" "<<l.algorithm<<std::endl;
    }
    file.close();
}
static LOGFONT lf;        // logical font structure
static DWORD rgbCurrent; //initial color selection
/*void selectColor()
{

    CHOOSECOLOR cc;                 // common dialog box structure
    static COLORREF acrCustClr[16]; // array of custom colors
    HWND hwnd;                      // owner window
    HBRUSH hbrush;                  // brush handle
//HWND hwnd;                // owner window
//HDC hdc;                  // display device context of owner window
    CHOOSEFONT cf;            // common dialog box structure  // current text color
    HFONT hfont, hfontPrev;
    DWORD rgbPrev;

// Initialize CHOOSEFONT
    ZeroMemory(&cf, sizeof(cf));
    cf.lStructSize = sizeof (cf);
    cf.hwndOwner = hwnd;
    cf.lpLogFont = &lf;
    cf.rgbColors = rgbCurrent;
    cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

    if (ChooseFont(&cf)==TRUE)
    {
        //hfont = CreateFontIndirect(cf.lpLogFont);
        //hfontPrev = SelectObject(hdc, hfont);
        rgbCurrent= cf.rgbColors;
        //rgbPrev = SetTextColor(hdc, rgbCurrent);
    }
}*/
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("GFX");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+4;//5

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("GFX"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               600,                 /* The programs width */
               400,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
//HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
//SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_PAINT:
    {
        if(NumClicks==3)
        {
            PAINTSTRUCT PS;
            hdc = BeginPaint (hwnd,&PS);
            Draw();
        }
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    }
    case WM_LBUTTONDOWN:
    {
        double xPos=LOWORD(lParam);
        double yPos=HIWORD(lParam);
        if (NumClicks < 2)
        {
            p.x=xPos;
            p.y=yPos;
            if (NumClicks==0)l.pFirst = p, points.push(p);//push points
            if (NumClicks==1)l.pSecond = p, points.push(p);//push points
            NumClicks++;
        }
        if(NumClicks == 2)
        {
            l.algorithm = type;
            lines.push_back(l);
            linesq.push(l);
            //points.push(l.pFirst);
            //points.push(l.pSecond);

            NumLine ++;
            NumClicks++;
            InvalidateRect(hwnd,NULL,false);
        }
        break;
    }
    case WM_CREATE: // to create the Menu bar
    {
        HMENU hMenubar = CreateMenu();
        HMENU hundo = CreateMenu();
        HMENU hredo = CreateMenu();

        HMENU htype = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP,(UINT_PTR)htype, "Circle");
        AppendMenu(htype, MF_STRING,3, "Cartesian");
        AppendMenu(htype, MF_STRING,4, "Midpoint Circle");
        AppendMenu(htype, MF_STRING,14, "Polar circle!");
        AppendMenu(htype, MF_STRING,15, "Modified Polar Circle!");
        AppendMenu(htype, MF_STRING,16, "Midpoint circle!");
        AppendMenu(htype, MF_STRING,17, "Modified Midpoint circle!");

        HMENU hline= CreateMenu();
        AppendMenu(hMenubar, MF_POPUP,(UINT_PTR)hline, "Line");
        AppendMenu(hline, MF_STRING,7, "SDDA line");

        AppendMenu(hline, MF_STRING,8, "Midpoint Line");
        AppendMenu(hline, MF_STRING,9, "Parametric");
        AppendMenu(hline, MF_STRING,10, "DDA");
        AppendMenu(hline, MF_STRING,11, "Cross Lines");
        AppendMenu(hline, MF_STRING,12, "Triangle");
        AppendMenu(hline, MF_STRING,13, "Rectangle");

        HMENU hEllipse = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP,(UINT_PTR)hEllipse, "Ellipse");
        AppendMenu(hEllipse,MF_STRING,20, "Cartesian Ellipse");
        AppendMenu(hEllipse,MF_STRING,18, "Polar Ellipse");
        AppendMenu(hEllipse,MF_STRING,21, "Modified Polar Ellipse");
        AppendMenu(hEllipse,MF_STRING,22, "Midpoint Ellipse");

        HMENU hCurve = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP,(UINT_PTR)hCurve, "Curve");
        AppendMenu(hCurve,MF_STRING,19, "Herimate");
        AppendMenu(hCurve,MF_STRING,23, "Bezier");

        HMENU hfile = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP,(UINT_PTR)hfile, "File");
        AppendMenu(hfile, MF_STRING,1, "Open");
        AppendMenu(hfile, MF_STRING,2, "Save");

        HMENU hEdit = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP,(UINT_PTR)hEdit, "Edit");
        AppendMenu(hEdit,MF_STRING,5, "Undo");
        AppendMenu(hEdit, MF_STRING,6, "Redo");

        SetMenu(hwnd,hMenubar);
        break;
    }
    case WM_COMMAND:
    {
        if(LOWORD(wParam) == 1)
        {
            Open();
            PAINTSTRUCT PS;
            hdc = BeginPaint (hwnd,&PS);
            for(int i=0; i<(int)lines.size(); i++)
            {
                NumLine = i;
                l = lines[i];
                Draw();
            }
        }
        else if(LOWORD(wParam) == 2)
        {
            Save();
        }
        else if(LOWORD(wParam) == 3) // for Cartesian algorithm
            type = 1;

        else if(LOWORD(wParam) == 4)// for Midpoint Circle algorithm
            type = 2;

        else if(LOWORD(wParam) == 5 && NumLine >= 0) // to make Undo
        {
            Draw(RGB(255,255,255));
            NumLine--;
        }
        else if(LOWORD(wParam) == 6 && NumLine != (int)lines.size() - 1)// to make Redo
        {
            NumLine++;
            Draw();
        }
        else if(LOWORD(wParam) == 7)  // SDDA line
        {
            type = 3;
        }
        else if(LOWORD(wParam) == 8)// for Midpoint line algorithm
            type = 4;
        else if(LOWORD(wParam) == 9)//parametric line
            type = 5;
        else if(LOWORD(wParam) == 10)//DDA line
            type = 6;
        else if(LOWORD(wParam) == 11)//Cross lines
            type = 7;
        else if(LOWORD(wParam) == 12)//Triangle
            type = 8;
        else if(LOWORD(wParam) == 13)//Rectangle
            type = 9;
        else if(LOWORD(wParam) == 14)//polar circle- new
            type = 10;
        else if(LOWORD(wParam) == 15)//Modified polar circle- new
            type = 11;
        else if(LOWORD(wParam) == 16)//MidPoint circle- new
            type = 12;
        else if(LOWORD(wParam) == 17)//Modified MidPoint circle- new
            type = 13;
        else if(LOWORD(wParam) == 18)//polar ellipse- new
            type = 14;
        else if(LOWORD(wParam) == 20)//cartesian ellipse- new
            type = 16;
        else if(LOWORD(wParam) == 21)//Modified polar  Ellipse- new
            type = 17;
        else if(LOWORD(wParam) == 19)//Hermite Curve
            type = 15;
        else if(LOWORD(wParam) == 22)//midpoint Ellipse - new
            type = 18;
        else if(LOWORD(wParam) == 23)//Bezier Curve
            type = 20;
        break;
    }
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
