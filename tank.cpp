#include "tank.h"
#include "paint.h"

Tank::Tank() {};

Tank::Tank(int number,  //0 - игрок, 1-7 - враги, 8 - прокачанный враг, 9 - игрок 2
           QLabel &label,
           int x, int y, int l_orient, int t_status, //позиция, угол, статус
           QPixmap &pixmap,
           Wall (&r_walls)[0xFF] )
{
    tank_number = number;
    tank_status = t_status;
    x_position = x;
    y_position = y;
    azimuth = l_orient;
    *walls = (&r_walls)[0xFF];
    //tank_destroyed = pixmap;
    label_panzer = &label;
};

void Tank::ForwardImplementation(Paint &paint, Wall (&r_walls)[0xFF]) //берет ссылку на массив стен
{
    BREAK_OUT=false;
    if (this->GetStatus()!=0)
        switch (azimuth)
        {
        case 0:
        {
            x_position = x_position + 40;
            for (int i=1; i<16; i++)
            {    for (int j=1; j<16; j++)
                 if ( (r_walls[i*16+j].GetStatus()>0 && x_position == (i-1)*40 + 10 && y_position == (j-1)*40 + 10) || x_position < 10 || x_position > 570 || y_position < 10 || y_position > 570) //номер - 0х двузначная позиция
                    {
                     x_position = (i-2)*40 + 10;
                     BREAK_OUT=true;
                     break;
                    }
            if (BREAK_OUT==true) break;
            }
               BREAK_OUT=false; break;
        }
        case 90:
        {
            y_position = y_position - 40;
            BREAK_OUT=false;
            for (int i=1; i<16; i++)
            {    for (int j=1; j<16; j++)
                 if ( (r_walls[i*16+j].GetStatus()>0 && (y_position == (j-1)*40 + 10) && (x_position == (i-1)*40 + 10) )  || x_position < 10 || x_position > 570 || y_position < 10 || y_position > 570 ) {y_position = (j)*40 + 10; BREAK_OUT = true; break;}
             if (BREAK_OUT==true) break;
            }
           BREAK_OUT=false; break;
        }
        case 180:
        {
            x_position = x_position - 40;
            BREAK_OUT=false;
            for (int i=15; i>0; i--)
            {    for (int j=1; j<16; j++)
                 if ( (r_walls[i*16+j].GetStatus()>0 && x_position == (i-1)*40 + 10 && (y_position == (j-1)*40 + 10))  || x_position < 10 || x_position > 570 || y_position < 10 || y_position > 570 ) {x_position = (i)*40 + 10; BREAK_OUT=true;  break;}
             if (BREAK_OUT==true) break;
            }
           BREAK_OUT=false; break;
        }
        case 270:
        {
            y_position = y_position + 40;
            BREAK_OUT=false;
            for (int i=1; i<16; i++)
             {
                for (int j=15; j>0; j--)
                 if ( (r_walls[i*16+j].GetStatus()>0 && y_position == (j-1)*40 + 10 && (x_position == (i-1)*40 + 10))  || x_position < 10 || x_position > 570 || y_position < 10 || y_position > 570 ) {y_position = (j-2)*40 + 10; BREAK_OUT=true; break;}
             if (BREAK_OUT==true) break;
            }
           BREAK_OUT=false; break;
        }
        default: break;
    }
        GetCoordinates(paint);
}

