//
// Created by micka on 31/05/2022.
//
#ifndef CPP_QT_TPMINIPROJET_PLAYER_H
#define CPP_QT_TPMINIPROJET_PLAYER_H


#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QPainter>
#include <QRectF>
#include <QKeyEvent>
#include <QGraphicsLineItem>


// Global Variables
#define GRAVITY  10
#define JUMP 15
#define XMOVE 2
#define START_X 10
#define START_Y -10


class Player : public QGraphicsPixmapItem {

private:
    // Player
    QGraphicsPixmapItem* qgti;
    // PLayer Hit boxes
    QGraphicsLineItem* leftHitBox;
    QGraphicsLineItem* RightHitBox;
    QGraphicsLineItem* UpHitBox;
    QGraphicsLineItem* DownHitBox;

    // other values
    bool leftMove = false;
    bool rightMove = false;
    bool downMove = false;
    bool onPlatform = false;
    bool upMove = false;

public:
    // constructeur
    Player();

    // Player Controls
    void move();

    // Mutateurs
    void setLeftMove(bool val);
    void setRightMove(bool val);
    void setUpMove(bool val);
    void setDownMove(bool val);
    void setOnPlatform(bool val);

    // Asceceurs
    bool getLeftMove() const;
    bool getRightMove() const;
    bool getUpMove() const;
    bool getDownMove() const;// => not used
    bool getOnPlatform() const;
    // Player
    QGraphicsPixmapItem* getQgti();
    QGraphicsLineItem* getLeftHitbox();
    QGraphicsLineItem* getRightHitbox();
    QGraphicsLineItem* getUpHitbox();
    QGraphicsLineItem* getDownHitbox();
};

#endif //CPP_QT_TPMINIPROJET_PLAYER_H
