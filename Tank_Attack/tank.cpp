// tank.cpp
#include "tank.h"
#include <QRandomGenerator>
#include <QtWidgets/QGraphicsScene> // For QGraphicsScene
#include <QtCore/QTimer> // For QTimer
#include <queue>


Tank::Tank(TankColor color, QGraphicsItem *parent)
    : QGraphicsItem(parent), tankColor(color), health(100)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
}

QRectF Tank::boundingRect() const
{
    return QRectF(-20, -20, 40, 40); // Tamaño del tanque
}

void Tank::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Color según el tipo de tanque
    QColor color;
    switch(tankColor) {
    case BLUE: color = Qt::blue; break;
    case LIGHT_BLUE: color = Qt::cyan; break;
    case RED: color = Qt::red; break;
    case YELLOW: color = Qt::yellow; break;
    }

    painter->setBrush(color);
    painter->drawRect(-20, -20, 40, 40);

    // Dibujar barra de vida
    painter->setBrush(Qt::green);
    painter->drawRect(-20, -30, (health * 40) / 100, 5);
}

void Tank::moveToPosition(QPoint destination)
{
    // Determinar el tipo de movimiento según el color y probabilidades
    int random = QRandomGenerator::global()->bounded(100);

    if (tankColor == BLUE || tankColor == LIGHT_BLUE) {
        // 50% BFS, 50% Random
        if (random < 50) {
            currentPath = calculateBFS(QPoint(pos().x(), pos().y()), destination);
        } else {
            currentPath = calculateRandomPath(QPoint(pos().x(), pos().y()), destination);
        }
    } else {
        // 80% Dijkstra, 20% Random para tanques rojos y amarillos
        if (random < 80) {
            currentPath = calculateDijkstra(QPoint(pos().x(), pos().y()), destination);
        } else {
            currentPath = calculateRandomPath(QPoint(pos().x(), pos().y()), destination);
        }
    }

    showPathVisually();
}

void Tank::takeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
    update();
}


QVector<QPoint> Tank::calculateBFS(QPoint start, QPoint end)
{
    QVector<QPoint> path;
    QQueue<QPoint> queue;
    QMap<QPoint, QPoint> cameFrom; // Para rastrear el camino
    QSet<QPoint> visited;

    queue.enqueue(start);
    visited.insert(start);

    while (!queue.isEmpty()) {
        QPoint current = queue.dequeue();

        // Si alcanzamos el destino, reconstruimos el camino
        if (current == end) {
            QPoint step = end;
            while (step != start) {
                path.prepend(step);
                step = cameFrom[step];
            }
            path.prepend(start);
            return path; // Retorna el camino encontrado
        }

        // Explorar vecinos
        for (const QPoint& neighbor : getNeighbors(current)) {
            if (!visited.contains(neighbor) && isValidMove(neighbor)) {
                queue.enqueue(neighbor);
                visited.insert(neighbor);
                cameFrom[neighbor] = current; // Guardamos de dónde venimos
            }
        }
    }

    return path; // Si no se encontró camino, retorna vacío
}

QVector<QPoint> Tank::getNeighbors(QPoint point)
{
    QVector<QPoint> neighbors;
    // Agregar los 4 vecinos (arriba, abajo, izquierda, derecha)
    neighbors.append(QPoint(point.x(), point.y() - 1)); // Arriba
    neighbors.append(QPoint(point.x(), point.y() + 1)); // Abajo
    neighbors.append(QPoint(point.x() - 1, point.y())); // Izquierda
    neighbors.append(QPoint(point.x() + 1, point.y())); // Derecha
    return neighbors;
}

QVector<QPoint> Tank::calculateDijkstra(QPoint start, QPoint end)
{
    QMap<QPoint, int> distances; // Distancias desde el inicio
    QMap<QPoint, QPoint> cameFrom; // Para rastrear el camino
    QSet<QPoint> visited;
    std::priority_queue // Cola de prioridad

    distances[start] = 0;
    queue.enqueue(start);

    while (!queue.isEmpty()) {
        QPoint current = queue.dequeue();

        // Si alcanzamos el destino, reconstruimos el camino
        if (current == end) {
            QVector<QPoint> path;
            QPoint step = end;
            while (step != start) {
                path.prepend(step);
                step = cameFrom[step];
            }
            path.prepend(start);
            return path; // Retorna el camino encontrado
        }

        visited.insert(current);

        // Explorar vecinos
        for (const QPoint& neighbor : getNeighbors(current)) {
            if (!visited.contains(neighbor) && isValidMove(neighbor)) {
                int newDistance = distances[current] + 1; // Suponiendo costo de 1 por movimiento
                if (!distances.contains(neighbor) || newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    cameFrom[neighbor] = current;
                    queue.enqueue(neighbor);
                }
            }
        }
    }

    return QVector<QPoint>(); // Si no se encontró camino, retorna vacío
}

QVector<QPoint> Tank::
