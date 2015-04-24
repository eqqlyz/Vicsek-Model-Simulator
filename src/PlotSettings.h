#ifndef PLOTSET_H
#define PLOTSET_H

#include<math.h>
#include <QStyleOptionFocusRect>
//#include<qstyleoption.h>
#include<QStylePainter>
//#include<qstylepainter.h>

class PlotSettings
{
public:
    PlotSettings();
	//公共的调节方法
	void setPlotter(double MinX,double MaxX,double MinY,double MaxY);
    void scroll(int dx, int dy);
    void adjust();
    double spanX() const { return maxX - minX; }
    double spanY() const { return maxY - minY; }

    double minX;
    double maxX;
    int numXTicks;
    double minY;
    double maxY;
    int numYTicks;

private:
    static void adjustAxis(double &min, double &max, int &numTicks);
};
#endif