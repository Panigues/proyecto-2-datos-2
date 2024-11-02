// tank.h
#ifndef TANK_H
#define TANK_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QVector>
#include <QPoint>

class Tank : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum TankColor { BLUE, LIGHT_BLUE, RED, YELLOW };
    enum MovementType { BFS, DIJKSTRA, RANDOM };

    Tank(TankColor color, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void moveToPosition(QPoint destination);
    void calculatePath(QPoint destination);
    int getHealth() const { return health; }
    void takeDamage(int damage);

private:
    TankColor tankColor;
    int health;
    QVector<QPoint> currentPath;

    // Algoritmos de pathfinding
    QVector<QPoint> calculateBFS(QPoint start, QPoint end);
    QVector<QPoint> calculateDijkstra(QPoint start, QPoint end);
    QVector<QPoint> calculateRandomPath(QPoint start, QPoint end);

    bool isValidMove(QPoint position);
    void showPathVisually();
};

#endif
