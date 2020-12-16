/* 
 * Program pre ovládanie dvoch LEGO motorčekov pomocou ESP8266
 *
 * Posledna zmena(last change): 16.12.2020
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2016 - 2020 Ing. Peter VOJTECH ml.
 * @license
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.3
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
//#include <WiFi.h>

IPAddress local_IP(192,168,4,200);
IPAddress gateway(192,168,4,100);
IPAddress subnet(255,255,255,0);

const char* host     = "auticko";

WiFiClient client;

const byte pwm_pins[2] = {12, 13}; // D6, D7

int min_servo = 0;       // Minimálna hodnota pre servo
int cen_servo = 512;     // Stredná    -- // --
int max_servo = 1023;    // Maximálna  -- // --

void setup() {
  Serial.begin(9600);
  //Wifi.begin();
  Serial.print("Nastavujem soft-AP konfiguráciu ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet));

  Serial.print("Nastavujem soft-AP pripojenie ...");
  Serial.println(WiFi.softAP("ESPsoftAP_auticko") ? "Ready" : "Failed!");
  
  Serial.print("Moja IP adresa je:");
  Serial.println(WiFi.softAPIP());

  // Use WiFiClient class to create TCP connections
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  } else {
    Serial.print("Host "); Serial.print(host);
    Serial.println(" pripojený");
  }
}

void loop() {
  if (client.available()) {
    String msg = client.readStringUntil('\n');
    if (msg.startsWith("mo")) {              // Zisti, či je príkaz pre motor
      String _tmpRy = msg.substring(3);      // Zisti rýchlosť
      int rychlost = _tmpRy.toInt();

      String _tmpId = msg.substring(2, 3);   // Zisti id motora
      int id = _tmpId.toInt();

      if ((id == 1) || (id == 2)) {   // Over či id = 1 alebo 2
        int servo_rychlost = map(rychlost, 0, 255, min_servo, max_servo);
        client.println(String("Motor1: \"")  + String(id) + String("->") + String(rychlost) + String("\" ") + String(msg));
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