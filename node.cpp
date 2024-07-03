#include "node.h"
#include "game.h"
extern Game* g;
node::node(ImageElement* _object) : imgelemnt(_object),rowAndColOfElement(_object->rowAndColOfElement)
{
}




void node::addneighbour(node* otherNode){
     if((imgelemnt->name=="fence"&&otherNode->imgelemnt->name=="emptyland")) {
        if(otherNode->imgelemnt->inner==true)
             Neighbours[otherNode->rowAndColOfElement] = std::make_pair(otherNode, otherNode->imgelemnt->costToPass);
         else
                 Neighbours[otherNode->rowAndColOfElement] = std::make_pair(otherNode, imgelemnt->costToPass);
     }
    else
    Neighbours[otherNode->rowAndColOfElement] = std::make_pair(otherNode, otherNode->imgelemnt->costToPass);

   // qDebug()<<otherNode->id<<otherNode->object->name<<"cost to pass:"<< otherNode->object->costToPass;
}




