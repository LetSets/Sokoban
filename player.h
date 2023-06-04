#ifndef PLAYER_H
#define PLAYER_H
#include <QPainter>
#include <QPaintEvent>
#include <QPoint>
#include <QPixmap>
#include <QString>
enum Direction{Up,Down,Right,Left};

class Player
{
private:
    QPoint pos;
    Direction dir;
    QString imagePath;
public:
    Player();
    Player(QPoint pos);
    void drawPlayer(QPainter* painter);
    void move(Direction dir);
    QPoint getPos();
    void setDir(Direction dir);
    Direction getDir();
};

#endif // PLAYER_H
