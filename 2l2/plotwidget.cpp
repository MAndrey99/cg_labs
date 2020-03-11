#include "plotwidget.h"
#include <QDebug>
#include "cspline.h"

PlotWidget::PlotWidget(QWidget* parent): QCustomPlot(parent) {
    setFixedSize(PLOTSIZE);  // не будем обрабатывать изменения размеров окна
}

void PlotWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::MouseButton::LeftButton)
        return;  // учитываем только нажатия левой кнопки

    auto pos = event->pos();
    qDebug() << pos;

    // ищем тыкнули ли в уже существующую точку
    for (auto it = points.begin(); it != points.end(); it++)
        if (pow(abs(it->x() - pos.x()), 2) + pow(abs(it->y() - pos.y()), 2) < POINT_RADIUS * POINT_RADIUS) {
            // надо удалить точку, в которую тыкнули
            points.erase(it);
            updatePlot();
            qDebug() << "точка удалена\n";
            return;  // больше точек в близости нажатия быть не может тк между ними минимум 2 их радиуса = 10
        }

    // проверяем можем ли мы поставить сюда точку или она будет слишком близкоа к другой
    for (auto& it : points) {
        if (pow(abs(it.x() - pos.x()), 2) + pow(abs(it.y() - pos.y()), 2) < 4 * POINT_RADIUS * POINT_RADIUS
            or it.x() == pos.x()) {
            qDebug() << "точка не может быть добавлена\n";
            return;
        }
    }

    points.emplace_back(pos);
    qDebug() << "точка добавлена\n";
    updatePlot();
}

void PlotWidget::updatePlot() {
    clearGraphs();

    // рисуем отмеченые точки

    addGraph();
    graph()->setPen(QPen(Qt::black));
    graph()->setLineStyle(QCPGraph::lsLine);
    graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, POINT_RADIUS));
    QVector<double> x, y;
    x.reserve(int(points.size()));
    y.reserve(int(points.size()));
    for (auto& it : points) {
        x.append(xAxis->pixelToCoord(it.x()));
        y.append(yAxis->pixelToCoord(it.y()));
    }
    graph()->setData(x, y);
    replot();

    // рисуем результат интерполяции с помощью нашего сплайна

    // инициализируем график
    addGraph();
    graph()->setPen(QPen(Qt::red));
    graph()->setLineStyle(QCPGraph::lsLine);
    // graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone));

    // создаем сплайн
    std::vector<QPointF> graph_points;
    x.reserve(int(points.size()));
    for (auto a = x.begin(), b = y.begin(); a != x.end(); ++a, ++b)
        graph_points.emplace_back(QPointF(*a, *b));
    CSpline spline(graph_points);

    // создаем sx и предсказываем для него sy
    QVector<double> sx;
    sx.reserve(int(points.size()));
    for (int i = points.front().x(); i <= points.back().x(); i++) {
        sx.append(xAxis->pixelToCoord(i));
    }
    auto sy = spline.predictY(sx);
    graph()->setData(sx, sy);

    graph()->rescaleAxes(true);
    replot();
}
