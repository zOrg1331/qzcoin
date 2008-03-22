// Time-stamp: <coingraph2.cpp - 13:51:24 08.11.2005>

#include <QTextCodec>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QValidator>

#include "coingraph2.h"
#include "physic.h"
#include <zchart.h>
#include <translate.h>

void CoinGraph2::setNoise(int noiseNew)
{
     if (noise != noiseNew) {
	  noise = noiseNew;
     }
}

void CoinGraph2::drawSpeedLine(double x)
{
     if (oldSpeed == x) { return; }
     oldSpeed = x;

     speedMark->clear();
     speedMark->add(x, 0);
     speedMark->add(x, 5000);

     chart->update();

     // �������� �� ��������� ��������� ��������
     emit newInitSpeed(x);
}

void CoinGraph2::drawExpect()
{
     int vMax = MAXVEL;
     chart->setXRange(0, vMax+1);
     chart->setYRange(0, 1);
     // ���������� ���������
     const int numStarts = numStartsEdit->text().toInt();
     // ����, �� ������� ����������� �������, �������� � ��������� ��������� vT
     float angle = 0;
     // ������� ����� ������ ����� ��� �����
     int totalOrel = 0;
     int totalReska = 0;

     // ��������� ������ ������
     noiseGraph->clear();
     for (float vT = 0; vT <= vMax; vT += 0.3) {
	  totalOrel = 0;
	  totalReska = 0;
	  if (noise != 0) {
	       for (int c = 0; c < numStarts; c++) {
		    float rnd = myrand(0, NOISEPOWER);
		    float vTn = vT;
		    if ((int)(myrand(0, 2)) == 0) {
			 vTn += noise * rnd / 100;
		    } else {
			 vTn -= noise * rnd / 100;
		    }
		    angle = 2 * vTn * (WCOEF * vTn) / 9.8;
		    while (angle > 360) {
			 angle -= 360;
		    }
		    if ( ( (angle >= 0) && (angle <= 90) )
			 || ( (angle >= 270) && (angle <= 360) ) ) {
			 ++totalOrel;
		    } else {
			 ++totalReska;
		    }
	       }
	       noiseGraph->add(vT, 1.0-((float)totalReska/(float)numStarts));
	  } else {
	       angle = 2 * vT * (WCOEF * vT) / 9.8;
	       while (angle > 360) {
		    angle -= 360;
	       }
	       if ( ( (angle >= 0) && (angle <= 90) )
		    || ( (angle >= 270) && (angle <= 360) ) ) {
		    ++totalOrel;
	       } else {
		    ++totalReska;
	       }
	       noiseGraph->add(vT, 1.0-((float)totalReska));
	  }
     }

     // ������ "������" (�) ������
     chart->update();
}

CoinGraph2::CoinGraph2(QWidget *parent) : QWidget(parent)
{
     noise = 0;

     // ������� ����������� �������
     chart = new ZChart(this);
     numStartsLabel = new QLabel(translate("���������� ���������:"), this);
     redraw = new QPushButton(translate("������������"), this);
     numStartsEdit = new QLineEdit(this);

     // ����������� ������ �����������
     redraw->setFont(QFont("Sans Serif", 10, QFont::Bold));
     connect(redraw, SIGNAL(clicked()), this, SLOT(drawExpect()));

     // ����������� LineEdit
     QValidator *validator = new QIntValidator(0, 1000, this);
     numStartsEdit->setValidator(validator);
     numStartsEdit->setAlignment(Qt::AlignRight);
     numStartsEdit->setMaxLength(4);
     numStartsEdit->setText("1000");
     numStartsEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

     // ����������� �������
     chart->setBorderType(0);
     chart->setGraphPanelBorderType(0);
     chart->setMargin(2);
     chart->setSpacing(2);
     chart->setFirstText("");
     chart->setSecondText("������ ������� �� ���������� ���������. ��������!");
     chart->setTitle("������ ���-�� ����������� ��������� ���� �� ��������� ��������");

     // �������� ����� ������ ������� ������� ��������
     // � ������ �����������
     speedMark = new ZSimpleSeries("Speed line");
     speedMark->setColor(Qt::green);
     chart->addSeries(speedMark);
     noiseGraph = new ZSimpleSeries("Noise graph");
     noiseGraph->setColor(Qt::magenta);
     chart->addSeries(noiseGraph);

     // �������� ������ �����������
     drawExpect();

     // ��� �������� ������ �� ������� �������� ������������ ������,
     // �������� ����� ��������� ��������
     connect(chart, SIGNAL(clickCoordX(double)),
	     this, SLOT(drawSpeedLine(double)));

     // ����������� ��������� ����������
     QGridLayout *bottomLayout = new QGridLayout;
     bottomLayout->addWidget(redraw, 0, 0, 1, 2);
     bottomLayout->addWidget(numStartsLabel, 0, 3, 1, 2);
     bottomLayout->addWidget(numStartsEdit, 0, 5);
     bottomLayout->setMargin(0);

     QVBoxLayout *rightLayout = new QVBoxLayout;
     rightLayout->addWidget(chart);
     rightLayout->addLayout(bottomLayout);
     rightLayout->setMargin(0);

     setLayout(rightLayout);
}
