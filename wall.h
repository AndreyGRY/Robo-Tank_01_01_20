#ifndef WALL_H
#define WALL_H

//класс описания стен, цели и т.д.

#include <QWidget>
//#include <QTimer>
//#include <QResizeEvent>
#include <QPainter>
#include <QLabel>
//#include "battlefield.h"
//#include "paint.h"
//#include "ui_paint.h"

class Paint;
class Tank;

class Wall : public QWidget
{
    Q_OBJECT
public:
    /*explicit*/     Wall() {};

    Wall(int r_number, int x, int y, int r_status, QLabel &r_label, QPixmap &r_pixmap)
    {
            number = r_number;
            x_wposition = x;
            y_wposition = y;
            status = r_status;                                  //степень повреждений
            w_label = &r_label;
             w_pixmap = &r_pixmap;
    };
    friend class Paint;

    //void DrawWall(int n_X, int n_Y);
    void AddWall(int _number,               //внесение новой стены
                 int _x, int _y,
                 int _status,
                  QLabel &_label,
                 QPixmap &_pixmap);

    void SetStatus(int status);
    int GetStatus();
    void Repaint();

    void SetLabel(QLabel &label);
    void SetCoordinates(int x, int y);
    void SetPixmap(QPixmap &pixmap);
    void SetNumber(int number);
    int GetNumber(void);
    void Struck();

private:

    QLabel *w_label;
    QPixmap *w_pixmap;
    int x_wposition, y_wposition, number, status;
    QPixmap wall_destroyed;
    QPixmap wall;
    QPixmap target;
    QPixmap ground;
    Paint *paint;
};

#endif // WALL_H
