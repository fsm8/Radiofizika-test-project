
///// Подключаем библиотеки для датчика отн. влажности, температуры и атм. давления марки BME280
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//#define DEBUG // Дебаг

///// Подключаем библиотеку для работы с SPI
#include <SPI.h>

#define CS_PORT 5 // Порт МК для CS

Adafruit_BME280 bme; // Создаем экземпляр класса, или "создаем имя датчика"

void setup()
{

#ifdef DEBUG
  {
    Serial.begin(115200); // Инициализация последовательного порта Ардуино
  }
#endif

  bme.begin(0x76); // Инициализация датчика BME280

  pinMode(CS_PORT, OUTPUT); // Инициализация порта CS

  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0)); // Настройка режима работы SPI
  SPI.begin(); // Запускаем SPI
}

void loop()
{
  // Измеряем и выводим на последовательный порт отн. влажность и температуру воздуха
  int Temp = (bme.readTemperature());
  int Hum = (bme.readHumidity());

#ifdef DEBUG
  {
    Serial.print("Temperature = ");
    Serial.print(Temp);
    Serial.print(" C. ");
    Serial.print("Himidity = ");
    Serial.print(Hum);
    Serial.println(" %.");
  }
#endif

  // Передаем в STM32 через SPI отн. влажность и температуру
  digitalWrite(CS_PORT, 0); // CS = 0
  SPI.transfer(Temp); // Передаем значение температуры воздуха
  SPI.transfer(Hum); // Передаем значение влажности воздуха
  digitalWrite(CS_PORT, 1); // CS = 1

  delay(1000); // пауза в измерениях
}
