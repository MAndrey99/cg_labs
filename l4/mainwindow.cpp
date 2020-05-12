#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->menuBar->addAction("сгенерировать линии", this, &MainWindow::on_linesBut_clicked);
    connect(this, &MainWindow::gen_lines, ui->drawField, &drawer::gen_lines);
    connect(this, &MainWindow::do_box, ui->drawField, &drawer::do_box);
    connect(ui->drawField, &drawer::points_n_updated, this, &MainWindow::on_points_n_updated);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_linesBut_clicked() {
    emit gen_lines();
    emit do_box(ui->spinBox->value());
}

void MainWindow::on_spinBox_valueChanged(int n) {
    emit do_box(n);
}

void MainWindow::on_points_n_updated(int n) {
    ui->label_2->setText(QString::number(n));
}
