#pragma once
#include <QPoint>
#include <list>
#include "../qcustomplot/qcustomplot.h"

constexpr static int POINT_RADIUS = 10;
constexpr static QSize PLOTSIZE = QSize(750, 500);

/**
 * @brief Класс, описывающий область, в которой будем строить граффики
 */
class PlotWidget: public QCustomPlot {
    Q_OBJECT

public:
    PlotWidget(QWidget* parent);

protected:
    /**
     * @brief добавление/удаление точек, через которые пойдет график
     */
    virtual void mousePressEvent(QMouseEvent* event) override;

private:
    void updatePlot();  ///< перестраивает график основываясь на points

    std::list<QPoint> points;  ///< точки, через которые строим график (координаты в пикселях)
};
