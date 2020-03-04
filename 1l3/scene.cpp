#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include "scene.h"


Scene::Scene(QObject* parent) : QGraphicsScene(parent) {
    // инициализируем нашу картинку черным фоном
    QPixmap pm(250, 250);
    image = pm.toImage();

    // рисуем квадрат
    QPainter painter(&image);
    painter.setPen(QPen(Qt::white));
    painter.drawRect(100, 100, 50, 50);

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

    // рисуем точку, относительно которой будет поворот
    QPixmap pm(QPixmap::fromImage(image));
    QPainter painter(&pm);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(rotation_point.x() - 5, rotation_point.y() - 5, 10, 10);

    // перересовываем сцену
    clear();
    addPixmap(pm);

    emit rotation_point_selected();
    qDebug() << rotation_point.x() << " " << rotation_point.y() << endl;
}

void Scene::rotate() {

}
