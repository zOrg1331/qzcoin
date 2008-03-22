// Time-stamp: <coinsetup.cpp - 01:32:27 09.11.2005>

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextCodec>

#include "coinsetup.h"
#include "physic.h"
#include <zchart.h>
#include <translate.h>

void CoinSetup::setSettings()
{
     WCOEF = wcoefEdit->text().toFloat();
     NOISEPOWER = noiseEdit->text().toFloat();
     SLOMO = slomoEdit->text().toFloat();
     STARTACCEL = accelEdit->text().toFloat();
     MAXVEL = maxvelEdit->text().toInt();

     emit settChanged();
}

void CoinSetup::updWidgets()
{
     QString str = "";
     wcoefEdit->setText(str.setNum(WCOEF));
     noiseEdit->setText(str.setNum(NOISEPOWER));
     slomoEdit->setText(str.setNum(SLOMO));
     accelEdit->setText(str.setNum(STARTACCEL));
     maxvelEdit->setText(str.setNum(MAXVEL));
}

CoinSetup::CoinSetup(QWidget *parent) : QWidget(parent)
{
     // Создаем необходимые виджеты
     setSett = new QPushButton(translate("Применить настройки"), this);
     wcoefLabel = new QLabel(translate("угл. ск-ть/лин. ск-ть"));
     noiseLabel = new QLabel(translate("коэфф. влияния шума"));
     slomoLabel = new QLabel(translate("виз. зам. вращ. монетки"));
     accelLabel = new QLabel(translate("виз. уск. полет монетки"));
     maxvelLabel = new QLabel(translate("макс. ск-ть монетки"));
     wcoefEdit = new QLineEdit(this);
     noiseEdit = new QLineEdit(this);
     slomoEdit = new QLineEdit(this);
     accelEdit = new QLineEdit(this);
     maxvelEdit = new QLineEdit(this);

     // устанавливаем tooltipы
     wcoefLabel->setToolTip(translate("Отношение начальной угловой скорости к\nначальной линейной скорости"));
     wcoefEdit->setToolTip(translate("Отношение начальной угловой скорости к\nначальной линейной скорости"));
     noiseLabel->setToolTip(translate("Константа определяет \"силу\" влияния шума\nна значение начальной линейной скорости"));
     noiseEdit->setToolTip(translate("Константа определяет \"силу\" влияния шума\nна значение начальной линейной скорости"));
     slomoLabel->setToolTip(translate("Величина визуального замедления вращения монетки\nНа расчеты не влияет\nДля \"физичного\" процесса надо устанавливать значение \"1\""));
     slomoEdit->setToolTip(translate("Величина визуального замедления вращения монетки\nНа расчеты не влияет\nДля \"физичного\" процесса надо устанавливать значение \"1\""));
     accelLabel->setToolTip(translate("Величина визуального ускорения полета монетки\nНа расчеты не влияет\nДля \"физичного\" процесса надо устанавливать значение \"1\""));
     accelEdit->setToolTip(translate("Величина визуального ускорения полета монетки\nНа расчеты не влияет\nДля \"физичного\" процесса надо устанавливать значение \"1\""));
     maxvelLabel->setToolTip(translate("Максимальная линейная скорость запуска монетки (м/с)"));
     maxvelEdit->setToolTip(translate("Максимальная линейная скорость запуска монетки (м/с)"));

     // Настраиваем кнопку перерисовки
     setSett->setFont(QFont("Sans Serif", 10, QFont::Bold));
     connect(setSett, SIGNAL(clicked()), this, SLOT(setSettings()));

     QString str = "";

     wcoefEdit->setAlignment(Qt::AlignRight);
     wcoefEdit->setMaxLength(3);
     wcoefEdit->setText(str.setNum(WCOEF));
     wcoefEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
     noiseEdit->setAlignment(Qt::AlignRight);
     noiseEdit->setMaxLength(3);
     noiseEdit->setText(str.setNum(NOISEPOWER));
     noiseEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
     slomoEdit->setAlignment(Qt::AlignRight);
     slomoEdit->setMaxLength(3);
     slomoEdit->setText(str.setNum(SLOMO));
     slomoEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
     accelEdit->setAlignment(Qt::AlignRight);
     accelEdit->setMaxLength(3);
     accelEdit->setText(str.setNum(STARTACCEL));
     accelEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
     maxvelEdit->setAlignment(Qt::AlignRight);
     maxvelEdit->setMaxLength(3);
     maxvelEdit->setText(str.setNum(MAXVEL));
     maxvelEdit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

     QGridLayout *mainLayout = new QGridLayout;
     mainLayout->addWidget(wcoefLabel, 0, 0, 1, 2);
     mainLayout->addWidget(noiseLabel, 1, 0, 1, 2);
     mainLayout->addWidget(slomoLabel, 0, 3, 1, 2);
     mainLayout->addWidget(accelLabel, 1, 3, 1, 2);
     mainLayout->addWidget(maxvelLabel, 0, 6, 1, 2);
     mainLayout->addWidget(wcoefEdit, 0, 2);
     mainLayout->addWidget(noiseEdit, 1, 2);
     mainLayout->addWidget(slomoEdit, 0, 5);
     mainLayout->addWidget(accelEdit, 1, 5);
     mainLayout->addWidget(maxvelEdit, 0, 8);
     mainLayout->addWidget(setSett, 1, 6, 1, 3);
     mainLayout->setMargin(0);

     setLayout(mainLayout);
}
