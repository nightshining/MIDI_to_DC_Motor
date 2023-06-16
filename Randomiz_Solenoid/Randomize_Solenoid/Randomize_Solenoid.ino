int solenoidPins[4];
int delayTime = 1000;
int activePin = 0;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 6000;  //th 1000ms

void setup() 
{
  Serial.begin(9600);
  startMillis = millis();  //initial start time

  // set pins
  solenoidPins[0] = 8;
  solenoidPins[1] = 9;
  solenoidPins[2] = 10;
  solenoidPins[3] = 11;

  size_t size = sizeof(solenoidPins);
  
  for (int i = 0; i < size; i++) {
    pinMode(solenoidPins[i], OUTPUT);
  }
}

void loop() 
{
  randomize();

  digitalWrite(solenoidPins[activePin], HIGH); 
  Serial.print("On");     //Switch Solenoid ON
  delay(delayTime);                          //Wait 1 Second
  digitalWrite(solenoidPins[activePin], LOW); 
  Serial.print("Off");      //Switch Solenoid OFF
  delay(delayTime);                          //Wait 1 Second
}

void randomize() {

   currentMillis = millis();  
  if (currentMillis - startMillis >= period)  
  {
    activePin = random(4);
    delayTime = random(100,1000);
    startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  }
  
}