void Tank::BackwardImplementation(Paint &paint, Wall (&r_walls)[0xFF])
{
    BREAK_OUT=false;
    if (this->GetStatus()!=0)
        switch (azimuth)
        {
        case 0:
        {
            x_position = x_position - 40*digit_array[count_letters-count_words];
            for (int i=1; i<16; i++)
            {    for (int j=1; j<16; j++)
                 if (r_walls[i*16+j].GetStatus()>0 && x_position == (i-1)*40 + 10 && y_position == (j-1)*40 + 10) {x_position = (i)*40 + 10; BREAK_OUT=true; break;}
            if (BREAK_OUT==true) break;
            }
               BREAK_OUT=false; break;
        }
        case 90:
        {
            y_position = y_position - 40*digit_array[count_letters-count_words];
            for (int i=1; i<16; i++)
            {    for (int j=1; j<16; j++)
                 if (r_walls[i*16+j].GetStatus()>0 && (y_position == (j-1)*40 + 10) && (x_position == (i-1)*40 + 10) ) {y_position = (j-2)*40 + 10; BREAK_OUT=true; break;}
             if (BREAK_OUT==true) break;
            }
           BREAK_OUT=false; break;
        }
        case 180:
        {
            x_position = x_position + 40*digit_array[count_letters-count_words];
            for (int i=15; i>0; i--)
            {    for (int j=1; j<16; j++)
                 if (r_walls[i*16+j].GetStatus()>0 && x_position == (i-1)*40 + 10 && (y_position == (j-1)*40 + 10) ) {x_position = (i-2)*40 + 10; BREAK_OUT=true;  break;}
             if (BREAK_OUT==true) break;
            }
           BREAK_OUT=false; break;
        }
        case 270:
        {
            y_position = y_position - 40*digit_array[count_letters-count_words];
            for (int i=1; i<16; i++)
             {   for (int j=15; j>0; j--)
                 if (r_walls[i*16+j].GetStatus()>0 && y_position == (j-1)*40 + 10 && (x_position == (i-1)*40 + 10) ) {y_position = (j)*40 + 10; BREAK_OUT=true; break;}
             if (BREAK_OUT==true) break;
            }
           BREAK_OUT=false; break;
        }
        default: break;
    }
        GetCoordinates(paint);
}

void Tank::TurnLeftImplementation(Paint &paint, int l_orient)
{
    QPixmap p_tank_0(":/images/p_tank_0.png");
    QPixmap p_tank_90(":/images/p_tank_90.png");
    QPixmap p_tank_180(":/images/p_tank_180.png");
    QPixmap p_tank_270(":/images/p_tank_270.png");
    QPixmap e_tank_0(":/images/e_tank_0.png");
    QPixmap e_tank_90(":/images/e_tank_90.png");
    QPixmap e_tank_180(":/images/e_tank_180.png");
    QPixmap e_tank_270(":/images/e_tank_270.png");

    azimuth = l_orient + 90;
    if (azimuth == 360) azimuth = 0;
    if (azimuth == -360) azimuth = 0;
    if (azimuth == -90) azimuth = 270;

    if (this->GetStatus()!=0)
    if (tank_number == 0)
    switch (azimuth)
    {
    case 0: {
        SetPixmap(p_tank_0);
        break;}
    case 90: {
        SetPixmap(p_tank_90);
        break;}
    case 180: {
        SetPixmap(p_tank_180);
        break;}
    case 270: {
        SetPixmap(p_tank_270);
        break;}
    default: break;
    }
    else
        switch (azimuth)
        {
        case 0: {
            SetPixmap(e_tank_0);
            break;}
        case 90: {
            SetPixmap(e_tank_90);
            break;}
        case 180: {
            SetPixmap(e_tank_180);
            break;}
        case 270: {
            SetPixmap(e_tank_270);
            break;}
        default: break;
        }

    label_panzer->repaint();
GetOrient(paint);
}

void Tank::TurnRightImplementation(Paint &paint, int r_orient)
{
    QPixmap p_tank_0(":/images/p_tank_0.png");
    QPixmap p_tank_90(":/images/p_tank_90.png");
    QPixmap p_tank_180(":/images/p_tank_180.png");
    QPixmap p_tank_270(":/images/p_tank_270.png");
    QPixmap e_tank_0(":/images/e_tank_0.png");
    QPixmap e_tank_90(":/images/e_tank_90.png");
    QPixmap e_tank_180(":/images/e_tank_180.png");
    QPixmap e_tank_270(":/images/e_tank_270.png");

    azimuth = r_orient - 90;
    if (azimuth == 360) azimuth = 0;
    if (azimuth == -360) azimuth = 0;
    if (azimuth == -90) azimuth = 270;

    if (this->GetStatus()!=0)
    if (tank_number == 0)
    switch (azimuth)
    {
    case 0: {
        SetPixmap(p_tank_0);
        break;}
    case 90: {
        SetPixmap(p_tank_90);
        break;}
    case 180: {
        SetPixmap(p_tank_180);
        break;}
    case 270: {
        SetPixmap(p_tank_270);
        break;}
    default: break;
    }
    else
        switch (azimuth)
        {
        case 0: {
            SetPixmap(e_tank_0);
            break;}
        case 90: {
            SetPixmap(e_tank_90);
            break;}
        case 180: {
            SetPixmap(e_tank_180);
            break;}
        case 270: {
            SetPixmap(e_tank_270);
            break;}
        default: break;
        }
    label_panzer->repaint();

GetOrient(paint);
}

