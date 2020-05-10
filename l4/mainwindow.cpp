#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QObject::connect(this, SIGNAL(gen_lines()), ui->drawField, SLOT(gen_lines()));
    QObject::connect(this, SIGNAL(do_box(int)), ui->drawField, SLOT(do_box(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_linesBut_clicked() {
    emit gen_lines();
}

void MainWindow::on_boxBut_clicked() {
    emit(do_box(ui->sides->text().toInt()));
}
