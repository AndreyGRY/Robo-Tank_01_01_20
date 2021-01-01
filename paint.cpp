#include "paint.h"
#include "ui_paint.h"
#include "windows.h"
#include "QDebug"



Paint::Paint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Paint)
{
    ui->setupUi(this);

    scene = new Battlefield();       // Инициализируем графическую сцену
    ui->painting->setScene(scene);  // Устанавливаем графическую сцену
     ui->battlefield->setScene(scene);

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &Paint::slotTimer, Qt::DirectConnection);
    timer2 = new QTimer();       // Инициализируем таймер
    connect(timer2, &QTimer::timeout, this, &Paint::TargetMode, Qt::DirectConnection);
    timer->start(100);          // Запускаем таймер

    for (int i=0; i<600; i=i+40)
    {
        scene->addLine(-155, i-210, 445, i-210);
        scene->addLine(i-155, -210, i-155, 390);
    }
ui->label_win->hide();
ui->label_lose->hide();
ui->im_shell->hide();
ui->im_shell_2->hide();
ui->im_shell_3->hide();
ui->im_shell_4->hide();
ui->im_shell_5->hide();
ui->im_shell_6->hide();
ui->im_shell_7->hide();
ui->im_shell_8->hide();
ui->im_fire1_0->hide();
ui->im_fire2_0->hide();
ui->im_fire1_90->hide();
ui->im_fire2_90->hide();
ui->im_fire1_180->hide();
ui->im_fire2_180->hide();
ui->im_fire1_270->hide();
ui->im_fire2_270->hide();

ui->label_win->hide();
ui->label_lose->hide();
ui->label_etank_1->hide();
ui->label_etank_2->hide();
ui->label_etank_3->hide();
ui->label_etank_4->hide();
ui->label_etank_5->hide();
ui->label_etank_6->hide();
ui->label_etank_7->hide();
ui->label_smart_etank->hide();

ui->label_manual_target_mode->show();
ui->label_manual_feast_mode->hide();
ui->label_manual_terminator_mode->hide();
ui->label_manual_human_mode->hide();
ui->pic_manual_target_mode->show();
ui->pic_manual_feast_mode->hide();
ui->pic_manual_terminator_mode->hide();
ui->pic_manual_human_mode->hide();

BuildWall();
}

Paint::~Paint()
{
    delete ui;
}

void Paint::slotTimer()
{
    timerStopped = true;
    timer->stop();
    scene->setSceneRect(0,0, ui->painting->width() - 20, ui->painting->height() - 20);
}

void Paint::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void Paint::on_ButtonForward_clicked()
{
   command[0] = "Вперед, ";
}

void Paint::on_ButtonBackward_clicked()
{
    command[0] = "Назад, ";

}

void Paint::on_ButtonLeft_clicked()
{
    command[0] = "Влево ";

}

void Paint::on_ButtonRight_clicked()
{
    command[0] = "Вправо ";
}

void Paint::on_ButtonFire_clicked()
{
    command[0] = "Огонь ";
}

void Paint::on_Write_NumberSheets_copyAvailable(bool b)
{
}

void Paint::on_AddCommand_clicked() //запись команды в очередь
{
   int NumberOfCommandsCondition = 0;
        if (isCicle)             //если в цикле, считать команды в цикле
    {
        NumberOfCommandsCicle++;
        ui->Write_CommandList->insertPlainText("В цикле ");
    }
    if ( (!isCicle) && NumberOfCommandsCicle > 0)     //если , то -
    {
        for (int j=1; j<NumberOfCicles; j++)
        for (int i=1; i<=NumberOfCommandsCicle; i++)   //повторять столько, сколько команд в циклах
            {
            commands_array[count_words] = commands_array[count_words-NumberOfCommandsCicle];
            alt_commands_array[count_words] = alt_commands_array[count_words-NumberOfCommandsCicle];
            qDebug() << " цикл " << commands_array[count_words] << count_words;
            //digit_array[count_letters]='C';
            count_words++;
            count_letters++;
            }
    NumberOfCommandsCicle = 0;
    }
    if (isCondition) {                                                                                                   //По условию впереди
         if (isTank) {commands_array[count_words]='T'; ui->Write_CommandList->insertPlainText("если впереди танк - "); }   //танк
         if (isWall) {commands_array[count_words]='W'; ui->Write_CommandList->insertPlainText("если впереди стена - "); }   //стена
        if (command[0] == "Вперед, ") {alt_commands_array[count_words]='F'; digit_array[count_letters]=ui->Write_NumberSheets->toPlainText().toFloat();}        //работает альтернативный массив команд
       else if (command[0] == "Назад, ") {alt_commands_array[count_words]='B'; digit_array[count_letters]=ui->Write_NumberSheets->toPlainText().toFloat();}
       else if (command[0] == "Влево ") {alt_commands_array[count_words]='L'; digit_array[count_letters]=0;}
       else if (command[0] == "Вправо ") {alt_commands_array[count_words]='R'; digit_array[count_letters]=0;}
       else if (command[0] == "Огонь ") {alt_commands_array[count_words]='I'; digit_array[count_letters]=0;}
    NumberOfCommandsCondition++;
    }
    else
        if (command[0] == "Вперед, ") {commands_array[count_words]='F'; digit_array[count_letters]=ui->Write_NumberSheets->toPlainText().toFloat();}     //без условного режима работает основной массив
    else if (command[0] == "Назад, ") {commands_array[count_words]='B'; digit_array[count_letters]=ui->Write_NumberSheets->toPlainText().toFloat();}
    else if (command[0] == "Влево ") {commands_array[count_words]='L'; digit_array[count_letters]=0;}
    else if (command[0] == "Вправо ") {commands_array[count_words]='R'; digit_array[count_letters]=0;}
    else if (command[0] == "Огонь ") {commands_array[count_words]='I'; digit_array[count_letters]=0;}

    if (command[0] == "Вперед, "||"Назад, ") { ui->Write_CommandList->insertPlainText(command[0]+ui->Write_NumberSheets->toPlainText()+";\n");}
    else  ui->Write_CommandList->insertPlainText(command[0]+";\n");

    qDebug() << "added " << command << "word " << count_words << "digit " << count_letters;
    count_letters++;
    count_words++;
}

