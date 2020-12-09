/* 
 * Program pre ovládanie dvoch LEGO motorčekov pomocou ESP8266
 *
 * Posledna zmena(last change): 09.12.2020
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2016 - 2020 Ing. Peter VOJTECH ml.
 * @license
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.2
 * 
 * Servo:
 * https://www.hwkitchen.cz/geekservo-9g-360-kontinualni-kompatibilni-s-lego/
 *
 * Príkaz spolu s doplňujúcou informáciou v tvare PPPxxx, 
 * kde PPP - príkaz; xxx - doplňujúca informácia
 * 
 * Povolené príkazy z wifi:
 * moCxyz - pohyb motora, kde C- čísko motora a xyz = 0..127 - vzad; 128 - stop; 129..255 - vpred
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>

const byte pwm_pins[2] = {12, 13}; // D6, D7

int min_servo = 0;       // Minimálna hodnota pre servo
int cen_servo = 512;     // Stredná    -- // --
int max_servo = 1023;    // Maximálna  -- // --

void setup() {
  //Wifi.begin();
  WiFi.softAP("ESPsoftAP_auticko");
}

void loop() {
  if (Wifi.available()) {
    String msg = Wifi.readStringUntil('\n');
    if (msg.startsWith("mo")) {              // Zisti, či je príkaz pre motor
      String _tmpRy = msg.substring(3);      // Zisti rýchlosť
      int rychlost = _tmpRy.toInt();

      String _tmpId = msg.substring(2, 3);   // Zisti id motora
      int id = _tmpId.toInt();

      if ((id == 1) || (id == 2)) {   // Over či id = 1 alebo 2
        int servo_rychlost = map(rychlost, 0, 255, min_servo, max_servo);
        Wifi.println(String("Motor1: \"")  + String(id) + String("->") + String(rychlost) + String("\" ") + String(msg));
        analogWrite(pwm_pins[(id-1)], servo_rychlost);
      }
      /*if (rychlost1 > 128) {        // Pohyb motora vpred
        analogWrite(pwm1_pin, servo_rychlost);
      } else if (rychlost1 < 128) { // Pohyb motora vzad
        analogWrite(pwm1_pin, servo_rychlost);
      } else {                      // Motor stop
        analogWrite(pwm1_pin, servo_rychlost);
      }*/
    }
  }
}