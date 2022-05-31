#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

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
//#define JUMP 2
#define XMOVE 2
#define START_X 10
#define START_Y -10


class MyScene : public QGraphicsScene {
    Q_OBJECT

private :
    // Gamer entities
    QTimer* timer;
    QGraphicsPixmapItem* qgti;
    QGraphicsRectItem* qgri;
    QGraphicsRectItem* platform1;
    QGraphicsRectItem* platform2;
    QGraphicsRectItem* wall;
    QGraphicsRectItem* finish;
    QGraphicsLineItem* leftHitBox;
    QGraphicsLineItem* RightHitBox;
    QGraphicsLineItem* UpHitBox;
    QGraphicsLineItem* DownHitBox;

    //bool pour collision
//    bool leftCollision = false;
//    bool leftCollision = false;
//    bool leftCollision = false;
//    bool leftCollision = false;

    // other values
    int countJump = 2;
    int speed;
    bool leftMove = false;
    bool rightMove = false;
    bool downMove = false;
    bool upMove = false;
    bool onPlatform = false;

    // PLateforme
    int speedPlateforme = 1;
    bool retourPlateforme = false;

public :
    MyScene(QObject* parent = nullptr);
    void drawBackground(QPainter* painter, const QRectF& rect);
    virtual ~MyScene();

    QPixmap background;
    int countDeaths = 0;

    // Mutateurs
    void setLeftMove(bool val);
    void setRightMove(bool val);
    void setUpMove(bool val);
    void setDownMove(bool val);
    void setOnPlatform(bool val);
    void setSpeed(int speed) { this->speed = speed; }

    void move();
    void colisions();
    void playerFalls();
    void playerFinished();

    void movePlatforms();

    // Asceceurs
    bool getLeftMove();
    bool getRightMove();
    bool getUpMove();
    bool getDownMove();

    bool getOnPlatform();

    int getSpeed() const { return speed; }

     bool isGamerOnPlatform();
    // fonction detect Colission plat/plat et joueur/plat sur les differents cotés de la hitbox
    // set Level => create Walls and platforms
    // faire un flag vert quand on le touche le player vois une fenetre qui souvre avec son temps et le meilleurs temp

    // [BONUS]
    // faire des sons quand le perso gagne/meurt/début de partie
    // faire en sorte que quand le personnage recule il se retourne
    // petit scénario => sauver la princesse

public slots :
    void update();

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
//    void keyReleaseEvent(QKeyEvent* event);
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H
