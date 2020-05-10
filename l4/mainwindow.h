#pragma once

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
signals:
    void gen_lines();
    void do_box(int sides);
private slots:
    void on_linesBut_clicked();
    void on_boxBut_clicked();
};
