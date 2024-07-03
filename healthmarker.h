#ifndef HEALTHMARKER_H
#define HEALTHMARKER_H
#include <QGraphicsRectItem>
#include <QObject>
#include<QGraphicsScene>
#include <QGraphicsPixmapItem>
class HealthMarker:public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    HealthMarker();
};

#endif // HEALTHMARKER_H
