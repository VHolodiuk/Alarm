#include "pitches.h"
#include <PubSubClient.h>
#include <TimeLib.h> 
#include <Time.h>
#include <TimeAlarms.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define ALARM_ON_PIN 5
#define LED 16

//Параметри для Wi-Fi
const char* ssid = "Frankof_DIR-825";
const char* password = "70736948";
const int du1 = 500;
const int du2 = 1000;
const int de1 = 510;
const int de2 = 1010;

//Безкоштовний MQTT брокер
const char* mqtt_server = "broker.mqtt-dashboard.com";

//Адреса NTP серверу
IPAddress timeServer(91, 206, 8, 36); // 0.at.pool.ntp.org

//Часовий пояс, який змінюється при переведенні годинника!!!!!!!!!!!!!!!
const int timeZone = 2;  

unsigned int localPort = 9000;

WiFiClient espClient;
WiFiUDP Udp;
PubSubClient client(espClient);

String msg="";

//long lastMsg = 0;
//char msg[50];
//int value = 0;

void setup_wifi() {

  delay(10);
  // Спроба з'єднання з Wi-Fi
  Serial.println();
  Serial.print("З'єднуємось з ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi під'єднано");
  Serial.println("IP адреса: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  msg="";
  Serial.print("Повідомлення прийшло [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    msg+=(char)payload[i];
   
  }
  Serial.println(msg);
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if (msg == "ALARM") {
    client.publish("frankof/alarmer/out", "ALARM");
    //client.publish("frankof/alarmer/out", "ALARM2");
    AlarmON();
    //digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    
    //digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  if(WiFi.status() == WL_CONNECTED){
  while (!client.connected()) {
    Serial.print("Спроба MQTT з'єднання...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("З'єднано");
      // Once connected, publish an announcement...
      //client.publish("frankof/alarmer/out", "hello world");
      // ... and resubscribe
      client.subscribe("frankof/alarmer/in");
    } else {
      Serial.print("помилка, rc=");
      Serial.print(client.state());
      Serial.println(" спроба через 5 секуднд");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  }
  else{
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    }
  }

void setup() {
  Serial.begin(115200);
  pinMode(ALARM_ON_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(ALARM_ON_PIN, LOW); 
  digitalWrite(LED, HIGH); 
  setup_wifi();
  UpdateNTP();
  Serial.println("Встановлюємо будильники...");
  Alarm.alarmRepeat(8,00,0, AlarmON); 
  Alarm.alarmRepeat(9,45,0, AlarmON2);
  Alarm.alarmRepeat(10,0,0, AlarmON);
  Alarm.alarmRepeat(10,15,0, AlarmON);
  Alarm.alarmRepeat(12,0,0, AlarmON);
  Alarm.alarmRepeat(12,30,0, AlarmON);
  Alarm.alarmRepeat(14,45,0, AlarmON2);
  Alarm.alarmRepeat(15,0,0, AlarmON);
  Alarm.alarmRepeat(15,00,0, AlarmON);
  Alarm.alarmRepeat(17,0,0, AlarmON);
  Alarm.alarmRepeat(0,0,1, UpdateNTP);
  //Alarm.timerRepeat(30, AlarmON); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

time_t prevDisplay = 0;

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //digitalClockDisplay();
  Alarm.delay(1000); 
  
  

//  long now = millis();
//  if (now - lastMsg > 2000) {
//    lastMsg = now;
//    ++value;
//    snprintf (msg, 50, "hello world #%ld", value);
//    Serial.print("Publish message: ");
//    Serial.println(msg);
//    client.publish("outTopic", msg);
//  }
}

/*void AlarmON(){
  Serial.println("Alaaaaarm!");
  client.publish("frankof/alarmer/out", "ALARM");
  for (int i=0; i < 3; i++){
  digitalWrite(ALARM_ON_PIN, HIGH);
  delay(1500);
  digitalWrite(ALARM_ON_PIN, LOW);
  delay(500);
  digitalWrite(ALARM_ON_PIN, HIGH);
  delay(1500);
  digitalWrite(ALARM_ON_PIN, LOW);
  delay(500);
  digitalWrite(ALARM_ON_PIN, HIGH);
  delay(1500);
  digitalWrite(ALARM_ON_PIN, LOW);
  delay(3000);
   }
}*/
void AlarmON(){
  Serial.println("Alaaaaarm!");
  client.publish("frankof/alarmer/out", "ALARM");
  for (int i=0; i < 3; i++){
    digitalWrite(ALARM_ON_PIN, HIGH);
    delay(1500);
    digitalWrite(ALARM_ON_PIN, LOW);
    delay(500);
    digitalWrite(ALARM_ON_PIN, HIGH);
    delay(1500);
    digitalWrite(ALARM_ON_PIN, LOW);
    delay(500);
    digitalWrite(ALARM_ON_PIN, HIGH);
    delay(1500);
    digitalWrite(ALARM_ON_PIN, LOW);
    delay(3000);
  }

/*  tone(ALARM_ON_PIN, NOTE_F4, du1);
  delay(de1);
  tone(ALARM_ON_PIN, NOTE_E4, du1);
  delay(de1);
  tone(ALARM_ON_PIN, NOTE_D4, du1);
  delay(de1);
  tone(ALARM_ON_PIN, NOTE_C4, du1);
  delay(de1);
  tone(ALARM_ON_PIN, NOTE_G4, du2);
  delay(de2);
  tone(ALARM_ON_PIN, NOTE_G4, du2);
  delay(de2);

  tone(ALARM_ON_PIN, NOTE_F4, du1);
  tone(ALARM_ON_PIN, NOTE_E4, 250);
  tone(ALARM_ON_PIN, NOTE_D4, 250);
  tone(ALARM_ON_PIN, NOTE_C4, 250);
  tone(ALARM_ON_PIN, NOTE_G4, 500);
  tone(ALARM_ON_PIN, NOTE_G4, 500);

  tone(ALARM_ON_PIN, NOTE_F4, 250);
  tone(ALARM_ON_PIN, NOTE_A4, 250);
  tone(ALARM_ON_PIN, NOTE_A4, 250);
  tone(ALARM_ON_PIN, NOTE_F4, 250);

  tone(ALARM_ON_PIN, NOTE_E4, 250);
  tone(ALARM_ON_PIN, NOTE_G4, 250);
  tone(ALARM_ON_PIN, NOTE_G4, 250);
  tone(ALARM_ON_PIN, NOTE_E4, 250);
  
  tone(ALARM_ON_PIN, NOTE_D4, 250);
  tone(ALARM_ON_PIN, NOTE_E4, 250);
  tone(ALARM_ON_PIN, NOTE_F4, 250);
  tone(ALARM_ON_PIN, NOTE_D4, 250);
  tone(ALARM_ON_PIN, NOTE_C4, 500);
  tone(ALARM_ON_PIN, NOTE_C4, 500);
  
  tone(ALARM_ON_PIN, NOTE_F4, 250);
  tone(ALARM_ON_PIN, NOTE_A4, 250);
  tone(ALARM_ON_PIN, NOTE_A4, 250);
  tone(ALARM_ON_PIN, NOTE_F4, 250);
  
  tone(ALARM_ON_PIN, NOTE_E4, 250);
  tone(ALARM_ON_PIN, NOTE_G4, 250);
  tone(ALARM_ON_PIN, NOTE_G4, 250);
  tone(ALARM_ON_PIN, NOTE_E4, 250); 
   
  tone(ALARM_ON_PIN, NOTE_D4, 250);
  tone(ALARM_ON_PIN, NOTE_E4, 250);
  tone(ALARM_ON_PIN, NOTE_F4, 250);
  tone(ALARM_ON_PIN, NOTE_D4, 250);
  tone(ALARM_ON_PIN, NOTE_C4, 500);
  tone(ALARM_ON_PIN, NOTE_C4, 500);
 */
}

void AlarmON2(){
  Serial.println("Alaaaaarm2!");
  client.publish("frankof/alarmer/out", "ALARM2");
}

void UpdateNTP() {
  Serial.println("TimeNTP");
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Спроба з'єднання з ");
    Serial.println(ssid);
  WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
 }
  }
  
  Serial.print("IP адреса DHCP ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Піднімаємо UDP");
  Udp.begin(localPort);
  Serial.print("UDP порт: ");
  Serial.println(Udp.localPort());
  Serial.println("очікуємо на синхронізацію");
  setSyncProvider(getNtpTime);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(".");
  Serial.print(month());
  Serial.print(".");
  Serial.print(year()); 
  Serial.println(); 
}



void printDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*-------- NTP code ----------*/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Відправляємо NTP Запит");
  sendNTPpacket(timeServer);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Отримує NTP Відповідь");
      digitalWrite(LED, LOW);
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  UpdateNTP();
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:                 
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}
