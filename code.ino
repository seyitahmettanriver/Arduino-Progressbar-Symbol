#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);

byte barLeft[8] = {
  B11111,
  B10000,
  B10111,
  B10111,
  B10111,
  B10111,
  B10000,
  B11111
};

byte barFull[8] = {
  B11111,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B11111
};

byte barNoFull[8] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};

byte barRight[8] = {
  B11111,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B11111
};
void setup() {
  dht.begin();
  lcd.begin();
  lcd.createChar(0, barLeft);
  lcd.createChar(1, barFull);
  lcd.createChar(2, barNoFull);
  lcd.createChar(3, barRight);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("IFTARA KALAN SURE");
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  for (int i = 0; i < 12; i++) {
    lcd.write(byte(1));
  }
  for (int i = 0; i < 6; i++) {
    lcd.write(byte(2));
  }
  lcd.write(byte(3));
  lcd.setCursor(4, 3);
  lcd.print("02:22 (%85)");
}

void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Nem: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Sıcaklık: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Isı endeksi: ");
  Serial.print(hic);
  Serial.println(" *C ");
}
