#include <AFMotor.h>

// Motor shield pin connections
const int leftMotorPin = 1;
const int rightMotorPin = 2;
const int servoPin = 9;

// Motor speed
const int motorSpeed = 200;

// Create motor shield object
AF_DCMotor motorShield(4);

// Servo motor object
Servo servoMotor;

// Ultrasonic sensor pin
const int trigPin = 7;
const int echoPin = 6;

void setup() {
 // Initialize serial communication
 Serial.begin(9600);

 // Attach servo motor to pin
 servoMotor.attach(servoPin);

 // Set up ultrasonic sensor pins
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
}

void loop() {
 Check_side();
}

void Check_side() {
 Stop();
 delay(100);

 float leftDistance = measureDistance(leftMotorPin);
 float rightDistance = measureDistance(rightMotorPin);

 compareDistance(leftDistance, rightDistance);
}

float measureDistance(int motorPin) {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);

 long duration = pulseIn(echoPin, HIGH);
 float distance = duration * 0.0344 / 2;

 servoMotor.write(motorPin);
 return distance;
}

void compareDistance(float leftDistance, float rightDistance) {
 if (leftDistance > rightDistance) {
    turnRight();
 } else if (leftDistance < rightDistance) {
    turnLeft();
 } else {
    forword();
 }
}

void forword() {
 motorShield.setSpeed(motorSpeed);
 motorShield.run(FORWARD);
}

void backword() {
 motorShield.setSpeed(motorSpeed);
 motorShield.run(BACKWARD);
}

void turnRight() {
 motorShield.setSpeed(motorSpeed);
 motorShield.run(BACKWARD);
}

void turnLeft() {
 motorShield.setSpeed(motorSpeed);
 motorShield.run(FORWARD);
}

void Stop() {
 motorShield.run(RELEASE);
}