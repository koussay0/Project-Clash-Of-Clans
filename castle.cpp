#include "castle.h"
#include "enemy.h"
#include"game.h"
#include <QGraphicsScene>
#include"game.h"
#include"citizens.h"


extern Game *g;
Castle::Castle() {

    health=30;
    costToPass=2;

    name = "Castle";

 }


void Castle::DecreaseHealth(int d){
    health-=d;
    qDebug()<<"castle health decreased";
    if(health==0){
        Die();
    }
}

void Castle::Die(){

    g->gameOver();



}
