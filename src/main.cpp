/* 
 * Program pre ovládanie dvoch LEGO motorčekov pomocou ESP8266
 *
 * Posledna zmena(last change): 26.12.2020
 * @author Ing. Peter VOJTECH ml. <petak23@gmail.com>
 * @copyright  Copyright (c) 2016 - 2020 Ing. Peter VOJTECH ml.
 * @license
 * @link       http://petak23.echo-msz.eu
 * @version 1.0.5
 * 
 * Servo:
 * https://www.hwkitchen.cz/geekservo-9g-360-kontinualni-kompatibilni-s-lego/
 *
 * Príkaz spolu s doplňujúcou informáciou v tvare PPPxxx, 
 * kde PPP - príkaz; xxx - doplňujúca informácia
 * 
 * Povolené príkazy z wifi:
 * ledx - on/off vstavanej LED, kde x = 0 - off; x = 1 - on
 * moCxyz - pohyb motora, kde C- čísko motora a xyz = 0..127 - vzad; 128 - stop; 129..255 - vpred
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

IPAddress local_IP(192,168,4,1);
IPAddress subnet(255,255,255,0);
IPAddress my_IP;
const int port = 9876; // and this port

const char* ssid = "ESPsoftAP_auticko";
const char* password = "456789";

WiFiServer server(port);
WiFiClient client;

const byte pwm_pins[2] = {12, 13}; // D6, D7

int min_servo = 0;       // Minimálna hodnota pre servo
int cen_servo = 512;     // Stredná    -- // --
int max_servo = 1023;    // Maximálna  -- // --

char cmd[100]; // stores the command chars received from RoboRemo
int cmdIndex;
unsigned long lastCmdTime = 60000;
unsigned long aliveSentTime = 0;

void setup() {
  Serial.begin(9600);
  
  Serial.println();
  Serial.println("----------------------------------------");
  Serial.print("Nastavujem soft-AP konfiguráciu ... ");
  Serial.println(WiFi.softAPConfig(local_IP, local_IP, subnet));

  Serial.print("Nastavujem soft-AP pripojenie ... ");
  Serial.println(WiFi.softAP(ssid) ? "Ready" : "Failed!");
  
  //Note: by default, the access point IP address is 192.168.4.1
  my_IP = WiFi.softAPIP();

  server.begin(); // Start TCP server
  
  Serial.println((String)"SSID: " + ssid);// + "  PASS: " + password);
  Serial.println((String)"RoboRemo sa musí pripojiť na: " + my_IP.toString() + ":" + port);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);  
}

void loop() {
  if(!client.connected()) {
    client = server.available();
    return;
  }

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
    } else if (msg.startsWith("led")) {   
      String _tmpLED = msg.substring(3, 4);
      digitalWrite(LED_BUILTIN, _tmpLED.toInt());
    }
  }
}