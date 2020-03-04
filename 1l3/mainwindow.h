#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <memory>
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void rotation_point_selected();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    Scene *scene;
};

#endif // MAINWINDOW_H
