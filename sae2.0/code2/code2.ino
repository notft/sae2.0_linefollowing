#include <AFMotor.h> // Include the Adafruit Motor Shield library
#include <Servo.h>   // Include the Servo library

AF_DCMotor motor1(1); // Motor objects
AF_DCMotor motor2(2);
Servo servo;           // Servo object

const int leftIR = A0;    // Left Infrared sensor pin
const int rightIR = A1;   // Right Infrared sensor pin
const int trigPin = 0;    // Ultrasonic sensor trig pin
const int echoPin = 1;   // Ultrasonic sensor echo pin

const int IR_threshold = 500; // Threshold for IR sensors
const int obstacleDistanceThreshold = 15; // Threshold for obstacle detection

const int baseSpeed = 150; // Base speed for motors

void setup() {
  motor1.setSpeed(baseSpeed);
  motor2.setSpeed(baseSpeed);
  servo.attach(10); // Attach servo to pin 10

  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600); // Initialize Serial for debugging
}

void loop() {
  int leftIRValue = analogRead(leftIR);
  int rightIRValue = analogRead(rightIR);

  if (checkObstacle()) {
    avoidObstacle();
  } else {
    if (leftIRValue < IR_threshold && rightIRValue < IR_threshold) {
      moveForward();
    } else if (leftIRValue < IR_threshold && rightIRValue > IR_threshold) {
      turnRight();
    } else if (leftIRValue > IR_threshold && rightIRValue < IR_threshold) {
      turnLeft();
    } else {
      stopMoving();
    }
  }
}

void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

void stopMoving() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

bool checkObstacle() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  return (distance < obstacleDistanceThreshold);
}

void avoidObstacle() {
  // Stop the robot
  stopMoving();
  
  // Move away from the line
  servo.write(90); // Assuming the servo is centered at 90 degrees
  delay(1000); // Adjust this delay for your robot's movement

  // Turn the robot to avoid the obstacle
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(1000); // Adjust this delay for your robot's movement

  // Resume line following
  servo.write(0); // Assuming the servo is at 0 degrees for line following
  delay(1000); // Adjust this delay for your robot's movement
}
