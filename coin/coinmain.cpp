/**************************************************
 *** ���������� ������� �������� ���� ��������� ***
 **************************************************/

// Time-stamp: <coinmain.cpp - 13:47:54 08.11.2005>

#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QTextCodec>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QSpinBox>
#include <QCheckBox>
#include <QLCDNumber>
#include <QHBoxLayout>

#include "coinmain.h"
#include "coinanim.h"
#include "coingraph1.h"
#include "coingraph2.h"
#include "coingraph3.h"
#include "coinsetup.h"
#include "physic.h"
#include <translate.h>

// ������������� � �������� ������ �������� �������� �������
// ������� ����������, �.�. ��� ����� ����� �� ��������� � ����� ������� ��������
void CoinMain::setVelEditText(int newSpeed)
{
  QString str;
  str.setNum(newSpeed);
  if (velEdit->text() == str) return;
  velEdit->setText(str);
}

// ��. ����, ������ ��������
void CoinMain::setVelSliderValue(const QString &newSpeed)
{
  int value;
  value = newSpeed.toInt();
  if (velSlider->value() == value) return;
  velSlider->setValue(value);
}

void CoinMain::setVelSliderValueD(double x)
{
  velSlider->setValue((int)x);
}

void CoinMain::setNoiseEditText(int newNoise)
{
  QString str;
  str.setNum(newNoise);
  if (noiseEdit->text() == str) return;
  noiseEdit->setText(str);
}

void CoinMain::setNoiseSliderValue(const QString &newNoise)
{
  int value;
  value = newNoise.toInt();
  if (noiseSlider->value() == value) return;
  noiseSlider->setValue(value);
}

// ������� �������
void CoinMain::startAnim()
{
  // ������� ������� ���
  coinAnim->setNoise(noiseSlider->value());
  // �������� � ��������� ��������� countBox->value()
  // � ������: ���������� ������� ���� � ��������, ��� ���
  coinAnim->start(countBox->value(), isRTValues->isChecked(),
		  isRarePainting->isChecked(), false);
}

void CoinMain::replaceGraphs(bool Replace)
{
  if (phase->isChecked()) {
    coinGraph1->setVisible(false);
    coinGraph2->setVisible(false);
    coinGraph3->setVisible(true);
  } else {
    if (expand->isChecked() == true) {
      coinGraph1->setVisible(true);
      coinGraph2->setVisible(true);
      coinGraph3->setVisible(false);
    }
  }
}

void CoinMain::replaceGraphs1(bool Replace)
{
  if (!Replace) {
    coinGraph1->setVisible(false);
    coinGraph2->setVisible(false);
    coinGraph3->setVisible(false);
    phase->setVisible(false);
    phase->setChecked(false);
    setup->setVisible(false);
    setup->setChecked(false);
  } else {
    coinGraph1->setVisible(true);
    coinGraph2->setVisible(true);
    coinGraph3->setVisible(false);
    phase->setVisible(true);
    phase->setChecked(false);
    setup->setVisible(true);
    setup->setChecked(false);
  }
}

void CoinMain::updWidgets()
{
  velSlider->setRange(0, MAXVEL);
  velSlider->setTickInterval((int)(MAXVEL/10));

}

