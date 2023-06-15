int solenoidPin = 7;                    //This is the output pin on the Arduino

void setup() 
{
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);          //Sets that pin as an output
}

void loop() 
{
  digitalWrite(solenoidPin, HIGH); 
  Serial.print("On");     //Switch Solenoid ON
  delay(1000);                          //Wait 1 Second
  digitalWrite(solenoidPin, LOW); 
  Serial.print("Off");      //Switch Solenoid OFF
  delay(1000);                          //Wait 1 Second
}

