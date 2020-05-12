#pragma once

#include <QMainWindow>
#include <QSpinBox>

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void gen_lines();
    void do_box(int sides);

private slots:
    void on_linesBut_clicked();
    void on_spinBox_valueChanged(int);
    void on_points_n_updated(int);

private:
    Ui::MainWindow *ui;
    int slides = 0;
};
