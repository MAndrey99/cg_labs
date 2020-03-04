#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new Scene(this)) {
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    connect(scene, &Scene::rotation_point_selected, this, &MainWindow::rotation_point_selected);
    connect(ui->rotation, &QPushButton::pressed, scene, &Scene::rotate);
}

void MainWindow::rotation_point_selected() {
    ui->rotation->setEnabled(true);
}
