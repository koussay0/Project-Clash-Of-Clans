#include "healthmarker.h"

HealthMarker::HealthMarker() {
    QPixmap marker (":/new/images/images/health maker.png");
    marker=marker.scaledToWidth(30);
    marker=marker.scaledToHeight(30);
    setPixmap(marker);
    int random_number = rand() %1125;
    int random_number2= rand()%750;
    setPos(random_number,random_number2);
}
