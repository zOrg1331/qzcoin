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

     // �������� �� ��������� ��������� ��������
     emit newInitSpeed(x);

     // ��� ���������� ��������� ��������, �� � ������� ���� �������� ������������
     if (oldNoise != 0) { drawNoiseInt(oldNoise); }
}

void CoinGraph1::drawNoiseInt(int x)
{
     oldNoise = x;

     // ������ ���������� ������
     noiseInt->clear();
     noiseInt->add(oldSpeed - (NOISEPOWER * x) / 100, 5000);
     noiseInt->add(oldSpeed - (NOISEPOWER * x) / 100, 0);
     noiseInt->add(oldSpeed + (NOISEPOWER * x) / 100, 0);
     noiseInt->add(oldSpeed + (NOISEPOWER * x) / 100, 5000);

     // ������ "������" (�) ������
     chart->update();
}

void CoinGraph1::drawAngle()
{
     angleGraph->clear();
     sideZones->clear();

     // ������������ ��������� ��������
     int vMax = MAXVEL;
     // ����, �� ������� ����������� �������, �������� � ��������� ��������� vT
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
     // ������� ����������� �������
     chart = new ZChart(this);
     redraw = new QPushButton(translate("������������"), this);

     // ����������� ������ �����������
     redraw->setFont(QFont("Sans Serif", 10, QFont::Bold));
     connect(redraw, SIGNAL(clicked()), this, SLOT(drawAngle()));

     // ����������� �������
     chart->setBorderType(0);
     chart->setGraphPanelBorderType(0);
     chart->setMargin(2);
     chart->setSpacing(2);
     chart->setFirstText("");
     chart->setSecondText("����� ���� - ����, ����� ������� ����");
     chart->setTitle("������ ����������� ���� �������� ������� �� ��������� ��������");

     angleGraph = new ZSimpleSeries("Angle");
     angleGraph->setColor(Qt::red);
     chart->addSeries(angleGraph);

     sideZones = new ZSimpleSeries("Side");
     sideZones->setColor(Qt::blue);
     chart->addSeries(sideZones);

     // ������ ������, ������������ �� ����� ���� ���������� �������
     // � ����������� �� ��������� ��������
     drawAngle();

     // ����� ������ ������� ������� �������� �������� �������
     speedMark = new ZSimpleSeries("Speed line");
     speedMark->setColor(Qt::green);
     chart->addSeries(speedMark);
     // ��� �� � ��� ��������� �����������, �.�. ��� ��� - ������� �� �������
     noiseInt = new ZSimpleSeries("Noise interval");
     noiseInt->setColor(Qt::cyan);
     chart->addSeries(noiseInt);

     // ��� �������� ������ �� ������� �������� ������������ ������,
     // �������� ����� ��������� ��������
     connect(chart, SIGNAL(clickCoordX(double)),
	     this, SLOT(drawSpeedLine(double)));

     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(chart);
     mainLayout->addWidget(redraw);
     mainLayout->setMargin(0);

     setLayout(mainLayout);
}