void Paint::on_DeleteCommand_clicked() //удаление
{
    ui->Write_CommandList->redo();
    commands_array[count_words] = 'z';
    count_words--;
count_letters = count_words;
}

void Paint::on_ButtonStart_clicked()
{
     DrawStart(); //старт
}

void Paint::on_ButtonStop_clicked () //остановка
{
    win = -1;
    WinOrPerish(win);

    ui->label_win->hide();
    ui->label_lose->hide();
}

void Paint::on_Write_NumberSheets_textChanged()
{
}

void Paint::on_Write_CommandList_textChanged()
{
}

void Paint::DrawStart()
{
    QPixmap p_tank_0(":/images/p_tank_0.png");
    QPixmap p_tank_90(":/images/p_tank_90.png");
    QPixmap p_tank_180(":/images/p_tank_180.png");
    QPixmap p_tank_270(":/images/p_tank_270.png");
    QPixmap e_tank_0(":/images/e_tank_0.png");
    QPixmap e_tank_90(":/images/e_tank_90.png");
    QPixmap e_tank_180(":/images/e_tank_180.png");
    QPixmap e_tank_270(":/images/e_tank_270.png");

    QPixmap fire1_0(":/images/fire1_0.png");
    QPixmap fire1_90(":/images/fire1_90.png");
    QPixmap fire1_180(":/images/fire1_180.png");
    QPixmap fire1_270(":/images/fire1_270.png");
    QPixmap fire2_0(":/images/fire2_0.png");
    QPixmap fire2_90(":/images/fire2_90.png");
    QPixmap fire2_180(":/images/fire2_180.png");
    QPixmap fire2_270(":/images/fire2_270.png");

    QPixmap ground(":/images/ground.png");
    QPixmap shell(":/images/shell.png");
    QPixmap tank_destroyed(":/images/tank_destroyed.png");
    QPixmap wall_destroyed(":/images/wall_destroyed.png");
    QPixmap wall(":/images/wall.png");
    QPixmap target(":/images/target.png");

    for (int i=0; i<600; i=i+40)
    {
        scene->addLine(-155, i-210, 445, i-210);
        scene->addLine(i-155, -210, i-155, 390);
    }
    switch (mode)
    {
    case mode_target:
    {
        for (int i=1; i<9; i++) tanks[i].SetStatus(1); //все враги отключены
        TargetMode(); break;}
    case mode_feast:
    {
        for (int i=1; i<8; i++) tanks[i].SetStatus(1);  //все враги кроме терминатора включены
        tanks[8].SetStatus(-1);
        FeastMode(); break;}
    case mode_fight_terminator:
    {
        for (int i=1; i<8; i++) tanks[i].SetStatus(-1);  //все враги кроме терминатора отключены
        tanks[8].SetStatus(1);
        FightTerminatorMode(); break;}
    case mode_fight_human:
    {
        for (int i=2; i<9; i++) tanks[i].SetStatus(-1);   //все враги кроме 1 отключены, 1 на ручном управлении
        tanks[1].SetStatus(1);
        FightHumanMode(); break;}
    default:
    { break;}
    }
}

void Paint::DrawTank(int X, int Y, int rot)
{
}

void Paint::DrawWall(int X, int Y)
{
}

void Paint::DrawTarget(int X, int Y)
{
    scene->setPalette(Qt::blue);
    scene->palette();
    int n_X=(X-1)*2;
    int n_Y=(Y-1)*2;
 scene->addLine(X_RIGHT-(n_X+1)*20, Y_DOWN-(n_Y)*20+2, X_RIGHT-(n_X+1)*20, Y_DOWN-(n_Y+2)*20-2);
scene->addLine(X_RIGHT-(n_X+2)*20, Y_DOWN-(n_Y)*20+2, X_RIGHT-(n_X)*20, Y_DOWN-(n_Y)*20+2);
scene->addLine(X_RIGHT-(n_X+1)*20, Y_DOWN-(n_Y+1)*20+2, X_RIGHT-(n_X+0.5)*20, Y_DOWN-(n_Y+1.5)*20);
scene->addLine(X_RIGHT-(n_X+1)*20, Y_DOWN-(n_Y+2)*20-2, X_RIGHT-(n_X+0.5)*20, Y_DOWN-(n_Y+1.5)*20);
}

void Paint::WinOrPerish(int isWin)
{
    if (isWin == 1)
    {
        Sleep(1000);
         win = 3;
        command[0] = "";
        for (int i = 0; i<50; i++)
        {
            commands_array[i] = 'z';
            digit_array[i] = 0;
        }

        x_pos = 570; y_pos = 570; orient = 90, orients[0] = 90;
        tanks[0].SetCoordinates(570, 570);
        count_letters=0;
        count_words=0;
        scene->clear();
        //ui->Write_CommandList->clear();
        ui->label_win->show();
        ui->label_tank->move(x_pos, y_pos);
        ui->label_tank->repaint();
        BuildWall();
    }
   else if (isWin == -1)
    {
        Sleep(1000);
        ui->label_lose->show();
        //ui->label_tank->move(x_pos, y_pos);
       win = 0;
        command[0] = "";

        for (int i = 0; i<50; i++)
        {
            commands_array[i] = 'z';
            digit_array[i] = 0;
        }
        x_pos = 570; y_pos = 570; orient = 90, orients[0] = 90;
        tanks[0].SetCoordinates(570, 570);
        coords[0][0] = 570;
        coords[0][1] = 570;

        count_letters=0;
        count_words=0;
        scene->clear();
        ui->Write_CommandList->clear();

        //ui->label_win->show();
        ui->label_tank->move(x_pos, y_pos);
        ui->label_tank->repaint();
        BuildWall();
    }
}

