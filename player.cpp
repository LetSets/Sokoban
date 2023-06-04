#include "player.h"

Player::Player()
{

}

Player::Player(QPoint pos):pos(pos)
{
    dir=Down;
    imagePath=":/images/down.png";
}

void Player::move(Direction dir) {
    switch(dir){
    case Up:
        pos.ry()-=75;
        break;
    case Down:
        pos.ry()+=75;
        break;
    case Right:
        pos.rx()+=75;
        break;
    case Left:
        pos.rx()-=75;
        break;
    }
}

void Player::drawPlayer(QPainter* painter) {
    painter->save();
    painter->drawPixmap(pos.x(),pos.y(),75,75,QPixmap(imagePath));
    painter->restore();
}

QPoint Player::getPos() {
    return pos;
}

Direction Player::getDir() {
    return dir;
}

void Player::setDir(Direction dir) {
    this->dir=dir;
    switch(dir){
    case Up:
        imagePath=":/images/up.png";
        break;
    case Down:
        imagePath=":/images/down.png";
        break;
    case Right:
        imagePath=":/images/right.png";
        break;
    case Left:
        imagePath=":/images/left.png";
        break;
    }
}
