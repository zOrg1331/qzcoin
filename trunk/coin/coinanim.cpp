/***********************************
 *** Реализация анимации монетки ***
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
     // Вставляем таймер
     autoStartTimer = new QTimer(this);
     // На каждий тик таймера двигаем монетку
     connect(autoStartTimer, SIGNAL(timeout()), this, SLOT(moveCoin()));
     // Цвет фона
     setPalette(QPalette(QColor(50, 220, 225)));
     // Инициализация переменных
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
     // Минимальный размер виджета анимации
     // см. coinAnim QSizePolicy в coinmain.cpp
     QSize size;
     size = QSize(160, 500);
     return size;
}

// Задаем новую скорость пуска монетки
void CoinAnim::setSpeed(int newSpeed)
{
     if (initSpeed == newSpeed) return;
     // Изменяем начальную скорость только если таймер "молчит"
     if (autoStartTimer->isActive()) { return; }
     initSpeed = newSpeed;
}

// Задаем новую величину погрешности
void CoinAnim::setNoise(int newNoise)
{
     if (noise == newNoise) return;
     // Изменяем шум только если таймер "молчит"
     if (autoStartTimer->isActive()) { return; }
     noise = newNoise;
}

// Вычисляем какой сторогой упала монетка
void CoinAnim::calcCoinSide()
{
     // по хорошему, здесь должен быть просто angle,
     // но так как не получается физически смоделировать полет монетки,
     // приходится жульничать :)
     // т.е. рассчитывается угол, под которым монетка должна упасть на пол,
     // исходя из начальной скорости
     float ugol = 2 * noiseInitSpeed * (WCOEF * noiseInitSpeed) / 9.8; //angle;
     while (ugol > 360) { ugol -= 360; }
     // В зависимости от того, под каким углом монетка коснулась пола,
     // определяем, на какую сторону она упала
     if (((ugol >= 0) && (ugol <= 90))
	  || ((ugol >= 270) && (ugol <= 360))) {
	  ++totalOrel; // увеличиваем общее количество выпавших орлов
	  nowOrel = true; // явно задаем, что выпал орел
	  emit totalOrelChanged(totalOrel); // излучаем соответствующий сигнал
     } else {
	  ++totalReska;
	  nowOrel = false;
	  emit totalReskaChanged(totalReska);
     }
}

// Корректируем начальную скорость в зависимости от погрешности
void CoinAnim::correctInitSpeed()
{
     noiseInitSpeed = initSpeed;
     float rnd = myrand(0, NOISEPOWER);
     // случайным образом определяем увеличивать скорость или уменьшать
     if (((int)(myrand(0, 2))) == 0) {
	  // увеличиваем скорость на процент от сгенерированной выше случайной величины
	  noiseInitSpeed += noise * rnd / 100;
     } else {
	  noiseInitSpeed -= noise * rnd / 100;
     }
}

// пускаем монетку
void CoinAnim::start(int Times, bool showRTV, bool RarePainting, bool Inside)
{
     // Стартуем только если таймер "молчит"
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

// Функция возвращает игрекувую координату центра монетки
float CoinAnim::getCoord()
{
     // приходится делить на SLOMO, чтобы монетка крутилась не так быстро,
     // но из-за этого не получается физически смоделировать полет монетки
     float time = timerCount / SLOMO;
     float y0 = rect().height();
     // домножаем на STARTACCEL, чтобы монетка взлетала чуть выше на маленьких скоростях
     // из-за этого опять-таки отдыхает возможность физического моделирования
     float y = y0 - STARTACCEL * noiseInitSpeed * time + 0.5 * 9.8 * time * time;
     currSpeed = noiseInitSpeed - 9.8 * time;
     angle = WCOEF * noiseInitSpeed * time;
     // Излучаем событие о смене текущей скорости только при последнем прыжке
     if ((count == 0) && (showRTValues)) {
	  emit currSpeedChanged(fabs(currSpeed));
     }
     return y;
}

void CoinAnim::moveCoin()
{
     // следующий такт
     ++timerCount;
     // Если вышли из области - останавливаем процесс
     // Учитываем, что "бросать", возможно, придется несколько раз
     // Учитываем с точностью до касания монеткой пола углом
     // Если же пользователь захотел смотреть только на каждую десятую монетку,
     // то мы, кроме того, что не будем её рисовать, не будем её и считать!
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
	       // Если надо еще, то останавливаем таймер и запускаем еще раз
	       autoStartTimer->stop();
	       calcCoinSide();
	       angle = 0;
	       update();
	       start(count, showRTValues, isRarePainting, true);
	  }
     }
     // перерисовываем область
     update();
}


void CoinAnim::paintEvent(QPaintEvent *)
{
     // Инициализируем Painter
     QPainter painter(this);
     // Включаем сглаживание
     painter.setRenderHint(QPainter::Antialiasing);
     // Рисуем монетку
     paintCoin(painter);
}

void CoinAnim::paintCoin(QPainter &painter)
{
     // Отрисовка монетки
     if (autoStartTimer->isActive()) {
	  // рисуется каждая десятая попытка и первая
	  if (isRarePainting) {
	       if ((((times - count) % 10) == 0) || (count == (times - 1)) || (count == 0)) {
		    // Перемещаем начало координат в центр монетки
		    painter.translate(rect().width() / 2, getCoord());
		    // Сохраняем настройки
		    painter.save();
		    // Поворачиваем координатную систему
		    painter.rotate(angle);
		    // Излучаем событие только при последнем прыжке
		    if ((count == 0) && (showRTValues)) {
			 emit currAngleChanged(angle);
		    }
	       }
	  } else {
	       // Перемещаем начало координат в центр монетки
	       painter.translate(rect().width() / 2, getCoord());
	       // Сохраняем настройки
	       painter.save();
	       // Поворачиваем координатную систему
	       painter.rotate(angle);
	       // Излучаем событие только при последнем прыжке
	       if ((count == 0) && (showRTValues)) {
		    emit currAngleChanged(angle);
	       }
	  }
     } else {
	  // Рисуется покоящаяся монетка
	  painter.translate(rect().width() / 2, rect().height() - 6);
	  painter.save();
     }
     // Рисуем монетку
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
	       // Восстанавливаем настройки
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
	  // Восстанавливаем настройки
	  painter.restore();
     }
}

QRect CoinAnim::coinRect(QString type) const
{
     // Выдаем координаты половинок монетки
     if (type == "top") {
	  QRect result(-30, -6, 60, 6);
	  return result;
     } else {
	  QRect result(-30, 0, 60, 6);
	  return result;
     }
}