void Paint::SetWin(int w)
{
  win = w;
}

void Paint::BuildWall() //инициализация стен
{
    Current_Tank_Turn = 0;
    QPixmap wall_destroyed(":/images/wall_destroyed.png");
    QPixmap wall(":/images/wall.png");
    QPixmap target(":/images/target.png");

    for (int i=1; i<0xFF; i++)
        {
        walls_array[i].AddWall(i, 0, 0, 0, *ui->wall_8_2, target);
        walls_array[i].SetStatus(0);
         }
    walls_array[0x94].AddWall(0, 9, 4, 3, *ui->label_target, target);
    walls_array[0x94].SetStatus(3);

    walls_array[0x82].AddWall(1, 8, 2, 2, *ui->wall_8_2, wall);
    walls_array[0x92].AddWall(2, 9, 2, 2, *ui->wall_9_2, wall);
    walls_array[0xA2].AddWall(3, 10, 2, 2, *ui->wall_10_2, wall);
    walls_array[0xB2].AddWall(4, 11, 2, 2, *ui->wall_11_2, wall);
    walls_array[0xC2].AddWall(5, 12, 2, 2, *ui->wall_12_2, wall);
    walls_array[0x73].AddWall(6, 7, 3, 2, *ui->wall_7_3, wall);
    walls_array[0x64].AddWall(7, 6, 4, 2, *ui->wall_6_4, wall);
    walls_array[0x75].AddWall(8, 7, 5, 2, *ui->wall_7_5, wall);
    walls_array[0x86].AddWall(9, 8, 6, 2, *ui->wall_8_6, wall);
    walls_array[0x97].AddWall(10, 9, 7, 2, *ui->wall_9_7, wall);
    walls_array[0xA8].AddWall(11, 10, 8, 2, *ui->wall_10_8, wall);
    walls_array[0xB9].AddWall(12, 11, 9, 2, *ui->wall_11_9, wall);
    walls_array[0xCA].AddWall(13, 12, 10, 2, *ui->wall_12_10, wall);
    walls_array[0xB4].AddWall(14, 11, 4, 2, *ui->wall_11_4, wall);
    walls_array[0xB5].AddWall(15, 11, 5, 2, *ui->wall_11_5, wall);
    walls_array[0x2B].AddWall(16, 2, 11, 2, *ui->wall_2_11, wall);
    walls_array[0x3B].AddWall(17, 3, 11, 2, *ui->wall_3_11, wall);
    walls_array[0x6B].AddWall(18, 6, 11, 2, *ui->wall_6_11, wall);
    walls_array[0x7B].AddWall(19, 7, 11, 2, *ui->wall_7_11, wall);
    walls_array[0x3C].AddWall(20, 3, 12, 2, *ui->wall_3_12, wall);
    walls_array[0x4C].AddWall(21, 4, 12, 2, *ui->wall_4_12, wall);
    walls_array[0x5C].AddWall(22, 5, 12, 2, *ui->wall_5_12, wall);
    walls_array[0x6C].AddWall(23, 6, 12, 2, *ui->wall_6_12, wall);
    walls_array[0xFC].AddWall(24, 15, 12, 2, *ui->wall_15_12, wall);
    walls_array[0xEC].AddWall(25, 14, 12, 2, *ui->wall_14_12, wall);
    walls_array[0xDC].AddWall(26, 13, 12, 2, *ui->wall_13_12, wall);
    walls_array[0xCC].AddWall(27, 12, 12, 2, *ui->wall_12_12, wall);
    walls_array[0xF3].AddWall(28, 15, 3, 1, *ui->wall_15_3, wall_destroyed);
    walls_array[0xE3].AddWall(28, 15, 3, 1, *ui->wall_14_3, wall_destroyed);
    walls_array[0x6F].AddWall(28, 15, 3, 1, *ui->wall_6_15, wall_destroyed);
    walls_array[0x6E].AddWall(28, 15, 3, 1, *ui->wall_6_14, wall_destroyed);
    walls_array[0x7F].AddWall(28, 15, 3, 1, *ui->wall_7_15, wall_destroyed);

    //инициализация танков
    //непонятно, как инициализировать массив, если для widget'ов запрещено копирование и присваивание
QPixmap p_tank_90(":/images/p_tank_90.png");
QPixmap e_tank_0(":/images/e_tank_0.png");
QPixmap e_tank_90(":/images/e_tank_90.png");
QPixmap e_tank_180(":/images/e_tank_180.png");
QPixmap e_tank_270(":/images/e_tank_270.png");

//установка параметров для игрока
    tanks[0].SetNumber(0);
    tanks[0].SetStatus(1);
    tanks[0].SetLabel(*ui->label_tank);
    tanks[0].SetCoordinates(570, 570);
    tanks[0].SetPixmap(p_tank_90);
    tanks[0].SetOrient(90);
    tanks[0].SetFireLabels(*ui->im_fire1_0, *ui->im_fire2_0, *ui->im_fire1_90, *ui->im_fire2_90,
                           *ui->im_fire1_180, *ui->im_fire2_180, *ui->im_fire1_270, *ui->im_fire2_270, *ui->im_shell);
    tanks[0].Repaint();

    //установка параметров для врагов

    tanks[1].SetLabel(*ui->label_etank_1);
    tanks[2].SetLabel(*ui->label_etank_2);
    tanks[3].SetLabel(*ui->label_etank_3);
    tanks[4].SetLabel(*ui->label_etank_4);
    tanks[5].SetLabel(*ui->label_etank_5);
    tanks[6].SetLabel(*ui->label_etank_6);
    tanks[7].SetLabel(*ui->label_etank_7);
    tanks[8].SetLabel(*ui->label_smart_etank);

    for (int i=1; i<9; i++)
    {
        tanks[i].SetNumber(i);
        tanks[i].SetStatus(1);
        tanks[i].SetFireLabels(*ui->im_fire1_0, *ui->im_fire2_0, *ui->im_fire1_90, *ui->im_fire2_90,
                 *ui->im_fire1_180, *ui->im_fire2_180, *ui->im_fire1_270, *ui->im_fire2_270, *ui->im_shell);
        tanks[i].SetPixmap(e_tank_270);
        tanks[i].SetOrient(270);
        tanks[i].Repaint();
    }

    tanks[6].SetPixmap(e_tank_0);
    tanks[6].SetOrient(0);
    tanks[7].SetPixmap(e_tank_0/*e_tank_0*/);
    tanks[7].SetOrient(0);
    tanks[8].SetPixmap(e_tank_0/*e_tank_0*/);
    tanks[8].SetOrient(0);

    tanks[1].SetCoordinates(10, 10);
    tanks[2].SetCoordinates(130, 10);
    tanks[3].SetCoordinates(570, 10);
    tanks[4].SetCoordinates(450, 10);
    tanks[5].SetCoordinates(290, 10);
    tanks[6].SetCoordinates(410, 90);
    tanks[7].SetCoordinates(410, 210);
    tanks[8].SetCoordinates(250, 130);

    //tanks[0] = Tank(0, *ui->label_tank, 570, 570, 90, p_tank_90, walls_array[0]);

    ui->label_etank_1->hide();
    ui->label_etank_2->hide();
    ui->label_etank_3->hide();
    ui->label_etank_4->hide();
    ui->label_etank_5->hide();
    ui->label_etank_6->hide();
    ui->label_etank_7->hide();
    ui->label_smart_etank->hide();

    isTank = FALSE;
    isWall = FALSE;
    //NumberOfCommandsCondition = 0;
}

