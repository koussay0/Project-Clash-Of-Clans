#include <QApplication>
#include <iostream>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QBrush>
#include<QFile>
#include<QTextStream>
#include<QGraphicsPixmapItem>
#include "enemy.h"
#include <QTimer>
#include "game.h"
#include <QFont>
#include"bullet.h"
#include"mainwindow.h"
#include<QMessageBox>
#include "empty.h"
#include "wonlevel.h"
#include "lostwindow.h"
#include "citizens.h"
#include <QMediaPlayer>
#include<QAudioOutput>
#include "wongame.h"
#include "healthmarker.h"
extern MainWindow *w;
extern QString Map;
extern int Volume;
extern QString CastlePath;
extern QString BackgroundPath;
Game::Game(int h)

{
    gameover=false;

    hardness=h;
    qDebug()<<hardness;
    enemydestroyed=0;
    extradamage=0;
    powerup=0;
    Q = new QMediaPlayer;
    Q ->setSource(QUrl("qrc:/new/Sound/Sound/FinalBackgroundMusic.mp3"));

    QAudioOutput *audio = new QAudioOutput;
    Q->setAudioOutput(audio);
    audio->setVolume(Volume);

    Q->play();
    Iterator=0;
    view= new QGraphicsView;
    view->setWindowTitle("Game Project");
    scene=new QGraphicsScene;
    scene->setSceneRect(0,0,1125,750);

    view->setFixedSize(1125,750);
    view->setBackgroundBrush(QBrush(QImage(BackgroundPath)));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    QFile file(Map);
    file.open(QIODevice::ReadOnly);
   std::vector<std::vector<int>>boarddata;
    int rows=0;
    int cols=0;
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        QString row = stream.readLine();
        QStringList numbers = row.split(' ');
        std::vector<int> temp;
        for (const QString& number : numbers) {
            temp.push_back(number.toInt());
            }
            boarddata.push_back(temp);
            rows++;
            cols = temp.size();
    }
    file.close();
    qDebug()<<rows<<cols;
    graphimages.resize(rows);
    for(int i = 0; i < rows; i++)
    {
            graphimages[i].resize(cols);
    }




    QPixmap castlephoto (CastlePath);
    castlephoto=castlephoto.scaledToWidth(75);
    castlephoto=castlephoto.scaledToHeight(75);
    castle = new Castle();
    castle->setPixmap(castlephoto);

    QGraphicsPixmapItem boardimages[rows][cols];
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(boarddata[i][j] == 0)
            {
                graphimages[i][j]=new empty();
                graphimages[i][j]->setPos(75*j,75*i);
                graphimages[i][j]->inner=false;
               scene->addItem(graphimages[i][j]);
            }
            else if(boarddata[i][j] == 7)
            {
                graphimages[i][j]=new empty();
                graphimages[i][j]->setPos(75*j,75*i);
                 graphimages[i][j]->inner=true;
                scene->addItem(graphimages[i][j]);
            }
            else if(boarddata[i][j] == 1)
            {
                graphimages[i][j]=castle;
                graphimages[i][j]->setPos(75*j,75*i);
                scene->addItem(graphimages[i][j]);
                castle->castleRow=i;
                castle->castleColumn=j;
            }
            else if (boarddata[i][j] == 2)
            {
                graphimages[i][j]= new Defense();
                graphimages[i][j]->setPos(75*j,75*i);
                cannonx=75*j;
                cannony=75*i;
                scene->addItem(graphimages[i][j]);
            }
            else
            {
                graphimages[i][j]= new Fence();
                graphimages[i][j]->setPos(75*j,75*i);
                scene->addItem(graphimages[i][j]);
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            graphimages[i][j]->rowAndColOfElement =  std::to_string(i) + ", " + std::to_string(j) ;
        }
    }

    view->viewport()->installEventFilter(this);
  nodes = ConstructNodesforTheGraph(graphimages);

    printConnections();
