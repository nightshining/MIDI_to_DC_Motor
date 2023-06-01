

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <midi_serialization.h>
#include <usbmidi.h>


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 
Adafruit_MotorShield AFMS_bottom(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMS_top(0x60); // Default address, no jumpers
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor1 = AFMS_bottom.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS_top.getMotor(4);

// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
void sendCC(uint8_t channel, uint8_t control, uint8_t value) {
	USBMIDI.write(0xB0 | (channel & 0xf));
	USBMIDI.write(control & 0x7f);
	USBMIDI.write(value & 0x7f);
}

void sendNote(uint8_t channel, uint8_t note, uint8_t velocity) {
	USBMIDI.write((velocity != 0 ? 0x90 : 0x80) | (channel & 0xf));
	USBMIDI.write(note & 0x7f);
	USBMIDI.write(velocity &0x7f);
}

const int ANALOG_PIN_COUNT = 4;
const int BUTTON_PIN_COUNT = 2;

// Change the order of the pins to change the ctrl or note order.
int analogPins[ANALOG_PIN_COUNT] = { A3, A2, A1, A0 };
int buttonPins[BUTTON_PIN_COUNT] = { 9, 8 };

int ccValues[ANALOG_PIN_COUNT];
int buttonDown[BUTTON_PIN_COUNT];

int readCC(int pin) {
	// Convert from 10bit value to 7bit.
	return analogRead(pin) >> 3;
}

int isButtonDown(int pin) {
	return digitalRead(pin) == 0;
}



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS_top.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");


  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->setSpeed(200);
  myMotor1->run(FORWARD);
  // turn on motor
  myMotor1->run(RELEASE);
}

void loop() {

  //Handle USB communication
	USBMIDI.poll();

	while (USBMIDI.available()) {
		// We must read entire available data, so in case we receive incoming
		// MIDI data, the host wouldn't get stuck.
		u8 b = USBMIDI.read();

  

  //     //sendCC(0, 2, 56);
  //  if(key==67 && velocity == 100){
  //    Serial.println("ON");
  //    sendCC(0, 2, 127);
  //  } else if (key == 67 && velocity < 100) {
  //    Serial.println("OFF");
  //    sendCC(0, 2, 0);
  //  }
  
	}

	for (int i=0; i<ANALOG_PIN_COUNT; ++i) {
		int value = readCC(analogPins[i]);

		// Send CC only if th has changed.
		if (ccValues[i] != value) {
			sendCC(0, i, value);
			ccValues[i] = value;
		}
	}

	for (int i=0; i<BUTTON_PIN_COUNT; ++i) {
		int down = isButtonDown(buttonPins[i]);

		if (down != buttonDown[i]) {
			sendNote(0, 64 + i, down ? 127 : 0);
			buttonDown[i] = down;
		}
	}

	// Flush the output.
	USBMIDI.flush();

  //midiLoop();
  // if (key == 65 && velocity == 127){
  //    myMotor1->run(FORWARD);  
  // }else if (key == 65 && velocity == 0) {
  //    myMotor1->run(RELEASE);
  // }
    
//  myMotor->run(FORWARD);
//  for (i=0; i<100; i++) {
//    myMotor->setSpeed(i);  
//    delay(10);
//  }
//  for (i=100; i!=0; i--) {
//    myMotor->setSpeed(i);  
//    delay(10);
//  }
//  
//  Serial.print("tock");
//
//  myMotor->run(BACKWARD);
//  for (i=0; i<100; i++) {
//    myMotor->setSpeed(i);  
//    delay(10);
//  }
//  for (i=100; i!=0; i--) {
//    myMotor->setSpeed(i);  
//    delay(10);
//  }
//
//  Serial.print("tech");
//  myMotor->run(RELEASE);
//  delay(1000);
  

}