void Paint::TargetMode()
{
    if (!timer2->isActive() )

    timer2->start(500);
    timerStopped = false;

    QPixmap p_tank_0(":/images/p_tank_0.png");
    QPixmap p_tank_90(":/images/p_tank_90.png");
    QPixmap p_tank_180(":/images/p_tank_180.png");
    QPixmap p_tank_270(":/images/p_tank_270.png");
    QPixmap e_tank_0(":/images/e_tank_0.png");
    QPixmap e_tank_90(":/images/e_tank_90.png");
    QPixmap e_tank_180(":/images/e_tank_180.png");
    QPixmap e_tank_270(":/images/e_tank_270.png");

    QPixmap fire1_0(":/images/fire1_0.png");
    QPixmap fire1_90(":/images/fire1_90.png");
    QPixmap fire1_180(":/images/fire1_180.png");
    QPixmap fire1_270(":/images/fire1_270.png");
    QPixmap fire2_0(":/images/fire2_0.png");
    QPixmap fire2_90(":/images/fire2_90.png");
    QPixmap fire2_180(":/images/fire2_180.png");
    QPixmap fire2_270(":/images/fire2_270.png");

    QPixmap ground(":/images/ground.png");
    QPixmap shell(":/images/shell.png");
    QPixmap tank_destroyed(":/images/tank_destroyed.png");
    QPixmap wall_destroyed(":/images/wall_destroyed.png");

        if(commands_array[count_letters-count_words]=='F')
            tanks[0].ForwardImplementation(*this, walls_array);

        else if (commands_array[count_letters-count_words]=='B')
            tanks[0].BackwardImplementation(*this, walls_array);

        else if (commands_array[count_letters-count_words]=='L')
        {
            tanks[0].TurnLeftImplementation(*this, orients[0]);

        }
        else if (commands_array[count_letters-count_words]=='R')
            tanks[0].TurnRightImplementation(*this, orients[0]);

        else if (commands_array[count_letters-count_words]=='I')
        {
            tanks[0].SetFireLabels(*ui->im_fire1_0, *ui->im_fire2_0, *ui->im_fire1_90, *ui->im_fire2_90, *ui->im_fire1_180, *ui->im_fire2_180, *ui->im_fire1_270, *ui->im_fire2_270, *ui->im_shell);
            tanks[0].FireImplementation(*this, walls_array, tanks);
        }
        count_words--;
        tanks[0].SetCoordinates(coords[0][0], coords[0][1]);
        ui->label_tank->repaint();

        if (walls_array[0x94].GetStatus() == 0 ) win = 1;  // победа при поражении флага
        if (count_words <= 0 &&  win != 3) win = -1;
        if (win != 0) timer2->stop();
        WinOrPerish(win);
}

