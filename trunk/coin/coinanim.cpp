/***********************************
 *** ���������� �������� ������� ***
 ***********************************/

// Time-stamp: <coinanim.cpp - 01:16:26 08.11.2005>

#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QDateTime>

#include <math.h>

#include "coinanim.h"
#include "physic.h"

CoinAnim::CoinAnim(QWidget *parent) : QWidget(parent)
{
     // ��������� ������
     autoStartTimer = new QTimer(this);
     // �� ������ ��� ������� ������� �������
     connect(autoStartTimer, SIGNAL(timeout()), this, SLOT(moveCoin()));
     // ���� ����
     setPalette(QPalette(QColor(50, 220, 225)));
     // ������������� ����������
     initSpeed = 0;
     noise = 0;
     currSpeed = 0;
     noiseInitSpeed = 0;
     angle = 0;
     count = 0;
     showRTValues = true;
     totalOrel = 0;
     totalReska = 0;
     nowOrel = true;
     timerCount = 0;
}

QSize CoinAnim::sizeHint() const
{
     // ����������� ������ ������� ��������
     // ��. coinAnim QSizePolicy � coinmain.cpp
     QSize size;
     size = QSize(160, 500);
     return size;
}

// ������ ����� �������� ����� �������
void CoinAnim::setSpeed(int newSpeed)
{
     if (initSpeed == newSpeed) return;
     // �������� ��������� �������� ������ ���� ������ "������"
     if (autoStartTimer->isActive()) { return; }
     initSpeed = newSpeed;
}

// ������ ����� �������� �����������
void CoinAnim::setNoise(int newNoise)
{
     if (noise == newNoise) return;
     // �������� ��� ������ ���� ������ "������"
     if (autoStartTimer->isActive()) { return; }
     noise = newNoise;
}

// ��������� ����� �������� ����� �������
void CoinAnim::calcCoinSide()
{
     // �� ��������, ����� ������ ���� ������ angle,
     // �� ��� ��� �� ���������� ��������� ������������� ����� �������,
     // ���������� ���������� :)
     // �.�. �������������� ����, ��� ������� ������� ������ ������ �� ���,
     // ������ �� ��������� ��������
     float ugol = 2 * noiseInitSpeed * (WCOEF * noiseInitSpeed) / 9.8; //angle;
     while (ugol > 360) { ugol -= 360; }
     // � ����������� �� ����, ��� ����� ����� ������� ��������� ����,
     // ����������, �� ����� ������� ��� �����
     if (((ugol >= 0) && (ugol <= 90))
	  || ((ugol >= 270) && (ugol <= 360))) {
	  ++totalOrel; // ����������� ����� ���������� �������� �����
	  nowOrel = true; // ���� ������, ��� ����� ����
	  emit totalOrelChanged(totalOrel); // �������� ��������������� ������
     } else {
	  ++totalReska;
	  nowOrel = false;
	  emit totalReskaChanged(totalReska);
     }
}

// ������������ ��������� �������� � ����������� �� �����������
void CoinAnim::correctInitSpeed()
{
     noiseInitSpeed = initSpeed;
     float rnd = myrand(0, NOISEPOWER);
     // ��������� ������� ���������� ����������� �������� ��� ���������
     if (((int)(myrand(0, 2))) == 0) {
	  // ����������� �������� �� ������� �� ��������������� ���� ��������� ��������
	  noiseInitSpeed += noise * rnd / 100;
     } else {
	  noiseInitSpeed -= noise * rnd / 100;
     }
}

// ������� �������
void CoinAnim::start(int Times, bool showRTV, bool RarePainting, bool Inside)
{
     // �������� ������ ���� ������ "������"
     if (autoStartTimer->isActive()) { return; }
     showRTValues = showRTV;
     isRarePainting = RarePainting;
     angle = 0;
     currSpeed = 0;
     noiseInitSpeed = 0;

     correctInitSpeed();

     emit totalOrelChanged(totalOrel);
     emit totalReskaChanged(totalReska);

     if (!Inside) { times = Times; }
     count = Times - 1;
     inside = Inside;
     timerCount = 0;
     autoStartTimer->start(5);
}

// ������� ���������� ��������� ���������� ������ �������
float CoinAnim::getCoord()
{
     // ���������� ������ �� SLOMO, ����� ������� ��������� �� ��� ������,
     // �� ��-�� ����� �� ���������� ��������� ������������� ����� �������
     float time = timerCount / SLOMO;
     float y0 = rect().height();
     // ��������� �� STARTACCEL, ����� ������� �������� ���� ���� �� ��������� ���������
     // ��-�� ����� �����-���� �������� ����������� ����������� �������������
     float y = y0 - STARTACCEL * noiseInitSpeed * time + 0.5 * 9.8 * time * time;
     currSpeed = noiseInitSpeed - 9.8 * time;
     angle = WCOEF * noiseInitSpeed * time;
     // �������� ������� � ����� ������� �������� ������ ��� ��������� ������
     if ((count == 0) && (showRTValues)) {
	  emit currSpeedChanged(fabs(currSpeed));
     }
     return y;
}

