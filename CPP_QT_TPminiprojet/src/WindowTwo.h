//
// Created by micka on 31/05/2022.
//

#ifndef CPP_QT_TPMINIPROJET_WINDOWTWO_H
#define CPP_QT_TPMINIPROJET_WINDOWTWO_H

#include <QProgressBar>
#include <QSlider>
#include <QObject>
#include <QLabel>
#include <QTimer>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QObject>
#include <QString>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <string>

class WindowTwo : public QMainWindow {
Q_OBJECT
public :
    QTimer* timer;
    // constructeur
    WindowTwo(QWidget* parent = nullptr, int score = 0);
    // destructor
//    virtual ~Window(){};
public slots :
    void setUserName();
    void viewResults();
    void setStartTime();
    void quitGame();
signals :
private :
    // Rajouter Qlabel qui montre le meilleur score
    // QlabelText for the user pseudo and informations about the score board
    QLabel* infoTextLabel;
    // Text zone
    QLineEdit* userNameLineEdit;
    // button input UserName
    QPushButton* buttonUserName;
    // View results Button
    QPushButton* viewResultsButton;
    // Restart Button
    QPushButton* restartButton;
    // Quit Button
    QPushButton* quitButton;
    // QtableView pour display score


    // Player Score
    int score = 0;

    // Scene timer
//    QTimer* timerSec;

    // Player UserName
    std::string userName = "";
};

#endif //CPP_QT_TPMINIPROJET_WINDOWTWO_H