void Paint::FeastMode()
{
    if (!timer2->isActive() )
    timer2->start(200);
    timerStopped = false;
    QPixmap p_tank_0(":/images/p_tank_0.png");
    QPixmap p_tank_90(":/images/p_tank_90.png");
    QPixmap p_tank_180(":/images/p_tank_180.png");
    QPixmap p_tank_270(":/images/p_tank_270.png");
    QPixmap e_tank_0(":/images/e_tank_0.png");
    QPixmap e_tank_90(":/images/e_tank_90.png");
    QPixmap e_tank_180(":/images/e_tank_180.png");
    QPixmap e_tank_270(":/images/e_tank_270.png");

    QPixmap fire1_0(":/images/fire1_0.png");
    QPixmap fire1_90(":/images/fire1_90.png");
    QPixmap fire1_180(":/images/fire1_180.png");
    QPixmap fire1_270(":/images/fire1_270.png");
    QPixmap fire2_0(":/images/fire2_0.png");
    QPixmap fire2_90(":/images/fire2_90.png");
    QPixmap fire2_180(":/images/fire2_180.png");
    QPixmap fire2_270(":/images/fire2_270.png");

    QPixmap ground(":/images/ground.png");
    QPixmap shell(":/images/shell.png");
    QPixmap tank_destroyed(":/images/tank_destroyed.png");
    QPixmap wall_destroyed(":/images/wall_destroyed.png");

    if (Current_Tank_Turn==0)
     {
        if (commands_array[count_letters-count_words]=='T')    // если проверено верное условие, команда изменяется - переключение на команды альтернативного массива
    {
            int NumberOfCommandsConditionT = 0;
            while (commands_array[count_letters-count_words+NumberOfCommandsConditionT]=='T') NumberOfCommandsConditionT++;

        if(tanks[0].CheckFireResult(orients[0], *this, walls_array, tanks, 0) == 1) commands_array[count_letters-count_words] = alt_commands_array[count_letters-count_words];
            else count_words = count_words-NumberOfCommandsConditionT; //если условие не выполнено, в основном массиве пропустить пустые команды
            NumberOfCommandsConditionT = 0;
        }
    else if (commands_array[count_letters-count_words]=='W')
    {
            int NumberOfCommandsConditionW = 0;
            while (commands_array[count_letters-count_words+NumberOfCommandsConditionW]=='W') NumberOfCommandsConditionW++;

         if(tanks[0].CheckFireResult(orients[0], *this, walls_array, tanks, 0) == 2) commands_array[count_letters-count_words] = alt_commands_array[count_letters-count_words];
             else count_words = count_words-NumberOfCommandsConditionW;  //если условие не выполнено, в основном массиве пропустить пустые команды
         NumberOfCommandsConditionW = 0;
        }
//        if (alt_commands_array[count_letters-count_words] != '\0')
//        {count_words = count_words + NumberOfCommandsCondition; NumberOfCommandsCondition = 0;}   //если альтмассив, пропустить пустые команды в основном массиве

    if(commands_array[count_letters-count_words]=='F')
            tanks[0].ForwardImplementation(*this, walls_array);

        else if (commands_array[count_letters-count_words]=='B')
            tanks[0].BackwardImplementation(*this, walls_array);

        else if (commands_array[count_letters-count_words]=='L')
        {
            tanks[0].TurnLeftImplementation(*this, orients[0]);

        }
        else if (commands_array[count_letters-count_words]=='R')
            tanks[0].TurnRightImplementation(*this, orients[0]);

        else if (commands_array[count_letters-count_words]=='I')
        {
            tanks[0].FireImplementation(*this, walls_array, tanks);
        }

        count_words--;
        tanks[0].SetCoordinates(coords[0][0], coords[0][1]);
        ui->label_tank->repaint();
    }
    else // другие танки
    {
        int next_step = rand() % 6;
        qDebug() << "tank number" << Current_Tank_Turn << " chose " << next_step;
        //char next_step[] = {'F', 'B', 'L', 'R', 'I'};

          if (next_step == 1)
           tanks[Current_Tank_Turn].ForwardImplementation(*this, walls_array);

       else if (next_step == 2)
           tanks[Current_Tank_Turn].BackwardImplementation(*this, walls_array);

       else if (next_step == 3)
       {
           tanks[Current_Tank_Turn].TurnLeftImplementation(*this, orients[Current_Tank_Turn]);
       }
       else if (next_step == 4)
           tanks[Current_Tank_Turn].TurnRightImplementation(*this, orients[Current_Tank_Turn]);

       else if (next_step == 5)
       {
           tanks[Current_Tank_Turn].FireImplementation(*this, walls_array, tanks);
       }
          else;

       tanks[Current_Tank_Turn].SetCoordinates(coords[Current_Tank_Turn][0], coords[Current_Tank_Turn][1]);
       tanks[Current_Tank_Turn].Repaint();
   }

    if (count_words <= 0 &&  win != 3) win = -1;
    if (win != 0) timer2->stop();

 Current_Tank_Turn++;
    if (Current_Tank_Turn==8)
        {
        int check_status = 0;
            Current_Tank_Turn = 0; //ход танка игрока
            for (int i = 1; i < 8; ++i)
            {
                check_status += tanks[i].GetStatus();
            }
            if (check_status == 0)  win = 1;  // победа при уничтожении целей
         }
        WinOrPerish(win);
}

