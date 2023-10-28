#include <Arduino.h>
#include <index.h>
#include <GyverOLED.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <EEPROM.h>

GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;
ESP8266WebServer server(80);
String lists[30];
int page;

void eeprom_update(int adres, byte value){
  if(EEPROM.read(adres) != value){
    EEPROM.write(adres, value);
    EEPROM.commit();
  }
}
void write_to_eeprom(int number) {
  for(unsigned int j = 0; j < lists[number].length(); j++) {
    eeprom_update(number*85+j, byte(lists[number][j]));
  }
}
void read_from_eeprom(int number) {
  lists[number]="";
  for(unsigned int j = 0; j < 84; j++) {
    if(EEPROM.read(number*85+j) != 255)
      lists[number] += char(EEPROM.read(number*85+j));
  }
}
void get_pages() {
    lists[0] = server.arg("list0");
    lists[1] = server.arg("list1");
    lists[2] = server.arg("list2");
    lists[3] = server.arg("list3");
    lists[4] = server.arg("list4");
    lists[5] = server.arg("list5");
    lists[6] = server.arg("list6");
    lists[7] = server.arg("list7");
    lists[8] = server.arg("list8");
    lists[9] = server.arg("list9");
    lists[10] = server.arg("list10");
    lists[11] = server.arg("list11");
    lists[12] = server.arg("list12");
    lists[13] = server.arg("list13");
    lists[14] = server.arg("list14");
    lists[15] = server.arg("list15");
    lists[16] = server.arg("list16");
    lists[17] = server.arg("list17");
    lists[18] = server.arg("list18");
    lists[19] = server.arg("list19");
    lists[20] = server.arg("list20");
    lists[21] = server.arg("list21");
    lists[22] = server.arg("list22");
    lists[23] = server.arg("list23");
    lists[24] = server.arg("list24");
    lists[25] = server.arg("list25");
    lists[26] = server.arg("list26");
    lists[27] = server.arg("list27");
    lists[28] = server.arg("list28");
    lists[29] = server.arg("list29");
}
void MainRequest() {
  if(server.hasArg("list0")) {
    get_pages();
    for(unsigned int i=0; i<30; i++)
      write_to_eeprom(i);
  }
  if(server.hasArg("UP")) {
    if(page < 29){
      page++;
    }
  }
  if(server.hasArg("DOWN")) {
    if(page > 0){
      page--;
    }
  }
  eeprom_update(4095, byte(page));
  String index_html = index_html_0+String(page)+"/30"+index_html_1+lists[0]+list0+lists[1]+list1+lists[2]+list2+lists[3]+list3+lists[4]+list4+lists[5]+list5+lists[6]+list6+lists[7]+list7+lists[8]+list8+lists[9]+list9+lists[10]+list10+lists[11]+list11+lists[12]+list12+lists[13]+list13+lists[14]+list14+lists[15]+list15+lists[16]+list16+lists[17]+list17+lists[18]+list18+lists[19]+list19+lists[20]+list20+lists[21]+list21+lists[22]+list22+lists[23]+list23+lists[24]+list24+lists[25]+list25+lists[26]+list26+lists[27]+list27+lists[28]+list28+lists[29]+list29;
  server.send(200, "text/html", index_html);
}
void RedirectRequest() {
  server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0; url=/\" />");
}

void setup() {
  oled.init(2, 14);
  Serial.begin(115200);
  EEPROM.begin(4096);
  page = EEPROM.read(4095);

  oled.setScale(1);
  oled.autoPrintln(true);
  oled.flipH(true);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("Glasses", "kotik123");

  server.on("/", MainRequest);
  server.onNotFound(RedirectRequest);

  server.begin();

  for(unsigned int i=0; i<30; i++)
      read_from_eeprom(i);
}

void loop() {
  server.handleClient();
  oled.clear();
  oled.home();
  oled.print(lists[page]);
  oled.update();
}

