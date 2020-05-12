#include "drawer.h"
#include <QPainter>
#include <QStyleOption>
#include <cmath>
#include <numeric>
#include "QTime"
#include "stdlib.h"

drawer::drawer(QWidget *parent): QWidget(parent) {
    box_sides = 0;
    mDrawMode = false;
    cur_amount = 0;
}

void drawer::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && (cur_amount <= box_sides)) {
        mDrawMode = true;

        sides.append(event->pos());
        event->accept();
        cur_amount++;
    }
}

void drawer::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && (cur_amount <= box_sides)) {
        mDrawMode = false;
        sides.append(event->pos());
        this->update();
        event->accept();
    }
}

double scalar(QPoint a, QPoint b) {
    return double(a.x() * b.x() + a.y() * b.y());
}

QPoint normal(QPoint a, QPoint b, QPoint z) {
    QPoint d = b - a;
    QPoint n(-d.y(), d.x());
    QPoint v(z.x() - a.x(), z.y() - a.y());

    double dot = scalar(v, n);

    if (fabs(dot) <= std::numeric_limits<double>::epsilon()) {
        return QPoint();
    } else if (dot < 0) {
        n *= -1;
    }

    return n;
}

void CyrusBeckAlgorithm(QVector<QPoint> polygon, QPoint a, QPoint b, QPainter &painter) {
    QPoint d = b - a;
    QPoint dir(d.x(), d.y());

    double tEnter = 0.0;
    double tLeave = 1.1;

    QPoint boundary(polygon[polygon.size() - 2]);

    for (size_t i = 0; i < polygon.size() - 1; ++i) {
        QPoint edge_p0(polygon[i]);
        QPoint edge_p1(polygon[i + 1]);

        QPoint norm(normal(edge_p0, edge_p1, boundary));
        QPoint w(a.x() - edge_p0.x(), a.y() - edge_p0.y());

        double num = scalar(w, norm);
        double den = scalar(dir, norm);

        if (fabs(den) <= std::numeric_limits<double>::epsilon()) {
            if (num < 0)
                return;
            else
                continue;
        }

        double t = -num / den;

        if (den > 0) {
            tEnter = std::max(tEnter, t);
        } else if (den < 0) {
            tLeave = std::min(tLeave, t);
        }

        boundary = edge_p0;
    }

    if (tEnter > tLeave) {
        return;
    }

    QPoint clipped_p0;
    clipped_p0.setX(a.x() + (d.x() * tEnter));
    clipped_p0.setY(a.y() + (d.y() * tEnter));

    QPoint clipped_p1;
    clipped_p1.setX(a.x() + (d.x() * tLeave));
    clipped_p1.setY(a.y() + (d.y() * tLeave));

    painter.setPen(Qt::gray);
    painter.drawLine(a, clipped_p0);  // начало линии -> начало отсечения
    painter.setPen(Qt::red);
    painter.drawLine(clipped_p0, clipped_p1);  // отсеченная линия
    painter.setPen(Qt::gray);
    painter.drawLine(clipped_p1, b);  // конец отсечения -> конец линии
}

void drawer::paintEvent(QPaintEvent *) {
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    painter.setPen(Qt::gray);

    emit points_n_updated(cur_amount);

    for (int i = 0; i < lines.size(); i++)
        painter.drawLine(lines[i]);

    painter.setPen(Qt::green);
    painter.setBrush(Qt::green);
    if (sides.size() < 1)
        return;

    QVector<QPoint> side;
    if (cur_amount == box_sides)
        sides.append(*sides.begin());

    QList<QPoint>::const_iterator it = sides.begin();
    while (it != sides.end()) {
        QPoint buf = *it;
        side.push_back(buf);
        it++;
    }
    it = sides.begin();

    QPoint start = *it;
    it++;
    while (it != sides.end()) {
        QPoint end = *it;
        painter.drawLine(start, end);
        start = end;
        it++;
    }

    if (cur_amount == box_sides) {
        for (int i = 0; i < lines.size(); i++) {
            CyrusBeckAlgorithm(side, lines[i].p1(), lines[i].p2(), painter);
        }
    }
    //Кирус-Бэк
}

inline int rand_less(int number) {
    int result = qrand() % number;
    return result;
}

void drawer::gen_lines() {
    lines.clear();
    sides.clear();
    qsrand(uint(time(nullptr)));

    int amount = qrand() % 20;
    QLine buf;
    QPoint p1;
    QPoint p2;
    for (int i = 0; i < amount; i++) {
        p1.setX(rand_less(this->width()));
        p1.setY(rand_less(this->height()));

        p2.setX(rand_less(this->width()));
        p2.setY(rand_less(this->height()));

        buf.setP1(p1);
        buf.setP2(p2);

        lines.push_back(buf);
    }

    update();
}

void drawer::do_box(int s) {
    sides.clear();
    box_sides = s;
    cur_amount = 0;

    update();
}