void Tank::FireImplementation(Paint &paint, Wall (&r_walls)[0xFF], Tank (&tanks)[9])
{
    fire_distance = 0;
    TARGET_STRUCK = false;
    if (this->GetStatus()>0)
    {
        FireShow(azimuth);
        CheckFireResult(azimuth, paint, r_walls, tanks, TRUE);
    }
}

int Tank::CheckFireResult(int r_orient, Paint &paint, Wall (&r_walls)[0xFF], Tank (&tanks)[9], bool isFire)
{
    int fire_distance_to_wall = 1000;
    int fire_distance_to_tank = 1000;
    int tmp_distance = 1000;
    int nearest_tank = -1;

    if (this->GetStatus()!=0)
    for (int i=0; i<16; i++)
    {
        //if (TARGET_STRUCK == true) break;
        for (int j=0; j<16; j++)
     {
            //if (TARGET_STRUCK == true) break;
            switch (r_orient) {
            case 0:
            {
                for (int n = 0; n < 9; ++n)     // проверка попадания по танкам
                {tmp_distance = tanks[n].GetX() - x_position;
                    if (this->GetNumber()!=n)
                    if (tanks[n].GetNumber()!=this->GetNumber() && tanks[n].GetStatus()>0 && (tmp_distance >= 0) && (tmp_distance <= 200) && (x_position+tmp_distance <= tanks[n].GetX() ) && y_position == tanks[n].GetY() )
                    {
                        TARGET_STRUCK = true;
                        tmp_distance = tanks[n].GetX() - x_position;
                        if (tmp_distance < fire_distance_to_tank)
                        {
                            fire_distance_to_tank = tmp_distance;
                            nearest_tank = n;
                        }
                    }
                }
                tmp_distance = 40*(i-1) + 10 - x_position;                    // проверка попадания по стенам
                if (r_walls[i*16+j].GetStatus()>0 && (tmp_distance >= 0) && (tmp_distance >= 0) && (tmp_distance <= 200) && ( x_position+40+tmp_distance <= (i*40 + 10) ) && y_position == (j-1)*40 + 10 && tmp_distance <= fire_distance_to_tank)
                {
                    TARGET_STRUCK = true;
                    fire_distance_to_wall = tmp_distance;
                    if (isFire) //был ли выстрел
                        r_walls[i*16+j].Struck();
                    return (2);
                }
         break;
            }
            case 90:
            {
                for (int n = 0; n < 9; ++n)     // проверка попадания по танкам
                {  tmp_distance = y_position - tanks[n].GetY() ;
                    if (this->GetNumber()!=n)
                    if (tanks[n].GetNumber()!=this->GetNumber() && tanks[n].GetStatus()>0 && (tmp_distance >= 0) && (tmp_distance <= 200) && (y_position+tmp_distance >= tanks[n].GetY() ) && x_position == tanks[n].GetX() /*&& fire_distance_to_tank <= fire_distance_to_wall*/ )
                    {
                        TARGET_STRUCK = true;
                        if (tmp_distance < fire_distance_to_tank)
                        {
                            fire_distance_to_tank = tmp_distance;
                            nearest_tank = n;
                        }
                    }
                }
                tmp_distance = y_position - 40*(j-1) - 10 ;                    // проверка попадания по стенам
                if (r_walls[i*16+j].GetStatus()>0 && (tmp_distance >= 0) && (tmp_distance <= 200) && ( y_position+tmp_distance >= ((j-1)*40 + 10) ) && x_position == (i-1)*40 + 10 && tmp_distance <= fire_distance_to_tank)
                {
                    fire_distance_to_wall = tmp_distance;
                    TARGET_STRUCK = true;
                                for (int k = 0/*j*/; k <= (y_position-10)/40; k++) // считать с другой стороны
                    {    if (r_walls[i*16+k].GetStatus()>0)
                            j = k;   }
                    if (isFire) //был ли выстрел
                        r_walls[i*16+j].Struck();
                    return (2);
                }
                  break;
            }

            case 180:
            {
                for (int n = 0; n < 9; ++n)     // проверка попадания по танкам
                {   tmp_distance = x_position - tanks[n].GetX() ;
                    if (this->GetNumber()!=n)
                    if (tanks[n].GetNumber()!=this->GetNumber() && tanks[n].GetStatus()>0 && tmp_distance >= 0 && tmp_distance <= 200 && (x_position+tmp_distance >= tanks[n].GetX() ) && y_position == tanks[n].GetY() /*&& fire_distance_to_tank <= fire_distance_to_wall*/)
                    {
                        TARGET_STRUCK = true;
                        tmp_distance = x_position - tanks[n].GetX() ;
                        if (tmp_distance < fire_distance_to_tank)
                        {
                            fire_distance_to_tank = tmp_distance;
                            nearest_tank = n;
                        }
                    }
                }
                tmp_distance = x_position - 40*(i-1) - 10 ;                    // проверка попадания по стенам
                if (r_walls[i*16+j].GetStatus()>0 && (tmp_distance >= 0) && (tmp_distance <= 200) && (x_position+tmp_distance >= ((i+1)*40 + 10) ) && y_position == (j-1)*40 + 10 && tmp_distance <= fire_distance_to_tank)
                {
                    TARGET_STRUCK = true;
                    fire_distance_to_wall = tmp_distance;
                                for (int k = 0/*i*/; k <= (x_position-10)/40; k++) // считать с другой стороны
                        if (r_walls[k*16+j].GetStatus()>0) i = k;
                    if (isFire) //был ли выстрел
                        r_walls[i*16+j].Struck();
                    return (2);
                }
                break;
            }

            case 270:
            {
                for (int n = 0; n < 9; ++n)     // проверка попадания по танкам
                { tmp_distance = tanks[n].GetY() - y_position;
                    if (this->GetNumber()!=n)
                    if (tanks[n].GetNumber()!=this->GetNumber() && tanks[n].GetStatus()>0 && (tmp_distance >= 0) && (tmp_distance <= 200) && x_position == tanks[n].GetX() )
                    {
                        TARGET_STRUCK = true;
                        tmp_distance = tanks[n].GetY() - y_position;
                        if (tmp_distance < fire_distance_to_tank)
                        {
                            fire_distance_to_tank = tmp_distance;
                            nearest_tank = n;
                        }
                    }
                }
                tmp_distance = 40*(j-1) + 10 - y_position;                    // проверка попадания по стенам
                if (r_walls[i*16+j].GetStatus()>0 && (tmp_distance >= 0) && (tmp_distance <= 200) && (y_position+40+tmp_distance <= (j*40 + 10) ) && x_position == (i-1)*40 + 10 && tmp_distance <= fire_distance_to_tank)
                {
                    TARGET_STRUCK = true;
                    fire_distance_to_wall = tmp_distance;
                    if (isFire) //был ли выстрел
                        r_walls[i*16+j].Struck();
                    return (2);
                }
                break;
            }
            default: break;
        }
    }   
}

    if (TARGET_STRUCK && nearest_tank != -1 && fire_distance_to_wall >= fire_distance_to_tank && fire_distance_to_tank != 1000)
    {
      if (isFire) //был ли выстрел
        tanks[nearest_tank].Struck(paint);
 return (1);
    }
}

