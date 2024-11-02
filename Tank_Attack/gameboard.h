// gameboard.h
#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QGraphicsScene>
#include <QVector>
#include "tank.h"

class GameBoard : public QGraphicsScene
{
    Q_OBJECT
public:
    GameBoard(QObject *parent = nullptr);
    void initializeGame();
    void handleTankMovement(Tank* tank, QPoint destination);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QVector<Tank*> player1Tanks;
    QVector<Tank*> player2Tanks;
    bool isPlayer1Turn;
    Tank* selectedTank;

    void generateRandomObstacles();
    bool isValidPosition(QPoint pos);

public slots:
    void shootBullet(Tank* shooter, QPointF target);
};

#endif
