#ifndef BULLET_H
#define BULLET_H
#include<QGraphicsPixmapItem>
#include<QObject>
#include<QGraphicsItem>
class bullet:public QObject, public QGraphicsPixmapItem
{

    Q_OBJECT
public slots:
    void move();
public:
    bullet(int x, int y,int d);
    ~bullet();
    double CalculatePos();
private:
    int targetX;
    int targetY;
    int damage;

};

#endif // BULLET_H
