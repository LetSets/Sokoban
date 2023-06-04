#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow{parent}
{

}

GameWindow::GameWindow(QWidget *parent, int idx)
    : QMainWindow{parent}, game_idx(idx)
{
    for(int i=0;i<10;i++) {
        for(int j=0;j<16;j++) {
            gameMap[i][j]=new Map(MapList[game_idx-1][i][j],QPoint(j*75,i*75));
            if(MapList[game_idx-1][i][j]==3)
                finalCount++;
        }
    }
    player=new Player(playerPos[game_idx-1]);
    if(game_idx==4) {
        gameMap[7][7]->setType(BOX);
        finalCount--;
    }
    scoreLabel=new QLabel(this);
    scoreLabel->setStyleSheet("color:white");
    scoreLabel->setFont(QFont("JetBrains Mono",25));
    scoreLabel->setText(QString("当前成绩:%1").arg(step));
    scoreLabel->adjustSize();
    scoreLabel->move(50,700);
    recordLabel=new QLabel(this);
    recordLabel->setStyleSheet("color:white");
    recordLabel->setFont(QFont("JetBrains Mono",25));
    recordLabel->setText(QString("最好成绩:%1").arg(greatest_step[game_idx-1]));
    recordLabel->adjustSize();
    recordLabel->move(1000,700);
    manualBtn=new QPushButton("操作说明",this);
    manualBtn->setFont(QFont("JetBrains Mono",25));
    manualBtn->move(1025,0);
    manualBtn->resize(150,50);
    connect(manualBtn,&QPushButton::clicked,this,[=](){
        manualBox=new QMessageBox(this);
        manualBox->setText("WASD：控制人物上下左右移动\n\n"
                           "R：重新开始本关\n\n"
                           "Z：撤回到上一步\n\n"
                           "B/N：切换到上一关/下一关\n\n"
                           "Esc：回到开始界面");
        manualBox->setIconPixmap(QPixmap(":/images/manual.png"));
        manualBox->show();
    });
}

void GameWindow::startGame() {
    this->setFixedSize(1200,750);
    this->setGeometry(35,35,1200,750);
    this->setWindowTitle(QString("第%1关").arg(game_idx));
    this->show();
}

void GameWindow::drawGameMap(QPainter* painter) {
    for(int i=0;i<10;i++) {
        for(int j=0;j<16;j++)
            gameMap[i][j]->drawMap(painter);
    }
    player->drawPlayer(painter);
}

void GameWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawGameMap(&painter);
}

