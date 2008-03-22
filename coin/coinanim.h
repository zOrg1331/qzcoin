/**************************************************
 *** Создаем виджет, содержащий анимацию монеты ***
 **************************************************/

// Time-stamp: <coinanim.h - 01:12:58 08.11.2005>

#ifndef COINANIM_H
#define COINANIM_H

#include <QWidget>

class QTimer;

class CoinAnim : public QWidget
{
     Q_OBJECT

public:
     CoinAnim(QWidget *parent = 0);

     // Перехватываем контроль над размерами виджета
     QSize sizeHint() const;

public slots:

     // Задаем начальную скорость
     void setSpeed(int newSpeed);
     // Задаем шум
     void setNoise(int newNoise);
     // Запуск монетки
     void start(int Times, bool showRTValues, bool RarePainting, bool Inside);

private slots:

     // Двигаем монету
     void moveCoin();

signals:

     // Изменилась скорость
     void currSpeedChanged(double currSpeed);
     // Изменился угол поворота
     void currAngleChanged(double currAngle);
     // Монетка упала орлом вверх
     void totalOrelChanged(int totalOrel);
     // Монетка упала решкой вверх
     void totalReskaChanged(int totalReska);

protected:

     // Собитие перерисовки
     void paintEvent(QPaintEvent *event);

private:

     // Начальная скорость
     float initSpeed;
     // Шум, %
     int noise;
     // текущая скорость
     float currSpeed;
     // начальная скорость под влиянием шума
     float noiseInitSpeed;
     // текущий угол
     float angle;
     // сколько раз надо "прыгать"
     int times;
     // сколько раз осталось "прыгнуть" - 1
     int count;
     // флаг, показывающий как запустилась процедура start()
     // нажатием на кнопку Пуск или изнутри
     bool inside;
     // показывать или нет текущие угол и скорость
     bool showRTValues;
     // может рисовать только каждый десятый полет монетки?
     bool isRarePainting;
     // Всего орлов
     int totalOrel;
     // Всего решек
     int totalReska;
     // Как выпала монетка последний раз?
     bool nowOrel;

     // Отрисовка монеты
     void paintCoin(QPainter &painter);
     // Область с монеткой
     QRect coinRect(QString type) const;
     // Координата центра монетки
     float getCoord();
     // Расчет стороны, на которую упала монетка
     void calcCoinSide();

     // Добавляем таймер
     int timerCount;
     QTimer *autoStartTimer;

     // Корректируем начальную скорость в зависимости от погрешности
     void correctInitSpeed();
};

#endif
