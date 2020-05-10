#pragma once

#include <QMouseEvent>
#include <QVector>
#include <QWidget>

class drawer: public QWidget {
    Q_OBJECT
public:
    explicit drawer(QWidget *parent = 0);

signals:
protected:
    void paintEvent(QPaintEvent *e);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

public slots:
    void gen_lines();
    void do_box(int sides);

private:
    QVector<QLine> lines;
    int box_sides;
    int cur_amount;
    QList<QPoint> sides;
    bool mDrawMode;
};
