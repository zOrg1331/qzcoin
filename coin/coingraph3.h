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
     // ������������� ����� �������� ����
     void setNoise(int Noise);

private slots:
     // ������ ������� �������
     void drawPhase();
     // ������ ���� �����
     void drawStartArea(double, double);

signals:
     // ���������� ��������� ��������
     void startSpeedChanged(double x);
     // ���������� ����������� ����� ��������� ������� � �������� ����������
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
