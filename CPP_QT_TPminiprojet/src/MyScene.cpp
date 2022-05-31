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


#include "MyScene.h"


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
    this->player = new Player();

//    this->qgti = new QGraphicsRectItem(START_X, START_Y, 10, 10); OLD
    this->addItem(player->getQgti());

    // Set Hitbox
    this->addItem(player->getLeftHitbox());

    this->addItem(player->getRightHitbox());

    this->addItem(player->getDownHitbox());

    this->addItem(player->getUpHitbox());

    // Debug Start Position
    this->player->getQgti()->setPos(START_X, START_Y); // function set initPos
}


// Ascesseur
Player* MyScene::getPLayer(){
    return player;
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
    if (!player->getOnPlatform()){
        QPointF pos = player->getQgti()->pos(); //récupération de la position de l’objet getQgti()
        player->getQgti()->setPos(pos.rx(), pos.ry() + GRAVITY); //incrémentation de la coordonnée y
    }
//    cout << "is on platform : " << getOnPlatform() << endl;
//    cout << "count Deaths : " << countDeaths << endl;

    // Colosions
    colisions();

    // Déplacements
    player->move();

    // Moving platforms
    movePlatforms();

    // SetPos player if he falls
    playerFalls();

    // Checking if the player finished the level
    playerFinished();
}


void MyScene::playerFalls(){
    QPointF pos = player->getQgti()->pos();
//    cout << pos.ry() << endl;
    if (pos.ry() > 300){
        QMessageBox msgBox; // Mesage box
        msgBox.setText("Vous êtes mort !");
        msgBox.exec();
        // Reseting the Movement bools
        player->setLeftMove(false);
        player->setRightMove(false);
        player->setUpMove(false);
        player->setDownMove(false);
        player->getQgti()->setPos(START_X, START_Y);
        countDeaths++;
    }
}


void MyScene::playerFinished(){
    if (player->getDownHitbox()->collidesWithItem(finish)){
        QMessageBox msgBox; // Mesage box
        msgBox.setText("Vous avez terminé !");
        msgBox.exec();
        // Reseting the Movement bools
        player->setLeftMove(false);
        player->setRightMove(false);
        player->setUpMove(false);
        player->setDownMove(false);
        // teleporting the player to the start
        player->getQgti()->setPos(START_X, START_Y);
    }
}


void MyScene::colisions(){

    // Colision with the upper part of a platform
    if (player->getDownHitbox()->collidesWithItem(qgri) || player->getDownHitbox()->collidesWithItem(platform2) || player->getDownHitbox()->collidesWithItem(wall) || player->getDownHitbox()->collidesWithItem(platform1) || player->getDownHitbox()->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = player->getQgti()->pos();
//        cout << "Collision basse !" << endl;
        player->getQgti()->setPos(pos.rx(), pos.ry());
        player->setOnPlatform(true);
    }
    else {
        player->setOnPlatform(false);
    }

    // Colision with the lower part of a platform
    if (player->getUpHitbox()->collidesWithItem(qgri) || player->getUpHitbox()->collidesWithItem(platform2) || player->getUpHitbox()->collidesWithItem(wall) || player->getUpHitbox()->collidesWithItem(platform1) || player->getUpHitbox()->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = player->getQgti()->pos();
//        cout << "Collision haute !" << endl;
        player->getQgti()->setPos(pos.rx(), pos.ry() + 40);
    }

    // Left colision with a wall or platform
    if (player->getLeftHitbox()->collidesWithItem(qgri) || player->getLeftHitbox()->collidesWithItem(platform2) || player->getLeftHitbox()->collidesWithItem(wall) || player->getLeftHitbox()->collidesWithItem(platform1) || player->getLeftHitbox()->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = player->getQgti()->pos();
//        cout << "Collision gauche !" << endl;
        player->getQgti()->setPos(pos.rx() + XMOVE, pos.ry());
    }

    // Right colision with a wall or platform
    if (player->getRightHitbox()->collidesWithItem(qgri) || player->getRightHitbox()->collidesWithItem(platform2) || player->getRightHitbox()->collidesWithItem(wall) || player->getRightHitbox()->collidesWithItem(platform1) || player->getRightHitbox()->collidesWithItem(finish)) { // liste de mur colide with item
        QPointF pos = player->getQgti()->pos();
//        cout << "Collision droite !" << endl;
        player->getQgti()->setPos(pos.rx() - XMOVE, pos.ry());
    }
}


void MyScene::movePlatforms() {
    QPointF pos = platform2->pos();
    if (platform2->collidesWithItem(finish)) {
        speedPlateforme = -1;
    }
    if (platform2->collidesWithItem(qgri)) {
        speedPlateforme = 1;
//        cout << "collision avec la première palteforme ! " << endl;
    }
    platform2->setPos(pos.rx() + speedPlateforme, pos.ry());
}


bool MyScene::isGamerOnPlatform(){ //detect if collision between platform and getDownHitbox()
    if (player->getDownHitbox()->collidesWithItem(qgri) || player->getDownHitbox()->collidesWithItem(platform2) || player->getDownHitbox()->collidesWithItem(wall) || player->getDownHitbox()->collidesWithItem(platform1) || player->getDownHitbox()->collidesWithItem(finish)){
        return true;
    }
    return false;
}


void MyScene::keyPressEvent(QKeyEvent* event){

    if (event->key() == Qt::Key_Up){ // activer si et suelement si le personnage est en contact avec une plateforme sous lui
//        cout << "is Gamer on platform : " << getOnPlatform() << endl;
        if (player->getOnPlatform()){
            player->setUpMove(true);
        }
        else {
            player->setUpMove(false);
        }
    }

    if (event->key() == Qt::Key_Down){
        player->setDownMove(true);
    }
    if (event->key() == Qt::Key_Left){
        player->setLeftMove(true);
    }
    if (event->key() == Qt::Key_Right){
        player->setRightMove(true);
    }
}


void MyScene::keyReleaseEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Up){ // relachement sur la touche haut du clavier
        player->setUpMove(false);
    }

    if (event->key() == Qt::Key_Down){
        player->setDownMove(false);
    }

    if (event->key() == Qt::Key_Left){
        player->setLeftMove(false);
    }
    if (event->key() == Qt::Key_Right){
        player->setRightMove(false);
    }
}


MyScene::~MyScene() {
    delete this->timer;
//    for(PlaneItem* planeItem : this->planeItems){
//        delete planeItem;
//    }
}
