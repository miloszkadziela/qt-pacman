#include "mainwindow.h"
#include "ui_mainwindow.h"

Game *game;

void quitAction()
{
    qApp->quit();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(size());
    game = new Game();
    ui->stackedWidget->addWidget(game);
    connect
    (
        PlayerStats::Instance(),
        SIGNAL(gameState(int)),
        this,
        SLOT(changeGameState(int))
    );
    connect
    (
        PlayerStats::Instance(),
        SIGNAL(updateStats()),
        this,
        SLOT(updateUI())
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeGameState(int gameState)
{
    switch (gameState)
    {
        case MENU:
            ui->stackedWidget->setCurrentIndex(MENU);
        break;
        case GAME:
            game->initializeGame();
            ui->stackedWidget->setCurrentIndex(GAME);
        break;
        case GAMEOVER:
            game->hide();
            ui->stackedWidget->setCurrentIndex(GAMEOVER);
            ui->finalscore->setText("Score: " + QString::number(PlayerStats::Instance()->getScore()));
        break;
    }
}

void MainWindow::updateUI()
{
    ui->score->setText("Score: " + QString::number(PlayerStats::Instance()->getScore()));
    ui->lives->setText("Lives: " + QString::number(PlayerStats::Instance()->getLives()));
}

void MainWindow::on_playButton_clicked()
{
    PlayerStats::Instance()->gameState(GAME);
}

void MainWindow::on_quitButton_clicked()
{
    quitAction();
}

void MainWindow::on_quitButton_2_clicked()
{
    quitAction();
}
