#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define ALARM_ON_PIN 5
#define LED 16


// Update these with values suitable for your network.

const char* ssid = "Frankof_Workers";
const char* password = "70736948";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);

String msg="";
int counter = 0;
bool ff = true;

//long lastMsg = 0;
//char msg[50];
//int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
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
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
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
    if(counter != 2)
      {
        AlarmON();
        counter++;
      }
    else if(counter == 2)
      {
        counter = 0;
      }    
    
    //digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  }
  else if (msg == "ALARM2") {
    counter=0;
    counter++;
    AlarmON();
    
    
    
    //digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  }
  else  {
    //digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      digitalWrite(LED, LOW);
      // Once connected, publish an announcement...
      client.subscribe("frankof/alarmer/out");
      // ... and resubscribe
      //client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      digitalWrite(LED, HIGH);
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(ALARM_ON_PIN, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(ALARM_ON_PIN, LOW); 
  digitalWrite(LED, HIGH);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

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

void AlarmON(){
  Serial.println("Alaaaaarm!");
  //client.publish("frankof/alarmer/out", "ALARM");
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
}

void AlarmON2(){
  Serial.println("Alaaaaarm2!");
  client.publish("frankof/alarmer/out", "ALARM2");
}
