// gameboard.cpp
#include "gameboard.h"
#include "bullet.h"
#include <QGraphicsSceneMouseEvent>
#include <QtCore/QTimer>

GameBoard::GameBoard(QObject *parent)
    : QGraphicsScene(parent), isPlayer1Turn(true), selectedTank(nullptr)
{
    setSceneRect(0, 0, 800, 600); // Tamaño del tablero
    initializeGame();
}

void GameBoard::initializeGame()
{
    // Crear tanques para el jugador 1
    for (int i = 0; i < 2; i++) {
        Tank* blueTank = new Tank(Tank::BLUE);
        Tank* redTank = new Tank(Tank::RED);
        player1Tanks.append(blueTank);
        player1Tanks.append(redTank);
        addItem(blueTank);
        addItem(redTank);
    }

    // Crear tanques para el jugador 2
    for (int i = 0; i < 2; i++) {
        Tank* lightBlueTank = new Tank(Tank::LIGHT_BLUE);
        Tank* yellowTank = new Tank(Tank::YELLOW);
        player2Tanks.append(lightBlueTank);
        player2Tanks.append(yellowTank);
        addItem(lightBlueTank);
        addItem(yellowTank);
    }

    generateRandomObstacles();
}

void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPoint clickPos = event->scenePos().toPoint();

    if (event->button() == Qt::LeftButton) {
        // Seleccionar tanque o mover el tanque seleccionado
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        Tank* tank = dynamic_cast<Tank*>(item);

        if (tank) {
            selectedTank = tank;
        }else if (selectedTank) {
            handleTankMovement(selectedTank, clickPos);
            selectedTank = nullptr;
            isPlayer1Turn = !isPlayer1Turn; // Cambiar turno
        }
    }
}

void GameBoard::handleTankMovement(Tank* tank, QPoint destination)
{
    if (isValidPosition(destination)) {
        tank->moveToPosition(destination);
    }
}

// (implementación del método shootBullet)
void GameBoard::shootBullet(Tank* shooter, QPointF target)
{
    Bullet* bullet = new Bullet(shooter->pos(), target);
    bullet->setDamage(shooter->getTankType() == Tank::BLUE || shooter->getTankType() == Tank::LIGHT_BLUE ? 25 : 50); // Daño según el tipo de tanque
    addItem(bullet);

    // Conectar un timer para mover la bala
    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, [=]() {
        bullet->move();
    });
    timer->start(50); // Mover la bala cada 50 ms
}
