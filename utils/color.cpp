HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);  // получение дескриптора
// окна консоли
// перечисление доступных цветов
enum class color : unsigned short
{
    black, blue, green, cyan, red, magenta, brown, lightgray, darkgray,
    lightblue, lightgreen, lightcyan, lightred, lightmagenta, yellow, white
};
// меняет цвет в консоли на указанный
// foreground - цвет текста
// background - цвет фона
void set_col(color foreground, color background)
{
    SetConsoleTextAttribute(
        hout,   // дескриптор окна консоли в котором необходимо изменить цвет
        ((short)background << 4) | (short)foreground); // флаг
    // в котором закодирован необходимые цвета
    // (short)background << 4 - приводим к типу short и смещаем на 4 бита влево
    // (short)foreground - приводим к типу short и объединяем бинарным или |
}