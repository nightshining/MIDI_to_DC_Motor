/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->	http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
//Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
//Note: Stacked shields x 2
Adafruit_MotorShield AFMS_bottom(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMS_top(0x60); // Default address, no jumpers

Adafruit_DCMotor *myMotor1 = AFMS_bottom.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS_top.getMotor(1);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS_bottom.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  if (!AFMS_top.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->setSpeed(150);
  myMotor2->setSpeed(150);

}

void loop() {
  uint8_t i;

  Serial.print("tick");

  myMotor1->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor1->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor1->setSpeed(i);
    delay(10);
  }

  Serial.print("tock");

  myMotor1->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor1->setSpeed(i);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor1->setSpeed(i);
    delay(10);
  }

  Serial.print("tech");
  myMotor1->run(RELEASE);
  delay(1000);
}