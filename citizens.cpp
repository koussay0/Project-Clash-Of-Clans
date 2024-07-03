#include "citizens.h"
#include"fence.h"
#include"QTimer"
#include "enemy.h"
#include <queue>
#include "game.h"
extern Game* g;
Citizens::Citizens() {
    citizendied=false;
    shouldlookForFence=true;
    animationiterator=0;
    setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(80, 80));


    dX = 0;
    dY = 0;

    MoveTimer = new QTimer(this);
    connect( MoveTimer,&QTimer::timeout, this, [=](){
        if(!g->gameover){

        if (shouldlookForFence)
            {
                lookFence();
            }
        else{
 distancetillCurrentNode = sqrt(pow(this->x() - CurrentNode->imgelemnt->x(), 2) + pow(this->y() - CurrentNode->imgelemnt->y(), 2));
        if(distancetillCurrentNode<35)
        {
            if(pathiterator != 0){
                pathiterator--;
                CurrentNode = shortestPath[pathiterator];
            }
        }
        if(!citizendied){
            move();
        }}}});
    MoveTimer->start(50);
}

void Citizens::move()
{
    if(!g->gameover){
    if(animationiterator%4>1)
        setPixmap(QPixmap(":/citizen/images/citizen 1.png").scaled(80, 80));

            else {
              setPixmap(QPixmap(":/citizen/images/citizen2.png").scaled(80, 80));
        }
            animationiterator++;
    continuemove=true;
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
         Enemy *enemy = dynamic_cast<Enemy*>(colliding_items[i]);
            if (enemy) {
             MoveTimer->stop();
             citizendied=true;
             scene()->removeItem(this);
                delete this;
            }
        }
    }

    QList<QGraphicsItem *> colliding_items2 = collidingItems();
    for (int i = 0; i < colliding_items2.size(); ++i) {
        if (Fence* fenceItem = dynamic_cast<Fence*>(colliding_items[i])) {
            if(fenceItem->x()==targetFenceCol*75&&fenceItem->y()==targetFenceRow*75){
            fenceItem->increaseHealth();
                continuemove=false;// qDebug()<<"currentcostduringhealing"<<g->nodes[targetFenceRow][targetFenceCol]->object->costToPass;
 setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(80,80));
            }
            }
        }
    if(g->nodes[targetFenceRow][targetFenceCol]->imgelemnt->costToPass==60||g->nodes[targetFenceRow][targetFenceCol]->imgelemnt->costToPass==10){
        shouldlookForFence=true;  setPixmap(QPixmap(":/new/images/images/citizenWorker.png").scaled(80, 80));
        return;}
    dX = (CurrentNode->imgelemnt->x() - this->x()) / distancetillCurrentNode;
    dY = (CurrentNode->imgelemnt->y() - this->y()) / distancetillCurrentNode;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;


    if(continuemove)
    {
        setPos(newX, newY);
    }
    }
}

void Citizens::lookFence()
{
    if(!g->gameover){    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            Enemy *enemy = dynamic_cast<Enemy*>(colliding_items[i]);
            if (enemy) {
                 MoveTimer->stop();
                citizendied=true;
                scene()->removeItem(this);
                delete this;
            }
        }
    }

    int min=6000;
    for (const auto& row : g->nodes) {
        for (const auto& node_ptr : row) {
            if(node_ptr->imgelemnt->name=="fence")
            {
             //   qDebug()<<"wer are in a fence that has health:"<<node_ptr->object->costToPass;
                if (node_ptr->imgelemnt->costToPass<60&&node_ptr->imgelemnt->costToPass>10&&(sqrt(pow(this->x() -node_ptr->imgelemnt->x(), 2) + pow(this->y() - node_ptr->imgelemnt->y(), 2))<min))
                {
                    min=sqrt(pow(this->x() -node_ptr->imgelemnt->x(), 2) + pow(this->y() - node_ptr->imgelemnt->y(), 2));
                    targetFenceRow= node_ptr->imgelemnt->y()/75;
                     targetFenceCol= node_ptr->imgelemnt->x()/75;
                    shouldlookForFence=false;

                }
            }
        }
    }
    if(!shouldlookForFence)
    {
        node* start = g->nodes[y()/75][x()/75];
        //  qDebug()<<"targetrow:"<<targetFenceRow<<"targetcol"<<targetFenceCol;
        node* end = g->nodes[targetFenceRow][targetFenceCol];
        shortestPath = DikestraAlgorithm(start, end);
        pathiterator = shortestPath.size()-2;
        CurrentNode = shortestPath[pathiterator];
        distancetillCurrentNode = sqrt(pow(this->x() - CurrentNode->imgelemnt->x(), 2) + pow(this->y() - CurrentNode->imgelemnt->y(), 2));
      //  qDebug()<<"rached here without crash";
    }
    }
}

std::vector<node*> Citizens::DikestraAlgorithm(node* start, node* end) {
    std::vector<node*> path;
    std::unordered_map<node*, double> distances;
    std::unordered_map<node*, node*> previous;
    std::priority_queue<std::pair<double, node*>, std::vector<std::pair<double, node*>>, std::greater<std::pair<double, node*>>> priorityq;

    for (const auto& row :g-> nodes) {
        for (const auto& node_ptr : row) {
            distances[node_ptr] = std::numeric_limits<double>::infinity();
            previous[node_ptr] = nullptr;
        }
    }

    distances[start] = 0;
    priorityq.push({0, start});

    while (!priorityq.empty()) {
        node* n = priorityq.top().second;
        priorityq.pop();

        if (n == end) {
            break;
        }

        for (const auto& connection : n->Neighbours) {
            node* n2 = connection.second.first;
            double weight = connection.second.second;

            double alternate = distances[n] + weight;

            if (alternate < distances[n2]) {
                distances[n2] = alternate;
                previous[n2] = n;
                priorityq.push({alternate, n2});
            }
        }
    }

    node* current = end;
    while (current != nullptr) {
        path.push_back(current);
        current = previous[current];
    }

    return path;
}
