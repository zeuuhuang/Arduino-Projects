#include <dht.h>
#include <LiquidCrystal.h>

dht DHT;
LiquidCrystal lcd(10,9,5,4,3,2);

#define DHT11_PIN 11

void setup(){
  lcd.begin(16, 2);
}

void loop(){
  int chk = DHT.read11(DHT11_PIN);
  lcd.setCursor(0,0); 
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(2000);
}
