#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "gameboard.h"
#include "tank.h"
#include "bullet.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crear la vista y la escena
    QGraphicsView view;
    GameBoard *scene = new GameBoard();

    // Configurar la vista
    view.setScene(scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setRenderHint(QPainter::SmoothPixmapTransform);
    view.setFixedSize(800, 600); // Tamaño de la ventana
    view.setWindowTitle("Tank Attack!");

    // Mostrar la vista
    view.show();

    // Iniciar el bucle de eventos de la aplicación
    return app.exec();
}
