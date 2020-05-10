#pragma once
#include <QSurfaceDataArray>

using namespace QtDataVisualization;

//это сама функция для счета интерполяции
QSurfaceDataArray *getData(QVector<QVector3D> &points, float step)//очень важен порядок обхода точек
{


    if (points.size()!=4)
        return nullptr;

    QSurfaceDataArray *data = new QSurfaceDataArray;

    for(float y = points[0].y(); y <= points[2].y(); y+=step)
    {
        QSurfaceDataRow *dataRow = new QSurfaceDataRow;
        for(float x = points[0].x(); x<= points[1].x(); x+=step)
        {
            float x1 =points[0].x(), y1 =points[0].y();
            float x2= points[1].x(), y2 = points[2].y();

            float z = points[0].z()*(x2-x)*(y2-y)/((x2-x1)*(y2-y1))
                    + points[1].z()*(x-x1)*(y2-y)/((x2-x1)*(y2-y1))
                    + points[2].z()*(x2-x)*(y-y1)/((x2-x1)*(y2-y1))
                    + points[3].z()*(x-x1)*(y-y1)/((x2-x1)*(y2-y1));
            *dataRow << QVector3D(x,y,z);
        }
        *data << dataRow;
    }
    return data;
}

//тут реализован пример из википкдии
QSurfaceDataArray *get() {

    QVector<QVector3D> points(4);
    points[0] = QVector3D(0,0,0);
    points[1] = QVector3D(1,0,1);
    points[2] = QVector3D(0,1,1);
    points[3] = QVector3D(1,1,0.5);
    QSurfaceDataArray *data = new QSurfaceDataArray;
    data = getData(points,0.01);

    return data;
}
