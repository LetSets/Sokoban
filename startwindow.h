#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QFont>
#include <QMessageBox>
#include "gamewindow.h"

class StartWindow : public QMainWindow
{
    Q_OBJECT
private:
    QPushButton* enterBtn;
    QPushButton* exitBtn;
    QPushButton* manualBtn;
    QMessageBox* manualBox;
    GameWindow* currGame;
public:
    StartWindow(QWidget *parent = nullptr);
    void enterGame();
    void drawStartWindow(QPainter* painter);
    void paintEvent(QPaintEvent*);
    void closeEvent(QCloseEvent* event);
    ~StartWindow();
};
#endif // STARTWINDOW_H
