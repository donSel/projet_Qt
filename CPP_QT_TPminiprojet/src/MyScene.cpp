#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include <QMessageBox>
#include <string>
#include <QApplication>


#include "MyScene.h"
#include "WindowTwo.h"


using namespace std;

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {

    // Set timer
    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    this->timer->start(30); //toutes les 30 millisecondes
    // Connect update function
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // Display Score
    displayScore = new QGraphicsTextItem(); // display score above the player
    displayScore->setDefaultTextColor(Qt::red);
    this->addItem(displayScore);

    // Display begining message
    displayInfo = new QGraphicsTextItem(); // display score in direct
    displayInfo->setDefaultTextColor(Qt::cyan);
    this->addItem(displayInfo);
    string infoString = "Welcome To the Gulag, to be free go to the green platform. \nTherefore use the arrow keys to move.\nTo Restart Press \'R\' key !\nTo Quit Press the \'Q\' key. ";
    QString info = QString::fromStdString(infoString);
    displayInfo->setPlainText(info);
    displayInfo->setPos(-50, -170);


            // Creating the Obstacles Vector
        // creating obstacles elements
    // Moving Platforms
    // Platform
    this->obstacles.push_back(createFinishPlatform(1200, 0, 50, 20));
    this->obstacles.push_back(createMovingPlatform(50, 0));
    this->obstacles.push_back(createPlatform(300, 0));
    this->obstacles.push_back(createPlatform(10, 0));
    this->obstacles.push_back(createPlatform(-70, -70, 100, 20));
    this->obstacles.push_back(createPlatform(600, 0, 150, 20));
    this->obstacles.push_back(createPlatform(650, -60, 150, 20));
    this->obstacles.push_back(createPlatform(1000, -60, 70, 20));
    this->obstacles.push_back(createMovingPlatform(680, -60));
    // Walls
    this->obstacles.push_back(createWall(50, -40));
    this->obstacles.push_back(createWall(200, -40));
    this->obstacles.push_back(createWall(450, 0));
    this->obstacles.push_back(createWall(500, 0));
    this->obstacles.push_back(createWall(550, 0));
    this->obstacles.push_back(createWall(700, -100));
    this->obstacles.push_back(createWall(1120, -20));
    this->obstacles.push_back(createWall(1120, -20));
    this->obstacles.push_back(createWall(1120, -20));

    // pushing obstacles to Vector
    int nbObstacles = this->obstacles.size();
    // Adding them to the Scene
    for (int i = 0; i < nbObstacles; i++) {
        QGraphicsRectItem* obstacle = this->obstacles[i];
        this->addItem(obstacle);
    }

    // Set Player
    this->player = new Player();
    this->addItem(player->getQgti());

    // Set Hitboxes of the player
    this->addItem(player->getLeftHitbox());
    this->addItem(player->getRightHitbox());
    this->addItem(player->getDownHitbox());
    this->addItem(player->getUpHitbox());

    // Debug Start Position
    this->player->getQgti()->setPos(START_X, START_Y); // function set initPos
}


void MyScene::update() {
    QPointF pos = player->getQgti()->pos();

    // Update score value
    scoreInMs += 30;
    scoreInMsTwo = (scoreInMs / 2);
    // Display player Value
    string scoreInMsString = to_string(scoreInMsTwo);
    string timeTextString = timeText + scoreInMsString + timeTextTwo;
    QString timeString = QString::fromStdString(timeTextString);
    displayScore->setPlainText(timeString);
    displayScore->setPos(pos.rx() - 40, pos.ry() - 100);

    // Center player View
    persoViews.append(this->views());
    persoViews[0]->centerOn(this->player->getQgti());

    // Gravité => check if the player is not on a plateform to implement gravity
    if (!player->getOnPlatform()){
        QPointF pos = player->getQgti()->pos(); //récupération de la position de l’objet getQgti()
        player->getQgti()->setPos(pos.rx(), pos.ry() + GRAVITY); //incrémentation de la coordonnée y
    }

    // Colosions
    colisions();

    // Déplacements
    player->move();

    // Moving platforms
    movePlatform1();
    movePlatform2();

    // SetPos player if he falls
    playerFalls();

    // Checking if the player finished the level
    playerFinished();
}


void MyScene::playerFalls(){ // runs when player die, restarting game
    QPointF pos = player->getQgti()->pos();
    if (pos.ry() > 300){
        QMessageBox msgBox; // Mesage box
        msgBox.setText("Wasted !");
        msgBox.exec();
        // Reseting the Movement bools
        player->setLeftMove(false);
        player->setRightMove(false);
        player->setUpMove(false);
        player->setDownMove(false);
        player->getQgti()->setPos(START_X, START_Y);
        scoreInMs = 0;
    }
}


void MyScene::playerFinished(){ // runs when player win, open a End window
    if (player->getDownHitbox()->collidesWithItem(obstacles[0])){
        QMessageBox msgBox; // Mesage box
        msgBox.setText("You win !");
        msgBox.exec();
        // Reseting the Movement bools
        player->setLeftMove(false);
        player->setRightMove(false);
        player->setUpMove(false);
        player->setDownMove(false);
        // teleporting the player to the start
        player->getQgti()->setPos(START_X, START_Y);

        // Display Ending Image
        timer->stop(); // mise en pause
        WindowTwo* window = new WindowTwo(nullptr, scoreInMs / 2);
        window->timer = this->timer; // passing the Scene Timer to the WindowTwo Class
        window->show();
        scoreInMs = 0;
    }
}


