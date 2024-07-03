#include "Imageelemnt.h"

ImageElement::ImageElement()
{
}


ImageElement::~ImageElement(){
}



ImageElement::ImageElement(const ImageElement& other) {
    setPos(other.pos());
    rowAndColOfElement = other.rowAndColOfElement;
    costToPass=other.costToPass;
    name = other.name;
    setPixmap(other.pixmap());
}
