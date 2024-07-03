#ifndef NODE_H
#define NODE_H
#include<QGraphicsPixmapItem>
#include"Imageelemnt.h"
class node
{
public:
    node(ImageElement* _object);
    ImageElement* imgelemnt;
    std::string rowAndColOfElement;
    std::map<std::string, std::pair<node*, int>> Neighbours; // Store both the node and the weight
    void addneighbour(node* node1);


};

#endif // NODE_H
