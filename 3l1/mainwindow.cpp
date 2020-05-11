#include "mainwindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "algo.hpp"
#include "pointsinputdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->verticalLayout->addWidget(QWidget::createWindowContainer(&surface));
    build_plot();
}

void MainWindow::build_plot() {
    QSurface3DSeries *series = new QSurface3DSeries;
    data = getData(PointsInputDialog::getPoints(), .01f);
    series->dataProxy()->resetArray(data);
    surface.addSeries(series);
    surface.show();
    ui->rotateX->setEnabled(true);
    ui->rotateY->setEnabled(true);
}

void MainWindow::on_rotateX_pressed() {
    for (auto i : *data)
        for (auto &j : *i)
            j.setX(-j.x());

    update_data();
    surface.axisX()->setRange(-surface.axisX()->max(), -surface.axisX()->min());
}

void MainWindow::on_rotateY_pressed() {
    for (auto i : *data)
        for (auto &j : *i)
            j.setY(-j.y());

    update_data();
}

void MainWindow::update_data() {
    QSurface3DSeries *series = new QSurface3DSeries;
    series->dataProxy()->resetArray(data);
    for (auto &it : surface.seriesList())
        surface.removeSeries(it);
    surface.addSeries(series);
    surface.show();
}

MainWindow::~MainWindow() {
    delete ui;
}