CoinMain::CoinMain(QWidget *parent) : QWidget(parent)
{
  // ����������� ��� ������� ����
  QWidget::setWindowFlags(Qt::WindowMaximizeButtonHint);
  QWidget::setWindowFlags(Qt::WindowMinimizeButtonHint);

  // ������� ����������� �������
  setWindowTitle(translate("�������"));
  coinAnim = new CoinAnim(this);
  coinGraph1 = new CoinGraph1(this);
  coinGraph2 = new CoinGraph2(this);
  coinGraph3 = new CoinGraph3(this);
  coinSetup = new CoinSetup(this);
  velSlider = new QSlider(Qt::Horizontal, this);
  noiseSlider = new QSlider(Qt::Horizontal, this);
  velEdit = new QLineEdit(this);
  noiseEdit = new QLineEdit(this);
  start = new QPushButton(translate("����!"), this);
  phase = new QPushButton(translate("���. �������"), this);
  expand = new QPushButton(translate("����. ���"), this);
  setup = new QPushButton(translate("���������"), this);
  velLabel = new QLabel(translate("���. ��������"), this);
  noiseLabel = new QLabel(translate("������� ����"), this);
  countLabel = new QLabel(translate("���"), this);
  countBox = new QSpinBox(this);
  currAngleLabel = new QLabel(translate("����:"), this);
  currAngleValueLCD = new QLCDNumber(4, this);
  currSpeedLabel = new QLabel(translate("����.:"), this);
  currSpeedValueLCD = new QLCDNumber(4, this);
  totalOrelLabel = new QLabel(translate("����� �����:"), this);
  totalReskaLabel = new QLabel(translate("����� �����:"), this);
  totalOrelValueLCD = new QLCDNumber(2, this);
  totalReskaValueLCD = new QLCDNumber(2, this);
  isRTValues = new QCheckBox(translate("����������\n��������\n� ����"), this);
  isRarePainting = new QCheckBox(translate("��������\n������\n�������"), this);

  // ����������� ������ �����
  start->setDefault(true);
  start->setFont(QFont("Sans Serif", 10, QFont::Bold));
  connect(start, SIGNAL(clicked()), this, SLOT(startAnim()));

  // ����������� ������ ������ �������� ��������
  phase->setAutoDefault(false);
  phase->setFont(QFont("Sans Serif", 10, QFont::Bold));
  phase->setVisible(false);
  phase->setCheckable(true);
  connect(phase, SIGNAL(toggled(bool)), this, SLOT(replaceGraphs(bool)));

  // ����������� ������ ������������ ����
  expand->setAutoDefault(false);
  expand->setFont(QFont("Sans Serif", 10, QFont::Bold));
  expand->setCheckable(true);
  connect(expand, SIGNAL(toggled(bool)), this, SLOT(replaceGraphs1(bool)));

  // ����������� ������ ������ ��������
  setup->setAutoDefault(false);
  setup->setFont(QFont("Sans Serif", 10, QFont::Bold));
  setup->setCheckable(true);
  setup->setVisible(false);
  connect(setup, SIGNAL(toggled(bool)), coinSetup, SLOT(setVisible(bool)));

  // ����������� �������, ������������� �� ��������� ��������
  velSlider->setRange(0, MAXVEL);
  velSlider->setTickInterval((int)(MAXVEL/10));
  velSlider->setTickPosition(QSlider::TicksAbove);
  connect(velSlider, SIGNAL(valueChanged(int)), coinAnim, SLOT(setSpeed(int)));
  connect(velSlider, SIGNAL(valueChanged(int)), this, SLOT(setVelEditText(int)));
  connect(velSlider, SIGNAL(valueChanged(int)),
	  coinGraph1, SLOT(setSpeed(int)));

  // ����������� �������, ������������� �� �����������
  noiseSlider->setRange(0, 100);
  noiseSlider->setTickInterval(10);
  noiseSlider->setTickPosition(QSlider::TicksBelow);
  connect(noiseSlider, SIGNAL(valueChanged(int)), coinAnim, SLOT(setNoise(int)));
  connect(noiseSlider, SIGNAL(valueChanged(int)), coinGraph2, SLOT(setNoise(int)));
  connect(noiseSlider, SIGNAL(valueChanged(int)), this, SLOT(setNoiseEditText(int)));
  connect(noiseSlider, SIGNAL(valueChanged(int)), coinGraph1, SLOT(drawNoiseInt(int)));
  connect(noiseSlider, SIGNAL(valueChanged(int)), coinGraph3, SLOT(setNoise(int)));

  // ����������� LineEdit, ������������� �� ��������� ��������
  QValidator *validator = new QIntValidator(0, 100, this);
  velEdit->setAlignment(Qt::AlignRight);
  velEdit->setMaxLength(3);
  velEdit->setText("0");
  velEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  velEdit->setValidator(validator);
  connect(velEdit, SIGNAL(textChanged(const QString &)), this,
	  SLOT(setVelSliderValue(const QString &)));

  // ����������� LineEdit, ������������� �� �����������
  noiseEdit->setAlignment(Qt::AlignRight);
  noiseEdit->setMaxLength(3);
  noiseEdit->setText("0");
  noiseEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  noiseEdit->setValidator(validator);
  connect(noiseEdit, SIGNAL(textChanged(const QString &)), this,
	  SLOT(setNoiseSliderValue(const QString &)));

  // ����������� ��������
  countBox->setMaximum(1000);
  countBox->setValue(1);

  // ����������� ������� ��������
  coinAnim->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  // ����������� ��������
  isRTValues->setCheckState(Qt::Checked);
  isRarePainting->setCheckState(Qt::Unchecked);
  // isRarePainting->setFont(QFont("Arial", 9, QFont::Normal));

  // ����������� LCD � �������� ��������� � �����
  currSpeedValueLCD->setSmallDecimalPoint(true);
  currSpeedValueLCD->setSegmentStyle(QLCDNumber::Flat);
  currAngleValueLCD->setSmallDecimalPoint(true);
  currAngleValueLCD->setSegmentStyle(QLCDNumber::Flat);
  connect(coinAnim, SIGNAL(currSpeedChanged(double)), currSpeedValueLCD,
	  SLOT(display(double)));
  connect(coinAnim, SIGNAL(currAngleChanged(double)), currAngleValueLCD,
	  SLOT(display(double)));

  // ����������� LCD � ����������� ����� � �����
  totalOrelValueLCD->setSmallDecimalPoint(true);
  totalOrelValueLCD->setSegmentStyle(QLCDNumber::Flat);
  totalReskaValueLCD->setSmallDecimalPoint(true);
  totalReskaValueLCD->setSegmentStyle(QLCDNumber::Flat);
  connect(coinAnim, SIGNAL(totalOrelChanged(int)), totalOrelValueLCD,
	  SLOT(display(int)));
  connect(coinAnim, SIGNAL(totalReskaChanged(int)), totalReskaValueLCD,
	  SLOT(display(int)));

  // �������� �������������� ����� �����
  coinGraph1->setVisible(false);
  coinGraph2->setVisible(false);
  coinGraph3->setVisible(false);
  coinSetup->setVisible(false);

  // ��������� �������� ������ ��������������� ���������� �� ���� ��������
  connect(coinGraph1, SIGNAL(newInitSpeed(double)),
	  coinGraph2, SLOT(drawSpeedLine(double)));
  connect(coinGraph2, SIGNAL(newInitSpeed(double)),
	  coinGraph1, SLOT(drawSpeedLine(double)));
  connect(coinGraph1, SIGNAL(newInitSpeed(double)),
	  this, SLOT(setVelSliderValueD(double)));
  connect(coinGraph3, SIGNAL(startSpeedChanged(double)),
	  coinGraph1, SIGNAL(newInitSpeed(double)));

  // �������� �� ��������� WCOEF ����� ������ � ������� �������������
  connect(coinGraph3, SIGNAL(wcoefChanged()),
	  coinSetup, SLOT(updWidgets()));
  connect(coinGraph3, SIGNAL(wcoefChanged()),
	  this, SLOT(updWidgets()));
  connect(coinSetup, SIGNAL(settChanged()),
	  this, SLOT(updWidgets()));

  // ����������� ��������� ����������
  QGridLayout *topLayout = new QGridLayout;
  topLayout->addWidget(coinAnim, 0, 3, 15, 9);
  topLayout->addWidget(setup, 10, 13, 1, 2);
  topLayout->addWidget(phase, 11, 13, 1, 2);
  topLayout->addWidget(expand, 12, 13, 1, 2);
  topLayout->addWidget(start, 13, 13, 1, 2);
  topLayout->addWidget(countLabel, 14, 14);
  topLayout->addWidget(countBox, 14, 13);
  topLayout->addWidget(currAngleLabel, 11, 0);
  topLayout->addWidget(currAngleValueLCD, 11, 1);
  topLayout->addWidget(currSpeedLabel, 12, 0);
  topLayout->addWidget(currSpeedValueLCD, 12, 1);
  topLayout->addWidget(totalOrelLabel, 13, 0, 1, 2);
  topLayout->addWidget(totalOrelValueLCD, 13, 2);
  topLayout->addWidget(totalReskaLabel, 14, 0, 1, 2);
  topLayout->addWidget(totalReskaValueLCD, 14, 2);
  topLayout->addWidget(isRTValues, 9, 0, 2, 2);
  topLayout->addWidget(isRarePainting, 7, 0, 2, 2);
  topLayout->setMargin(0);

  QGridLayout *bottomLayout = new QGridLayout;
  bottomLayout->addWidget(velLabel, 0, 0);
  bottomLayout->addWidget(velSlider, 0, 1);
  bottomLayout->addWidget(velEdit, 0, 2);
  bottomLayout->addWidget(noiseLabel, 1, 0);
  bottomLayout->addWidget(noiseSlider, 1, 1);
  bottomLayout->addWidget(noiseEdit, 1, 2);
  bottomLayout->setMargin(0);

  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addLayout(topLayout);
  leftLayout->addLayout(bottomLayout);
  leftLayout->setMargin(0);

  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(coinGraph1);
  rightLayout->addWidget(coinGraph2);
  rightLayout->addWidget(coinGraph3);
  rightLayout->setMargin(0);

  QHBoxLayout *mainHLayout = new QHBoxLayout;
  mainHLayout->setSizeConstraint(QLayout::SetFixedSize);
  mainHLayout->addLayout(leftLayout);
  mainHLayout->addLayout(rightLayout);
  mainHLayout->setMargin(0);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  mainLayout->addLayout(mainHLayout);
  mainLayout->addWidget(coinSetup);
  mainLayout->setMargin(0);

  setLayout(mainLayout);
}
