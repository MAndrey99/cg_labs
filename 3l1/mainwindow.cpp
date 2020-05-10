#include "mainwindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "algo.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QSurface3DSeries *series = new QSurface3DSeries;
    data = getData();
    series->dataProxy()->resetArray(data);
    surface.addSeries(series);

    ui->verticalLayout->addWidget(QWidget::createWindowContainer(&surface));
    surface.show();
}

void MainWindow::on_rotateX_pressed() {
    for (auto i : *data)
        for (auto &j : *i)
            j.setX(-j.x());

    update_data();
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