void GameWindow::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Up:
    case Qt::Key_W: {
        step++;
        QPoint currPos=player->getPos();
        TYPE ty=gameMap[currPos.y()/75-1][currPos.x()/75]->getType();
        if(ty==FREE || ty==FINAL) {
            moveStack.push_back({Up,player->getDir()});
            player->move(Up);
            player->setDir(Up);
            update();
        }
        else if(ty==BOX) {
            moveStack.push_back({Up,player->getDir()});
            TYPE tty=gameMap[currPos.y()/75-2][currPos.x()/75]->getType();
            if(tty==FREE) {
                player->move(Up);
                player->setDir(Up);
                gameMap[currPos.y()/75-2][currPos.x()/75]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75-1][currPos.x()/75]!=3)
                    gameMap[currPos.y()/75-1][currPos.x()/75]->setType(FREE);
                else {
                    gameMap[currPos.y()/75-1][currPos.x()/75]->setType(FINAL);
                    finalCount++;
                }
                update();
            }
            else if(tty==FINAL) {
                player->move(Up);
                player->setDir(Up);
                gameMap[currPos.y()/75-2][currPos.x()/75]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75-1][currPos.x()/75]!=3) {
                    gameMap[currPos.y()/75-1][currPos.x()/75]->setType(FREE);
                    finalCount--;
                }
                else
                    gameMap[currPos.y()/75-1][currPos.x()/75]->setType(FINAL);
                update();
            }
            else
                step--;
        }
        else
            step--;
        scoreLabel->setText(QString("当前成绩:%1").arg(step));
        scoreLabel->adjustSize();
        judgeWin();
        break;
    }
    case Qt::Key_Down:
    case Qt::Key_S: {
        step++;
        QPoint currPos=player->getPos();
        TYPE ty=gameMap[currPos.y()/75+1][currPos.x()/75]->getType();
        if(ty==FREE || ty==FINAL) {
            moveStack.push_back({Down,player->getDir()});
            player->move(Down);
            player->setDir(Down);
            update();
        }
        else if(ty==BOX) {
            moveStack.push_back({Down,player->getDir()});
            TYPE tty=gameMap[currPos.y()/75+2][currPos.x()/75]->getType();
            if(tty==FREE) {
                player->move(Down);
                player->setDir(Down);
                gameMap[currPos.y()/75+2][currPos.x()/75]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75+1][currPos.x()/75]!=3)
                    gameMap[currPos.y()/75+1][currPos.x()/75]->setType(FREE);
                else {
                    gameMap[currPos.y()/75+1][currPos.x()/75]->setType(FINAL);
                    finalCount++;
                }
                update();
            }
            else if(tty==FINAL) {
                player->move(Down);
                player->setDir(Down);
                gameMap[currPos.y()/75+2][currPos.x()/75]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75+1][currPos.x()/75]!=3) {
                    gameMap[currPos.y()/75+1][currPos.x()/75]->setType(FREE);
                    finalCount--;
                }
                else
                    gameMap[currPos.y()/75+1][currPos.x()/75]->setType(FINAL);
                update();
            }
            else
                step--;
        }
        else
            step--;
        scoreLabel->setText(QString("当前成绩:%1").arg(step));
        scoreLabel->adjustSize();
        judgeWin();
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D: {
        step++;
        QPoint currPos=player->getPos();
        TYPE ty=gameMap[currPos.y()/75][currPos.x()/75+1]->getType();
        if(ty==FREE || ty==FINAL) {
            moveStack.push_back({Right,player->getDir()});
            player->move(Right);
            player->setDir(Right);
            update();
        }
        else if(ty==BOX) {
            moveStack.push_back({Right,player->getDir()});
            TYPE tty=gameMap[currPos.y()/75][currPos.x()/75+2]->getType();
            if(tty==FREE) {
                player->move(Right);
                player->setDir(Right);
                gameMap[currPos.y()/75][currPos.x()/75+2]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75+1]!=3)
                    gameMap[currPos.y()/75][currPos.x()/75+1]->setType(FREE);
                else {
                    gameMap[currPos.y()/75][currPos.x()/75+1]->setType(FINAL);
                    finalCount++;
                }
                update();
            }
            else if(tty==FINAL) {
                player->move(Right);
                player->setDir(Right);
                gameMap[currPos.y()/75][currPos.x()/75+2]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75+1]!=3) {
                    gameMap[currPos.y()/75][currPos.x()/75+1]->setType(FREE);
                    finalCount--;
                }
                else
                    gameMap[currPos.y()/75][currPos.x()/75+1]->setType(FINAL);
                update();
            }
            else
                step--;
        }
        else
            step--;
        scoreLabel->setText(QString("当前成绩:%1").arg(step));
        scoreLabel->adjustSize();
        judgeWin();
        break;
    }
    case Qt::Key_Left:
    case Qt::Key_A: {
        step++;
        QPoint currPos=player->getPos();
        TYPE ty=gameMap[currPos.y()/75][currPos.x()/75-1]->getType();
        if(ty==FREE || ty==FINAL) {
            moveStack.push_back({Left,player->getDir()});
            player->move(Left);
            player->setDir(Left);
            update();
        }
        else if(ty==BOX) {
            moveStack.push_back({Left,player->getDir()});
            TYPE tty=gameMap[currPos.y()/75][currPos.x()/75-2]->getType();
            if(tty==FREE) {
                player->move(Left);
                player->setDir(Left);
                gameMap[currPos.y()/75][currPos.x()/75-2]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75-1]!=3)
                    gameMap[currPos.y()/75][currPos.x()/75-1]->setType(FREE);
                else {
                    gameMap[currPos.y()/75][currPos.x()/75-1]->setType(FINAL);
                    finalCount++;
                }
                update();
            }
            else if(tty==FINAL) {
                player->move(Left);
                player->setDir(Left);
                gameMap[currPos.y()/75][currPos.x()/75-2]->setType(BOX);
                if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75-1]!=3) {
                    gameMap[currPos.y()/75][currPos.x()/75-1]->setType(FREE);
                    finalCount--;
                }
                else
                    gameMap[currPos.y()/75][currPos.x()/75-1]->setType(FINAL);
                update();
            }
            else
                step--;
        }
        else
            step--;
        scoreLabel->setText(QString("当前成绩:%1").arg(step));
        scoreLabel->adjustSize();
        judgeWin();
        break;
    }
    case Qt::Key_R: {
        GameWindow* newGame=new GameWindow(this->parentWidget(),game_idx);
        setAttribute(Qt::WA_DeleteOnClose);
        newGame->startGame();
        delete this;
        break;
    }
    case Qt::Key_Z: {
        if(moveStack.size()==1) {
            GameWindow* newGame=new GameWindow(this->parentWidget(),game_idx);
            setAttribute(Qt::WA_DeleteOnClose);
            newGame->startGame();
            delete this;
            break;
        }
        else if(moveStack.size()>0) {
            QVector<Direction> last=moveStack.back();
            moveStack.pop_back();
            if(last[0]==Up) {
                QPoint currPos=player->getPos();
                TYPE ty=gameMap[currPos.y()/75-1][currPos.x()/75]->getType();
                if(ty==FREE || ty==FINAL || ty==BOUNDARY) {
                    player->move(Down);
                    player->setDir(last[1]);
                    update();
                }
                else {
                    player->move(Down);
                    player->setDir(last[1]);
                    gameMap[currPos.y()/75][currPos.x()/75]->setType(BOX);
                    if(MapList[game_idx-1][currPos.y()/75-1][currPos.x()/75]!=3) {
                        gameMap[currPos.y()/75-1][currPos.x()/75]->setType(FREE);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]==3)
                            finalCount--;
                    }
                    else {
                        gameMap[currPos.y()/75-1][currPos.x()/75]->setType(FINAL);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]!=3)
                            finalCount++;
                    }
                    update();
                }
            }
            else if(last[0]==Down) {
                QPoint currPos=player->getPos();
                TYPE ty=gameMap[currPos.y()/75+1][currPos.x()/75]->getType();
                if(ty==FREE || ty==FINAL || ty==BOUNDARY) {
                    player->move(Up);
                    player->setDir(last[1]);
                    update();
                }
                else {
                    player->move(Up);
                    player->setDir(last[1]);
                    gameMap[currPos.y()/75][currPos.x()/75]->setType(BOX);
                    if(MapList[game_idx-1][currPos.y()/75+1][currPos.x()/75]!=3) {
                        gameMap[currPos.y()/75+1][currPos.x()/75]->setType(FREE);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]==3)
                            finalCount--;
                    }
                    else {
                        gameMap[currPos.y()/75+1][currPos.x()/75]->setType(FINAL);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]!=3)
                            finalCount++;
                    }
                    update();
                }
            }
            else if(last[0]==Right) {
                QPoint currPos=player->getPos();
                TYPE ty=gameMap[currPos.y()/75][currPos.x()/75+1]->getType();
                if(ty==FREE || ty==FINAL || ty==BOUNDARY) {
                    player->move(Left);
                    player->setDir(last[1]);
                    update();
                }
                else {
                    player->move(Left);
                    player->setDir(last[1]);
                    gameMap[currPos.y()/75][currPos.x()/75]->setType(BOX);
                    if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75+1]!=3) {
                        gameMap[currPos.y()/75][currPos.x()/75+1]->setType(FREE);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]==3)
                            finalCount--;
                    }
                    else {
                        gameMap[currPos.y()/75][currPos.x()/75+1]->setType(FINAL);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]!=3)
                            finalCount++;
                    }
                    update();
                }
            }
            else {
                QPoint currPos=player->getPos();
                TYPE ty=gameMap[currPos.y()/75][currPos.x()/75-1]->getType();
                if(ty==FREE || ty==FINAL || ty==BOUNDARY) {
                    player->move(Right);
                    player->setDir(last[1]);
                    update();
                }
                else {
                    player->move(Right);
                    player->setDir(last[1]);
                    gameMap[currPos.y()/75][currPos.x()/75]->setType(BOX);
                    if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75-1]!=3) {
                        gameMap[currPos.y()/75][currPos.x()/75-1]->setType(FREE);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]==3)
                            finalCount--;
                    }
                    else {
                        gameMap[currPos.y()/75][currPos.x()/75-1]->setType(FINAL);
                        if(MapList[game_idx-1][currPos.y()/75][currPos.x()/75]!=3)
                            finalCount++;
                    }
                    update();
                }
            }
            step--;
        }
        scoreLabel->setText(QString("当前成绩:%1").arg(step));
        scoreLabel->adjustSize();
        break;
    }
    case Qt::Key_N: {
        if(game_idx<10)
            nextGame();
        break;
    }
    case Qt::Key_B: {
        if(game_idx>1) {
            GameWindow* newGame=new GameWindow(this->parentWidget(),game_idx-1);
            newGame->setAttribute(Qt::WA_DeleteOnClose);
            newGame->startGame();
            delete this;
        }
        break;
    }
    case Qt::Key_Escape: {
        this->parentWidget()->show();
        delete this;
        break;
    }
    }
}

