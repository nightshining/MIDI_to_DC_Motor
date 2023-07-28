#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <midi_serialization.h>
#include <usbmidi.h>

#define MIDI_NOTE_OFF   0b10000000
#define MIDI_NOTE_ON    0b10010000


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_MotorShield AFMS_bottom(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMS_top(0x60); // Default address, no jumpers
Adafruit_DCMotor *myMotor1 = AFMS_bottom.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS_top.getMotor(4);



void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  if (!AFMS_top.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->setSpeed(100);
  myMotor1->run(FORWARD);
  // turn on motor
  myMotor1->run(RELEASE);
}

void loop() {

  //Handle USB communication
	USBMIDI.poll();

	while (USBMIDI.available()) {
		
		u8 command=0, channel=0, key=0, pitchbend=0, pblo=0, pbhi=0, velocity=0;

     //Skip to beginning of next message (silently dropping stray data bytes)
    while(!(USBMIDI.peek() & 0b10000000)) USBMIDI.read();

    command = USBMIDI.read();
    channel = (command & 0b00001111)+1;
    command = command & 0b11110000;

    switch(command) {
      case MIDI_NOTE_ON:
      case MIDI_NOTE_OFF:
        if(USBMIDI.peek() & 0b10000000) continue; key      = USBMIDI.read();
        if(USBMIDI.peek() & 0b10000000) continue; velocity = USBMIDI.read();
        break;
    }


    // MIDI LOGIC //
    if(command == MIDI_NOTE_ON && velocity > 0 && key == 65) {
      digitalWrite(LED_BUILTIN, HIGH);
     // myMotor1->run(FORWARD);
      Serial.println("ON");
    }

    if(command == MIDI_NOTE_OFF || velocity == 0 || key == 0)  {
      digitalWrite(LED_BUILTIN, LOW);
    //  myMotor1->run(RELEASE);
      Serial.println("OFF");
    }
  
	}

	// Flush the output.
//	USBMIDI.flush();

// Additional: //
//
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

  

}