void Paint::FightTerminatorMode()
{
    if (!timer2->isActive() )
    timer2->start(200);
    timerStopped = false;
    QPixmap p_tank_0(":/images/p_tank_0.png");
    QPixmap p_tank_90(":/images/p_tank_90.png");
    QPixmap p_tank_180(":/images/p_tank_180.png");
    QPixmap p_tank_270(":/images/p_tank_270.png");
    QPixmap e_tank_0(":/images/e_tank_0.png");
    QPixmap e_tank_90(":/images/e_tank_90.png");
    QPixmap e_tank_180(":/images/e_tank_180.png");
    QPixmap e_tank_270(":/images/e_tank_270.png");

    QPixmap fire1_0(":/images/fire1_0.png");
    QPixmap fire1_90(":/images/fire1_90.png");
    QPixmap fire1_180(":/images/fire1_180.png");
    QPixmap fire1_270(":/images/fire1_270.png");
    QPixmap fire2_0(":/images/fire2_0.png");
    QPixmap fire2_90(":/images/fire2_90.png");
    QPixmap fire2_180(":/images/fire2_180.png");
    QPixmap fire2_270(":/images/fire2_270.png");

    QPixmap ground(":/images/ground.png");
    QPixmap shell(":/images/shell.png");
    QPixmap tank_destroyed(":/images/tank_destroyed.png");
    QPixmap wall_destroyed(":/images/wall_destroyed.png");

//    if (Current_Tank_Turn==0)
//     {
        if (commands_array[count_letters-count_words]=='T')    // если проверено верное условие, команда изменяется - переключение на команды альтернативного массива
    {
            int NumberOfCommandsConditionT = 0;
            while (commands_array[count_letters-count_words+NumberOfCommandsConditionT]=='T') NumberOfCommandsConditionT++;

        if(tanks[0].CheckFireResult(orients[0], *this, walls_array, tanks, 0) == 1) commands_array[count_letters-count_words] = alt_commands_array[count_letters-count_words];
            else count_words = count_words-NumberOfCommandsConditionT; //если условие не выполнено, в основном массиве пропустить пустые команды
            NumberOfCommandsConditionT = 0;
        }
    else if (commands_array[count_letters-count_words]=='W')
    {
            int NumberOfCommandsConditionW = 0;
            while (commands_array[count_letters-count_words+NumberOfCommandsConditionW]=='W') NumberOfCommandsConditionW++;

         if(tanks[0].CheckFireResult(orients[0], *this, walls_array, tanks, 0) == 2) commands_array[count_letters-count_words] = alt_commands_array[count_letters-count_words];
             else count_words = count_words-NumberOfCommandsConditionW;  //если условие не выполнено, в основном массиве пропустить пустые команды
         NumberOfCommandsConditionW = 0;
        }
//        if (alt_commands_array[count_letters-count_words] != '\0')
//        {count_words = count_words + NumberOfCommandsCondition; NumberOfCommandsCondition = 0;}   //если альтмассив, пропустить пустые команды в основном массиве

    if(commands_array[count_letters-count_words]=='F')
            tanks[0].ForwardImplementation(*this, walls_array);

        else if (commands_array[count_letters-count_words]=='B')
            tanks[0].BackwardImplementation(*this, walls_array);

        else if (commands_array[count_letters-count_words]=='L')
        {
            tanks[0].TurnLeftImplementation(*this, orients[0]);
        }
        else if (commands_array[count_letters-count_words]=='R')
            tanks[0].TurnRightImplementation(*this, orients[0]);

        else if (commands_array[count_letters-count_words]=='I')
        {
            tanks[0].FireImplementation(*this, walls_array, tanks);
        }

        count_words--;
        tanks[0].SetCoordinates(coords[0][0], coords[0][1]);
        ui->label_tank->repaint();
//    }
//     ход терминатора
//    {
        switch (orients[8])
        {
            case (0):
            {
            if (coords[0][0] >= coords[8][0] && coords[0][1] == coords[8][1])   //если игрок севернее
                {if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 2 || tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 1) tanks[8].FireImplementation(*this, walls_array, tanks);    //если игрок/препятствие на линии огня - убить
                     else if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) != 1||2) tanks[8].ForwardImplementation(*this, walls_array); } //иначе догнать
            else if (coords[0][1] <= coords[8][1]) tanks[8].TurnLeftImplementation(*this, orients[8]);  //если игрок западнее - навестись
            else if (coords[0][1] > coords[8][1]) tanks[8].TurnRightImplementation(*this, orients[8]);  //если игрок восточнее - навестись
            else tanks[8].BackwardImplementation(*this, walls_array);  //отход
            break;
        }
            case (90):
            {
            if (coords[0][1] < coords[8][1])   //если игрок западнее
                {if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 2 || tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 1) tanks[8].FireImplementation(*this, walls_array, tanks);    //если игрок/препятствие на линии огня - убить
                     else if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) != 1||2) tanks[8].ForwardImplementation(*this, walls_array); } //иначе сократить дистанцию
            else if (coords[0][0] <= coords[8][0]) tanks[8].TurnLeftImplementation(*this, orients[8]);  //если игрок южнее - навестись
            else if (coords[0][0] > coords[8][0]) tanks[8].TurnRightImplementation(*this, orients[8]);  //если игрок севернее - навестись
            else tanks[8].BackwardImplementation(*this, walls_array);  //отход
            break;
        }
            case (180):
            {
            if (coords[0][0] <= coords[8][0] && coords[0][1] == coords[8][1])   //если игрок южнее
                {if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 2 || tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 1) tanks[8].FireImplementation(*this, walls_array, tanks);    //если игрок/препятствие на линии огня - убить
                     else if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) != 1||2) tanks[8].ForwardImplementation(*this, walls_array); } //иначе догнать
            else if (coords[0][1] <= coords[8][1]) tanks[8].TurnRightImplementation(*this, orients[8]);  //если игрок западнее - навестись
            else if (coords[0][1] > coords[8][1]) tanks[8].TurnLeftImplementation(*this, orients[8]);  //если игрок восточнее - навестись
            else tanks[8].BackwardImplementation(*this, walls_array);  //отход
            break;
        }
            case (270):
            {
            if (coords[0][1] > coords[8][1])   //если игрок восточнее
                {if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 2 || tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) == 1) tanks[8].FireImplementation(*this, walls_array, tanks);    //если игрок/препятствие на линии огня - убить
                     else if (tanks[8].CheckFireResult(orients[8], *this, walls_array, tanks, FALSE) != 1||2) tanks[8].ForwardImplementation(*this, walls_array); } //иначе сократить дистанцию
            else if (coords[0][0] >= coords[8][0]) tanks[8].TurnLeftImplementation(*this, orients[8]);  //если игрок севернее - навестись
            else if (coords[0][0] < coords[8][0]) tanks[8].TurnRightImplementation(*this, orients[8]);  //если игрок южнее - навестись
            else tanks[8].BackwardImplementation(*this, walls_array);  //отход
            break;
        }
            default: break;
        }
       tanks[8].SetCoordinates(coords[8][0], coords[8][1]);
       tanks[8].Repaint();

