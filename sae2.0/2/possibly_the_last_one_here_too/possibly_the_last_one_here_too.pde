import processing.serial.*;

Serial myPort;
String val;
int leftSensor, rightSensor, distance;

void setup() {
  size(400, 200);
  myPort = new Serial(this, "COMX", 9600); // Replace "COMX" with your Arduino's port
}

void draw() {
  if (myPort.available() > 0) {
    val = myPort.readStringUntil('\n');

    if (val != null) {
      String[] sensors = split(val, ',');
      if (sensors.length >= 3) {
        leftSensor = int(sensors[0]);
        rightSensor = int(sensors[1]);
        distance = int(sensors[2]);
      }
    }
  }

  background(255);
  fill(0);
  textAlign(LEFT);
  text("Left Sensor: " + leftSensor, 20, 30);
  text("Right Sensor: " + rightSensor, 20, 60);
  text("Distance: " + distance + " cm", 20, 90);
}
