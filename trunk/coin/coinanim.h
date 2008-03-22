/**************************************************
 *** ������� ������, ���������� �������� ������ ***
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

     // ������������� �������� ��� ��������� �������
     QSize sizeHint() const;

public slots:

     // ������ ��������� ��������
     void setSpeed(int newSpeed);
     // ������ ���
     void setNoise(int newNoise);
     // ������ �������
     void start(int Times, bool showRTValues, bool RarePainting, bool Inside);

private slots:

     // ������� ������
     void moveCoin();

signals:

     // ���������� ��������
     void currSpeedChanged(double currSpeed);
     // ��������� ���� ��������
     void currAngleChanged(double currAngle);
     // ������� ����� ����� �����
     void totalOrelChanged(int totalOrel);
     // ������� ����� ������ �����
     void totalReskaChanged(int totalReska);

protected:

     // ������� �����������
     void paintEvent(QPaintEvent *event);

private:

     // ��������� ��������
     float initSpeed;
     // ���, %
     int noise;
     // ������� ��������
     float currSpeed;
     // ��������� �������� ��� �������� ����
     float noiseInitSpeed;
     // ������� ����
     float angle;
     // ������� ��� ���� "�������"
     int times;
     // ������� ��� �������� "��������" - 1
     int count;
     // ����, ������������ ��� ����������� ��������� start()
     // �������� �� ������ ���� ��� �������
     bool inside;
     // ���������� ��� ��� ������� ���� � ��������
     bool showRTValues;
     // ����� �������� ������ ������ ������� ����� �������?
     bool isRarePainting;
     // ����� �����
     int totalOrel;
     // ����� �����
     int totalReska;
     // ��� ������ ������� ��������� ���?
     bool nowOrel;

     // ��������� ������
     void paintCoin(QPainter &painter);
     // ������� � ��������
     QRect coinRect(QString type) const;
     // ���������� ������ �������
     float getCoord();
     // ������ �������, �� ������� ����� �������
     void calcCoinSide();

     // ��������� ������
     int timerCount;
     QTimer *autoStartTimer;

     // ������������ ��������� �������� � ����������� �� �����������
     void correctInitSpeed();
};

#endif