void CoinAnim::moveCoin()
{
     // ��������� ����
     ++timerCount;
     // ���� ����� �� ������� - ������������� �������
     // ���������, ��� "�������", ��������, �������� ��������� ���
     // ��������� � ��������� �� ������� �������� ���� �����
     // ���� �� ������������ ������� �������� ������ �� ������ ������� �������,
     // �� ��, ����� ����, ��� �� ����� ţ ��������, �� ����� ţ � �������!
     if ((((getCoord() + 30 * sin(angle)) > rect().height()) && (currSpeed < 0))
	 || (isRarePainting
	     && (((times - count) % 10) != 0) && (count != (times - 1)) && (count != 0))) {
	  if (count == 0) {
	       autoStartTimer->stop();
	       calcCoinSide();
	       totalOrel = 0;
	       totalReska = 0;
	       angle = 0;
	       emit currSpeedChanged(0);
	       emit currAngleChanged(0);
	  } else {
	       // ���� ���� ���, �� ������������� ������ � ��������� ��� ���
	       autoStartTimer->stop();
	       calcCoinSide();
	       angle = 0;
	       update();
	       start(count, showRTValues, isRarePainting, true);
	  }
     }
     // �������������� �������
     update();
}


void CoinAnim::paintEvent(QPaintEvent *)
{
     // �������������� Painter
     QPainter painter(this);
     // �������� �����������
     painter.setRenderHint(QPainter::Antialiasing);
     // ������ �������
     paintCoin(painter);
}

void CoinAnim::paintCoin(QPainter &painter)
{
     // ��������� �������
     if (autoStartTimer->isActive()) {
	  // �������� ������ ������� ������� � ������
	  if (isRarePainting) {
	       if ((((times - count) % 10) == 0) || (count == (times - 1)) || (count == 0)) {
		    // ���������� ������ ��������� � ����� �������
		    painter.translate(rect().width() / 2, getCoord());
		    // ��������� ���������
		    painter.save();
		    // ������������ ������������ �������
		    painter.rotate(angle);
		    // �������� ������� ������ ��� ��������� ������
		    if ((count == 0) && (showRTValues)) {
			 emit currAngleChanged(angle);
		    }
	       }
	  } else {
	       // ���������� ������ ��������� � ����� �������
	       painter.translate(rect().width() / 2, getCoord());
	       // ��������� ���������
	       painter.save();
	       // ������������ ������������ �������
	       painter.rotate(angle);
	       // �������� ������� ������ ��� ��������� ������
	       if ((count == 0) && (showRTValues)) {
		    emit currAngleChanged(angle);
	       }
	  }
     } else {
	  // �������� ���������� �������
	  painter.translate(rect().width() / 2, rect().height() - 6);
	  painter.save();
     }
     // ������ �������
     if (isRarePainting) {
	  if ((((times - count) % 10) == 0) || (count == (times - 1)) || (count == 0)) {
	       if (nowOrel) {
		    painter.setPen(Qt::NoPen);
		    painter.setBrush(Qt::blue);
		    painter.drawRect(coinRect("top"));

		    painter.setPen(Qt::NoPen);
		    painter.setBrush(Qt::red);
		    painter.drawRect(coinRect("bottom"));
	       } else {
		    painter.setPen(Qt::NoPen);
		    painter.setBrush(Qt::red);
		    painter.drawRect(coinRect("top"));

		    painter.setPen(Qt::NoPen);
		    painter.setBrush(Qt::blue);
		    painter.drawRect(coinRect("bottom"));
	       }
	       // ��������������� ���������
	       painter.restore();
	  }
     } else {
	  if (nowOrel) {
	       painter.setPen(Qt::NoPen);
	       painter.setBrush(Qt::blue);
	       painter.drawRect(coinRect("top"));

	       painter.setPen(Qt::NoPen);
	       painter.setBrush(Qt::red);
	       painter.drawRect(coinRect("bottom"));
	  } else {
	       painter.setPen(Qt::NoPen);
	       painter.setBrush(Qt::red);
	       painter.drawRect(coinRect("top"));

	       painter.setPen(Qt::NoPen);
	       painter.setBrush(Qt::blue);
	       painter.drawRect(coinRect("bottom"));
	  }
	  // ��������������� ���������
	  painter.restore();
     }
}

QRect CoinAnim::coinRect(QString type) const
{
     // ������ ���������� ��������� �������
     if (type == "top") {
	  QRect result(-30, -6, 60, 6);
	  return result;
     } else {
	  QRect result(-30, 0, 60, 6);
	  return result;
     }
}
