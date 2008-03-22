// Time-stamp: <coinsetup.h - 01:36:15 08.11.2005>

#ifndef COINSETUP_H
#define COINSETUP_H

#include <QWidget>

class QPushButton;
class QLabel;
class QLineEdit;
class QGridLayout;

class CoinSetup : public QWidget
{
     Q_OBJECT

public:
     CoinSetup(QWidget *parent = 0);

public slots:
     // ��������� ��������� ��������
     void updWidgets();

private slots:
     // ��������� ���������
     void setSettings();

signals:
     // �������� �� ��������� ��������
     void settChanged();

private:
     QPushButton *setSett;
     QLabel *wcoefLabel;
     QLabel *noiseLabel;
     QLabel *slomoLabel;
     QLabel *accelLabel;
     QLabel *maxvelLabel;
     QLineEdit *wcoefEdit;
     QLineEdit *noiseEdit;
     QLineEdit *slomoEdit;
     QLineEdit *accelEdit;
     QLineEdit *maxvelEdit;
     QGridLayout *mainLayout;
};

#endif
