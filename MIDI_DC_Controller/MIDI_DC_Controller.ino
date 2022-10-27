

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <midi_serialization.h>
#include <usbmidi.h>

#define MIDI_NOTE_OFF   0b10000000
#define MIDI_NOTE_ON    0b10010000
#define MIDI_CONTROL    0b10110000
#define MIDI_PITCH_BEND 0b11100000
//#define SNDOUT 10 //Audio output pin

u8 command=0, channel=0, key=0, pitchbend=0, pblo=0, pbhi=0, velocity=0, cc=0, value=0;

//Convert MIDI note to frequency
//double base_a4=440; //set A4=440Hz
//double note_to_freq(double n) {
//  if( n>=0 && n<=119 ) {
//    return base_a4*pow(2,(n-57)/12);
//  } else {
//    return -1;
//  }
//}
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


// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(200);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
}

void loop() {

  midiLoop();
  if (key == 65 && velocity == 127){
      myMotor->run(FORWARD);  
  }else if (key == 65 && velocity == 0) {
    myMotor->run(RELEASE);
  }
    


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


void midiLoop() {
  //Handle USB communication
  USBMIDI.poll();

  // While there's MIDI USB input available...
  while (USBMIDI.available()) {

    //Parse MIDI
//    u8 command=0, channel=0, key=0, pitchbend=0, pblo=0, pbhi=0, velocity=0, cc=0, value=0;

    //Skip to beginning of next message (silently dropping stray data bytes)
    while(!(USBMIDI.peek() & 0b10000000)) USBMIDI.read();

    command = USBMIDI.read();
    channel = (command & 0b00001111)+1;
    command = command & 0b11110000;
       

    switch(command) {
      case MIDI_NOTE_ON:
      case MIDI_NOTE_OFF:
        {
        if(USBMIDI.peek() & 0b10000000) continue; key      = USBMIDI.read();
        if(USBMIDI.peek() & 0b10000000) continue; velocity = USBMIDI.read();
        
        break;
        }
        case MIDI_PITCH_BEND:
        {
        if(USBMIDI.peek() & 0b10000000) continue; pblo = USBMIDI.read();
        if(USBMIDI.peek() & 0b10000000) continue; pbhi = USBMIDI.read();
        int pitchbend = (pblo << 7) | pbhi;
        //TODO: apply pitchbend to tone
     
        break;   
        }
        case MIDI_CONTROL:
        {
        if(USBMIDI.peek() & 0b10110000) continue; cc   = USBMIDI.read();
        if(USBMIDI.peek() & 0b10110000) continue; value   = USBMIDI.read();
        break;
        }
        
    }
       
    //Play tones
//    unsigned int pitch = note_to_freq(key);
//    if(command == MIDI_NOTE_ON && velocity > 0 && pitch > 0) tone(SNDOUT, pitch);
//    if(command == MIDI_NOTE_OFF || velocity == 0 || pitch == 0) noTone(SNDOUT);

    //Debug
    Serial.print(command);
    Serial.print(" Channel:");
    Serial.print(channel);
    Serial.print(" Key:");
    Serial.print(key);
    Serial.print("\tVel:");
    Serial.print(velocity);
   // Serial.print("\tPitch:");
   // Serial.print(pitch);
    Serial.print("\tPBend:");
    Serial.print(pitchbend, BIN);
    Serial.print(" (");
    Serial.print(pblo, BIN);
    Serial.print(" ");
    Serial.print(pbhi, BIN);
    Serial.print(")\tF:");
   // Serial.print(pitch);
    Serial.print(")\tCC:");
    Serial.print(cc);
    Serial.print(")\tValue:");
    Serial.print(value);
    Serial.print('\n');

//       //sendCC(0, 2, 56);
//    if(key==67 && velocity == 100){
//      Serial.println("ON");
//      sendCC(0, 2, 127);
//    } else if (key == 67 && velocity < 100) {
//      Serial.println("OFF");
//      sendCC(0, 2, 0);
//    }
  }      
  
 
    USBMIDI.flush();
  

}
