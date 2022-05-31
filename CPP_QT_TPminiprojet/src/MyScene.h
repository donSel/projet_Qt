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
    QGraphicsRectItem* qgri;
    QGraphicsRectItem* platform1;
    QGraphicsRectItem* platform2;
    QGraphicsRectItem* wall;
    QGraphicsRectItem* finish;

    // other values
    int countDeaths = 0;
    int scoreInMs = 0;

    // PLateforme
    int speedPlateforme = 1;

    // Player View
//    QGraphicsView* playerView;
    QList<QGraphicsView*> persoViews;

public :
    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();

//    // Player Controls
    void colisions();
    void playerFalls();
    void playerFinished();
// Ascesseur
    Player* getPLayer();


    // Moving Platform
    void movePlatforms();
    bool isGamerOnPlatform();// => not used

    // NOTES
    // afficher le score pendant la partie au dessus du perso
    // funcitonSetPlatform that create plat/text/addToVect
    // fonction detect Colission plat/plat et joueur/plat sur les differents cotés de la hitbox
    // set Level => create Walls and platforms

    // [BONUS]
    // faire des sons quand le perso gagne/meurt/début de partie
    // faire en sorte que quand le personnage recule il se retourne
    // petit scénario => sauver la princesse
    // ajouter une princesse
    // gestion mémoire
    // afficher image de début et de fin du jeu

public slots :
    void update();

protected:
    void keyPressEvent(QKeyEvent* event); //=> laisser ici ?
    void keyReleaseEvent(QKeyEvent* event);
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
