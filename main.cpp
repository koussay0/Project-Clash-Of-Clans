#include "mainwindow.h"
#include"game.h"
#include <QApplication>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QBrush>
#include<QLabel>
#include<QFile>
#include<QTextStream>
#include<QGraphicsPixmapItem>//>
Game *g;
MainWindow *w;
int *hard;
QString Map;
int Volume;
QString land;
QString CastlePath;
QString fence;
QString BackgroundPath;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w= new MainWindow;
    QGraphicsView view;
Map=":/ClanMaps/Clan Maps/Map1.txt";
BackgroundPath=":/new/images/images/snowybackground.png";
Volume = 50;
CastlePath = ":/new/images/images/ICYTown_Hall.png";
land =":/new/images/images/snowemptyland.jpg";
fence=":/new/images/images/icefence.png";


    view.setWindowTitle("Game Project");
    QGraphicsScene scene;
    scene.setSceneRect(0,0,1200,1000);

    view.setFixedSize(1200,1000);
    view.setBackgroundBrush(QBrush(Qt::black));


    QGraphicsRectItem* rect = new QGraphicsRectItem();
    rect->setRect(0,0,1000,1200);
    scene.addItem(rect);
    view.setScene(&scene);



    w->show();
    return a.exec();
}
