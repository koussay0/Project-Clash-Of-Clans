#ifndef CITIZENS_H
#define CITIZENS_H
#include<QGraphicsPixmapItem>
#include<QObject>
#include "castle.h"
#include "fence.h"
#include<QTimer>
#include "node.h"
class Citizens:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Citizens();
      std::vector<node*> DikestraAlgorithm(node* start, node* end);
public slots:

    void move();
private:
    bool continuemove;
    bool shouldlookForFence;
    bool citizendied;
    int citizenRow;
    int citizenCol;
    int targetFenceRow;
    int animationiterator;
    int targetFenceCol;
    void lookFence();
    std::vector<node*> shortestPath;
    QTimer* MoveTimer;
    int pathiterator;
    node* CurrentNode;
    float dX, dY;
    float distancetillCurrentNode;
};

#endif // CITIZENS_H
