#pragma once

#include <Q3DSurface>
#include <QMainWindow>

using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void update_data();
    ~MainWindow();

public slots:
    void on_rotateX_pressed();
    void on_rotateY_pressed();

private:
    Ui::MainWindow *ui;
    Q3DSurface surface;
    QSurfaceDataArray *data;
};
