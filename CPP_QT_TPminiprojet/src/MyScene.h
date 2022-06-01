#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H


#include <QGraphicsScene>
#include <QPixmap>
#include <QList>
#include <QTimer>
#include <QPainter>
#include <QRectF>
#include <QKeyEvent>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <string>


#include "Player.h"
#include "WindowTwo.h"


// Global Variables
#define GRAVITY  10
#define JUMP 15
#define XMOVE 2
#define START_X 10
#define START_Y -10


class MyScene : public QGraphicsScene {
    Q_OBJECT

private :
    // Gamer entities
    QTimer* timer;

    // Player
    Player* player;

    // Platforms
    QVector<QGraphicsRectItem*> obstacles;

    // time
    int scoreInMs = 0;
    int scoreInMsTwo = 0;
    std::string timeText = "SCORE : ";
    std::string timeTextTwo = " ms";
    QGraphicsTextItem* displayScore; // set in MyScene constructor and udpate value in update and set pos

    // PLateforme
    int speedPlateforme = 1;
    int speedPlateformeTwo = 1;

    // Player View
    QList<QGraphicsView*> persoViews;

    // other
    QGraphicsTextItem* displayInfo; // display infos

public :
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();

//    // Player Controls
    void colisions();
    void playerFalls();
    void playerFinished();
    void reverseCharacter();
    // fonction detect Colission plat/plat et joueur/plat sur les differents cotés de la hitbox

// Ascesseur
    const QVector<QGraphicsRectItem*>& getObstacles(){return obstacles;}

    // Creating obstacles
    // funcitonSetPlatform that create platforms/walls/ and adding them to To Vect obstacle
    QGraphicsRectItem* createFinishPlatform(int x, int y, int w = 100, int h = 100);
    QGraphicsRectItem* createPlatform(int x, int y, int w = 100, int h = 100);
    QGraphicsRectItem* createMovingPlatform(int x, int y, int w = 50, int h = 10);
    QGraphicsRectItem* createWall(int x, int y, int w = 10, int h = 40);

    // Moving Platform
    void movePlatform1();
    void movePlatform2();
    bool isObstacleHitboxColision(QGraphicsLineItem* hitBox); // function return true if colision between the hitbos of the player passe and an obstacle
    // fonction move platform qui prend coord ou deux elements bloquants et élément en question

    // NOTES
    // princesse
    // enemi
    // faire en sorte que quand le personnage recule il se retourne

    // [BONUS]
    // petit scénario => sauver la princesse
    // afficher image de début et de fin du jeu
    //  gestion mémoire

public slots :
    void update();

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
