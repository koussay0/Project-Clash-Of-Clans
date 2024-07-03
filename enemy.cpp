#include "enemy.h"
#include <cmath>
#include <QGraphicsScene>
#include"game.h"
#include <QTimer>
#include <set>
#include<iostream>
#include <stack>
#include<QMediaPlayer>
#include<QAudioOutput>
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include<queue>
extern Game *g;
extern int Volume;
Enemy::Enemy(int d)
{
    animationiterator=0;
    damage=d;
    qDebug()<<"enemy constructed";
    enemydied=false;
    continuemove =true;
    health = 200;
    setPixmap(QPixmap(":/dragon/images/dragon1.png").scaled(75, 75));

    int random_number = rand() %1125;

    int random_number2= rand()%750;

    if (rand()%2)
    {
        while (random_number2>20 &&random_number2<730)
            {
                random_number2= rand()%750;
            }
    }
    else
    {
        while(random_number>20&&random_number<1105)
        {
            random_number=rand()%1125;
        }
    }
    setPos(random_number,random_number2);

    enemyRow=y()/75;
    enemyCol=x()/75;
    qDebug()<<enemyRow<<" "<<enemyCol<<"\n";
    node* start = g->nodes[enemyRow][enemyCol];
    node* end = g->nodes[g->getCastle()->castleRow][g->getCastle()->castleColumn];
     path = DikestraAlgorithm(start, end);

    for (auto it = path.rbegin(); it != path.rend(); it++) {
         qDebug()<<(*it)->imgelemnt->name << (*it)->imgelemnt->rowAndColOfElement << ": ";
        qDebug()  << "(" << (*it)->imgelemnt->x() << ", " << (*it)->imgelemnt->y() << ")" << "\n";
    }
       qDebug()  << "\n";
    pathiterator = path.size()-2;
    CurrentNode = path[pathiterator];

    distancetillCurrentNode = sqrt(pow(this->x() - CurrentNode->imgelemnt->x(), 2) + pow(this->y() - CurrentNode->imgelemnt->y(), 2));

    dX = 0;
     dY = 0;
    MoveTimer = new QTimer(this);
    connect( MoveTimer,&QTimer::timeout, this, [=](){

        distancetillCurrentNode = sqrt(pow(this->x() - CurrentNode->imgelemnt->x(), 2) + pow(this->y() - CurrentNode->imgelemnt->y(), 2));
        if(distancetillCurrentNode<35)
        {
            if(pathiterator != 0){
                pathiterator--;
                CurrentNode = path[pathiterator];
            }
        }
        if(enemydied != true){
            move();
        }});
    MoveTimer->start((6-g->hardness)*10+50);

}

void Enemy::DecreaseHealth(int d){
    health-=d;
    QMediaPlayer *Q = new QMediaPlayer;
    Q ->setSource(QUrl("qrc:/new/Sound/Sound/dead.mp3"));

    QAudioOutput *audio = new QAudioOutput;
    Q->setAudioOutput(audio);
    audio->setVolume(Volume);
    Q->play();
    if(health<=0)
    {
        Die();
    }

}

void Enemy::Die(){
    g->enemydestroyed++;
    MoveTimer->stop();
        scene()->removeItem(this);
        qDebug()<<"enemy died";
        enemydied=true;
        delete this;
}
void Enemy::move()
{
    if(!g->gameover){

    animationiterator++;    dX = (CurrentNode->imgelemnt->x() - this->x()) / distancetillCurrentNode;
    dY = (CurrentNode->imgelemnt->y() - this->y()) / distancetillCurrentNode;

    float newX = this->x() + 2*dX;
    float newY = this->y() + 2*dY;

    bool passFence=false;
    qDebug()<<CurrentNode->imgelemnt->name<<path[pathiterator+1]->imgelemnt->name;
    if((CurrentNode->imgelemnt->name=="emptyland"||CurrentNode->imgelemnt->name=="Castle")&&path[pathiterator+1]->imgelemnt->name=="emptyland")
    {
        passFence=true;

    }
    continuemove=true;
    bool fenceispartofpath=false;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (Fence* fenceItem = dynamic_cast<Fence*>(colliding_items[i])) {
            if(!passFence&&fenceItem->name=="fence"){
                for(auto ptr:path)
                {
                    if (ptr->imgelemnt->x()==fenceItem->x()&&ptr->imgelemnt->y()==fenceItem->y())
                        fenceispartofpath=true;
                }
                if(fenceispartofpath)
                {
                    fenceItem->DecreaseHealth(damage);
                    continuemove=false;
                }

            }
        }
        else if(Castle* castleItem = dynamic_cast<Castle*>(colliding_items[i])){
            castleItem->DecreaseHealth(damage);
            return;
            continuemove=false;
        }
    }
    if(continuemove){
        setPos(newX, newY);
        if(animationiterator%4>1)
            setPixmap(QPixmap(":/dragon/images/dragon1.png").scaled(75, 75));

        else {
            setPixmap(QPixmap(":/dragon/images/dragon2.png").scaled(75, 75));
        }} }
}


Enemy::~Enemy()
{
    qDebug()<<"enemy destructed";
    delete MoveTimer;
}

std::vector<node*> Enemy::DikestraAlgorithm(node* start, node* end) {
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
