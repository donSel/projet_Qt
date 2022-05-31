//
// Created by micka on 31/05/2022.
//
#include <iostream>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include <QBrush>
#include <QImage>
#include <QMessageBox>

#include "Player.h"

using namespace std;

// constructeur
Player::Player(){
    qgti = new QGraphicsPixmapItem(QPixmap("../img/Hero-idle-big.gif").scaled(30,40));
    qgti->setOffset(0, -40);

    leftHitBox = new QGraphicsLineItem(5, -1, 5, -10, qgti);
    leftHitBox->setOpacity(0);

    RightHitBox = new QGraphicsLineItem(25, -1, 25, -10, qgti);
    RightHitBox->setOpacity(0);

    DownHitBox = new QGraphicsLineItem(10, 0, 20, 0, qgti);
    DownHitBox->setOpacity(0);

    UpHitBox = new QGraphicsLineItem(10, -15, 20, -15, qgti);
    UpHitBox->setOpacity(0);
}

// Player Controls
void Player::move(){

    if (getLeftMove()){
        cout << "Gauche !" << endl;
        QPointF pos = qgti->pos();
        qgti->setPos(pos.rx() - XMOVE, pos.ry());
    }

    if (getRightMove()){
        cout << "Droite !" << endl;
        QPointF pos = qgti->pos();
        qgti->setPos(pos.rx() + XMOVE, pos.ry());
    }

    if (getUpMove()){
        QPointF pos = qgti->pos();
        qgti->setPos(pos.rx(), pos.ry() - JUMP);
    }
    else {
        QPointF pos = qgti->pos();
        qgti->setPos(pos.rx(), pos.ry());
    }
}


// Mutateurs
void Player::setLeftMove(bool val){
    leftMove = val;
}


void Player::setRightMove(bool val){
    rightMove = val;
}


void Player::setUpMove(bool val){
    downMove = val;
}


void Player::setDownMove(bool val){
    upMove = val;
}

void Player::setOnPlatform(bool val){
    onPlatform = val;
}


// Asceceurs
bool Player::getLeftMove() const {
    return leftMove;
}


bool Player::getRightMove() const {
    return rightMove;
}


bool Player::getUpMove() const {
    return downMove;
}


bool Player::getDownMove() const {
    return upMove;
}


bool Player::getOnPlatform() const {
    return onPlatform;
}

// Player
QGraphicsPixmapItem* Player::getQgti(){
    return qgti;
}


QGraphicsLineItem* Player::getLeftHitbox(){
    return leftHitBox;
}


QGraphicsLineItem* Player::getRightHitbox(){
    return RightHitBox;
}


QGraphicsLineItem* Player::getUpHitbox(){
    return UpHitBox;
}


QGraphicsLineItem* Player::getDownHitbox(){
    return DownHitBox;
}




