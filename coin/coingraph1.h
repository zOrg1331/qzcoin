// Time-stamp: <coingraph1.h - 01:32:03 08.11.2005>

#ifndef COINGRAPH1_H
#define COINGRAPH1_H

#include <QWidget>

class QPushButton;
class ZChart;
class ZSimpleSeries;

class CoinGraph1 : public QWidget
{
     Q_OBJECT

public:
     CoinGraph1(QWidget *parent = 0);

public slots:
     // Рисуем вертикальную линию, иллюстрирующую начальную скорость
     void drawSpeedLine(double x);
     void setSpeed(int x);
     // Рисуем вертикальные линии, иллюстрирующие
     // разброс начальных скоростей вследствии влияния шума
     void drawNoiseInt(int x);

private slots:
     void drawAngle();

signals:
     // Изменилась начальная скорость
     void newInitSpeed(double x);

private:
     double oldSpeed;
     int oldNoise;

     ZChart *chart;

     ZSimpleSeries *angleGraph;
     ZSimpleSeries *sideZones;
     ZSimpleSeries *speedMark;
     ZSimpleSeries *noiseInt;

     QPushButton *redraw;
};

#endif
