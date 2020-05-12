#pragma once

#include <QMouseEvent>
#include <QVector>
#include <QWidget>

class drawer: public QWidget {
    Q_OBJECT
public:
    explicit drawer(QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void points_n_updated(int);

public slots:
    void gen_lines();
    void do_box(int sides);

private:
    QVector<QLine> lines;
    QList<QPoint> sides;
    int box_sides;
    int cur_amount;
    bool mDrawMode;
};
