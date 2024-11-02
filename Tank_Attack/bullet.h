// bullet.h
#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPoint>

class Bullet : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Bullet(QPointF startPosition, QPointF targetPosition, QObject *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void move();
    void setDamage(int damage) { this->damage = damage; }
    int getDamage() const { return damage; }

private:
    QPointF currentPosition;
    QPointF targetPosition;
    int damage;
    qreal speed; // Velocidad de la bala
    QPointF direction; // Dirección de la bala

    void checkCollision();
};

#endif
