#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

//класс для рисования

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

class Battlefield : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit Battlefield(QObject *parent = 0);
    ~Battlefield();

private:
    QPointF     previousPoint;      // Координаты предыдущей точки


//private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};
#endif // BATTLEFIELD_H
