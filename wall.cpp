#include "wall.h"



void Wall::AddWall(int r_number,
                   int x, int y,
                   int r_status,
                   QLabel &r_label,
                   QPixmap &r_pixmap)
{
    this->SetCoordinates(x, y);
    number = r_number;
    x_wposition = x;
    y_wposition = y;
    status = r_status;
    w_label = &r_label;
    w_label->setPixmap(r_pixmap);
    w_pixmap = &r_pixmap;
    w_label->repaint();
    w_label->show();
}

void Wall::SetNumber(int l_number)
{
    number = l_number;
}

int Wall::GetNumber( )
{
    return number;
}

void Wall::SetCoordinates(int x, int y)
{
    x_wposition = x;
    y_wposition = y;
}

void Wall::SetStatus(int l_status)
{
    status = l_status;
}

int Wall::GetStatus()
{
    return status;
}

void Wall::Repaint()
{

}

void Wall::SetLabel(QLabel &l_label)
{
    w_label = &l_label;
}

void Wall::SetPixmap(QPixmap &l_pixmap)
{
    w_pixmap = &l_pixmap;
    w_label->setPixmap(*w_pixmap);
    w_label->repaint();
}

void Wall::Struck(void)
{
    QPixmap wall_destroyed(":/images/wall_destroyed.png");
    QPixmap tank_destroyed(":/images/tank_destroyed.png");
    QPixmap wall(":/images/wall.png");
    QPixmap ground(":/images/ground.png");
    QPixmap target(":/images/target.png");

    if (status==2)
        w_label->setPixmap(wall_destroyed);
    else if (status==1)
        w_label->setPixmap(ground);
    status--;
    w_label->repaint();

    if (status==3 || number == 0) // target
    {
        status = 0;
        w_label->setPixmap(tank_destroyed);
        w_label->repaint();
    }
}
