#ifndef PLOTTER_H
#define PLOTTER_H

#include <QPixmap>
#include <QVector>
#include <QWidget>
#include "PlotSettings.h"

class Plotter : public QWidget
{
    Q_OBJECT

public:
    Plotter(QWidget *parent = 0);

    void setPlotSettings(const PlotSettings &settings);
    void setCurveData(const QVector<QPointF> &data);
    void clearCurve(); 
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);//绘制事件
	
private:
    void updateRubberBandRegion();
    void refreshPixmap();
    void drawGrid(QPainter *painter);	//绘制网格
    void drawCurves(QPainter *painter);	//绘制曲线

    enum { Margin = 50 };
	
public:
    QVector<QPointF> curveMap;
    PlotSettings setting;
    bool rubberBandIsShown;
    QRect rubberBandRect;
    QPixmap pixmap;
};

#endif
