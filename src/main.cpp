/* 
 * Program pre ovládanie dvoch LEGO motorčekov pomocou ESP8266
 *
 * Posledna zmena(last change): 08.12.2020
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2016 - 2020 Ing. Peter VOJTECH ml.
 * @license
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.1
 * 
 * Toto servo:
 * https://www.hwkitchen.cz/geekservo-9g-360-kontinualni-kompatibilni-s-lego/
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

const int pwm1_pin = 12; // D6
const int pwm2_pin = 13; // D7
int rychlost1, rychlost2 = 0;

void setup() {
  // put your setup code here, to run once:
  //Wifi.begin();
  WiFi.softAP("ESPsoftAP_auticko");
}

void loop() {
  if (Wifi.available()) {
    String msg = Wifi.readStringUntil('\n'); // Príkaz spolu s doplňujúcou informáciou v tvare PPPxxxx, 
                                             // kde PPP - príkaz; xxxx - doplňujúca informácia
    String _tmpMsg =  msg.substring(3);      // Pomocná premenná pre doplňujúcu informáciu
    /**
     * Povolené príkazy z wifi:
     * moCxyz - pohyb motora, kde C- čísko motora a xyz = 0..511 - vzad; 512 - stop; 513..1023 - vpred
     */
    if (msg.startsWith("mo1")) {
      _tmpMsg = msg.substring(3);
      rychlost1 = _tmpMsg.toInt();
      Wifi.println(String("Motor1: \"")  + String(_tmpMsg) + String("->") + String(rychlost1) + String("\" ") + String(msg));
      if (rychlost1 > 512) {        // Pohyb motora vpred
        analogWrite(pwm1_pin, rychlost1);
      } else if (rychlost1 < 512) { // Pohyb motora vzad
        analogWrite(pwm1_pin, rychlost1);
      } else {                     // Motor stop
        analogWrite(pwm1_pin, 0);
      }
    }
    if (msg.startsWith("mo2")) {
      _tmpMsg = msg.substring(3);
      rychlost2 = _tmpMsg.toInt();
      Wifi.println(String("Motor2: \"")  + String(_tmpMsg) + String("->") + String(rychlost2) + String("\" ") + String(msg));
      if (rychlost2 > 512) {        // Pohyb motora vpred
        analogWrite(pwm2_pin, rychlost2);
      } else if (rychlost2 < 512) { // Pohyb motora vzad
        analogWrite(pwm2_pin, rychlost2);
      } else {                     // Motor stop
        analogWrite(pwm2_pin, 0);
      }
    }
  }
}