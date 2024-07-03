#include "defense.h"
#include<QGraphicsSceneMouseEvent>
#include"game.h"
#include <cmath>
extern Game *g;

Defense::Defense() {
    costToPass=2000;
    name="cannon";
    QPixmap defencephoto (":/Defense Images/images/1.png");
    defencephoto=defencephoto.scaledToWidth(75);
    defencephoto=defencephoto.scaledToHeight(75);
    setPixmap(defencephoto);

    rotatingPictures.resize(12);


    for(int i = 0; i < 12; i++) {
        rotatingPictures[i].load(":/Defense Images/images/" + QString::number(i+1) + ".png");
    }


    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, [=](){
        CurserPoint = QCursor::pos();
        LoadPhotos();
    });
    timer->start(200);

}




double Defense::CalculateAngle() {
    // Calculate the angle between the object and the cursor position
    double deltaX = CurserPoint.x()-this->x() ;
    double deltaY = this->y()-CurserPoint.y();

    double angle = qAtan2(deltaY, deltaX) * 180 / M_PI;
    return angle;
}



void Defense::LoadPhotos() {
    double angle = CalculateAngle();

   // qDebug()<<angle;
    // Determine which picture to load based on the angle
    if (angle >= 0 && angle < 30) {

        setPixmap(rotatingPictures[7].scaled(75, 75));
    } else if (angle >= 30 && angle < 60) {

        setPixmap(rotatingPictures[6].scaled(75, 75));
    } else if (angle >= 60 && angle < 90) {

        setPixmap(rotatingPictures[5].scaled(75, 75));
    } else if (angle >= 90 && angle < 120) {

        setPixmap(rotatingPictures[4].scaled(75, 75));
    } else if (angle >= 120 && angle < 150) {

        setPixmap(rotatingPictures[3].scaled(75, 75));
    } else if (angle >= 150 && angle < 180) {

        setPixmap(rotatingPictures[2].scaled(75, 75));
    } else if (angle >= -180 && angle < -150) {

        setPixmap(rotatingPictures[1].scaled(75, 75));
    } else if (angle >= -150 && angle < -120) {

        setPixmap(rotatingPictures[0].scaled(75, 75));
    } else if (angle >= -120 && angle < -90) {

        setPixmap(rotatingPictures[11].scaled(75, 75));
    } else if (angle >= -90 && angle < -60) {

        setPixmap(rotatingPictures[10].scaled(75, 75));
    } else if (angle >= -60 && angle < -30) {

        setPixmap(rotatingPictures[9].scaled(75, 75));
    } else if (angle >= -30 && angle < 0) {

        setPixmap(rotatingPictures[8].scaled(75, 75));
    }
}
