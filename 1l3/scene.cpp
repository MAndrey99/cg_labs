#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <cmath>
#include "scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    // инициализируем нашу картинку черным фоном
    QPixmap pm(500, 500);
    image = pm.toImage();

    // рисуем фигуры
    QPainter painter(&image);
    painter.setPen(QPen(Qt::white));
    painter.drawPolygon(QPolygon(QVector<QPoint>{
            QPoint(50, 50), QPoint(50, 450), QPoint(50, 250), QPoint(150, 50), QPoint(50, 250), QPoint(150, 450), QPoint(50, 250)
    }));  // K
    painter.drawPolygon(QPolygon(QVector<QPoint>{QPoint(260, 450), QPoint(260, 50), QPoint(450, 50), QPoint(260, 50)}));  // Г

    // добавляем картинку на сцену
    addPixmap(QPixmap::fromImage(image));
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // записываем координаты клика
    rotation_point = event->scenePos().toPoint();

    // проверка на выход за пределы изображения
    if (rotation_point.x() > image.size().width() or rotation_point.y() > image.size().height()
            or rotation_point.x() < 0 or rotation_point.y() < 0)
        return;

    has_rotation_point = true;
    update();

    emit rotation_point_selected();
    qDebug() << rotation_point.x() << " " << rotation_point.y() << endl;
}

void Scene::update() {
    clear();

    if (has_rotation_point) {
        // добавляем точку, относительно которой будет поворот
        QPixmap pm(QPixmap::fromImage(image.copy()));
        QPainter painter(&pm);
        painter.setBrush(Qt::yellow);
        painter.drawEllipse(rotation_point.x() - 5, rotation_point.y() - 5, 10, 10);
        addPixmap(pm);
    } else {
        addPixmap(QPixmap::fromImage(image));
    }
}

void Scene::rotate(double angle) {
    int width = image.width();
    int height = image.height();

    angle = -2 * M_PI * angle / 360;
    double s = sin(angle);
    double c = cos(angle);

    QPixmap pm(image.size());
    QImage newImage = pm.toImage().copy();

    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++) {
            double a = x - rotation_point.x();
            double b = y - rotation_point.y();
            int xx = int(+a * c - b * s + rotation_point.x());
            int yy = int(+a * s + b * c + rotation_point.y());

            if (xx >= 0 && xx < width && yy >= 0 && yy < height)
                newImage.setPixel(x, y, image.pixel(xx, yy));
            else
                newImage.setPixel(x, y, 0);
        }

    image = newImage;
    update();
}
