#include "cspline.h"
#include <QString>
#include <QVector>
#include <cmath>
#include <stdexcept>

float CSplineSubinterval::rightBoard() {
    return x;
}

double CSplineSubinterval::predictY(double x_) {
    return a + b * (x_ - x) + c * pow(x_ - x, 2) + d * pow(x_ - x, 3);
}

CSplineSubinterval::CSplineSubinterval(float a, float b, float c, float d, float x): a(a), b(b), c(c), d(d), x(x) {}

std::vector<CSplineSubinterval> CSplineSubinterval::buildSubintervals(const std::vector<QPointF> &points) {
    // TODO
}

CSpline::CSpline(const std::vector<QPointF> &points): subintervals(CSplineSubinterval::buildSubintervals(points)) {}

QVector<double> CSpline::predictY(const QVector<double> &x) {
    QVector<double> res;
    res.reserve(x.size());

    auto subintervalptr = subintervals.begin();
    for (auto it : x) {
        assert(it > double(leftBoard));
        while (it > double(subintervalptr->rightBoard()))
            subintervalptr++;

        res.append(subintervalptr->predictY(it));
    }

    return res;
}
