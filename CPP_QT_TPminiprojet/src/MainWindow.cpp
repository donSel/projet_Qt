#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new MyScene;

    // main View
    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);
    this->setCentralWidget(mainView);
    this->setWindowTitle("My main window");
    this->resize(400, 800);

    // Player View
    playerView = new QGraphicsView();
    playerView->setScene(mainScene);
    playerView->setWindowTitle("playerView");
    playerView->resize(300, 300);
    playerView->show();

    this->centralWidget()->setStyleSheet("border-image:url('../img/nighttimeruins.png') 0 0 0 0 stretch stretch;"); //=> final en commentaire car fait beuguer le jeu

    helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction* actionHelp = new QAction(tr("&About"), this);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_aboutMenu()));
    helpMenu->addAction(actionHelp);
}

MainWindow::~MainWindow(){

}

void MainWindow::slot_aboutMenu(){ // => wtf is that
    QMessageBox msgBox;
    msgBox.setText("A small QT/C++ projet...");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}