// Time-stamp: <coingraph3.cpp - 01:31:11 09.11.2005>

#include <QPushButton>
#include <QVBoxLayout>
#include <QTextCodec>

#include "coingraph3.h"
#include "physic.h"
#include <zchart.h>
#include <translate.h>

void CoinGraph3::setNoise(int Noise)
{
     if (noise == Noise) { return; }
     noise = Noise;
}

void CoinGraph3::drawStartArea(double x, double y)
{
     startArea->clear();
     startArea->add(x-(noise*x/100)-(0.02*MAXVEL), y-(0.02*MAXVEL));
     startArea->add(x-(noise*x/100)-(0.02*MAXVEL), y+(0.02*MAXVEL));
     startArea->add(x+(noise*x/100)+(0.02*MAXVEL), y+(0.02*MAXVEL));
     startArea->add(x+(noise*x/100)+(0.02*MAXVEL), y-(0.02*MAXVEL));
     startArea->add(x-(noise*x/100)-(0.02*MAXVEL), y-(0.02*MAXVEL));
     chart->update();
     // ��������� ����������� ����� ��������� ������� � �������� ����������
     WCOEF = y/x;
     emit wcoefChanged();
     emit startSpeedChanged(x);
}

void CoinGraph3::drawPhase()
{
     borders->clear();
     orelZones->clear();
     defaultLine->clear();
     // ������ ������� ��������� ���������� �����������
     // 100 - ������� ��� ����� �������� (������������, �������������)
     for (int j = 0; j <= 100; j += 1) {
	  borders->add(MAXVEL, 0);
	  borders->add(0, 0);
	  orelZones->add(MAXVEL, 0);
	  orelZones->add(0, 0);
	  // ���� �� ��� ��������� �������� ���������
	  for (float vT = 0; vT <= MAXVEL; vT += 0.2) {
	       // ����������� �������:
	       // alpha = 2*w0*v0/g = i*pi/2
	       // ������ ������� ��������� ����������:
	       // w0 = i*pi*g/(4*v0)
	       // i = 0, 1, 2, 3..., pi � ��������!
	       float w = j*180*9.8/(4*vT);
	       borders->add(vT, w);
	       if (vT == MAXVEL) {
		    borders->add(vT, 0);
		    borders->add(0, 0);
	       }
	       // ����������� ����, ����� ������� ����
	       if ((j % 2) != 0) {
		    orelZones->add(vT, (j-1)*180*9.8/(4*vT));
		    orelZones->add(vT, w);
	       }
	  }
     }
     // ������ ����� ������������ ����������� ����� ��������� ������� � �������� ����������
     defaultLine->add(0, 0);
     defaultLine->add(MAXVEL, MAXVEL*WCOEF);
     chart->update();
}

CoinGraph3::CoinGraph3(QWidget *parent) : QWidget(parent)
{
     // ������� ����������� �������
     chart = new ZChart(this);
     redraw = new QPushButton(translate("������������"), this);

     // ����������� ������ �����������
     redraw->setFont(QFont("Sans Serif", 10, QFont::Bold));
     connect(redraw, SIGNAL(clicked()), this, SLOT(drawPhase()));

     // ����������� �������
     chart->setBorderType(0);
     chart->setGraphPanelBorderType(0);
     chart->setMargin(2);
     chart->setSpacing(2);
     chart->setFirstText("");
     chart->setSecondText("��� ������� - ��������� �������� ��������, ������� - �������");
     chart->setTitle("�������� ����������");
     chart->setXRange(0, MAXVEL);
     chart->setYRange(0, WCOEF*MAXVEL);

     // �������� ����� ������ ������� ������� ��������
     // � ������ �����������
     borders = new ZSimpleSeries("Borders between the valleys of attraction");
     borders->setColor(Qt::red);
     chart->addSeries(borders);
     defaultLine = new ZSimpleSeries("Default coeff between v and w");
     defaultLine->setColor(Qt::magenta);
     chart->addSeries(defaultLine);
     orelZones = new ZSimpleSeries("Zones when orel respawns");
     orelZones->setColor(Qt::blue);
     chart->addSeries(orelZones);
     chart->addSeries(defaultLine);
     startArea = new ZSimpleSeries("Start interval");
     startArea->setColor(Qt::black);
     chart->addSeries(startArea);

     drawPhase();

     // ��� �������� ������ �� ������� �������� �������,
     // �������� ��������� �������� � ������� ��������,
     // ������������ ������� ������� ����
     connect(chart, SIGNAL(clickCoord(double, double)),
	     this, SLOT(drawStartArea(double, double)));

     QVBoxLayout *rightLayout = new QVBoxLayout;
     rightLayout->addWidget(chart);
     rightLayout->addWidget(redraw);
     rightLayout->setMargin(0);

     setLayout(rightLayout);
}
