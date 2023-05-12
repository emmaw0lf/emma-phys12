// Include the AccelStepper Library
#include &lt;AccelStepper.h&gt;

// Define pin connections
const int stepsPerRevolution = 200;
const int dirPin = 12;
const int stepPin = 13;
const int ledPin = 8;
int rotationCW = 0;
int rotationCCW = 0;
int sensorValue = 0; //
int location = 1;



// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper stepper(1, stepPin, dirPin); 

void setup() {
  stepper.setSpeed(1500);
  stepper.setAcceleration(1000);
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  //stepper.moveTo(200);
  pinMode(2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
}


void loop() {

  digitalWrite(8, HIGH);


  int sensorValue = digitalRead(2);
  Serial.println(sensorValue);

  if (sensorValue == 0) {

    if (location == 1) {

      Serial.println("clockwise");
      digitalWrite(dirPin, LOW);
      rotationCW =  (0.5 * stepsPerRevolution);

      stepper.moveTo(rotationCW);
      location = 2;
      delay(500);
      Serial.println("Location 2");

    } else {
      rotationCCW = (0);
      digitalWrite(dirPin, HIGH);
      Serial.println("counterclockwise");
      stepper.moveTo(rotationCCW);
      location = 1;
      delay(500);
      Serial.println("Location 1");
    }

  }
  stepper.run();
}



