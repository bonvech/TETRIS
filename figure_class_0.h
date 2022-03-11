//TETRIS_2022

#ifndef _CLASS_
#define _CLASS_

//Class
//==============================================================================================================================================================
//{
class Figure {
private:
    double x, y; //Координаты центра вращения фигуры
    Figure_type type; //Тип фигуры
    COLORREF color; //Цвет фигуры
    int direction; //Направление фигуры
    bool move = 1;
public:
    Figure(double x0, double y0, Figure_type t, COLORREF c, int d): x(x0), y(y0), type(t), color(c), direction(d) {}
    Figure& operator= (const Figure &f);

    void r_left(); //Функция поворота ввлево
                                                          //В качестве аргумента принимает ссылку на двумерный
                                                          //Массив со статичными фигурами поля.

    void r_right(); //Функция поворота вправо
                                                           //В качестве аргумента принимает ссылку на двумерный
                                                           //Массив со статичными фигурами поля.

    void m_left(); //Функция движения влево
                                                          //В качестве аргумента принимает ссылку на двумерный
                                                          //Массив со статичными фигурами поля.

    void m_right(); //Функция движения вправо
                                                           //В качестве аргумента принимает ссылку на двумерный
                                                           //Массив со статичными фигурами поля.

    void m_down(); //Функция движения вниз
                                                          //В качестве аргумента принимает ссылку на двумерный
                                                          //Массив со статичными фигурами поля.
                                                          //Если не может двигаться то вписывает себя в этот
                                                          //Массив и останавливается

    void set(bool m); //Установка значения переменной движения

    void set(Point p); //Установка координат

    void draw(double s); //Рисование

    void push(); //Фигура вписывает себя в двумерный массив статичных
                                                        //Блоков, ссылка на который является аргументом

    bool check(); //Проверка корректности постановки фигуры
                                                        //На основе информации из массива статичных фигур,
                                                        //Ссылка на который является аргументом


};
//}
//==============================================================================================================================================================


//Initialization
//==============================================================================================================================================================
//{
Figure& Figure::operator= (const Figure &f) {
    x = f.x;
    y = f.y;
    type = f.type;
    color = f.color;
    direction = f.direction;
    move = f.move;
    return *this;
}

void Figure::r_left() {
    int new_direction = (direction + 3) % 4;
    Figure cpy(x, y, type, color, new_direction);
    if (cpy.check())
        direction = new_direction;
}

void Figure::r_right() {
    int new_direction = (direction + 5) % 4;
    Figure cpy(x, y, type, color, new_direction);
    if (cpy.check())
        direction = new_direction;
}

void Figure::m_left() {
    Figure cpy(x - BLOCK_SIZE, y, type, color, direction);
    if(cpy.check())
        x = x - BLOCK_SIZE;
}

void Figure::m_right() {
    Figure cpy(x + BLOCK_SIZE, y, type, color, direction);
    if(cpy.check())
        x = x + BLOCK_SIZE;
}

void Figure::m_down() {
    Figure cpy(x, y + BLOCK_SIZE, type, color, direction);
    if(cpy.check()) {
        y = y + BLOCK_SIZE;
    }
    else {
        move = 0;
        push();
    }
}

void Figure::set(bool m) {
    move = m;
}

void Figure::set(Point p) {
    x = p.x;
    y = p.y;
}

void Figure::draw(double s = 1) {
    for (auto k : dict[type][direction]) {
        sqr_draw({x + k.x * BLOCK_SIZE, y + k.y * BLOCK_SIZE}, color, s);
    }
}

void Figure::push() {
    for (auto k : dict[type][direction]) {
        double X = x + k.x * BLOCK_SIZE;
        double Y = y + k.y * BLOCK_SIZE;
        X -= X_LEFT - BLOCK_SIZE * 3;
        Y -= Y_UP;
        int j = (int) (X) / BLOCK_SIZE;
        int i = (int) (Y) / BLOCK_SIZE;
        static_arr[i][j].first = 1;
        static_arr[i][j].second = color;
    }
}

bool Figure::check() {
    bool ans = 1;
    for (auto k : dict[type][direction]) {
        double X = x + k.x * BLOCK_SIZE;
        double Y = y + k.y * BLOCK_SIZE;
        X -= X_LEFT - BLOCK_SIZE * 3;
        Y -= Y_UP;
        int j = (int) (X) / BLOCK_SIZE;
        int i = (int) (Y) / BLOCK_SIZE;
        //cout << i << " " << j << "\n";
        if(static_arr[i][j].first)
            ans = 0;
    }
    return ans;
}
//}
//==============================================================================================================================================================
#endif
