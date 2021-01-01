#ifndef PAINT_H
#define PAINT_H

//класс логики игры

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QPainter>
#include <QLabel>
#include "battlefield.h"
#include "tank.h"
#include "wall.h"
#include <QDebug>

namespace Ui {
class Paint; class Tank; class Wall;
}

class Tank; class Wall;
class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();
    void DrawStart();//старт
    void DrawTank(int n_X, int n_Y, int rot);
    void DrawWall(int n_X, int n_Y);
    void BuildWall();// инициализация объектов
    void DrawTarget(int n_X, int n_Y);
    void SetWin(int w);
    void WinOrPerish(int isWin); // конец
    int FireImplementation(void);
    enum Mode {mode_target, mode_feast, mode_fight_terminator, mode_fight_human}; //режимы

    friend class Tank;
    friend class Wall;

private:
    /* Переопределяем событие изменения размера окна
     * для пересчёта размеров графической сцены
     * */
    void resizeEvent(QResizeEvent * event);
    QString command[9] = {"",  "", "", "", "", "", "", "", ""};
    char commands_array[1000] = ""; //очередь команд
    char alt_commands_array[1000] = ""; //очередь альтернативных команд
    int NumberOfCicles = 1;
    int NumberOfCommandsCicle = 0;
    int digit_array[50] = {0};
    int coords[9][2]={{570, 570}, {10, 10}, {130, 10}, {290, 10}, {450, 10}, {570, 10}, {410, 90}, {410, 210}, {250, 130} };
    int orients[9]={90, 270, 270, 270, 270, 270, 0, 0, 0 };
    Tank tanks[9];
    Wall walls_array[0xFF];                         //16-й для соотнесения номера с позицией
    int x_pos = 570, y_pos = 570, orient = 90;
    int win = 0;
    bool timerStopped=true;

    QPixmap p_tank_0;//пути к рисункам
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

    QPixmap ground;
    QPixmap shell;
    QPixmap tank_destroyed;
    QPixmap wall_destroyed;
    QPixmap wall;
    QPixmap target;

    int count_letters=0;
    int count_words=0;
    int X_RIGHT = 445, Y_DOWN = 390;
    Ui::Paint *ui;
    QLabel label;
    bool TARGET_STRUCK = false; //есть ли попадание
    bool BREAK_OUT = false; // выход из двойных циклов
    bool isCondition = FALSE;
    bool isCicle = FALSE;
    bool isTank = FALSE;
    bool isWall = FALSE;
    int fire_distance = 0; // расстояние стрельбы
    int Current_Tank_Turn=0;
    QPainter painter; //создание рисовальщика
    QBasicTimer Timer1;
    QTimer *timer, *timer2;      /* Определяем таймер для подготовки актуальных размеров
                         * графической сцены
                         * */
    Mode mode = mode_target;
    Battlefield *scene;  // Объявляем кастомную графическую сцену

private slots:
    void slotTimer();
    void on_ButtonForward_clicked();
    void on_ButtonBackward_clicked();
    void on_ButtonLeft_clicked();
    void on_ButtonRight_clicked();
    void on_ButtonFire_clicked();
    void on_Write_NumberSheets_copyAvailable(bool b);
    void on_AddCommand_clicked();
    void on_DeleteCommand_clicked();
    void on_ButtonStart_clicked();
    void on_ButtonStop_clicked();
    void on_Write_CommandList_textChanged();
    void on_Write_NumberSheets_textChanged();


    void on_Mode_Target_clicked();
    void on_Mode_Feast_clicked();
    void on_Mode_Fight_Terminator_clicked();
    void on_Mode_Fight_Human_clicked();
    void on_ButtonStartCondition_clicked();
    void on_ButtonFinishCondition_clicked();
    void on_ButtonStartCicle_clicked();
    void on_ButtonFinishCicle_clicked();
    void on_Write_NumberCicles_textChanged();

    void TargetMode(); //режим игры с уничтожением цели
    void FeastMode(void); //другие режимы не включены
    void FightTerminatorMode(void);
    void FightHumanMode(void);
    void on_ButtonConditionEnemyClose_clicked();
    void on_ButtonConditionWallClose_clicked();
};

#endif // PAINT_H
