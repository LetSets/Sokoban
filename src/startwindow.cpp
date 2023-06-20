#include "startwindow.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
{
    enterBtn=new QPushButton("开始游戏",this);
    enterBtn->setFont(QFont("JetBrains Mono",25));
    enterBtn->move(533,300);
    enterBtn->resize(150,50);
    connect(enterBtn,&QPushButton::clicked,this,[=](){
        this->hide();
        currGame=new GameWindow(this,1);
        currGame->setAttribute(Qt::WA_DeleteOnClose);
        currGame->startGame();
    });
    exitBtn=new QPushButton("退出游戏",this);
    exitBtn->setFont(QFont("JetBrains Mono",25));
    exitBtn->move(533,400);
    exitBtn->resize(150,50);
    connect(exitBtn,&QPushButton::clicked,this,&QWidget::close);
    manualBtn=new QPushButton("操作说明",this);
    manualBtn->setFont(QFont("JetBrains Mono",25));
    manualBtn->move(533,350);
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

void StartWindow::drawStartWindow(QPainter* painter) {
    painter->save();
    painter->drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/background.png"));
    painter->restore();
}

void StartWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    drawStartWindow(&painter);
}

void StartWindow::closeEvent(QCloseEvent* event) {
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

StartWindow::~StartWindow()
{

}