void Tank::FireShow(int r_azimuth)
{
    if (this->GetStatus()!=0)   //если не убит
    switch (r_azimuth)
    {
    case 0: {
        label_fire1_0->move(x_position+35, y_position);
        label_fire1_0->show();
       label_fire1_0->repaint();
         Sleep(200);
         label_fire2_0->move(x_position+40, y_position+10);
         label_fire2_0->show();
         label_fire1_0->hide();
        label_fire2_0->repaint();
          Sleep(100);
          label_fire2_0->hide();
        break;
    }
    case 90: {
        label_fire1_90->move(x_position, y_position-15);
        label_fire1_90->show();
        label_fire1_90->repaint();
         Sleep(200);
         label_fire2_90->move(x_position+10, y_position-40);
         label_fire2_90->show();
         label_fire1_90->hide();
        label_fire2_90->repaint();
          Sleep(100);
          label_fire2_90->hide();
        break;
    }
    case 180: {
        label_fire1_180->move(x_position-15, y_position);
        label_fire1_180->show();
        label_fire1_180->repaint();
         Sleep(200);
         label_fire2_180->move(x_position-40, y_position+10);
         label_fire2_180->show();
         label_fire1_180->hide();
        label_fire2_180->repaint();
          Sleep(100);
          label_fire2_180->hide();
        break;
    }
    case 270: {
        label_fire1_270->move(x_position, y_position+25);
        label_fire1_270->show();
        label_fire1_270->repaint();
         Sleep(200);
         label_fire2_270->move(x_position+10, y_position+40);
         label_fire2_270->show();
         label_fire1_270->hide();
        label_fire2_270->repaint();
          Sleep(100);
          label_fire2_270->hide();
        break;
    }
    default: break;
}

}

