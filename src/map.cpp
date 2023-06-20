#include "map.h"

Map::Map()
{
}

Map::Map(int type,QPoint pos):pos(pos)
{
    if (type==0) {
        imagePath=":/images/grass.png";
        this->type=FREE;
    }
    else if (type==1) {
        imagePath=":/images/wall.png";
        this->type=BOUNDARY;
    }
    else if (type==2) {
        imagePath=":/images/box.png";
        this->type=BOX;
    }
    else if(type==3) {
        imagePath=":/images/final.png";
        this->type=FINAL;
    }
}

void Map::drawMap(QPainter* painter) {
    painter->save();
    painter->drawPixmap(pos.x(),pos.y(),75,75,QPixmap(imagePath));
    painter->restore();
}

TYPE Map::getType() {
    return type;
}

void Map::setType(TYPE type) {
    if (type==0) {
        imagePath=":/images/grass.png";
        this->type=FREE;
    }
    else if (type==1) {
        imagePath=":/images/wall.png";
        this->type=BOUNDARY;
    }
    else if (type==2) {
        imagePath=":/images/box.png";
        this->type=BOX;
    }
    else if(type==3) {
        imagePath=":/images/final.png";
        this->type=FINAL;
    }
}
