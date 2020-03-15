#include "mainwindow.h"
#include <QDebug>
#include <QDialog>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow), scene(new Scene(this)) {
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    // создаем окно, которое будет отображать орегинальное изображение
    QWidget* window = new QWidget;
    QPalette pal = palette();
    pal.setBrush(QPalette::Window, QBrush(*scene->getImage()));
    window->setPalette(pal);
    window->resize(scene->getImage()->size());
    window->show();

    connect(scene, &Scene::rotation_point_selected, this, &MainWindow::rotation_point_selected);
    connect(ui->rotation, &QPushButton::pressed, scene, [this]() { scene->rotate(ui->rotationAngle->value()); });
}

void MainWindow::rotation_point_selected() {
    ui->rotation->setEnabled(true);
}
