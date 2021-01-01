#ifndef TANK_H
#define TANK_H

//класс описания танков

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QPainter>
#include <QLabel>
//#include "battlefield.h"
//#include "paint.h"
//#include "ui_paint.h"
#include "windows.h"

class Paint;
class Wall;
class Tank : public QWidget
{
    Q_OBJECT
public:
    /*explicit*/ Tank ( );

    Tank(int number,  //0 - игрок, 1-7 - враги, 8 - прокачанный враг, 9 - игрок 2
         QLabel &label,
         int x, int y, int l_orient, int t_status, //позиция, угол, статус
         QPixmap &pixmap,
         Wall (&r_walls)[0xFF] );                 //ссылка на объекты
//    {
//        this->SetNumber(number);
//        this->SetLabel(label);
//        this->SetCoordinates(x, y);
//        this->SetOrient(l_orient);
//        this->SetPixmap(pixmap);
        //walls[0] = &r_walls;
//    };

//    Tank(int number)
//    {
//        this->SetNumber(number);
//            };

//        ~Tank();

    friend class Paint;
    void ForwardImplementation(Paint &paint, Wall (&r_walls)[0xFF]); //отработка движения, поворота и огня
    void BackwardImplementation(Paint &paint, Wall (&r_walls)[0xFF]);
    void TurnLeftImplementation(Paint &paint, int l_orient);
    void TurnRightImplementation(Paint &paint, int r_orient);
    void FireImplementation(Paint &paint, Wall (&r_walls)[0xFF], Tank (&tanks)[9]);
    int CheckFireResult(int r_orient, Paint &paint, Wall (&r_walls)[0xFF], Tank (&tanks)[9], bool isFire);
    void CheckObjects(int i, int j, Paint &paint, Wall (&r_walls)[0xFF]);
    void FireShow(int r_orient);                                    //анимация стрельбы
    void SetLabel(QLabel &label); //установка картинок
    void SetFireLabels(QLabel &r_label_fire1_0, QLabel &r_label_fire2_0, QLabel &r_label_fire1_90, QLabel &r_label_fire2_90, QLabel &r_label_fire1_180, QLabel &r_label_fire2_180, QLabel &r_label_fire1_270, QLabel &r_label_fire2_270, QLabel &r_label_shell);

    QLabel GetLabel();

    void SetCoordinates(int x, int y);
    void GetCoordinates(Paint &paint);      //геттеры напрямую работают с переменными Paint
    void SetOrient(int l_orient);
    void GetOrient(Paint &paint);
    void SetPixmap(QPixmap &pixmap);
    void SetCommand(char command);
    char GetCommand();
    void SetNumber(int number);
    void Repaint();
    void SetStatus(int t_status);
    int GetNumber(void);      //геттеры не напрямую работают с переменными Paint
    int GetStatus(void);
    int GetX(void);
    int GetY(void);
    void Struck(Paint &paint);

private:

    QString order;
    char commands_list[50] = "";
    int digit_array[50] = {0};
    int x_position, y_position, azimuth, tank_number, tank_status = -1;


    QPixmap p_tank_0;
    QPixmap p_tank_90;
    QPixmap p_tank_180;
    QPixmap p_tank_270;
    QPixmap e_tank_0;
    QPixmap e_tank_90;
    QPixmap e_tank_180;
    QPixmap e_tank_270;

    QPixmap fire1_0;
    QPixmap fire1_90;
    QPixmap fire1_180;
    QPixmap fire1_270;
    QPixmap fire2_0;
    QPixmap fire2_90;
    QPixmap fire2_180;
    QPixmap fire2_270;
    QPixmap shell;
    QPixmap tank_destroyed;

    int count_letters=0;                    //очередь команд
    int count_words=0;
    int X_RIGHT = 445, Y_DOWN = 390;

    bool TARGET_STRUCK = false;
    bool BREAK_OUT = false;
    int fire_distance = 0;

    QLabel *label_panzer, *label_fire1_0, *label_fire2_0, *label_fire1_90, *label_fire2_90,
    *label_fire1_180, *label_fire2_180, *label_fire1_270, *label_fire2_270, *label_shell;
    Paint *paint;
    Wall *walls[0xFF];

};

#endif // TANK_H
