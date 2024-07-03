#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include "castle.h"
#include "fence.h"
#include<QTimer>
#include "node.h"
class Enemy:public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(int d);
    void Die();
    void DecreaseHealth(int d);


    std::vector<node*> DikestraAlgorithm(node* start, node* end);
    ~Enemy();
private:
    int enemyRow;
    int enemyCol;
    int animationiterator;
    std::vector<node*> path;
    int damage;
    bool continuemove;
    int health;
    bool enemydied;
    QTimer* MoveTimer;
    int pathiterator;

     node* CurrentNode;
    float dX, dY;
    float distancetillCurrentNode;
public slots:
    void move();

};

#endif // ENEMY_H
