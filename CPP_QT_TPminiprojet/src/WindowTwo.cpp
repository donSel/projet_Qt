//
// Created by micka on 31/05/2022.
//

#include "WindowTwo.h"

#include <QProgressBar>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <string>
#include <QApplication>
#include <string>
#include <QList>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsTextItem>


#include "WindowTwo.h"

using namespace std;

WindowTwo::WindowTwo(QWidget* parent, int score) : QMainWindow(parent) {
    // Setting Player score
//    this->score = (score / 2);
    this->score = score;

    // Main Widget
    this->setWindowTitle("Game End");
    this->setMinimumWidth(500);
    QWidget* mainWidget = new QWidget();

    // Layout
    QVBoxLayout* mainLayout = new QVBoxLayout();

    // infoText
    string stringScore = to_string(score);
    string endString = " milliseconds.";
    string textString = "Enter your username, Your score : ";
    string infoString = textString + stringScore + endString;
    QString infoStringTwo = QString::fromStdString(infoString);
    this->infoTextLabel = new QLabel();
    infoTextLabel->setText(infoStringTwo);
    mainLayout->addWidget(infoTextLabel);

    // Text zone
    this->userNameLineEdit = new QLineEdit();
    userNameLineEdit->setText("");
    mainLayout->addWidget(userNameLineEdit);

    // button input UserName => writes in the file
    this->buttonUserName = new QPushButton("Confirm User Name / Enter your score in the score board");
    buttonUserName->setGeometry(10, 10, 80, 30);
    mainLayout->addWidget(buttonUserName);

    // View results Button => opens the result file
    this->viewResultsButton = new QPushButton("View Score Board");
    viewResultsButton->setGeometry(10, 10, 80, 30);
    mainLayout->addWidget(viewResultsButton);

    // Restart Button // start->time()
    this->restartButton = new QPushButton("Restart");
    restartButton->setGeometry(10, 10, 80, 30);
    mainLayout->addWidget(restartButton);

    // Quit Button
    this->quitButton = new QPushButton("Quit");
    quitButton->setGeometry(10, 10, 80, 30);
    mainLayout->addWidget(quitButton);

    // Connect
    connect(buttonUserName, SIGNAL(clicked()), this, SLOT(setUserName()));
    connect(viewResultsButton, SIGNAL(clicked()), this, SLOT(viewResults()));
    connect(restartButton, SIGNAL(clicked()), this, SLOT(setStartTime()));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitGame()));

    // Final
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
}


void WindowTwo::setUserName() { // Open a txt file and write in a txt file the userName of the PLayer with her score
    // Getting UserName
    QString userNameInput = userNameLineEdit->text();

    // Setting player Username
    QFile file("../score_board.csv");
    if (file.open(QFile::Append | QFile::ExistingOnly)) {
        QTextStream stream(&file);
        stream << score << "\t" << ":" << userNameInput << "\n"; // this writes first line with two columns
        file.close();
    }

    // Message Box Confirm UserName entered
    QMessageBox msgBox; // Mesage box
    msgBox.setText("Your Name and your score have been Succesfully added to the score board ! (check the score_board.csv file to see the board)");
    msgBox.exec();
}


void WindowTwo::viewResults(){
    // open the score board
    QMessageBox msgBox; // Mesage box
    msgBox.setText("check the score_board.csv file to see all the results (format : score (in ms):username");
    msgBox.exec();
}


void WindowTwo::setStartTime(){
    // close the window
    timer->start(30);
    this->close();
}


void WindowTwo::quitGame(){
    // stops the game
    QCoreApplication::quit();
}
