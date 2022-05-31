#include "MyScene.h"

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

using namespace std;

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {

    // set Background
//    this->background.load("../img/background.png");
//    this->setSceneRect(0, 0, background.width(), background.height());

    // Set timer
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(30); //toutes les 30 millisecondes

    // Connect update function
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // Set Platforms
    this->qgri = new QGraphicsRectItem(10, 0, 100, 100);
    qgri->setBrush(Qt::gray); // setting color
    this->addItem(qgri);

    this->platform1 = new QGraphicsRectItem(-70, -70, 100, 20);
    platform1->setBrush(Qt::gray); // setting color
    this->addItem(platform1);

    // Set moving platform
    this->platform2 = new QGraphicsRectItem(50, 0, 50, 10);
    platform2->setBrush(Qt::gray); // setting color
    // setting image => unsuccessfull
//    QImage* img = new QImage("grass_bloc.jpg");
//    platform2->setTextureImage(&img);
    this->addItem(platform2);

    // Set Finish
    this->finish = new QGraphicsRectItem(300, 0, 50, 20);
    finish->setBrush(Qt::green); // setting color
    this->addItem(finish);

    // Set Walls
    this->wall = new QGraphicsRectItem(50, -40, 10, 40);
    wall->setBrush(Qt::darkGray); // setting color
    this->addItem(wall);

    // Set Player
//    this->qgti = new QGraphicsRectItem(START_X, START_Y, 10, 10);
    this->qgti = new QGraphicsPixmapItem(QPixmap("../img/Hero-idle-big.gif").scaled(30,40));
    qgti->setOffset(0, -40);
    this->addItem(qgti);

    // Set Hitbox
    this->leftHitBox = new QGraphicsLineItem(5, -1, 5, -10, qgti);
    leftHitBox->setOpacity(0);
    this->addItem(leftHitBox);
    this->RightHitBox = new QGraphicsLineItem(25, -1, 25, -10, qgti);
    RightHitBox->setOpacity(0);
    this->addItem(RightHitBox);
    this->DownHitBox = new QGraphicsLineItem(10, 0, 20, 0, qgti);
    DownHitBox->setOpacity(0);
    this->addItem(DownHitBox);
    this->UpHitBox = new QGraphicsLineItem(10, -15, 20, -15, qgti);
    UpHitBox->setOpacity(0);
    this->addItem(UpHitBox);

    // Debug Start Position
    QPointF pos = qgti->pos();
    this->qgti->setPos(START_X, START_Y);
}

// QrectPixmaItem
// tableau vect class brick update si il tape pas une brique colidWith

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
//    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MyScene::update() {
    // Gravité => (vérifier si le personnage est bien en contact avec une plateforme)
    if (!getOnPlatform()){
        QPointF pos = qgti->pos(); //récupération de la position de l’objet qgti
        qgti->setPos(pos.rx(), pos.ry() + GRAVITY); //incrémentation de la coordonnée y
    }
//    cout << "is on platform : " << getOnPlatform() << endl;
//    cout << "count Deaths : " << countDeaths << endl;

    // Colosions
    colisions();

    // Déplacements
    move();

    // Moving platforms
    movePlatforms();

    // SetPos player if he falls
    playerFalls();

    // Checking if the player finished the level
    playerFinished();
}


void MyScene::playerFalls(){
    QPointF pos = qgti->pos();
//    cout << pos.ry() << endl;
    if (pos.ry() > 300){
        QMessageBox msgBox; // Mesage box
        msgBox.setText("Vous êtes mort !");
        msgBox.exec();
        qgti->setPos(START_X, START_Y);
        countDeaths++;
    }
}


void MyScene::playerFinished(){
    if (DownHitBox->collidesWithItem(finish)){
        QMessageBox msgBox; // Mesage box
        msgBox.setText("Vous avez terminé !");
        msgBox.exec();
        QPointF pos = qgti->pos();
        qgti->setPos(START_X, START_Y);
    }
}


