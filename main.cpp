#include "paint.h"
#include <QApplication>

/* Цель игры - провести танк по полю 16х16 до цели и уничтожить ее
 * Команды записываются в очередь и после старта поочередно выполняются
 * Команды - вперед, назад, поворот влево, вправо, огонь (5 клеток)
 *
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Paint w;
    w.show();

    return a.exec();
}