if (count_words <= 0 &&  win != 3) win = -1;
   if (win != 0) timer2->stop();
 WinOrPerish(win);

// Current_Tank_Turn++;
//if (Current_Tank_Turn==9) Current_Tank_Turn = 0; //ход следующего танка
}

void Paint::FightHumanMode()
{

}

void Paint::on_Mode_Feast_clicked()
{
    disconnect(timer2, &QTimer::timeout, this, &Paint::TargetMode); //надо
    disconnect(timer2, &QTimer::timeout, this, &Paint::FeastMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightTerminatorMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightHumanMode);

    connect(timer2, &QTimer::timeout, this, &Paint::FeastMode, Qt::DirectConnection);  // соединяем таймер с нужным слотом

    //    ui->label_17->setDisabled(true);  //кнопки включаются во всех режимах, кроме таргет
        ui->label_18->setEnabled(true);
        ui->label_19->setEnabled(true);
    //    ui->label_20->setDisabled(true);
        ui->ButtonStartCicle->setEnabled(true);
        ui->ButtonFinishCicle->setEnabled(true);
        ui->ButtonStartCondition->setEnabled(true);
        ui->ButtonFinishCondition->setEnabled(true);
    //    ui->Write_NumberCicles->setDisabled(true);
    //    ui->ButtonConditionEnemyClose->setDisabled(true);
    //    ui->ButtonConditionWallClose->setDisabled(true);
    //    ui->AddCondition->setDisabled(true);
    //    ui->DeleteCondition->setDisabled(true);
    //    ui->AddCicles->setDisabled(true);
    //    ui->DeleteCicles->setDisabled(true);

    ui->label_manual_target_mode->hide();
    ui->label_manual_feast_mode->show();
    ui->label_manual_terminator_mode->hide();
    ui->label_manual_human_mode->hide();
    ui->pic_manual_target_mode->hide();
    ui->pic_manual_feast_mode->show();
    ui->pic_manual_terminator_mode->hide();
    ui->pic_manual_human_mode->hide();

    ui->label_etank_1->show();
    ui->label_etank_2->show();
    ui->label_etank_3->show();
    ui->label_etank_4->show();
    ui->label_etank_5->show();
    ui->label_etank_6->show();
    ui->label_etank_7->show();
    ui->label_smart_etank->hide();
}

void Paint::on_Mode_Fight_Terminator_clicked()
{
    disconnect(timer2, &QTimer::timeout, this, &Paint::TargetMode); //надо
    disconnect(timer2, &QTimer::timeout, this, &Paint::FeastMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightTerminatorMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightHumanMode);

    connect(timer2, &QTimer::timeout, this, &Paint::FightTerminatorMode, Qt::DirectConnection);  // соединяем таймер с нужным слотом

    //    ui->label_17->setDisabled(true);  //кнопки включаются во всех режимах, кроме таргет
        ui->label_18->setEnabled(true);
        ui->label_19->setEnabled(true);
    //    ui->label_20->setDisabled(true);
        ui->ButtonStartCicle->setEnabled(true);
        ui->ButtonFinishCicle->setEnabled(true);
        ui->ButtonStartCondition->setEnabled(true);
        ui->ButtonFinishCondition->setEnabled(true);
    //    ui->Write_NumberCicles->setDisabled(true);
    //    ui->ButtonConditionEnemyClose->setDisabled(true);
    //    ui->ButtonConditionWallClose->setDisabled(true);
    //    ui->AddCondition->setDisabled(true);
    //    ui->DeleteCondition->setDisabled(true);
    //    ui->AddCicles->setDisabled(true);
    //    ui->DeleteCicles->setDisabled(true);

    ui->label_manual_target_mode->hide();
    ui->label_manual_feast_mode->hide();
    ui->label_manual_terminator_mode->show();
    ui->label_manual_human_mode->hide();
    ui->pic_manual_target_mode->hide();
    ui->pic_manual_feast_mode->hide();
    ui->pic_manual_terminator_mode->show();
    ui->pic_manual_human_mode->hide();

    ui->label_etank_1->hide();
    ui->label_etank_2->hide();
    ui->label_etank_3->hide();
    ui->label_etank_4->hide();
    ui->label_etank_5->hide();
    ui->label_etank_6->hide();
    ui->label_etank_7->hide();
    ui->label_smart_etank->show();
}