void MyScene::colisions(){

    // Colision with the upper part of a platform
    if (DownHitBox->collidesWithItem(qgri) || DownHitBox->collidesWithItem(platform2) || DownHitBox->collidesWithItem(wall) || DownHitBox->collidesWithItem(platform1) || DownHitBox->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = qgti->pos();
//        cout << "Collision basse !" << endl;
        qgti->setPos(pos.rx(), pos.ry());
        setOnPlatform(true);
    }
    else {
        setOnPlatform(false);
    }

    // Colision with the lower part of a platform
    if (UpHitBox->collidesWithItem(qgri) || UpHitBox->collidesWithItem(platform2) || UpHitBox->collidesWithItem(wall) || UpHitBox->collidesWithItem(platform1) || UpHitBox->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = qgti->pos();
//        cout << "Collision haute !" << endl;
        qgti->setPos(pos.rx(), pos.ry() + 40);
    }

    // Left colision with a wall or platform
    if (leftHitBox->collidesWithItem(qgri) || leftHitBox->collidesWithItem(platform2) || leftHitBox->collidesWithItem(wall) || leftHitBox->collidesWithItem(platform1) || leftHitBox->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = qgti->pos();
//        cout << "Collision gauche !" << endl;
        qgti->setPos(pos.rx() + XMOVE, pos.ry());
    }

    // Right colision with a wall or platform
    if (RightHitBox->collidesWithItem(qgri) || RightHitBox->collidesWithItem(platform2) || RightHitBox->collidesWithItem(wall) || RightHitBox->collidesWithItem(platform1) || RightHitBox->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = qgti->pos();
//        cout << "Collision droite !" << endl;
        qgti->setPos(pos.rx() - XMOVE, pos.ry());
    }
}


void MyScene::move(){

    if (getLeftMove()){
        QPointF pos = qgti->pos();
        qgti->setPos(pos.rx() - XMOVE, pos.ry());
    }

    if (getRightMove()){
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


void MyScene::movePlatforms(){
    QPointF pos = platform2->pos();
    if (platform2->collidesWithItem(finish)){
        speedPlateforme = -1;
    }
    if (platform2->collidesWithItem(qgri)){
        speedPlateforme = 1;
//        cout << "collision avec la première palteforme ! " << endl;
    }
    platform2->setPos(pos.rx() + speedPlateforme, pos.ry());

//    platform2->setPos(pos.rx() + 1, pos.ry());
//    if (pos.rx() < 300){
//        platform2->setPos(pos.rx() + 1, pos.ry());
//    }
//    if (pos.rx() > ){
//        platform2->setPos(pos.rx() - 1, pos.ry());
//    }
//    if (pos.rx() < 300){
//        platform2->setPos(pos.rx() + 1, pos.ry());
}


void MyScene::keyPressEvent(QKeyEvent* event){

    if (event->key() == Qt::Key_Up){ // activer si et suelement si le personnage est en contact avec une plateforme sous lui
//        cout << "is Gamer on platform : " << getOnPlatform() << endl;
        if (getOnPlatform()){
            setUpMove(true);
        }
        else {
            setUpMove(false);
        }
    }

    if (event->key() == Qt::Key_Down){
        setDownMove(true);
    }
    if (event->key() == Qt::Key_Left){
        setLeftMove(true);
    }
    if (event->key() == Qt::Key_Right){
        setRightMove(true);
    }
}


bool MyScene::isGamerOnPlatform(){ //detect if collision between platform and DownHitBox
    if (DownHitBox->collidesWithItem(qgri) || DownHitBox->collidesWithItem(platform2) || DownHitBox->collidesWithItem(wall) || DownHitBox->collidesWithItem(platform1) || DownHitBox->collidesWithItem(finish)){
        return true;
    }
    return false;
}


void MyScene::keyReleaseEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Up){ // relachement sur la touche haut du clavier
        setUpMove(false);
    }

    if (event->key() == Qt::Key_Down){
        setDownMove(false);
    }

    if (event->key() == Qt::Key_Left){
        setLeftMove(false);
    }
    if (event->key() == Qt::Key_Right){
        setRightMove(false);
    }
}


void MyScene::setLeftMove(bool val){
    leftMove = val;
}


void MyScene::setRightMove(bool val){
    rightMove = val;
}


void MyScene::setUpMove(bool val){
    downMove = val;
}


void MyScene::setDownMove(bool val){
    upMove = val;
}

void MyScene::setOnPlatform(bool val){
    onPlatform = val;
}


bool MyScene::getLeftMove(){
    return leftMove;
}


bool MyScene::getRightMove(){
    return rightMove;
}


bool MyScene::getUpMove(){
    return downMove;
}


bool MyScene::getDownMove(){
    return upMove;
}


bool MyScene::getOnPlatform(){
    return onPlatform;
}


MyScene::~MyScene() {
    delete this->timer;
//    for(PlaneItem* planeItem : this->planeItems){
//        delete planeItem;
//    }
}
