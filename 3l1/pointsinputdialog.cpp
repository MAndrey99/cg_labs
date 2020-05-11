#include "pointsinputdialog.h"
#include <QVector3D>
#include "ui_pointsinputdialog.h"

PointsInputDialog::PointsInputDialog(QWidget *parent): QDialog(parent), ui(new Ui::PointsInputDialog) {
    ui->setupUi(this);
}

PointsInputDialog::~PointsInputDialog() {
    delete ui;
}

std::array<QVector3D, 4> PointsInputDialog::getPoints() {
    PointsInputDialog dlg;
    std::array<QVector3D, 4> res;
    connect(&dlg, &PointsInputDialog::points_specified, [&res](std::array<QVector3D, 4> points) { res = points; });
    dlg.exec();
    return res;
}

void PointsInputDialog::on_ok_pressed() {
    std::array<QVector3D, 4> data;
    data[0] = QVector3D(ui->doubleSpinBox_1x->value(), ui->doubleSpinBox_1y->value(), ui->doubleSpinBox_1z->value());
    data[1] = QVector3D(ui->doubleSpinBox_2x->value(), ui->doubleSpinBox_2y->value(), ui->doubleSpinBox_2z->value());
    data[2] = QVector3D(ui->doubleSpinBox_3x->value(), ui->doubleSpinBox_3y->value(), ui->doubleSpinBox_3z->value());
    data[3] = QVector3D(ui->doubleSpinBox_4x->value(), ui->doubleSpinBox_4y->value(), ui->doubleSpinBox_4z->value());

    emit points_specified(data);
    accept();
}
