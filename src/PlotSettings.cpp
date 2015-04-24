#include "PlotSettings.h"

//���캯����ɼ򵥵ĳ�ʼ�������ǣ���numXTicks��numYTicks�ĳ�ʼ���Ǳ���һ�²���ģ�
PlotSettings::PlotSettings()
{
    minX = 0.0;
    maxX = 10.0;
    numXTicks = 5;

    minY = 0.0;
    maxY = 10.0;
    numYTicks = 5;
}
//���ñ߿�Χ
void PlotSettings::setPlotter(double MinX,double MaxX,double MinY,double MaxY){
	minX=MinX;
	maxX=MaxX;
	minY=MinY;
	maxY=MaxY;
}
//�ı�������ķ�Χ����Ҫ�Ǻ�����
void PlotSettings::scroll(int dx, int dy)
{
    double stepX = spanX() / numXTicks;
    minX += dx * stepX;
    maxX += dx * stepX;

    double stepY = spanY() / numYTicks;
    minY += dy * stepY;
    maxY += dy * stepY;
}
//������������
void PlotSettings::adjust()
{
    adjustAxis(minX, maxX, numXTicks);
    adjustAxis(minY, maxY, numYTicks);
}
//��������������ķ���
void PlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    const int MinTicks = 4;
    double grossStep = (max - min) / MinTicks;
    double step = pow(10.0, floor(log10(grossStep)));

    if (5 * step < grossStep) {
        step *= 5;
    } else if (2 * step < grossStep) {
        step *= 2;
    }

    numTicks = int(ceil(max / step) - floor(min / step));
    if (numTicks < MinTicks)
        numTicks = MinTicks;
    min = floor(min / step) * step;
    max = ceil(max / step) * step;
}