Enemytimer = new QTimer();
QObject::connect(Enemytimer,SIGNAL(timeout()),this,SLOT(createEnemy()));
Enemytimer->start((9-hardness)*1000+3000);
CitizenTimer = new QTimer();
QObject::connect(  CitizenTimer,SIGNAL(timeout()),this,SLOT(createCitizens()));
CitizenTimer->start(1);
MarkerTimer = new QTimer();
QObject::connect(MarkerTimer,SIGNAL(timeout()),this,SLOT(createMarkers()));
MarkerTimer->start(50000);
wintimer = new QTimer(this);

// Set a single-shot timer for 5 minutes
wintimer->setSingleShot(true);
wintimer->start(5 * 60 * 1000);
Update= new QTimer();
QObject::connect(Update,SIGNAL(timeout()),this,SLOT(UpdateNeighbours()));
Update->start(2000);
// Connect a slot to the timer
connect(wintimer, &QTimer::timeout, this, [=]()
        {
             Enemytimer->stop();
            CitizenTimer->stop();
            scene->clear();
            view->hide();
            if(hardness==5)
            {
                wongame* gamewon=new wongame;
                gamewon->show();
            }
            else{
            WonLevel* newlevel= new WonLevel;
                newlevel->show();}
        });
}

void Game::createEnemy()
{
    if(!gameover){
    Enemy* e= new Enemy(hardness+1);
    scene->addItem(e);
    qDebug()<<"create enemy called";
    }
}
void Game::createCitizens()
{
    if(Iterator<5)
    {Citizens* c = new Citizens;
        c->setPos((castle->castleColumn*75-60)+rand()%100,(castle->castleRow*75-60)+rand()%100);
    scene->addItem(c);}
    Iterator++;
}

void Game::createMarkers()
{
    if(!gameover){
    HealthMarker* h= new HealthMarker;
        scene->addItem(h);}
}
void Game::mousePressEvent(QMouseEvent *event)
{
    if(!gameover){
increasedamageevery20=0;
    for(int i=0;i<powerup;i++)
    {
         increasedamageevery20+= 10*(6-hardness)*0.1;
    }
    bullet* B = new bullet(event->pos().x(), event->pos().y(),extradamage+increasedamageevery20+10*(6-hardness));
    B->setPos(cannonx+75/2,cannony+75/2);
    scene->addItem(B);
    }
}

bool Game::eventFilter(QObject *obj, QEvent *event)
{
    if(!gameover){
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            mousePressEvent(mouseEvent);
            return true; // Event handled
        }
    }
    return QObject::eventFilter(obj, event);
    }
}

void Game::gameOver()
{


    gameover=true;
   qDebug()<<" game over";
    scene->clear();
    LostWindow* l=new LostWindow;
    view->hide();
    l->show();
   delete this;
}
void Game::printNodes() const {
    // Iterate over each row of nodes
    for (const auto& row : nodes) {
        // Iterate over each node in the row
        for (const auto& node_ptr : row) {
            // Print the coordinates of the node
            qDebug() << "Node: (" << node_ptr->imgelemnt->x() << ", " << node_ptr->imgelemnt->y() << ")";
        }
    }
}
void Game::printConnections() const {
    // Iterate over each row of nodes
    for (const auto& row : nodes) {
        // Iterate over each node in the row
        for (const auto& node_ptr : row) {
            // Print connections of the current node
            qDebug()<<node_ptr->imgelemnt->name << "Connections of Node (" << node_ptr->imgelemnt->y()/75 << ", " << node_ptr->imgelemnt->x()/75 << "):";

            // Iterate over each connection of the current node
            for (const auto& connection : node_ptr->Neighbours) {
                // Print the coordinates of the connected node
                qDebug() << "  Connected Node: (" << connection.second.first->imgelemnt->y()/75 << ", " << connection.second.first->imgelemnt->x()/75 << ")"<<"cost:"<<connection.second.second;
            }
        }
    }
}
Game::~Game()
{
    Q->stop();
    delete Q;
    Update->stop();
    wintimer->stop();
    Enemytimer->stop();
    CitizenTimer->stop();
    for(int i=0;i<nodes.size();i++)
    {
        for(int j=0;j<nodes[i].size();j++)
        {
            delete nodes[i][j];
        }
    }

}

