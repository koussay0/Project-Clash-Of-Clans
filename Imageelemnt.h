#ifndef IMAGEELEMNT_H
#define IMAGEELEMNT_H
#include <QPixmap>
#include <QString>
#include <QGraphicsPixmapItem>

class ImageElement : public QGraphicsPixmapItem
{
public:
    std::string rowAndColOfElement;
    bool inner;
    QString name;
    int costToPass;
    ImageElement();
    ImageElement(const ImageElement& other); // copy constructor
    ~ImageElement();
};

#endif // IMAGEELEMNT_H
