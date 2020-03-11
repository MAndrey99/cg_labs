#pragma once
#include <QPointF>
#include <list>
#include <vector>

/**
 * @brief The CSplineSubinterval class
 *
 * Описывает интервалл между двух точек в виде полинома 3й степени
 */
class CSplineSubinterval {
public:
    /**
     * @brief производит расчет всех интервалов в сплайне
     * @param points: точки на основе кторовых идет интерполяция
     */
    static std::vector<CSplineSubinterval> buildSubintervals(const std::vector<QPointF> &points);

    float rightBoard();  ///< самое высокое значение x, для которого возможно предсказать y
    double predictY(double x);  ///< предсказывает y по позиции x

private:
    CSplineSubinterval(float a, float b, float c, float d, float x);

    float a, b, c, d, x;  ///< коэффициенты
};

/**
 * @brief The CSpline class
 *
 * Сплайн 3й степени для интерполяции
 */
class CSpline {
public:
    CSpline(const std::vector<QPointF> &points);

    QVector<double> predictY(const QVector<double> &x);  ///< предсказывает y для указаного отсортированного x

private:
    std::vector<CSplineSubinterval> subintervals;  ///< полиномы 3й степени, для предсказаний значений на интервалах
    float leftBoard;  ///< позиция x самой левой точки, значение которой можно предасказать
};
