#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "playerstats.h"
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_playButton_clicked();
    void on_quitButton_clicked();
    void on_quitButton_2_clicked();
    void updateUI();
    void changeGameState(int gameState);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
