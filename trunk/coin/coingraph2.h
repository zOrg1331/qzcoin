// Time-stamp: <coingraph2.h - 01:33:26 08.11.2005>

#ifndef COINGRAPH2_H
#define COINGRAPH2_H

#include <QWidget>

class QLabel;
class QPushButton;
class QLineEdit;
class ZChart;
class ZSimpleSeries;

class CoinGraph2 : public QWidget
{
     Q_OBJECT

public:
     CoinGraph2(QWidget *parent = 0);

public slots:
     // ������ ������������ �����, �������������� ��������� ��������
     void drawSpeedLine(double x);
     // ������ ���
     void setNoise(int noiseNew);

private slots:
     void drawExpect();

signals:
     // ���������� ��������� ��������
     void newInitSpeed(double x);

private:
     QPushButton *redraw;
     QLabel *numStartsLabel;
     QLineEdit *numStartsEdit;

     double oldSpeed;
     int noise;

     ZChart *chart;
     ZSimpleSeries *speedMark;
     ZSimpleSeries *noiseGraph;
};

#endif
