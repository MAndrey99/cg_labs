#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "algo.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QSurface3DSeries *series = new QSurface3DSeries;
    series->dataProxy()->resetArray(get());
    surface.addSeries(series);

    ui->horizontalLayout->addWidget(QWidget::createWindowContainer(&surface));
    surface.show();
}

MainWindow::~MainWindow() {
    delete ui;
}
