/*
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

//Adafruit_DCMotor *myMotor1 = AFMS_bottom.getMotor(1);
//Adafruit_DCMotor *myMotor2 = AFMS_top.getMotor(4);


const int totalMotors = 4;
Adafruit_DCMotor *myMotorsTop[totalMotors];
Adafruit_DCMotor *myMotorsBottom[totalMotors];


unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 6000;  //th 1000ms
int index_top = 0;
int index_bot = 0;


void setup() {

  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  startMillis = millis();  //initial start time

  // Initialize the motors
  for(int i = 0; i < totalMotors; i++) {
    myMotorsTop[i]    = AFMS_top.getMotor(i + 1);
    myMotorsBottom[i] = AFMS_bottom.getMotor(i + 1);
  }

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
  
  myMotorsTop[index_top]->setSpeed(200);
  
  
 // myMotor2->setSpeed(255);
}

void loop() {
  uint8_t i;

//randomize//
   currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    index_top = random(4);
    myMotorsTop[index_top]->setSpeed(200);
    Serial.println(index_top);
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
  //

  

  //Serial.print("tick");
  myMotorsTop[index_top]->run(FORWARD);      // turn it on going forward
  delay(100);

  //Serial.print("tock");
  myMotorsTop[index_top]->run(BACKWARD);     // the other way
  delay(100);
  
  //Serial.print("tack");
  for(int i = 0; i < totalMotors; i++) {
  myMotorsTop[i]->run(RELEASE);      // stopped
  }
  delay(100);

 // myMotor2->run(FORWARD);

  //myMotorsTop[index_top]->run(FORWARD);
 

  // for (i=0; i<255; i++) {
  
  //   myMotorsTop[index_top]->setSpeed(i);
  //   delay(5);
  // }

  // for (i=255; i!=0; i--) {
  
  //   myMotorsBottom[top_dc_index]->setSpeed(i);
  //   delay(10);
  // }

  //   Serial.println("tock");
  
  //   myMotorsBottom[top_dc_index]->run(BACKWARD);
  
  //   for (i=0; i<255; i++) {
  
  //     myMotorsBottom[top_dc_index]->setSpeed(i);
  //     delay(10);
    
  // }
  // for (i=255; i!=0; i--) {
  
  //   myMotorsBottom[top_dc_index]->setSpeed(i);
  //   delay(10);
  // }

  //Serial.println("release");
  
  //myMotorsBottom[top_dc_index]->run(RELEASE);
  
  //delay(1000);

  
}