void MyScene::colisions(){ // Managmement of the colisions
    // Colision with the upper part of a platform
    if (isObstacleHitboxColision(player->getDownHitbox())){ // liste de mur colide with item
        QPointF pos = player->getQgti()->pos();
        player->getQgti()->setPos(pos.rx(), pos.ry());
        player->setOnPlatform(true);
    }
    else {
        player->setOnPlatform(false);
    }

    // Colision with the lower part of a platform
    if (isObstacleHitboxColision(player->getUpHitbox())){ // liste de mur colide with item
        QPointF pos = player->getQgti()->pos();
        player->getQgti()->setPos(pos.rx(), pos.ry() + 20);
    }

    // Left colision with a wall or platform
    if (isObstacleHitboxColision(player->getLeftHitbox())){
        QPointF pos = player->getQgti()->pos();
        player->getQgti()->setPos(pos.rx() + XMOVE, pos.ry());
    }

    // Right colision with a wall or platform
    if (isObstacleHitboxColision(player->getRightHitbox())){
        QPointF pos = player->getQgti()->pos();
        player->getQgti()->setPos(pos.rx() - XMOVE, pos.ry());
    }
}


bool MyScene::isObstacleHitboxColision(QGraphicsLineItem* hitBox){ // return true if the player hit an obstacle
    int nbObstacles = this->obstacles.size();
    // Adding them to the Scene
    for (int i = 0; i < nbObstacles; i++) {
        if (hitBox->collidesWithItem(obstacles[i])){
            return true;
        }
    }
    return false;
}


void MyScene::movePlatform1() { // move the first plateform
    QPointF pos = obstacles[1]->pos();
    if (obstacles[1]->collidesWithItem(obstacles[2])) {
        speedPlateforme = -1;
    }
    if (obstacles[1]->collidesWithItem(obstacles[3])) {
        speedPlateforme = 1;
    }
    obstacles[1]->setPos(pos.rx()  + speedPlateforme, pos.ry());
}


void MyScene::movePlatform2() { // move the first plateform
    QPointF pos = obstacles[8]->pos();
    if (obstacles[8]->collidesWithItem(obstacles[7])) {
        speedPlateformeTwo = -1;
    }
    if (obstacles[8]->collidesWithItem(obstacles[6])) {
        speedPlateformeTwo = 1;
    }
    obstacles[8]->setPos(pos.rx()  + speedPlateformeTwo, pos.ry());
}


void MyScene::reverseCharacter() { // function to reverse the player image
    this->player->setPixmap(this->player->pixmap().transformed(QTransform().scale(-1,1)));
}


void MyScene::keyPressEvent(QKeyEvent* event){

    if (event->key() == Qt::Key_Up){ // activer si et seulement si le personnage est en contact avec une plateforme sous lui
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
        if (!player->getTurnedLeft()){ // turning the player image
            player->setTurnedLeft(true);
            player->setTurnedRight(false);
            reverseCharacter();
        }
    }
    if (event->key() == Qt::Key_Right){
        player->setRightMove(true);
        if (!player->getTurnedRight()){ // turning the player image
            player->setTurnedRight(true);
            player->setTurnedLeft(false);
            reverseCharacter();
        }
    }
    if (event->key() == Qt::Key_R){ // restart game if R pressed
        player->getQgti()->setPos(START_X, START_Y);
        scoreInMs = 0;
    }
    if (event->key() == Qt::Key_Q){ // close game if Q key pressed
        // Message Box Confirm UserName entered
        QMessageBox msgBox; // Mesage box
        msgBox.setText("Bye !");
        msgBox.exec();
        QCoreApplication::quit();
    }
}


void MyScene::keyReleaseEvent(QKeyEvent *event) {

    if (event->key() == Qt::Key_Up){ // management releasement of the key
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


// Creating obstacles
QGraphicsRectItem* MyScene::createFinishPlatform(int x, int y, int w, int h){
    QGraphicsRectItem* createdFinish = new QGraphicsRectItem(x, y, w, h);
    createdFinish->setBrush(Qt::green); // setting color
    return createdFinish;
}

// funcitonSetPlatform that create platforms/walls/ and adding them to To Vect obstacle
QGraphicsRectItem* MyScene::createPlatform(int x, int y, int w, int h){
    QGraphicsRectItem* createdPlatform =  new QGraphicsRectItem(x, y, w, h);
    createdPlatform->setBrush(Qt::gray); // setting color
    return createdPlatform;
}


QGraphicsRectItem* MyScene::createMovingPlatform(int x, int y, int w, int h){
    QGraphicsRectItem* createdPlatform =  new QGraphicsRectItem(x, y, w, h);
    createdPlatform->setBrush(Qt::gray); // setting color
    return createdPlatform;
}


QGraphicsRectItem* MyScene::createWall(int x, int y, int w, int h){
    QGraphicsRectItem* createdWall =  new QGraphicsRectItem(x, y, w, h);
    createdWall->setBrush(Qt::darkGray); // setting color
    return createdWall;
}

// Destructor
MyScene::~MyScene() {
    delete this->timer;
}
