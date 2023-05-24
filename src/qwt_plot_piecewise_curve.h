#pragma once

#include "qwt_plot_curve.h"

class QWT_EXPORT QwtPlotPiecewiseCurve: public QwtPlotCurve
{
public:
    explicit QwtPlotPiecewiseCurve();
    virtual QRectF boundingRect() const;
    virtual void drawSeries(QPainter *painter, const QwtScaleMap &xMap,
                            const QwtScaleMap &yMap, const QRectF &canvRect, int from, int to)  const;
};

inline QwtPlotPiecewiseCurve::QwtPlotPiecewiseCurve(): QwtPlotCurve()
{
}