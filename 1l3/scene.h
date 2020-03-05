#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

/**
 * @brief The Scene class
 *
 * Класс, описывающий область экрана, в которой отображается картинка
 */
class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    Scene(QObject* parent);

    /**
     * @brief поворот изображения
     * @param angle: угл в градусах, на который будет осуществлен поворот
     */
    void rotate(double angle);

signals:
    void rotation_point_selected();  /// сигнал о том, что rotation_point выбран и можно поворачивать изображение

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);  /// выбор rotation_point

private:
    void update(); /// заново ресует image

    QImage image;  /// картинка, которая будет поворачиваться!
    QPoint rotation_point; /// точка, относительно которой будет происходить поворот изображения
    bool has_rotation_point = false;
};

#endif // SCENE_H
