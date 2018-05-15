#define enablePin 6
#define receiverPin 2

volatile unsigned long normalTime = 0;
unsigned long blockTime = 0;
unsigned long lapTime = 0;
unsigned long totalTime = 0;
unsigned int laps = 0;
unsigned int mins = 0;
float secs = 0;

void setup() {
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  pinMode(receiverPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(receiverPin), normal, FALLING);
  Serial.begin(9600);
}

void loop() {
  if( (millis() - normalTime > 100) && (millis() - blockTime > 3000) ) {
    lapTime = millis() - blockTime;
    if( laps > 0 ) {
      totalTime += lapTime;
      mins = lapTime / 60000;
      secs = (lapTime % 60000) / 1000.00;
      Serial.print("Lap #");
      Serial.print(laps);
      Serial.print(" ");
      if( mins < 10 ) Serial.print("0");
      Serial.print(mins);
      Serial.print(":");
      if( secs < 10 ) Serial.print("0");
      Serial.println(secs);
    }
    else {
      Serial.println("Start!");
    }
    blockTime = millis();
    laps++;
  }
  
}

void normal() {
  normalTime = millis();
}

