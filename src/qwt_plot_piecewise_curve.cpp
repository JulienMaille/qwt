#include "qwt_plot_piecewise_curve.h"
#include <qnumeric.h>

// This is a slow implementation: it might be worth to cache valid data ranges.
void QwtPlotPiecewiseCurve::drawSeries(QPainter *painter, const QwtScaleMap &xMap, const QwtScaleMap &yMap,
                                       const QRectF &canvRect, int from, int to) const
{
    if( !painter || dataSize()<=0 )
        return;

    if( to<0 ) to = (int)dataSize()-1;

    int first, last=from;
    while( last<=to )
    {
        first = last;
        while( first <= to && (qIsNaN(sample(first).x()) || qIsNaN(sample(first).y())) )
            ++first;
        last = first;
        while( last <= to && !qIsNaN(sample(last).x()) && !qIsNaN(sample(last).y()) )
            ++last;
        if( first<=to )
            QwtPlotCurve::drawSeries(painter, xMap, yMap, canvRect, first, last-1);
    }
}

QRectF QwtPlotPiecewiseCurve::boundingRect() const
{
    if( dataSize()<=0 )
        return QRectF(1.0, 1.0, -2.0, -2.0); // Empty data.

    uint first=0;
    while( first<dataSize() && (qIsNaN(sample(first).x()) || qIsNaN(sample(first).y())) )
        ++first;

    if( first==dataSize() )
        return QRectF(1.0, 1.0, -2.0, -2.0); // Empty data.

    double minX, maxX, minY, maxY;
    minX = maxX = sample(first).x();
    minY = maxY = sample(first).y();
    for (uint i = first + 1; i < dataSize(); ++i)
    {
        const double xv = sample(i).x();
        if (xv < minX) minX = xv;
        if (xv > maxX) maxX = xv;
        const double yv = sample(i).y();
        if (yv < minY) minY = yv;
        if (yv > maxY) maxY = yv;
    }

    return QRectF(minX, minY, maxX-minX, maxY-minY);
}