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

String *arr[30];

void write_to_eeprom() {
  Serial.println(*arr[0]);
}

void get_pages() {
    list0 = server.arg("list0");
    list1 = server.arg("list1");
    list2 = server.arg("list2");
    list3 = server.arg("list3");
    list4 = server.arg("list4");
    list5 = server.arg("list5");
    list6 = server.arg("list6");
    list7 = server.arg("list7");
    list8 = server.arg("list8");
    list9 = server.arg("list9");
    list10 = server.arg("list10");
    list11 = server.arg("list11");
    list12 = server.arg("list12");
    list13 = server.arg("list13");
    list14 = server.arg("list14");
    list15 = server.arg("list15");
    list16 = server.arg("list16");
    list17 = server.arg("list17");
    list18 = server.arg("list18");
    list19 = server.arg("list19");
    list20 = server.arg("list20");
    list21 = server.arg("list21");
    list22 = server.arg("list22");
    list23 = server.arg("list23");
    list24 = server.arg("list24");
    list25 = server.arg("list25");
    list26 = server.arg("list26");
    list27 = server.arg("list27");
    list28 = server.arg("list28");
    list29 = server.arg("list29");

    arr[0] = &list0;
    arr[1] = &list1;
    arr[2] = &list2;

    write_to_eeprom();
}

void MainRequest() {
  if(server.hasArg("list0")) {
    get_pages();
  }
  if(server.hasArg("UP")) {
    if(page < 29)
      page++;
  }
  if(server.hasArg("DOWN")) {
    if(page > 0)
      page--;
  }
    server.send(200, "text/html", index_html);
}

void RedirectRequest() {
  server.send(200, "text/html", "<meta http-equiv=\"refresh\" content=\"0; url=/\" />");
}

void setup() {
  oled.init(2, 14);
  Serial.begin(115200);
  EEPROM.begin(4096);

  oled.setScale(1);
  oled.autoPrintln(true);
  oled.flipH(true);

  WiFi.mode(WIFI_AP);
  WiFi.softAP("Glasses", "kotik123");

  server.on("/", MainRequest);
  server.onNotFound(RedirectRequest);

  server.begin();
}

void loop() {
  server.handleClient();
  oled.clear();
  oled.home();
  oled.print(list0);
  oled.print(" Страниица ");
  oled.print(page);
  oled.update();
}

