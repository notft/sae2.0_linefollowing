#include <AFMotor.h>
#include <Servo.h>

#define LINE_SENSOR_LEFT 2
#define LINE_SENSOR_RIGHT 3
#define ULTRASONIC_TRIGGER 4
#define ULTRASONIC_ECHO 5
#define SERVO_PIN 9

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
Servo myservo;

int pos = 0;    // variable to store the servo position 

void setup() {
 pinMode(LINE_SENSOR_LEFT, INPUT);
 pinMode(LINE_SENSOR_RIGHT, INPUT);
 pinMode(ULTRASONIC_TRIGGER, OUTPUT);
 pinMode(ULTRASONIC_ECHO, INPUT);

 myservo.attach(SERVO_PIN); // attaches the servo on pin 9 to the servo object 
 myservo.write(90); // center position
}

void loop() {
 // Read the line sensor values
 int line_left = digitalRead(LINE_SENSOR_LEFT);
 int line_right = digitalRead(LINE_SENSOR_RIGHT);

 // If the line is detected by both sensors, follow the line
 if (line_left == HIGH && line_right == HIGH) {
    followLine();
 } else {
    // Otherwise, look for the line using the servo
    findLine();
 }

 // Avoid obstacles using the ultrasonic sensor
 avoidObstacles();
}

void followLine() {
 motor1.setSpeed(255);
 motor1.run(FORWARD);
 motor2.setSpeed(255);
 motor2.run(FORWARD);
}

void findLine() {
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
 } 
 for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
 } 
}

void avoidObstacles() {
 digitalWrite(ULTRASONIC_TRIGGER, LOW);
 delayMicroseconds(2);
 digitalWrite(ULTRASONIC_TRIGGER, HIGH);
 delayMicroseconds(10);
 digitalWrite(ULTRASONIC_TRIGGER, LOW);

 long duration = pulseIn(ULTRASONIC_ECHO, HIGH);

 // If the obstacle is too close, turn around
 if (duration < 300) {
    reverse();
    delay(1000);
 }
}

void reverse() {
 motor1.setSpeed(255);
 motor1.run(BACKWARD);
 motor2.setSpeed(255);
 motor2.run(BACKWARD);
}