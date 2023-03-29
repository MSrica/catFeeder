#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>

#define WIFI_SSID "m"
#define WIFI_PASS "mateomateo"

#define SERVO_PIN D4
#define STOP 90
#define ROTATE_SPEED 50
#define ROTATE_TIME 2000

#define WIFI_TIMEOUT 100

#define BREAKFAST_TIME 8
#define LUNCH_TIME 13
#define DINNER_TIME 18

#define SERIAL_SPEED 115200
#define LOOP_TIME 1000

const long UTC_OFFSET_S = 3600;  // UTC +1 -> 1 * 60 * 60 : 3600
const long DELAY_MS = 60000;     // 1000 * 60

Servo myservo;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_S);
bool breakfast = false, lunch = false, dinner = false;


void rotateServo() {
  myservo.write(ROTATE_SPEED);
  delay(ROTATE_TIME);
  myservo.write(STOP);
}

void connectToWifiIfNotConnected() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Connecting to ");
    Serial.print(WIFI_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      delay(WIFI_TIMEOUT);
      Serial.print(".");
    }
    Serial.println();
  }
}

void updateAndPrintTime() {
  timeClient.update();
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
}

bool activateServo(int time, bool meal) {
  if (timeClient.getHours() > time && !meal) {
    rotateServo();
    return !meal;
  }
  return meal;
}

void resetVariables(){
  if (timeClient.getHours() < 7) {
    breakfast = false;
    lunch = false;
    dinner = false;
  }
}


void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println();

  myservo.attach(SERVO_PIN);
  myservo.write(STOP);

  connectToWifiIfNotConnected();

  timeClient.begin();
}

void loop() {
  connectToWifiIfNotConnected();

  updateAndPrintTime();

  resetVariables();  

  breakfast = activateServo(BREAKFAST_TIME, breakfast);
  lunch = activateServo(LUNCH_TIME, lunch);
  dinner = activateServo(DINNER_TIME, dinner);

  delay(LOOP_TIME);
}
