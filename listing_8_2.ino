// Подключение библиотеки IRremote.h.
//#include <IRremote.h> // Подключаем глобально библиотеку из Arduino IDE.
#include "IRremote.h" // Подключаем локально библиотеку из текущего каталога
#include "motor.h" //Функции управления моторами.
// Порт для IR-приемника.
int RECV_PIN = 7;
// Создание IR-приемника.
IRrecv irrecv(RECV_PIN);
//Переменная для хранения кодов кнопок, получаемых от IR-приемника.
decode_results results;
// Хранит время последнего нажатия кнопки.
unsigned long _time;
/////////////
// Опишем коды кнопок макроподстановками:
#define FORWARD 0x3D9AE3F7
#define LEFT  0x8C22657B
#define RIGHT 0x449E79F
#define STOP  0x488F3CBB
#define BACKWARD  0x1BC0157B
#define FORWARDLEFT 0xE318261B
#define FORWARD2  0x511DBB
#define FORWARDRIGHT  0xEE886D7F
#define LEFT2 0x52A3D41F
#define STOP2 0xD7E84B1B
#define RIGHT2  0x20FE4DBB
#define BACKWARDLEFT 0xF076C13B
#define BACKWARD2 0xA3C8EDDB
#define BACKWARDRIGHT 0xE5CFBD7F
#define STOP3 0x97483BFB
#define STOP4 0xC101E57B
#define STOP5 0xF0C41643
//Инициализация.
void setup()
{
  // Переменные – номера контактов (пинов) Arduino.
  // Для левых и правых моторов машинки.
  setup_motor_system(2, 3, 4, 5);
  _stop(); //Двигатели остановлены.
  // Запуск IR-приемника.
  irrecv.enableIRIn();
  _time = millis();
 }
// Основная программа.
void loop()
{
  if (irrecv.decode(&results))
  {
    unsigned long val = results.value;
    _time = millis();
    switch (val) {
      // Вперед
      case FORWARD:
      case FORWARD2:
        forward();
        break;
      // Назад
      case BACKWARD:
      case BACKWARD2:
        backward();
        break;
      // Влево
      case LEFT:
      case LEFT2:
        left();
        break;
      // Вправо
      case RIGHT:
      case RIGHT2:
        right();
        break;
      // Прямо и влево
      case FORWARDLEFT:
        forward_left();
        break;
      // Прямо и вправо
      case FORWARDRIGHT:
        forward_right();
        break;
      // Назад и влево
      case BACKWARDLEFT:
        backward_left();
        break;
      // Назад и вправо
      case BACKWARDRIGHT:
        backward_right();
        break;
      // Стоп
      case STOP:
      case STOP2:
      case STOP3:
      case STOP4:
      case STOP5:
        _stop();
       break;
    }
    irrecv.resume();
  }
  //Если никакая клавиша не нажата более 0.3сек., то остановка.
  if((millis()-_time)>300) {_stop();}
}//=====================================================================
