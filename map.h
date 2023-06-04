#ifndef MAP_H
#define MAP_H

#include <QPoint>
#include <QPainter>
#include <QString>

enum TYPE{
    FREE,BOUNDARY,BOX,FINAL
};

class Map
{
private:
    TYPE type;
    QPoint pos;
    QString imagePath;
public:
    Map();
    Map(int type,QPoint pos);
    void drawMap(QPainter* painter);
    TYPE getType();
    void setType(TYPE type);
};

#endif // MAP_H
