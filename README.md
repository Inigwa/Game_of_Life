# Game of Life(2 - версия)

## Описание
Это реализация игры "Игра Жизнь" на C++ с использованием библиотеки SDL2. Игрок может расставлять клетки вручную и наблюдать за их развитием.

## Требования
- CMake 3.10+
- Компилятор с поддержкой C++17
- SDL2

## Сборка и запуск
В команднной строке на линукс 
(интерпритатор bash)
идем по адресу где расположен файл
1. mkdir build - создаем директорию билд
2. cd build - заходим в неё
3. cmake .. - компиляция файлов рабочего проекта
4. make - создание файлов рабочего проекта и исполняемого файла
5. ./GameOfLife2 - запуск исполняемого файла

## Управление и настройки
Оживить/убить клетку = левая кнопка мыши,
Поставить игру на паузу = "P",
--------
Внутри файла main.cpp 
1. CALL_SIZE определяет размер клетки ,номинально (10)
2. GRID_WIDTH определяет ширину игрового поля ,номинально (800)
3. GRID_HEIGHT определяет высоту игрового поля ,номинальна (600)
4. SDL_DELAY определяет скорость игры ,номинально (100)
### Установка SDL2
На Ubuntu:
интерпритатор bash
sudo apt-get install libsdl2-dev
