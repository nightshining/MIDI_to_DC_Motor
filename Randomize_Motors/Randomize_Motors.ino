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
int index_pair = 0;
int delay_time = 1000;



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
  myMotorsTop[index_pair]->setSpeed(200);
  myMotorsBottom[index_pair]->setSpeed(200);
  
}

void loop() {
  uint8_t i;

  //randomize//
   currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    index_pair = random(4);
    delay_time = random(500,1000);
    //index_pair = 0;
    // myMotorsTop[index_pair]->setSpeed(200);
    // myMotorsBottom[index_pair]->setSpeed(200);
    // Serial.println(index_pair);
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
  //


  delay(delay_time);

  Serial.println("Top");
  myMotorsTop[index_pair]->setSpeed(200);    
  myMotorsTop[index_pair]->run(FORWARD);      // turn it on going forward
  delay(delay_time);

  Serial.println("STOP");
  myMotorsTop[index_pair]->setSpeed(0);
  myMotorsBottom[index_pair]->setSpeed(0);
  myMotorsTop[index_pair]->run(RELEASE); 
  myMotorsBottom[index_pair]->run(RELEASE); 
  delay(delay_time);

  Serial.println("Bottom");
  myMotorsBottom[index_pair]->setSpeed(200);
  myMotorsBottom[index_pair]->run(FORWARD);      // turn it on going forward
  delay(delay_time);

  Serial.println("STOP");
  myMotorsTop[index_pair]->setSpeed(0);
  myMotorsBottom[index_pair]->setSpeed(0);
  myMotorsTop[index_pair]->run(RELEASE); 
  myMotorsBottom[index_pair]->run(RELEASE); 
  delay(delay_time);

/*
  Serial.println("Release");
  for(int i = 0; i < totalMotors; i++) {
  myMotorsTop[i]->run(RELEASE);      // stopped
  myMotorsBottom[i]->run(RELEASE);      // stopped
  }
  delay(2000);*/
  //Serial.print("tock");
  // myMotorsTop[index_top]->run(BACKWARD);     // the other way
  // delay(100);
  
 

}