// Time-stamp: <coingraph1.cpp - 13:49:04 08.11.2005>

#include <QTextCodec>
#include <QVBoxLayout>
#include <QPushButton>

#include "coingraph1.h"
#include "physic.h"
#include <zchart.h>
#include <translate.h>

void CoinGraph1::setSpeed(int x)
{
     drawSpeedLine((double)x);
}

void CoinGraph1::drawSpeedLine(double x)
{
     if (oldSpeed == x) { return; }
     oldSpeed = x;

     speedMark->clear();
     speedMark->add(x, 0);
     speedMark->add(x, 5000);

     chart->update();

     // Сообщаем об изменении начальной скорости
     emit newInitSpeed(x);

     // Раз изменилась начальная скорость, то и влияние шума придется пересмотреть
     if (oldNoise != 0) { drawNoiseInt(oldNoise); }
}

void CoinGraph1::drawNoiseInt(int x)
{
     oldNoise = x;

     // Задаем координаты прямых
     noiseInt->clear();
     noiseInt->add(oldSpeed - (NOISEPOWER * x) / 100, 5000);
     noiseInt->add(oldSpeed - (NOISEPOWER * x) / 100, 0);
     noiseInt->add(oldSpeed + (NOISEPOWER * x) / 100, 0);
     noiseInt->add(oldSpeed + (NOISEPOWER * x) / 100, 5000);

     // Строим "кривуя" (с) Евдрон
     chart->update();
}

void CoinGraph1::drawAngle()
{
     angleGraph->clear();
     sideZones->clear();

     // Максимальная начальная скорость
     int vMax = MAXVEL;
     // Угол, на который повернулась монетка, пущенная с начальной скоростью vT
     long double angle = 0, angleOld = 0;
     for (long double vT  = 0; vT <= vMax; vT += 0.1) {
	  angle = 2.0 * vT * (WCOEF * vT) / 9.8;
	  angleGraph->add(vT, angle);
	  angleOld = angle;
	  while (angle > 360) {
	       angle -= 360;
	  }
	  if ( ( (angle >= 0) && (angle <= 90) )
	       || ( (angle >= 270) && (angle <= 360) ) ) {
	       sideZones->add(vT, angleOld-1);
	       sideZones->add(vT, 0);
	  } else {
	       sideZones->add(vT, 0);
	  }
     }
     chart->setXRange(0, MAXVEL+1);
     chart->setYRange(0, 2.0*MAXVEL*(WCOEF*MAXVEL)/9.8);
     chart->update();
}

CoinGraph1::CoinGraph1(QWidget *parent) : QWidget(parent)
{
     // Создаем необходимые виджеты
     chart = new ZChart(this);
     redraw = new QPushButton(translate("Перерисовать"), this);

     // Настраиваем кнопку перерисовки
     redraw->setFont(QFont("Sans Serif", 10, QFont::Bold));
     connect(redraw, SIGNAL(clicked()), this, SLOT(drawAngle()));

     // настраиваем плоттер
     chart->setBorderType(0);
     chart->setGraphPanelBorderType(0);
     chart->setMargin(2);
     chart->setSpacing(2);
     chart->setFirstText("");
     chart->setSecondText("синяя зона - зона, когда выпадет орел");
     chart->setTitle("График зависимости угла поворота монетки от начальной скорости");

     angleGraph = new ZSimpleSeries("Angle");
     angleGraph->setColor(Qt::red);
     chart->addSeries(angleGraph);

     sideZones = new ZSimpleSeries("Side");
     sideZones->setColor(Qt::blue);
     chart->addSeries(sideZones);

     // Строим кривую, показывающую на какой угол повернется монетка
     // в зависимости от начальной скорости
     drawAngle();

     // Серию данных маркера текущей скорости создадим заранее
     speedMark = new ZSimpleSeries("Speed line");
     speedMark->setColor(Qt::green);
     chart->addSeries(speedMark);
     // Так же и для интервала погрешности, т.к. все это - реакция на события
     noiseInt = new ZSimpleSeries("Noise interval");
     noiseInt->setColor(Qt::cyan);
     chart->addSeries(noiseInt);

     // При кликании мышкой по графику рисуется вертикальная прямая,
     // задающая новую начальную скорость
     connect(chart, SIGNAL(clickCoordX(double)),
	     this, SLOT(drawSpeedLine(double)));

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(chart);
     mainLayout->addWidget(redraw);
     mainLayout->setMargin(0);

     setLayout(mainLayout);
}
