/************************************
 ***    Главное окно программы    ***
 ************************************/

// Time-stamp: <coinmain.h - 01:28:34 08.11.2005>

#ifndef COINMAIN_H
#define COINMAIN_H

#include <QWidget>

class QSlider;
class QLineEdit;
class QPushButton;
class QLabel;
class QSpinBox;
class QCheckBox;
class QLCDNumber;
class CoinAnim;
class CoinGraph1;
class CoinGraph2;
class CoinGraph3;
class CoinSetup;

class CoinMain : public QWidget
{
     Q_OBJECT

public:
     CoinMain(QWidget *parent = 0);

private slots:
     // Ставим слайдеры на место при изменении текста в LineEdit
     void setVelSliderValue(const QString &newSpeed);
     void setNoiseSliderValue(const QString &newNoise);

     // Меняем текст в LineEditах при перемещении слайдеров
     void setVelEditText(int newSpeed);
     void setNoiseEditText(int newNoise);

     // Пускаем анимацию
     void startAnim();

     void setVelSliderValueD(double x);

     // перетасовываем графики
     void replaceGraphs(bool Replace);
     void replaceGraphs1(bool Replace);

     // обновляем информацию на виджет в связи с изменением настроек
     void updWidgets();

private:
     CoinAnim *coinAnim;
     QSlider *velSlider;
     QSlider *noiseSlider;
     QLineEdit *velEdit;
     QLineEdit *noiseEdit;
     QPushButton *start;
     QPushButton *phase;
     QPushButton *expand;
     QPushButton *setup;
     QLabel *velLabel;
     QLabel *noiseLabel;
     QLabel *countLabel;
     QSpinBox *countBox;
     QLabel *currAngleLabel;
     QLCDNumber *currAngleValueLCD;
     QLabel *currSpeedLabel;
     QLCDNumber *currSpeedValueLCD;
     QLabel *totalOrelLabel;
     QLCDNumber *totalOrelValueLCD;
     QLabel *totalReskaLabel;
     QLCDNumber *totalReskaValueLCD;
     QCheckBox *isRTValues;
     QCheckBox *isRarePainting;
     CoinGraph1 *coinGraph1;
     CoinGraph2 *coinGraph2;
     CoinGraph3 *coinGraph3;
     CoinSetup *coinSetup;
};

#endif
