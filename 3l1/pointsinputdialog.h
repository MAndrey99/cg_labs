#ifndef POINTSINPUTDIALOG_H
#define POINTSINPUTDIALOG_H

#include <QDialog>
#include <QVector3D>
#include <array>

namespace Ui {
class PointsInputDialog;
}

class PointsInputDialog: public QDialog {
    Q_OBJECT

public:
    explicit PointsInputDialog(QWidget *parent = nullptr);
    ~PointsInputDialog();

    static std::array<QVector3D, 4> getPoints();

public slots:
    void on_ok_pressed();

signals:
    void points_specified(std::array<QVector3D, 4>);

private:
    Ui::PointsInputDialog *ui;
};

#endif  // POINTSINPUTDIALOG_H
