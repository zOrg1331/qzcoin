/****************************************************
 ****   Главный модуль программы демонстрации полета ****
 ****   монетки с учетом вероятностных эффектов             ****
 ****************************************************/
// Time-stamp: <main.cpp - 01:43:18 08.11.2005>

#include <QApplication>
#include <QPlastiqueStyle>

#include "coinmain.h"

int main(int argc, char *argv[])
{
     QApplication app(argc, argv);
     QApplication::setStyle(new QPlastiqueStyle);
     QFont defaultFont("Sans Serif", 10, QFont::Normal);
     defaultFont.setPointSize(10);
     QApplication::setFont(defaultFont);

     CoinMain *coinMain = new CoinMain;

     coinMain->setGeometry(0, 20, 300, 550);
     coinMain->show();
     return app.exec();
}
