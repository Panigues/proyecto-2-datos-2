// bullet.cpp
#include "bullet.h"
#include "tank.h"
#include <QLineF>
#include <QDebug>
#include <QGraphicsScene>

Bullet::Bullet(QPointF startPosition, QPointF targetPosition, QObject *parent)
    : QObject(parent), currentPosition(startPosition), targetPosition(targetPosition), damage(0), speed(10)
{
    // Calcular la dirección de la bala
    QLineF line(currentPosition, targetPosition);
    direction = line.p2() - line.p1();
    direction /= line.length(); // Normalizar la dirección
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-5, -5, 10, 10); // Tamaño de la bala
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::black);
    painter->drawEllipse(boundingRect());
}

void Bullet::move()
{
    // Mover la bala en la dirección calculada
    currentPosition += direction * speed;

    // Verificar colisiones
    checkCollision();

    setPos(currentPosition);
}

void Bullet::checkCollision()
{
    // Aquí se puede implementar la lógica de colisión con tanques u obstáculos
    // Si la bala colisiona con un tanque, se debe aplicar daño
    // Ejemplo de lógica de colisión:
    QList<QGraphicsItem*> collidingItems = scene()->collidingItems(this);
    for (QGraphicsItem* item : collidingItems) {
        Tank* tank = dynamic_cast<Tank*>(item);
        if (tank) {
            // Aplicar daño a la tanque
            tank->takeDamage(damage);
            // Eliminar la bala después de impactar
            scene()->removeItem(this);
            delete this;
            return;
        }
    }
}
