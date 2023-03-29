#include <Servo.h>

#define SERVO_PIN D4
#define STOP 90

#define SERIAL_SPEED 115200
#define LOOP_TIME 5000

Servo myservo;

void rotateServo(const int speed, const int time) {
  myservo.write(speed);
  delay(time);
  myservo.write(STOP);
}

void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println();

  myservo.attach(SERVO_PIN);
  myservo.write(STOP);
}

void loop() {
  delay(LOOP_TIME);

  Serial.println("First loop");
  rotateServo(70, 2000);
  delay(LOOP_TIME);

  Serial.println("Second loop");
  rotateServo(50, 2000);
  delay(LOOP_TIME);

  Serial.println("Third loop");
  rotateServo(30, 2000);
  delay(LOOP_TIME);

  Serial.println("Fourth loop");
  rotateServo(10, 2000);
  delay(LOOP_TIME);
}