void Game::UpdateNeighbours()
{
    if(!gameover){
    int rows = graphimages.size();
    int cols = graphimages[0].size();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j > 0) nodes[i][j]->addneighbour(nodes[i][j-1]); // left neighbour
            if (j < cols - 1) nodes[i][j]->addneighbour(nodes[i][j+1]); // right neighbour
            if (i > 0) nodes[i][j]->addneighbour(nodes[i-1][j]); // upper neighbour
            if (i < rows - 1) nodes[i][j]->addneighbour(nodes[i+1][j]); // Down neighbour


            if (i < rows - 1 && j > 0)
                nodes[i][j]->addneighbour(nodes[i+1][j-1]); // bottom left neighbour
            if (i < rows - 1 && j < cols - 1)
                nodes[i][j]->addneighbour(nodes[i+1][j+1]); // bottom right neighbour
            if (i > 0 && j > 0)
                nodes[i][j]->addneighbour(nodes[i-1][j-1]); // top left neighbour
            if (i > 0 && j < cols - 1)
                nodes[i][j]->addneighbour(nodes[i-1][j+1]); // top right neighbour

        }
    }
    }
}

std::vector<std::vector<node *> > Game::ConstructNodesforTheGraph(std::vector<std::vector<ImageElement *> > &UniqueNodes)
{
    int rows = UniqueNodes.size();
    int cols = UniqueNodes[0].size();

    std::vector<std::vector<node*>> nodes(rows, std::vector<node*>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            nodes[i][j] = new node(UniqueNodes[i][j]);
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j > 0) nodes[i][j]->addneighbour(nodes[i][j-1]); // left neighbour
            if (j < cols - 1) nodes[i][j]->addneighbour(nodes[i][j+1]); // right neighbour
            if (i > 0) nodes[i][j]->addneighbour(nodes[i-1][j]); // upper neighbour
            if (i < rows - 1) nodes[i][j]->addneighbour(nodes[i+1][j]); // Down neighbour


            if (i < rows - 1 && j > 0)
                nodes[i][j]->addneighbour(nodes[i+1][j-1]); // bottom left neighbour
            if (i < rows - 1 && j < cols - 1)
                nodes[i][j]->addneighbour(nodes[i+1][j+1]); // bottom right neighbour
            if (i > 0 && j > 0)
                nodes[i][j]->addneighbour(nodes[i-1][j-1]); // top left neighbour
            if (i > 0 && j < cols - 1)
                nodes[i][j]->addneighbour(nodes[i-1][j+1]); // top right neighbour

        }
    }

    return nodes;
}


void Game::showview()
{

    view->show();
}

void Game::boostshootpower()
{
    if(!gameover){
    qDebug()<<"bonus damage started";
    extradamage+=30;
    boostdamagetimer = new QTimer(this);

    // Set a single-shot timer
    boostdamagetimer->setSingleShot(true);
     boostdamagetimer->start(1 * 30* 1000);

    // Connect a slot to the timeout() signal of the timer
    connect( boostdamagetimer, &QTimer::timeout, this, [=]()
            {
         extradamage-=30;
         QMediaPlayer*Z= new QMediaPlayer;
         Z ->setSource(QUrl("qrc:/new/Sound/Sound/HealthMarkersDeactivation.mp3"));

         QAudioOutput *audio2 = new QAudioOutput;
         Z->setAudioOutput(audio2);
         audio2->setVolume(Volume);
         Q->stop();
         Z->play();
         Q->play();

         qDebug()<<"bonus damage stopped";
            });
    }
}

Castle *Game::getCastle()
{
    return castle;
}