void GameWindow::closeEvent(QCloseEvent* event) {
    QMessageBox* msgbox=new QMessageBox(this);
    msgbox->setIconPixmap(QPixmap(":/images/question.png"));
    msgbox->setText("确定要退出吗？\n");
    msgbox->addButton(QMessageBox::Yes);
    msgbox->addButton(QMessageBox::No);
    int ret=msgbox->exec();
    if(ret==QMessageBox::Yes){
        event->accept();
        exit(0);
    }
    else
        event->ignore();
}

void GameWindow::judgeWin() {
    if(finalCount==0) {
        if(!greatest_step[game_idx-1])
            greatest_step[game_idx-1]=step;
        else
            greatest_step[game_idx-1]=std::min(step,greatest_step[game_idx-1]);
        QMessageBox* msgbox=new QMessageBox(this);
        msgbox->setIconPixmap(QPixmap(":/images/win.png"));
        if(game_idx<10) {
            msgbox->setText("你赢了,是否进入下一关？\n");
            msgbox->addButton(QMessageBox::Yes);
            msgbox->addButton(QMessageBox::No);
        }
        else {
            msgbox->setText("恭喜你通过全部关卡，即将返回主界面\n");
            msgbox->addButton(QMessageBox::Yes);
        }
        int ret=msgbox->exec();
        if(ret==QMessageBox::No || game_idx==10){
            this->close();
            this->parentWidget()->show();
            delete this;
        }
        else
            nextGame();
    }
}

void GameWindow::nextGame() {
    GameWindow* newGame=new GameWindow(this->parentWidget(),game_idx+1);
    newGame->setAttribute(Qt::WA_DeleteOnClose);
    newGame->startGame();
    delete this;
}

GameWindow::~GameWindow() {
    for(int i=0;i<10;i++) {
        for(int j=0;j<16;j++)
            delete gameMap[i][j];
    }
    delete player;
}