void Paint::on_Mode_Fight_Human_clicked()
{
    disconnect(timer2, &QTimer::timeout, this, &Paint::TargetMode); //надо
    disconnect(timer2, &QTimer::timeout, this, &Paint::FeastMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightTerminatorMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightHumanMode);

    connect(timer2, &QTimer::timeout, this, &Paint::FightHumanMode, Qt::DirectConnection);  // соединяем таймер с нужным слотом

//    ui->label_17->setDisabled(true);  //кнопки включаются во всех режимах, кроме таргет
    ui->label_18->setEnabled(true);
    ui->label_19->setEnabled(true);
//    ui->label_20->setDisabled(true);
    ui->ButtonStartCicle->setEnabled(true);
    ui->ButtonFinishCicle->setEnabled(true);
    ui->ButtonStartCondition->setEnabled(true);
    ui->ButtonFinishCondition->setEnabled(true);
//    ui->Write_NumberCicles->setDisabled(true);
//    ui->ButtonConditionEnemyClose->setDisabled(true);
//    ui->ButtonConditionWallClose->setDisabled(true);
//    ui->AddCondition->setDisabled(true);
//    ui->DeleteCondition->setDisabled(true);
//    ui->AddCicles->setDisabled(true);
//    ui->DeleteCicles->setDisabled(true);

    ui->label_manual_target_mode->hide();
    ui->label_manual_feast_mode->hide();
    ui->label_manual_terminator_mode->hide();
    ui->label_manual_human_mode->show();
    ui->pic_manual_target_mode->hide();
    ui->pic_manual_feast_mode->hide();
    ui->pic_manual_terminator_mode->hide();
    ui->pic_manual_human_mode->show();

    ui->label_etank_1->show();
    ui->label_etank_2->hide();
    ui->label_etank_3->hide();
    ui->label_etank_4->hide();
    ui->label_etank_5->hide();
    ui->label_etank_6->hide();
    ui->label_etank_7->hide();
    ui->label_smart_etank->hide();
}

void Paint::on_Mode_Target_clicked()
{
    disconnect(timer2, &QTimer::timeout, this, &Paint::TargetMode); //надо
    disconnect(timer2, &QTimer::timeout, this, &Paint::FeastMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightTerminatorMode);
    disconnect(timer2, &QTimer::timeout, this, &Paint::FightHumanMode);

    connect(timer2, &QTimer::timeout, this, &Paint::TargetMode, Qt::DirectConnection);  // соединяем таймер с нужным слотом

    ui->label_17->setDisabled(true);  //кнопки включаются во всех режимах, кроме таргет
    ui->label_18->setDisabled(true);
    ui->label_19->setDisabled(true);
    ui->label_20->setDisabled(true);
    ui->ButtonStartCicle->setDisabled(true);
    ui->ButtonFinishCicle->setDisabled(true);
    ui->ButtonStartCondition->setDisabled(true);
    ui->ButtonFinishCondition->setDisabled(true);
    ui->Write_NumberCicles->setDisabled(true);
    ui->ButtonConditionEnemyClose->setDisabled(true);
    ui->ButtonConditionWallClose->setDisabled(true);
    ui->AddCondition->setDisabled(true);
    ui->DeleteCondition->setDisabled(true);
    //ui->AddCicles->setDisabled(true);
    //ui->DeleteCicles->setDisabled(true);

    ui->label_manual_target_mode->show();
    ui->label_manual_feast_mode->hide();
    ui->label_manual_terminator_mode->hide();
    ui->label_manual_human_mode->hide();
    ui->pic_manual_target_mode->show();
    ui->pic_manual_feast_mode->hide();
    ui->pic_manual_terminator_mode->hide();
    ui->pic_manual_human_mode->hide();

    ui->label_etank_1->hide();
    ui->label_etank_2->hide();
    ui->label_etank_3->hide();
    ui->label_etank_4->hide();
    ui->label_etank_5->hide();
    ui->label_etank_6->hide();
    ui->label_etank_7->hide();
    ui->label_smart_etank->hide();
}

void Paint::on_ButtonStartCondition_clicked()
{
        ui->label_17->setEnabled(true);  //кнопки отключаются, когда не нужны
        ui->ButtonConditionEnemyClose->setEnabled(true);
        ui->ButtonConditionWallClose->setEnabled(true);
        ui->AddCondition->setEnabled(true);
        ui->DeleteCondition->setEnabled(true);
        isCondition = TRUE;
}

void Paint::on_ButtonFinishCondition_clicked()
{
    ui->label_17->setDisabled(true);  //кнопки отключаются, когда не нужны
    ui->ButtonConditionEnemyClose->setDisabled(true);
    ui->ButtonConditionWallClose->setDisabled(true);
    ui->AddCondition->setDisabled(true);
    ui->DeleteCondition->setDisabled(true);
    isCondition = FALSE;
    isTank = FALSE;
    isWall = FALSE;
}

void Paint::on_ButtonStartCicle_clicked()
{
    ui->label_20->setEnabled(true);
    //ui->label_19->setEnabled(true);
    ui->Write_NumberCicles->setEnabled(true);
   //ui->AddCicles->setEnabled(true);
    //ui->DeleteCicles->setEnabled(true);
    isCicle = TRUE;
}

void Paint::on_ButtonFinishCicle_clicked()
{
    ui->label_20->setDisabled(true);
    //ui->label_19->setDisabled(true);
    ui->Write_NumberCicles->setDisabled(true);
   // ui->AddCicles->setDisabled(true);
    //ui->DeleteCicles->setDisabled(true);
    isCicle = FALSE;
}

void Paint::on_Write_NumberCicles_textChanged()
{
    QString stringCicles = ui->Write_NumberCicles->toPlainText();
    NumberOfCicles = stringCicles.toFloat();
}

void Paint::on_ButtonConditionEnemyClose_clicked()
{
    isTank = TRUE;
    isWall = FALSE;
}

void Paint::on_ButtonConditionWallClose_clicked()
{
    isTank = FALSE;
    isWall = TRUE;
}
