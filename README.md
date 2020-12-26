# Projekt esp8266-auticko

Ovládanie LEGO autíčka pomocou ESP8266 a aplikácie [roboremo](https://www.roboremo.com).

## Príkazy cez wifi

Príkaz spolu s doplňujúcou informáciou v tvare *PPPxxx*, kde *PPP* - príkaz; *xxx* - doplňujúca informácia.

Povolené príkazy z wifi:
 - **moCxyz** - pohyb motora("mo"), kde C je číslo motora a xyz = 0..127 - vzad; 128 - stop; 129..255 - vpred
 - **ledx** - on/off vstavanej LED, kde x = 0 - off; x = 1 - on

## Odkazy a referencie

 - [https://www.hwkitchen.cz/geekservo-9g-360-kontinualni-kompatibilni-s-lego/](https://www.hwkitchen.cz/geekservo-9g-360-kontinualni-kompatibilni-s-lego/)
 - [https://nettigo.eu/attachments/590](https://nettigo.eu/attachments/590)
 - [ESP8266WiFI.h](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)
 - [Arduino/Reference/WiFi](https://www.arduino.cc/en/Reference/WiFi)
 - [https://www.roboremo.com/projects/esp/esp8266-wifi-rc-car](https://www.roboremo.com/projects/esp/esp8266-wifi-rc-car)
 - [https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/](https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/)