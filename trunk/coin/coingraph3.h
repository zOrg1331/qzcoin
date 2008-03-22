// Time-stamp: <coingraph3.h - 01:34:57 08.11.2005>

#ifndef COINGRAPH3_H
#define COINGRAPH3_H

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class ZChart;
class ZSimpleSeries;

class CoinGraph3 : public QWidget
{
     Q_OBJECT

public:
     CoinGraph3(QWidget *parent = 0);

public slots:
     // устанавливаем новое значение шума
     void setNoise(int Noise);

private slots:
     // рисуем фазовый портрет
     void drawPhase();
     // рисуем зону пуска
     void drawStartArea(double, double);

signals:
     // изменилась начальная скорость
     void startSpeedChanged(double x);
     // изменилось соотношение между начальной угловой и линейной скоростями
     void wcoefChanged();

private:
     QPushButton *redraw;
     QVBoxLayout *rightLayout;
     ZChart *chart;
     ZSimpleSeries *borders;
     ZSimpleSeries *defaultLine;
     ZSimpleSeries *orelZones;
     ZSimpleSeries *startArea;

     int noise;
};

#endif
