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
    const int N = points.size() - 1;  // x0......xn
    std::vector<CSplineSubinterval> spline(N + 1);  //наш сплайн ^-^

    std::vector<double> h(N + 1, 0);  //массив h
    for (int i = 1; i <= N; i++) {
        h[i] = points[i].x() - points[i - 1].x();
    };

    //создаем матрицу и решаем ее подгонкой
    std::vector<double> a(N + 1, 0), b(N + 1, 0), c(N + 1, 0);
    for (int i = 2; i <= N - 1; i++) {
        a[i] = h[i];
        b[i] = h[i + 1];
        c[i] = 2 * (h[i] + h[i + 1]);
    }
    c[1] = 1;
    c[N] = 1;

    a[N] = h[N];
    std::vector<double> f(N + 1, 0);  //инициализируем массив f
    f[1] = 0;
    f[N] = 0;
    for (int i = 2; i < N; i++) {
        f[i] = 3 * ((points[i + 1].y() - points[i].y()) / h[i + 1] - (points[i].y() - points[i - 1].y()) / h[i]);
    }
    //считаем матричные альфы и беты
    std::vector<double> alpha(N + 1, 0), beta(N + 1, 0);
    alpha[2] = (-1) * b[1] / c[1];
    beta[2] = f[1] / c[1];
    for (int i = 3; i <= N; i++) {
        alpha[i] = (-1) * (b[i - 1] / (a[i - 1] * alpha[i - 1] + c[i - 1]));
        beta[i] = (f[i - 1] - a[i - 1] * beta[i - 1]) / (a[i - 1] * alpha[i - 1] + c[i - 1]);
    }
    //считаем коэфы с сплайна
    spline[N].c = (f[N] - a[N] * beta[N]) / (c[N] + a[N] * alpha[N]);
    for (int i = N - 1; i > 0; i--) {
        spline[i].c = alpha[i + 1] * spline[i + 1].c + beta[i + 1];
    }
    spline[0].a = points[0].y();
    for (int i = 1; i <= N; i++) {
        spline[i].a = points[i].y();
        spline[i].d = (spline[i].c - spline[i - 1].c) / (3 * h[i]);
        spline[i].b = (spline[i].a - spline[i - 1].a) / (h[i]) + (2 * spline[i].c + spline[i - 1].c) / 3 * h[i];
        spline[i].x = points[i].x();
    }
    spline.erase(spline.begin());  // в первом элементе мусор
    return spline;
}

CSpline::CSpline(const std::vector<QPointF> &points): subintervals(CSplineSubinterval::buildSubintervals(points)) {
    assert(points.size() > 0);
    leftBoard = points[0].x();
}

QVector<double> CSpline::predictY(const QVector<double> &x) {
    QVector<double> res;
    res.reserve(x.size());

    auto subintervalptr = subintervals.begin();
    for (auto it : x) {
        while (it > double(subintervalptr->rightBoard()))
            subintervalptr++;

        res.append(subintervalptr->predictY(it));
    }

    return res;
}