void Tank::Repaint()
{
       // if (this->GetStatus()!=0)   //если не убит
    label_panzer->repaint();
}

void Tank::SetFireLabels(QLabel &r_label_fire1_0, QLabel &r_label_fire2_0, QLabel &r_label_fire1_90, QLabel &r_label_fire2_90,
                         QLabel &r_label_fire1_180, QLabel &r_label_fire2_180, QLabel &r_label_fire1_270, QLabel &r_label_fire2_270, QLabel &r_label_shell)
{
    QPixmap fire1_0(":/images/fire1_0.png");
    QPixmap fire1_90(":/images/fire1_90.png");
    QPixmap fire1_180(":/images/fire1_180.png");
    QPixmap fire1_270(":/images/fire1_270.png");
    QPixmap fire2_0(":/images/fire2_0.png");
    QPixmap fire2_90(":/images/fire2_90.png");
    QPixmap fire2_180(":/images/fire2_180.png");
    QPixmap fire2_270(":/images/fire2_270.png");

    label_fire1_0 = &r_label_fire1_0;
    label_fire2_0 = &r_label_fire2_0;
    label_fire1_90 = &r_label_fire1_90;
    label_fire2_90 = &r_label_fire2_90;
    label_fire1_180 = &r_label_fire1_180;
    label_fire2_180 = &r_label_fire2_180;
    label_fire1_270 = &r_label_fire1_270;
    label_fire2_270 = &r_label_fire2_270;
    label_shell = &r_label_shell;
}

void Tank::SetLabel(QLabel &l_label)
{
    label_panzer = &l_label;
}

QLabel Tank::GetLabel()
{
   // return *label;
}

void Tank::SetCoordinates(int _x, int _y)
{
    x_position =_x;
    y_position =_y;
    label_panzer->move(_x, _y);
}

void Tank::SetOrient(int l_orient)
{
    azimuth = l_orient;
}

void Tank::GetCoordinates(Paint &paint)
{
    paint.coords[tank_number][0] = x_position;
    paint.coords[tank_number][1] = y_position;
}

void Tank::SetPixmap(QPixmap &pixmap)
{
    label_panzer->setPixmap(pixmap);
    label_panzer->resize( 40, 40 );
    label_panzer->show();
}

void Tank::GetOrient(Paint &paint)
{
    paint.orients[tank_number] = azimuth;
}

int Tank::GetNumber()
{
    return tank_number;
}

void Tank::SetNumber(int number)
{
    tank_number = number;
}

void Tank::SetStatus(int t_status)
{
    tank_status = t_status;
}

int Tank::GetStatus(void)
{
    return tank_status;
}

int Tank::GetX(void)
{
    return x_position;
}

int Tank::GetY(void)
{
    return y_position;
}

void Tank::Struck(Paint &paint)
{
   // QPixmap wall_destroyed(":/images/wall_destroyed.png");
    QPixmap tank_destroyed(":/images/tank_destroyed.png");
   // QPixmap wall(":/images/wall.png");
   // QPixmap ground(":/images/ground.png");
   // QPixmap target(":/images/target.png");
    //this->SetPixmap(wall_destroyed);

    if (tank_status==1)
       {
        label_panzer->setPixmap(tank_destroyed);
        tank_status--;
    }
    //else if (status==0)
    label_panzer->repaint();
    if (tank_number == 0)
    paint.SetWin(-1);
}

void Tank::CheckObjects(int i, int j, Paint &paint, Wall (&r_walls)[0xFF])
{

}
